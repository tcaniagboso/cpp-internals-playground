#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace cpp_playground::containers {

    template<typename T>
    class SimpleVector {
    public:
        //=================
        // Constructors
        //=================
        SimpleVector() = default;

        SimpleVector(std::size_t n, T value)
                : size_{n},
                  capacity_{n},
                  data_{(n == 0)? nullptr : AllocTraits::allocate(alloc_, n)} {
            if (n > 0) {
                std::size_t i{0};
                try {
                    construct(alloc_, data_, capacity_, value, i);
                } catch (...) {
                    destroy(alloc_, data_, i);
                    deallocate(alloc_, data_, capacity_);
                    size_ = 0;
                    throw;
                }
            }

        }

        explicit SimpleVector(std::size_t n)
                : SimpleVector(n, T{}) {}

        //=================
        // Copy Semantics
        //=================
        SimpleVector(const SimpleVector<T> &other)
                : alloc_{other.alloc_},
                  size_{other.size_},
                  capacity_{other.capacity_},
                  data_{(other.capacity_ == 0)? nullptr : AllocTraits::allocate(alloc_, other.capacity_)} {

            if (other.capacity_ > 0) {
                std::size_t i{0};

                try {
                    for (; i < size_; i++) {
                        AllocTraits::construct(alloc_, data_ + i, other[i]);
                    }
                } catch (...) {
                    destroy(alloc_, data_, i);
                    deallocate(alloc_, data_, capacity_); // Sets capacity to 0
                    size_ = 0;
                    throw;
                }
            }
        }

        SimpleVector<T> &operator=(const SimpleVector<T> &other) {

            if (this == &other) {
                return *this;
            }

            T* new_data = nullptr;
            if (other.capacity_ > 0) {
                new_data = AllocTraits::allocate(alloc_, other.capacity_);

                std::size_t i{0};
                std::size_t capacity = other.capacity_;
                try {
                    for (; i < other.size_; i++) {
                        AllocTraits::construct(alloc_, new_data + i, other[i]);
                    }
                } catch (...) {
                    destroy(alloc_, new_data, i);
                    deallocate(alloc_, new_data, capacity);
                    throw;
                }
            }

            destroy(alloc_, data_, size_); // can use clear() too
            deallocate(alloc_, data_, capacity_);

            data_ = new_data;
            size_ = other.size_;
            capacity_ = other.capacity_;

            return *this;
        }

        //=================
        // Move Semantics
        //=================
        SimpleVector(SimpleVector<T> &&other) noexcept
                : alloc_{other.alloc_},
                  size_{other.size_},
                  capacity_{other.capacity_},
                  data_{other.data_} {
            other.data_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }

        SimpleVector<T> &operator=(SimpleVector<T> &&other) noexcept {
            if (this == &other) {
                return *this;
            }

            clear();
            deallocate(alloc_, data_, capacity_);

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;

            return *this;
        }

        //=================
        // Destructor
        //=================
        ~SimpleVector() {
            if (data_) {
                clear();
                deallocate(alloc_, data_, capacity_);
            }
        }

        //==================
        // Properties
        //==================
        [[nodiscard]] std::size_t size() const { return size_; }

        [[nodiscard]] std::size_t capacity() const { return capacity_; }

        [[nodiscard]] bool empty() const { return size_ == 0; }

        // Allocates memory for the vector
        // Does nothing if new capacity is less than or equal to old capacity
        // Reconstructs all existing objects and leaves the remaining slots as raw memory
        void reserve(std::size_t n) {
            if (n <= capacity_) return;

            std::size_t new_capacity = n;
            T* new_data = AllocTraits::allocate(alloc_, new_capacity);

            std::size_t i{0};

            try {
                for (; i < size_; i++) {
                    AllocTraits::construct(alloc_, new_data + i, data_[i]);
                }
            } catch (...) {
                destroy(alloc_, new_data, i);
                deallocate(alloc_, new_data, new_capacity);
                throw;
            }

            destroy(alloc_, data_, size_);
            deallocate(alloc_, data_, capacity_);

            data_ = new_data;
            capacity_ = new_capacity;
        }

        // Changes the vector's size. Constructs new elements when growing and destroys elements when shrinking.
        void resize(std::size_t n) {
            if (n >= size_) {
                reserve(n);
                std::size_t i = size_;
                try {
                    construct(alloc_, data_, n, T{}, i);
                } catch (...) {
                    destroy(alloc_, data_ + size_, i - size_);
                    throw;
                }

            } else {
                destroy(alloc_, data_ + n, size_ - n);
            }

            size_ = n;
        }

        //==================
        // Access
        //==================
        T &operator[](std::size_t index) {
            validate_index(index);
            return data_[index]; // *(data_ + index)
        }

        const T &operator[](std::size_t index) const {
            validate_index(index);
            return data_[index]; // *(data_ + index)
        }

        T &at(std::size_t index) {
            validate_index(index);
            return data_[index]; // *(data_ + index)
        }

        const T &at(std::size_t index) const {
            validate_index(index);
            return data_[index]; // *(data_ + index)
        }

        T &front() {
            validate_state();
            return data_[0]; // *(data + 0)
        }

        const T &front() const {
            validate_state();
            return data_[0]; // *(data + 0)
        }

        T &back() {
            validate_state();
            return data_[size_ - 1]; // *(data_ + (size_ - 1))
        }

        const T &back() const {
            validate_state();
            return data_[size_ - 1]; // *(data_ + (size_ - 1))
        }

        T *data() {
            return data_;
        }

        const T *data() const {
            return data_;
        }

        //==================
        // Insertion
        //==================
        void push_back(T value) {
            if (size_ == capacity_) {
                (capacity_ == 0) ? reserve(1) : reserve(capacity_ * 2);
            }

            AllocTraits::construct(alloc_, data_ + size_, std::move(value));
            ++size_;
        }

        // Inserts 'value' at the given index; Calls shift_right to move objects.
        void insert(T value, std::size_t index) {
            if (index > size_) {
                throw std::out_of_range(std::to_string(index) + " is out of range");
            } else if (index == size_) {
                push_back(std::move(value));
            } else {
                if (size_ == capacity_) {
                    (capacity_ == 0) ? reserve(1) : reserve(capacity_ * 2);
                }
                shift_right(alloc_, data_, index, size_);
                data_[index] = std::move(value);
                ++size_;
            }

        }

        //==================
        // Removal
        //==================
        void pop_back() {
            validate_state();
            --size_;
            AllocTraits::destroy(alloc_, data_ + size_);
        }

        // Destroys all constructed objects and sets size_ to 0.
        void clear() {
            destroy(alloc_, data_, size_);
            size_ = 0;
        }

        // Erases the object at the given index; Calls shift_left to move objects.
        void erase(std::size_t index) {
            validate_index(index);

            if (index == size_ - 1) {
                pop_back();
            } else {
                // AllocTraits::destroy(alloc_, data_ + index);
                shift_left(alloc_, data_, index + 1, size_);
                --size_;
            }
        }

    private:
        using Allocator = std::allocator<T>;
        using AllocTraits = std::allocator_traits<Allocator>;

        Allocator alloc_{};
        std::size_t size_{0};
        std::size_t capacity_{0};
        T *data_{nullptr};

        // Constructs val objects starting from i to capacity
        static void construct(Allocator &alloc, T *data, std::size_t size, const T& val, std::size_t &offset) {
            for (; offset < size; offset++) {
                AllocTraits::construct(alloc, data + offset, val);
            }
        }

        // Destroys all the constructed objects
        static void destroy(Allocator &alloc, T *data, std::size_t count) {
            for (std::size_t i = 0; i < count; i++) {
                AllocTraits::destroy(alloc, data + i);
            }
        }

        // Deallocates raw memory and sets capacity to 0
        static void deallocate(Allocator &alloc, T*& data, std::size_t &capacity) {
            if (data) {
                AllocTraits::deallocate(alloc, data, capacity);
                data = nullptr;
                capacity = 0;
            }
        }

        // Validates empty state
        void validate_state() const {
            if (size_ == 0) {
                throw std::runtime_error("Vector is empty");
            }
        }

        // Validates index for out of bounds
        void validate_index(std::size_t index) const {
            if (index >= size_) {
                throw std::out_of_range(std::to_string(index) + " is out of range");
            }
        }

        // Shifts elements starting from 'pos' one spot leftwards
        static void shift_left(Allocator &alloc, T *data, std::size_t pos, std::size_t size) {
            for (std::size_t i = pos; i < size; i++) {
                data[i - 1] = std::move(data[i]);
            }

            AllocTraits::destroy(alloc, data + size - 1);
        }

        // Shifts elements starting from pos one spot rightwards
        static void shift_right(Allocator &alloc, T *data, std::size_t pos, std::size_t size) {
            AllocTraits::construct(alloc, data + size, std::move(data[size - 1]));
            auto signed_pos = static_cast<int64_t>(pos);
            for (int64_t i = static_cast<int64_t>(size) - 2; i >= signed_pos; i--) {
                auto idx = static_cast<size_t>(i);
                data[idx + 1] = std::move(data[idx]);
            }
        }
    };
} // namespace cpp_playground::containers
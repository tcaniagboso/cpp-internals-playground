#pragma once

#include <cstddef>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>

namespace cpp_playground::object_model {
    template<typename T>
    class HeapBuffer {
    public:
        explicit HeapBuffer() = default;
        explicit HeapBuffer(std::size_t n)
                : data_{static_cast<T *>(::operator new(sizeof(T) * n))},
                  size_{n} {
            std::size_t i = 0; // constructed count
            try {
                for (; i < n; i++) {
                    std::construct_at(data_ + i, T{});
                }
            } catch (...) {
                destroy_and_deallocate(data_, i);
                size_ = 0;
                data_ = nullptr;
                throw;
            }
        };

        // Copy Constructor
        HeapBuffer(const HeapBuffer<T> &other)
                : data_{static_cast<T *>(::operator new(sizeof(T) * other.size_))},
                  size_{other.size_} {

            std::size_t i = 0; // constructed count
            try {
                for (; i < other.size_; i++) {
                    std::construct_at(data_ + i, other[i]);
                }
            } catch (...) {
                destroy_and_deallocate(data_, i);
                size_ = 0;
                data_ = nullptr;
                throw;
            }
        }

        HeapBuffer<T> &operator=(const HeapBuffer<T> &other) {
            if (this == &other) {
                return *this;
            }

            T *new_data = static_cast<T *>(::operator new(sizeof(T) * other.size_));
            std::size_t i = 0; // constructed count
            try {
                for (; i < other.size_; i++) {
                    std::construct_at(new_data + i, other[i]);
                }
            }
            catch (...) {
                destroy_and_deallocate(new_data, i);
                throw;
            }

            clear();
            size_ = other.size_;
            data_ = new_data;

            return *this;
        }

        // Move constructor
        HeapBuffer(HeapBuffer<T> &&other) noexcept
                : data_{other.data_},
                  size_{other.size_} {
            other.data_ = nullptr;
            other.size_ = 0;
        }

        HeapBuffer<T> &operator=(HeapBuffer<T> &&other) noexcept {
            if (this == &other) {
                return *this;
            }

            clear();

            data_ = other.data_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.size_ = 0;

            return *this;
        }

        // Destructor
        ~HeapBuffer() {
            clear();
        }

        [[nodiscard]] std::size_t size() const { return size_; }

        T &operator[](std::size_t index) {
            validate_index(index);
            return data_[index]; // *(data_ + index)
        }

        const T &operator[](std::size_t index) const {
            validate_index(index);
            return data_[index]; //*(data_ + index)
        }

    private:
        T *data_;
        std::size_t size_{0};

        void validate_index(std::size_t index) const {
            if (index >= size_) {
                throw std::out_of_range(std::to_string(index) + " is out of range");
            }
        }

        static void destroy_and_deallocate(T *data, std::size_t count) noexcept {
            for (std::size_t i = 0; i < count; ++i) {
                std::destroy_at(data + i);
            }

            ::operator delete(data);
        }

        void clear() noexcept {
            destroy_and_deallocate(data_, size_);
            data_ = nullptr;
            size_ = 0;
        }
    };
} // namespace cpp_playground::object_model
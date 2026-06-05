#include "cpp_playground/containers/vector/simple_vector.hpp"

#include <cassert>
#include <iostream>
#include <utility>

namespace examples::containers::simple_vector {
    using SimpleVector = cpp_playground::containers::SimpleVector<int>;

    static void compare_with_value(const SimpleVector &vector, int value, std::size_t offset) {
        const std::size_t n = vector.size();

        for (std::size_t i = offset; i < n; i++) {
            if (vector[i] != value) {
                std::cout << "MISMATCH at index " << i << "\n";
                std::cout << vector[i] << " != " << value << "\n";
                assert(vector[i] == value);
            }

            assert(vector[i] == value);
        }
    }

    static void compare_data(const int* a, const int* b, const std::size_t n) {
        for (std::size_t i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                std::cout << "MISMATCH at index " << i << "\n";
                std::cout << a[i] << " != " << b[i] << "\n";
                assert(a[i] == b[i]);
            }

            assert(a[i] == b[i]);
        }
    }

    void compare_vectors(const SimpleVector &a, const SimpleVector &b) {
        if (a.capacity() != b.capacity()) {
            std::cout << "Capacity MISMATCH!\n";
            std::cout << a.capacity() << " != " << b.capacity() << "\n";
            assert(a.capacity() == b.capacity());
        }

        assert(a.capacity() == b.capacity());

        if (a.size() != b.size()) {
            std::cout << "Size MISMATCH!\n";
            std::cout << a.size() << " != " << b.size() << "\n";
            assert(a.size() == b.size());
        }

        assert(a.size() == b.size());

        std::size_t n = a.size();

        compare_data(a.data(), b.data(), n);
    }

    static void default_constructor_demo() {
        std::cout << "\n======== SimpleVector() = default =========\n";

        SimpleVector v{};

        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.data() == nullptr);

        std::cout << "All Fields MATCH! \n";
    }

    void constructor_with_size_and_value_demo() {
        std::cout << "\n======== SimpleVector(std:;size_t n, T value) =========\n";

        std::cout << "1. Initializing with 'capacity == 0' Demo:\n";

        std::size_t n = 0;
        int value = 10;
        SimpleVector v1{n, value};

        assert(v1.size() == n);
        assert(v1.capacity() == n);
        assert(v1.data() == nullptr);

        std::cout << "PASSED!\n";

        std::cout << "2. Initializing with 'capacity > 0' Demo:\n";

        n = 10;
        SimpleVector v2{n, value};

        assert(v2.size() == n);
        assert(v2.capacity() == n);
        assert(v2.data() != nullptr);

        compare_with_value(v2, value, 0);

        std::cout << "PASSED!\n";
    }

    void constructor_with_size_demo() {
        std::cout << "\n======== SimpleVector(std::size_t n) =========\n";

        std::cout << "1. Initializing with 'capacity == 0' Demo:\n";

        std::size_t n = 0;
        SimpleVector v1{n};

        assert(v1.size() == n);
        assert(v1.capacity() == n);
        assert(v1.data() == nullptr);

        std::cout << "PASSED! \n";

        std::cout << "2. Initializing with 'capacity > 0' Demo:\n";

        n = 10;
        SimpleVector v2{n};

        assert(v2.size() == n);
        assert(v2.capacity() == n);
        assert(v2.data() != nullptr);

        compare_with_value(v2, int{}, 0);

        std::cout << "PASSED!\n";
    }

    void copy_constructor_demo() {
        std::cout << "\n======== Copy Construction =========\n";

        std::cout << "1. SimpleVector() = default Demo:\n";

        SimpleVector a{};
        SimpleVector b = a;

        compare_vectors(a, b);
        std::cout << "PASSED!\n";

        std::cout << "2. SimpleVector(std::size_t n, T value) Demo:\n";

        std::size_t n = 10;
        int value = 10;

        SimpleVector c{n, value};
        SimpleVector d = c;

        compare_vectors(c, d);
        std::cout << "PASSED!\n";
    }

    void copy_assignment_demo() {
        std::cout << "\n======== Copy Assignment =========\n";

        // If they are both non-empty there is no chance of failure, so not tested.

        std::cout << "1. Empty vector copied to Non-Empty vector Demo:\n";

        std::size_t n = 10;
        int value = 10;

        SimpleVector a{};
        SimpleVector b{n, value};

        b = a;

        compare_vectors(a, b);
        std::cout << "PASSED!\n";

        std::cout << "2. Non-Empty vector copied to Empty vector Demo:\n";

        SimpleVector c{n, value};
        SimpleVector d{};

        d = c;

        assert(c.data() != d.data());
        compare_vectors(c, d);
        std::cout << "PASSED!\n";

        std::cout << "3. Non-Empty vector copied to Non-Empty vector Demo:\n";

        SimpleVector e{n, value};
        SimpleVector f{n + 5, value + 10};

        f = e;

        assert(e.data() != f.data());
        compare_vectors(e, f);
        std::cout << "PASSED!\n";
    }

    void move_constructor_demo() {
        std::cout << "\n======== Move Construction =========\n";

        std::cout << "1. SimpleVector() = default Demo:\n";

        SimpleVector a{};
        SimpleVector b = a;
        SimpleVector c = std::move(a);

        assert(a.data() == nullptr);
        assert(a.capacity() == 0);
        assert(a.empty());

        compare_vectors(b, c);
        std::cout << "PASSED!\n";

        std::cout << "2. SimpleVector(std::size_t n, T value) Demo: \n";

        std::size_t n = 10;
        int value = 10;

        SimpleVector d{n, value};
        auto* old_data = d.data();

        SimpleVector e = d;
        SimpleVector f = std::move(d);

        assert(f.data() == old_data);
        assert(d.data() == nullptr);
        assert(d.capacity() == 0);
        assert(d.empty());

        compare_vectors(e, f);
        std::cout << "PASSED!\n";
    }

    void move_assignment_demo() {
        std::cout << "\n======== Move Assignment =========\n";

        // If they are both non-empty there is no chance of failure, so not tested.

        std::cout << "1. Empty vector moved to Non-Empty vector:\n";

        std::size_t n = 10;
        int value = 10;

        SimpleVector a{};
        SimpleVector b{n, value};
        SimpleVector c = a;
        b = std::move(a);

        assert(b.data() == c.data());
        assert(a.data() == nullptr);
        assert(a.capacity() == 0);
        assert(a.empty());

        compare_vectors(b, c);
        std::cout << "PASSED!\n";

        std::cout << "2. Non-Empty vector moved to Empty vector Demo:\n";

        SimpleVector d{n, value};
        auto* old_data = d.data();

        SimpleVector e{};
        SimpleVector f = d;
        e = std::move(d);

        assert(e.data() == old_data);
        assert(d.data() == nullptr);
        assert(d.capacity() == 0);
        assert(d.empty());

        compare_vectors(e, f);
        std::cout << "PASSED!\n";

        std::cout << "3. Non-Empty vector moved to Non-Empty vector Demo:\n";

        SimpleVector g{n, value};
        old_data = g.data();

        SimpleVector h{n + 5, value + 10};
        SimpleVector i = g;
        h = std::move(g);

        assert(h.data() == old_data);
        assert(g.data() == nullptr);
        assert(g.capacity() == 0);
        assert(g.empty());
        compare_vectors(h, i);
        std::cout << "PASSED!\n";
    }

    void reserve_demo() {
        std::cout << "\n======== reserve(std::size_t n) =========\n";

        std::size_t n = 10;
        SimpleVector a(10);
        SimpleVector b = a;

        std::cout << "1. Reserving with n == capacity\n";
        assert(a.size() == n);
        assert(a.capacity() == n);
        a.reserve(n);
        compare_vectors(a, b);
        std::cout << "PASSED!\n";

        std::cout << "2. Reserving with n < capacity\n";
        std::size_t less_n = n >> 1;
        assert(less_n < a.capacity());
        a.reserve(less_n);
        compare_vectors(a, b);
        std::cout << "PASSED!\n";

        std::cout << "3. Reserving with n > capacity\n";
        std::size_t greater_n = n << 1;
        assert(greater_n > a.capacity());
        a.reserve(greater_n);
        assert(a.size() == n);
        assert(a.capacity() == greater_n);
        compare_data(a.data(), b.data(), n);
        std::cout << "PASSED!\n";
    }

    void resize_demo() {
        std::cout << "\n======== resize(std::size_t n) =========\n";

        std::size_t n = 10;

        SimpleVector a{10, 2};
        SimpleVector b = a;

        std::cout << "1. Resizing with n == size && n == capacity\n";
        assert(n == a.size());
        assert(n == a.capacity());
        a.resize(n);
        compare_vectors(a, b);
        std::cout << "PASSED!\n";

        std::cout << "2. Resizing with n > size && n > capacity\n";
        std::size_t greater_n = n << 1;
        assert(greater_n > a.size());
        assert(greater_n > a.capacity());
        a.resize(greater_n);
        assert(a.size() == greater_n);
        assert(a.capacity() == greater_n);
        compare_data(a.data(), b.data(), n);
        compare_with_value(a, int{}, n);
        std::cout << "PASSED!\n";

        std::cout << "3. Resizing with n < size && n < capacity\n";
        std::size_t less_n = n >> 1;
        assert(less_n < a.size());
        assert(less_n < a.capacity());
        a.resize(less_n);
        assert(a.size() == less_n);
        assert(a.capacity() == greater_n);
        compare_data(a.data(), b.data(), less_n);
        std::cout << "PASSED!\n";

        std::cout << "4. Resizing with n > size && n < capacity\n";
        assert(n < a.capacity());
        assert(n > a.size());
        a.resize(n);
        assert(a.size() == n);
        assert(a.capacity() == greater_n);
        compare_data(a.data(), b.data(), less_n);
        compare_with_value(a, int{}, less_n);
        std::cout << "PASSED!\n";
    }

    void access_read_demo() {
        std::cout << "\n======== Access: Read =========\n";

        std::size_t n = 3;
        int value = 10;

        SimpleVector v(n, value);

        assert(v[0] == value);
        assert(v.at(1) == value);
        assert(v.front() == value);
        assert(v.back() == value);
        assert(v.data() != nullptr);
        assert(v.data()[2] == value);

        std::cout << "PASSED!\n";
    }

    void access_mutation_demo() {
        std::cout << "\n======== Access: Mutation =========\n";

        std::size_t n = 3;
        int value = 10;

        SimpleVector v(n, value);

        v[0]++;
        assert(v[0] == value + 1);

        v.at(1)++;
        assert(v.at(1) == value + 1);

        v.front()++;
        assert(v.front() == value + 2);

        v.back()++;
        assert(v.back() == value + 1);

        v.data()[2]++;
        assert(v.data()[2] == value + 2);

        std::cout << "PASSED!\n";
    }

    void access_exception_demo() {
        std::cout << "\n======== Access: Exceptions =========\n";

        std::size_t n = 3;
        int value = 10;

        SimpleVector v(n, value);

        std::cout << "1. operator []\n";
        try {
            (void)v[3];
            assert(false && "Expected operator[] to throw");
        } catch (const std::out_of_range& e) {
            std::cout << "operator[] threw out_of_range as expected: " << e.what() << "\n";
        }
        std::cout << "PASSED!\n";

        std::cout << "2. at()\n";
        try {
            (void)v.at(3);
            assert(false && "Expected at() to throw");
        } catch (const std::out_of_range& e) {
            std::cout << "at() threw out_of_range as expected: " << e.what() << "\n";
        }
        std::cout << "PASSED!\n";

        std::cout << "3. front()\n";
        SimpleVector empty{};
        try {
            (void)empty.front();
            assert(false && "Expected front() to throw");
        } catch (const std::runtime_error& e) {
            std::cout << "front() threw runtime_error as expected: " << e.what() << "\n";
        }
        std::cout << "PASSED!\n";

        std::cout << "4. back()\n";
        try {
            (void)empty.back();
            assert(false && "Expected back() to throw");
        } catch (const std::runtime_error& e) {
            std::cout << "back() threw runtime_error as expected: " << e.what() << "\n";
        }

        std::cout << "PASSED!\n";
    }

    void const_access_demo() {
        std::cout << "\n======== Access: Const =========\n";

        std::size_t n = 3;
        int value = 10;

        SimpleVector v(n, value);
        const SimpleVector& cv = v;

        assert(cv[0] == value);
        assert(cv.at(1) == value);
        assert(cv.front() == value);
        assert(cv.back() == value);
        assert(cv.data() != nullptr);
        assert(cv.data()[2] == value);

        // These should not compile:
        // ca[0] = 99;
        // ca.at(0) = 99;
        // ca.front()++;
        // ca.back()++;
        // ca.data()[0] = 99;

        std::cout << "PASSED!\n";
    }

    void push_back_demo() {
        std::cout << "\n======== push_back(T value) =========\n";
        std::size_t n = 2;
        int value = 10;

        SimpleVector v(n, value);
        SimpleVector a = v;

        assert(v.capacity() == n);
        assert(v.size() == n);
        assert(v.back() == value);

        std::cout << "1. Push Back with Resizing\n";
        int new_value = 15;
        v.push_back(new_value);

        std::size_t new_capacity = n << 1;

        assert(v.size() == n + 1);
        assert(v.capacity() == new_capacity);
        assert(v.back() == new_value);
        std::cout << "PASSED!\n";

        std::cout << "2. Push Back without Resizing\n";
        v.push_back(new_value);
        assert(v.size() == n + 2);
        assert(v.capacity() == new_capacity);
        assert(v.back() == new_value);

        compare_data(v.data(), a.data(), a.size());

        std::cout << "PASSED!\n";
    }

    void insert_demo() {
        std::cout << "\n======== insert(T value, std::size_t index) =========\n";
        std::size_t n = 10;
        int value = 10;

        SimpleVector v(n, value);
        SimpleVector a = v;

        std::cout << "1. Inserting at the front\n";

        int front_val = 9;
        v.insert(front_val, 0);

        assert(v.size() == n + 1);
        assert(v.front() == front_val);

        compare_data(v.data() + 1, a.data(), n);

        std::cout << "PASSED!\n";

        std::cout << "2. Inserting at the middle\n";
        int middle_val = 11;
        std::size_t mid_idx = n / 2;
        v.insert(middle_val, mid_idx);

        assert(v.size() == n + 2);
        assert(v[mid_idx] == middle_val);
        compare_data(v.data() + 1, a.data(), mid_idx - 1);
        compare_data(v.data() + mid_idx + 1, a.data() + mid_idx, n - mid_idx);

        std::cout << "PASSED!\n";

        std::cout << "3. Inserting at the end\n";
        int end_val = 15;
        v.insert(end_val, v.size());

        assert(v.size() == n + 3);
        assert(v.back() == end_val);

        std::cout << "PASSED!\n";

        std::cout << "4. Invalid Index\n";

        try {
            v.insert(10, v.size() + 1);
            assert(false && "Expected insert() to throw");
        } catch (const std::out_of_range& e) {
            std::cout << "insert() threw out_of_range as expected: " << e.what() << "\n";
        }

        std::cout << "PASSED!\n";
    }

    void pop_back_demo() {
        std::cout << "\n======== pop_back() =========\n";

        std::cout << "1. Non-Empty Vector\n";
        std::size_t n = 2;
        SimpleVector v(n);

        v[0] = 1;
        v[1] = 2;

        v.pop_back();

        assert(v.size() == n - 1);
        assert(v.capacity() == n);
        assert(v.back() == 1);

        v.pop_back();
        assert(v.empty());
        assert(v.capacity() == n);

        std::cout << "PASSED!\n";

        std::cout << "2. Empty Vector\n";

        try {
            v.pop_back();
            assert(false && "Expected pop_back() to throw");
        } catch (const std::runtime_error& e) {
            std::cout << "pop_back() threw runtime_error as expected: " << e.what() << "\n";
        }
        std::cout << "PASSED!\n";
    }

    void clear_demo() {
        std::cout << "\n======== clear() =========\n";
        std::size_t n = 10;
        int value = 10;
        SimpleVector v(n, value);

        assert(v.size() == n);
        assert(v.capacity() == n);
        assert(v.data() != nullptr);

        v.clear();
        assert(v.empty());
        assert(v.capacity() == n);
        assert(v.data() != nullptr);

        std::cout << "PASSED!\n";
    }

    void erase_demo() {
        std::cout << "\n======== erase(std::size_t index) =========\n";
        std::size_t n = 10;
        int value = 10;

        SimpleVector v(n, value);
        SimpleVector a = v;

        std::cout << "1. Erasing from the front\n";

        int front_val = 9;
        v.front() = front_val;

        assert(v.size() == n);
        assert(v.front() == front_val);

        v.erase(0);

        assert(v.size() == n - 1);
        assert(v.front() == value);

        compare_data(v.data(), a.data() + 1, n - 1);

        std::cout << "PASSED!\n";

        std::cout << "2. Erasing from the middle\n";
        int middle_val = 11;
        std::size_t mid_idx = n / 2;
        v[mid_idx] = middle_val;

        assert(v.size() == n - 1);
        assert(v[mid_idx] == middle_val);

        v.erase(mid_idx);

        // 1 2 3 4 5 6 7 8 9 10 11
        // 2 3 4 5 6 7 8 9 10 11
        // 2 3 4 5 6 8 9 10 11

        // 1 2 3 4 5 6 7 8 9 10
        // 2 3 4 5 6 7 8 9 10
        // 2 3 4 5 6 8 9 10

        assert(v.size() == n - 2);
        assert(v[mid_idx] == value);

        compare_data(v.data(), a.data() + 1, std::min(v.size(), mid_idx - 1));
        compare_data(v.data() + mid_idx, a.data() + mid_idx + 2, std::min(v.size(), n - mid_idx -  2));

        std::cout << "PASSED!\n";

        std::cout << "3. Erasing from the end\n";
        int end_val = 15;
        v.back() = end_val;

        assert(v.size() == n - 2);
        assert(v.back() == end_val);

        v.erase(v.size() - 1);

        assert(v.size() == n - 3);
        assert(v.back() == value);

        std::cout << "PASSED!\n";

        std::cout << "4. Invalid Index\n";

        try {
            v.erase(v.size());
            assert(false && "Expected erase() to throw");
        } catch (const std::out_of_range& e) {
            std::cout << "erase() threw out_of_range as expected: " << e.what() << "\n";
        }

        std::cout << "PASSED!\n";
    }

    void run_demo_suite() {
        default_constructor_demo();
        constructor_with_size_and_value_demo();
        constructor_with_size_demo();
        copy_constructor_demo();
        copy_assignment_demo();
        move_constructor_demo();
        move_assignment_demo();
        reserve_demo();
        resize_demo();
        access_read_demo();
        access_mutation_demo();
        access_exception_demo();
        const_access_demo();
        push_back_demo();
        insert_demo();
        pop_back_demo();
        clear_demo();
        erase_demo();
    }
} // namespace examples::containers::simple_vector

int main() {
    examples::containers::simple_vector::run_demo_suite();
    return 0;
}
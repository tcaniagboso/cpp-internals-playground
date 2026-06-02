#include "cpp_playground/object_model/heap_buffer/heap_buffer.hpp"

#include <cassert>
#include <iostream>
#include <utility>

namespace examples::object_model::heap_buffer {

    using HeapBuffer = cpp_playground::object_model::HeapBuffer<int>;

    void fill(HeapBuffer &a, int value) {
        std::size_t size = a.size();
        for (std::size_t i = 0; i < size; i++) {
            a[i] = value;
        }
    }

    void compare_buffers(const HeapBuffer &a, const HeapBuffer &b) {
        if (a.size() != b.size()) {
            std::cout << "Sizes MISMATCH!\n";
            std::cout << a.size() << " != " << b.size() << "\n";
            assert(a.size() == b.size());
            return;
        }

        assert(a.size() == b.size());

        const std::size_t size = a.size();

        for (std::size_t i = 0; i < size; i++) {
            if (a[i] != b[i]) {
                std::cout << "MISMATCH at index " << i << "\n";
                std::cout << a[i] << " != " << b[i] << "\n";
                assert(a[i] == b[i]);
                return;
            }

            assert(a[i] == b[i]);
        }

        std::cout << "Buffers MATCH!" << "\n";
    }

    void compare_sizes(std::size_t a, std::size_t b) {
        if (a == b) {
            std::cout << "Sizes MATCH!\n";
        } else {
            std::cout << "Sizes MISMATCH!\n";
            std::cout << a << " != " << b << "\n";
        }
    }

    void construction_demo() {
        std::cout << "\n======== Construction ========\n";
        HeapBuffer a(10);

        compare_sizes(a.size(), 10);
    }

    void copy_constructor_demo() {
        std::cout << "\n======== Copy Construction =========\n";
        std::size_t ref_size = 10;
        HeapBuffer a(ref_size);
        fill(a, 1);

        HeapBuffer b = a;

        compare_buffers(a, b);

        assert(a.size() == ref_size);
        assert(a.size() == b.size());

        b[0] = 99;
        assert(a[0] == 1);
        assert(b[0] == 99);
    }

    void copy_assignment_demo() {
        std::cout << "\n======== Copy Assignment =========\n";
        std::size_t ref_size = 10;
        HeapBuffer a(ref_size);
        fill(a, 1);

        HeapBuffer b(15);
        fill(b, 2);

        b = a;

        compare_buffers(a, b);

        assert(a.size() == ref_size);
        assert(a.size() == b.size());

        b[0] = 99;
        assert(a[0] == 1);
        assert(b[0] == 99);
    }

    void move_constructor_demo() {
        std::cout << "\n======== Move Construction =========\n";
        std::size_t ref_size = 10;
        HeapBuffer a(ref_size);
        fill(a, 1);

        HeapBuffer b = a;

        HeapBuffer c = std::move(a);

        compare_buffers(b, c);

        assert(c.size() == ref_size);
        assert(b.size() == c.size());
        assert(a.size() == 0);

        b[0] = 99;
        assert(c[0] == 1);
        assert(b[0] == 99);
    }

    void move_assignment_demo() {
        std::cout << "\n======== Move Assignment =========\n";
        std::size_t ref_size = 10;
        HeapBuffer a(ref_size);
        fill(a, 1);

        HeapBuffer b = a;

        HeapBuffer c(20);
        fill(c, 3);

        c = std::move(a);

        compare_buffers(b, c);

        assert(c.size() == ref_size);
        assert(b.size() == c.size());
        assert(a.size() == 0);

        b[0] = 99;
        assert(c[0] == 1);
        assert(b[0] == 99);
    }

    void out_of_range_demo() {
        std::cout << "\n======== Out of Range =========\n";
        HeapBuffer a(3);

        try {
            a[3] = 10;
            assert(false);
        } catch (const std::out_of_range &) {
            std::cout << "Caught out_of_range as expected\n";
        }
    }

    void run_demo_suite() {
        std::cout << "\n======== Heap Buffer Demo Suite =========\n";
        construction_demo();
        copy_constructor_demo();
        copy_assignment_demo();
        move_constructor_demo();
        move_assignment_demo();
        out_of_range_demo();
    }
} // namespace examples::object_model::heap_buffer

int main() {
    examples::object_model::heap_buffer::run_demo_suite();
    return 0;
}
#include "cpp_playground/object_model/tracer/tracer.hpp"

#include <cassert>
#include <iostream>
#include <string_view>
#include <utility>

namespace examples::object_model::tracer {
    using Tracer = cpp_playground::object_model::Tracer;

    void compare_names(std::string_view a, std::string_view b) {
        if (a == b) {
            std::cout << "Names MATCH!\n";
        } else {
            std::cout << "Names MISMATCH!\n";
            std::cout << a << " != " << b << "\n";
        }
    }

    void construction_demo() {
        std::cout << "\n======== Construction ========\n";
        Tracer a("A");

        compare_names(a.name(), "A");
        assert(a.name() == "A");
    }

    void copy_constructor_demo() {
        std::cout << "\n======== Copy Construction =========\n";
        Tracer a("A");
        Tracer b = a;

        compare_names(a.name(), b.name());
        assert(a.name() == b.name());
    }

    void copy_assignment_demo() {
        std::cout << "\n======== Copy Assignment =========\n";
        Tracer a("A");
        Tracer b("B");

        b = a;

        compare_names(a.name(), b.name());
        assert(b.name() == "A");
    }

    void move_constructor_demo() {
        std::cout << "\n======== Move Construction =========\n";
        Tracer a("A");
        Tracer b = std::move(a);

        compare_names(b.name(), "A");
        assert(b.name() == "A");
    }

    void move_assignment_demo() {
        std::cout << "\n======== Move Assignment =========\n";
        Tracer a("A");
        Tracer b("B");

        b = std::move(a);

        compare_names(b.name(), "A");
        assert(b.name() == "A");
    }

    void run_demo_suite() {
        std::cout << "\n======== Tracer Demo Suite =========\n";
        construction_demo();
        copy_constructor_demo();
        copy_assignment_demo();
        move_constructor_demo();
        move_assignment_demo();
    }
} // namespace examples::object_model::tracer

int main() {
    examples::object_model::tracer::run_demo_suite();
    return 0;
}
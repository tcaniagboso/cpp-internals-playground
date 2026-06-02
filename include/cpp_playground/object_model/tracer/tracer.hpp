#pragma once

#include <iostream>
#include <string>
#include <utility>

namespace cpp_playground::object_model{

    class Tracer {
    public:
        explicit Tracer(const std::string& name) : name_{name} {
            std::cout << "Constructor called for " << name_ << "\n";
        }

        // Copy constructors
        Tracer(const Tracer& other) : name_{other.name_} {
            std::cout << "Copy constructor called from " << other.name_ << "\n";
        }

        Tracer& operator=(const Tracer& other) {
            std::cout << "Copy assignment called from " << other.name_ << " to " << name_ << "\n";
            if (this == &other) {
                return *this;
            }

            this->name_ = other.name_;
            return *this;
        }

        // Move constructors
        Tracer(Tracer&& other) noexcept : name_{std::move(other.name_)}{
            std::cout << "Move constructor called from " << other.name_ << "\n";
        }

        Tracer& operator=(Tracer&& other) noexcept {
            std::cout << "Move assignment called from " << other.name_ << " to " << name_ << "\n";

            if (this == &other) {
                return *this;
            }

            name_ = std::move(other.name_);
            return *this;
        }

        // Destructor
        ~Tracer() {
            std::cout << "Destructor called for " << name_ << "\n";
        }

        // Getter
        [[nodiscard]] const std::string& name() const { return name_; }

    private:
        std::string name_;
    };
} // cpp_playground::object_model
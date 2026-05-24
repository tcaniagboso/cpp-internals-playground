# C++ Internals Playground

A learning-focused C++20 repository where I rebuild small versions of core containers and object-model features from scratch.

The goal is not to replace the STL. The goal is to better understand how modern C++ works beneath the surface, including object lifetime, ownership, copy/move semantics, templates, iterators, allocator-backed storage, and memory management.

---

## Purpose

This repo is my C++ internals playground: a place to rebuild familiar abstractions slowly and intentionally so I can understand the language more deeply.

Rather than only using the STL, I want to understand the mechanisms behind it: how objects are constructed, copied, moved, destroyed, allocated, and stored.

---

## Current Implementations

### Object Model

- `Tracer`
  - Logs construction, copy construction, move construction, assignment, and destruction
  - Used to observe object lifetime and move semantics

- `HeapBuffer<T>`
  - Fixed-size heap-allocated buffer
  - Uses raw storage allocation with `::operator new`
  - Uses `std::construct_at` and `std::destroy_at`
  - Implements the Rule of Five
  - Demonstrates deep copy, move ownership transfer, and manual cleanup

### Containers

- `SimpleVector<T>`
  - Allocator-backed dynamic array
  - Tracks `size_` and `capacity_`
  - Supports copy and move semantics
  - Supports `reserve`, `resize`, `push_back`, `insert`, `erase`, `pop_back`, and `clear`
  - Uses `std::allocator<T>` and `std::allocator_traits`
  - Separates raw storage allocation from object construction

---

## Topics Covered

- Constructors and destructors
- Copy semantics
- Move semantics
- Rule of Five
- RAII and ownership
- Raw heap allocation
- Allocator-backed storage
- Object lifetime
- Dynamic arrays
- Size vs capacity
- Manual construction and destruction
- Basic exception safety
- Pointer arithmetic
- Templates

---

## Planned Implementations

- `SimpleVector<T>` iterators
- Const iterators
- Reverse iterators
- Range-based for loop support
- `SinglyLinkedList<T>`
- `DoublyLinkedList<T>`
- Linked list iterators
- Deleted functions examples
- Singleton example
- Smart pointer experiments
- More allocator and exception-safety experiments

---

## Learning Goals

Through this repo, I am practicing:

- How C++ manages object lifetime
- How copy and move operations actually work
- How containers separate allocation from construction
- How `std::vector`-like growth works internally
- How iterators behave like generalized pointers
- How RAII helps manage resources safely
- How modern C++ abstractions are built from lower-level mechanisms

---

## Status

This repository is intentionally educational and experimental. The implementations are not meant to replace standard library containers. They are built to make C++ internals less mysterious.
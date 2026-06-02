cmake_minimum_required(VERSION 3.20)

project(CppInternalsPlayground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tracer_demo examples/tracer_demo.cpp)

add_executable(heap_buffer_demo examples/heap_buffer_demo.cpp)

# add_executable(vector_demo examples/simple_vector_demo.cpp)

target_include_directories(tracer_demo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(heap_buffer_demo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#target_include_directories(vector_demo PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)
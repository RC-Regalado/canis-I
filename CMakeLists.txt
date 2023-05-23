cmake_minimum_required(VERSION 3.12)
project(grbl)


include_directories(include)

enable_testing()

add_subdirectory(src)

add_subdirectory(tests)


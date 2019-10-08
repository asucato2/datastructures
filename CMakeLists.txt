cmake_minimum_required(VERSION 3.14)
project(DataStructures
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(package_add_test)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(extern/googletest)
cmake_minimum_required(VERSION 3.14)
project(dynamicCircularArray)

set(CMAKE_CXX_STANDARD 14)

add_library(dynamicCircularArray CircularDynamicArray.h)
target_link_libraries(dynamicCircularArray circularArray)

set_target_properties(dynamicCircularArray PROPERTIES LINKER_LANGUAGE CXX)
project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run circularArrayTest.cpp circularDynamicArrayTest.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(Google_Tests_run circularArray dynamicCircularArray)

add_executable(memTest memTest.cpp)
target_link_libraries(memTest dynamicCircularArray)
add_executable(DynamicCircularArrayTest DynamicCircularArrayTest.cpp)
target_link_libraries(DynamicCircularArrayTest DynamicCircularArray gmock gtest gtest_main)

add_executable(BinarySearchTreeTest BinarySearchTreeTest.cpp)
target_link_libraries(BinarySearchTreeTest BinarySearchTree gmock gtest gtest_main)

add_executable(HeapTest HeapTest.cpp)
target_link_libraries(HeapTest Heap gmock gtest gtest_main)

add_executable(RBTreeTest RBTreeTest.cpp)
target_link_libraries(RBTreeTest RBTree gmock gtest gtest_main)

add_executable(Phase2 phase2.cpp)
target_link_libraries(Phase2 RBTree)

add_executable(BHeapTest BHeapTest.cpp)
target_link_libraries(BHeapTest BHeap gmock gtest gtest_main)

add_library(DynamicCircularArray ${DataStructures_SOURCE_DIR}/include/DataStructures/DynamicCircularArray.hpp)
target_include_directories(DynamicCircularArray PUBLIC ../include)
set_target_properties(DynamicCircularArray PROPERTIES LINKER_LANGUAGE CXX)

add_library(BinarySearchTree ${DataStructures_SOURCE_DIR}/include/DataStructures/BinarySearchTree.hpp)
target_include_directories(BinarySearchTree PUBLIC ../include)
set_target_properties(BinarySearchTree PROPERTIES LINKER_LANGUAGE CXX)

add_library(Heap ${DataStructures_SOURCE_DIR}/include/DataStructures/Heap.hpp)
target_include_directories(Heap PUBLIC ../include)
set_target_properties(Heap PROPERTIES LINKER_LANGUAGE CXX)

add_library(RBTree ${DataStructures_SOURCE_DIR}/include/DataStructures/RBTree.hpp)
target_include_directories(RBTree PUBLIC ../include)
set_target_properties(RBTree PROPERTIES LINKER_LANGUAGE CXX)

add_library(dynamicCircularArray ${DataStructures_SOURCE_DIR}/include/DataStructures/DynamicCircularArray.hpp)

target_include_directories(dynamicCircularArray PUBLIC ../include)

set_target_properties(dynamicCircularArray PROPERTIES LINKER_LANGUAGE CXX)
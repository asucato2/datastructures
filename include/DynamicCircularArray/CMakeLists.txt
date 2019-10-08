add_library(dynamicCircularArray DynamicCircularArray.hpp)

target_include_directories(dynamicCircularArray PUBLIC ../../include)

set_target_properties(dynamicCircularArray PROPERTIES LINKER_LANGUAGE CXX)
find_package(fmt REQUIRED)
add_library(pmsutils INTERFACE)
target_include_directories(pmsutils INTERFACE include)
target_link_libraries(pmsutils INTERFACE fmt::fmt)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(pms_test_fields tests/test_fields.cpp)
target_link_libraries(pms_test_fields PRIVATE pmsutils GTest::GTest GTest::Main)
enable_testing()
add_test(NAME pms_test_fields COMMAND pms_test_fields)

add_executable(pms_test_basic_item tests/test_basic_item.cpp)
target_link_libraries(pms_test_basic_item PRIVATE pmsutils GTest::GTest
                                                  GTest::Main)
add_test(NAME pms_test_basic_item COMMAND pms_test_basic_item)

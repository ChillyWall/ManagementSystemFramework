find_package(fmt REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_library(pmsutils INTERFACE)
target_include_directories(pmsutils INTERFACE include)

link_libraries(pmsutils fmt::fmt GTest::GTest GTest::Main)

enable_testing()

add_executable(pms_test_fields tests/test_fields.cpp)
add_test(NAME pms_test_fields COMMAND pms_test_fields)

add_executable(pms_test_basic_item tests/test_basic_item.cpp)
add_test(NAME pms_test_basic_item COMMAND pms_test_basic_item)

add_executable(pms_test_date_time tests/test_date_time.cpp)
add_test(NAME pms_test_date_time COMMAND pms_test_date_time)

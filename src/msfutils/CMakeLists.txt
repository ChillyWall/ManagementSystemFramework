find_package(fmt REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_library(msfutils INTERFACE)
target_include_directories(msfutils INTERFACE include)

link_libraries(msfutils fmt::fmt GTest::GTest GTest::Main)

enable_testing()

add_executable(msf_test_fields tests/test_fields.cpp)
add_test(NAME msf_test_fields COMMAND pms_test_fields)

add_executable(msf_test_basic_item tests/test_basic_item.cpp)
add_test(NAME msf_test_basic_item COMMAND msf_test_basic_item)

add_executable(msf_test_date_time tests/test_date_time.cpp)
add_test(NAME msf_test_date_time COMMAND msf_test_date_time)

add_library(demolib STATIC src/demo_lib.cpp)
target_include_directories(demolib PUBLIC include)

install(TARGETS demolib)
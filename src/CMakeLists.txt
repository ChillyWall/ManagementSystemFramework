cmake_minimum_required(VERSION 3.16)
project(demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_SOURCE_DIR .)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../devel/)

add_subdirectory(demo)
add_subdirectory(demo_lib)
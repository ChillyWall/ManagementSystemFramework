cmake_minimum_required(VERSION 3.16)
project(PrisonerManagementSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_SOURCE_DIR src)
set(CMAKE_BINARY_DIR build)
set(CMAKE_INSTALL_PREFIX devel)

add_subdirectory(src)

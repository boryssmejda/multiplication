cmake_minimum_required(VERSION 3.19)

project(NumberMultiplication LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE OFF)

option(USE_VALGRIND OFF)

    find_package(cmocka CONFIG REQUIRED PATHS ${CMAKE_SOURCE_DIR}/cmocka)

    add_library(project_warnings INTERFACE)
    include(cmake/compiler_warnings.cmake)
    set_project_warnings(project_warnings)

    add_subdirectory(src)
    add_subdirectory(test)

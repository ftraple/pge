cmake_minimum_required(VERSION 3.10)

project(pge VERSION 1.0.0 DESCRIPTION "Pixel Game Engine")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(pge)

option(BUILD_EXAMPLES "Build Examples" OFF)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

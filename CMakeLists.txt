cmake_minimum_required(VERSION 3.2)

project(
    aligned_tuple
    VERSION "0.1"
    HOMEPAGE_URL "https://github.com/ollirelander/aligned_tuple"
    DESCRIPTION "single-header C++14 library for creating an aligned tuple type that provides a standard-layout data structure"
    LANGUAGES CXX
)

option(ALIGNED_TUPLE_OPT_BUILD_EXAMPLES "Build aligned_tuple examples" ON)

if(ALIGNED_TUPLE_OPT_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

add_library(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/aligned_tuple.hpp")
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

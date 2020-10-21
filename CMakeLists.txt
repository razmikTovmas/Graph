cmake_minimum_required(VERSION 3.8)
project(graph VERSION 1.0.0 LANGUAGES CXX)
option(console_BUILD_TESTS OFF)
option(EXAMPLES "Build Examples" ON)

set(CONSOLE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(graph INTERFACE)
add_library(graph::graph ALIAS graph)

if (CMAKE_CXX_STANDARD EQUAL 17)
    target_compile_features(graph INTERFACE cxx_std_17)
    message(STATUS "Using C++17")
endif()

target_include_directories(graph INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

if (EXAMPLES)
  add_subdirectory(examples)
endif()

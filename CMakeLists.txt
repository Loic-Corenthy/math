cmake_minimum_required(VERSION 3.21.0)

set (target_name "permutations")

project (${target_name} VERSION 0.1.0
                        DESCRIPTION "Just a test"
                        LANGUAGES CXX)

add_executable(${target_name} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set_property(TARGET ${target_name} PROPERTY CMAKE_CXX_STANDARD C++20)

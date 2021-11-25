cmake_minimum_required(VERSION 3.21.0)

project ("permutations" VERSION 0.1.0
                        DESCRIPTION "A function to generate permutations on a set of items."
                        LANGUAGES CXX)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
                               PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Permutation.hpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_STANDARD C++20)

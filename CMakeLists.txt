cmake_minimum_required(VERSION 3.21.0)

project (mathUtilities VERSION 1.0.0
                       DESCRIPTION "Miscellaneous math function and classes"
                       LANGUAGES CXX)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_subdirectory(algebra)
add_subdirectory(combinatorics)
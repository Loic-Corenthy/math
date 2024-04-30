cmake_minimum_required(VERSION 3.21.0)

project (mathUtilities VERSION 1.0.0
                       DESCRIPTION "Miscellaneous math function and classes"
                       LANGUAGES CXX)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.0
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")

# Make CTest available for targets
include(CTest)

add_subdirectory(algebra)
add_subdirectory(combinatorics)

add_library(lcnsLargeMatrix)

target_sources(lcnsLargeMatrix
    PUBLIC
        "include/large/Matrix.hpp"
        "include/large/Multiplication.hpp"
    PRIVATE
        "src/Matrix.cpp"
        "src/Multiplication.cpp"
)

target_include_directories(lcnsLargeMatrix PUBLIC "include")

target_compile_features(lcnsLargeMatrix PUBLIC cxx_std_20)

target_compile_options(lcnsLargeMatrix PUBLIC -mavx512f)

set_target_properties(lcnsLargeMatrix PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lcnsLargeMatrix PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(lcnsLargeMatrix
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

add_library(lcns::large-matrix ALIAS lcnsLargeMatrix)

add_subdirectory(tests)
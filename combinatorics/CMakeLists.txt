add_library(lcnsCombinatorics INTERFACE)

target_sources(lcnsCombinatorics
    INTERFACE
        "include/combinatorics/Permutations.hpp"
        "include/combinatorics/Concepts.hpp"
)

target_include_directories(lcnsCombinatorics INTERFACE include)

target_compile_features(lcnsCombinatorics INTERFACE cxx_std_20)

set_target_properties(lcnsCombinatorics PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lcnsCombinatorics PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(lcnsCombinatorics
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

add_library(lcns::combinatorics ALIAS lcnsCombinatorics)

run_clang_tidy_on_interface(lcnsCombinatorics lcns::combinatorics "combinatorics/Permutations.hpp;combinatorics/Concepts.hpp")

add_subdirectory(tests)

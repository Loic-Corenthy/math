add_library(lcnsCombinatorics)

target_sources(lcnsCombinatorics
               PUBLIC
                 "include/combinatorics/Concepts.hpp"
                 "include/combinatorics/Permutations.hpp"
)

target_include_directories(lcnsCombinatorics PUBLIC include)

target_compile_features(lcnsCombinatorics PUBLIC cxx_std_20)

set_target_properties(lcnsCombinatorics PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lcnsCombinatorics PROPERTIES CXX_EXTENSIONS OFF)

add_library(lcns::combinatorics ALIAS lcnsCombinatorics)

add_subdirectory(tests)

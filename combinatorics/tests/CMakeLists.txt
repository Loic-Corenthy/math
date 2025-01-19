add_executable(testCombinatorics main.cpp)

target_link_libraries(testCombinatorics PRIVATE lcns::combinatorics)

target_compile_features(testCombinatorics INTERFACE cxx_std_20)

set_target_properties(testCombinatorics PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(testCombinatorics PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(testCombinatorics
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)


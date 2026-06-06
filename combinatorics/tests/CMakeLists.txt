add_executable(testCombinatorics)

target_sources(testCombinatorics
    PRIVATE
      TestPermutations.cpp
)

add_test(NAME "Test perm1" COMMAND "$<TARGET_FILE:testCombinatorics>" "[perm1]")
add_test(NAME "Test perm2" COMMAND "$<TARGET_FILE:testCombinatorics>" "[perm2]")
add_test(NAME "Test perm3" COMMAND "$<TARGET_FILE:testCombinatorics>" "[perm3]")
add_test(NAME "Test perm4" COMMAND "$<TARGET_FILE:testCombinatorics>" "[perm4]")
add_test(NAME "Test perm5" COMMAND "$<TARGET_FILE:testCombinatorics>" "[perm5]")
set_tests_properties("Test perm1" "Test perm2" "Test perm3" "Test perm4" "Test perm5" PROPERTIES LABELS "testCombinatorics")


target_link_libraries(testCombinatorics PRIVATE lcns::combinatorics Catch2::Catch2WithMain)

target_compile_features(testCombinatorics INTERFACE cxx_std_20)

set_target_properties(testCombinatorics PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(testCombinatorics PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(testCombinatorics
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)


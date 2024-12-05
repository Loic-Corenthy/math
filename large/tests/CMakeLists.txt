add_executable(testLargeMatrix)

target_sources(testLargeMatrix
  PRIVATE
    "TestLargeMatrix.cpp"
    "BenchmarkLargeMatrix.cpp"
)

add_test(NAME "Test large matrix (basic)" COMMAND "$<TARGET_FILE:testLargeMatrix>" "[test][matrix][large][basic]")
add_test(NAME "Test large matrix (simd)" COMMAND "$<TARGET_FILE:testLargeMatrix>" "[test][matrix][large][simd]")
add_test(NAME "Benchmark large matrix" COMMAND "$<TARGET_FILE:testLargeMatrix>" "[benchmark][matrix][large]")

####################################
# Setup common to all test targets #
####################################
set(ALL_TEST_TARGETS  testLargeMatrix)

foreach(TEST_TARGET IN LISTS ALL_TEST_TARGETS)
    target_link_libraries(${TEST_TARGET} PRIVATE lcns::large-matrix Catch2::Catch2WithMain)

    target_compile_features(${TEST_TARGET} PRIVATE cxx_std_20)

    set_target_properties(${TEST_TARGET} PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(${TEST_TARGET} PROPERTIES CXX_EXTENSIONS OFF)

    target_compile_options(${TEST_TARGET}
      PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
endforeach()

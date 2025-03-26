add_executable(benchmarkMultiplicationLarge)

target_sources(benchmarkMultiplicationLarge
    PRIVATE
        "BenchmarkMultiplicationLarge.cpp"
)

add_test(NAME "Benchmark large matrix with 256 rows" COMMAND "$<TARGET_FILE:benchmarkMultiplicationLarge>" "[benchmark][matrix][large][256]")
add_test(NAME "Benchmark large matrix with 1000 rows" COMMAND "$<TARGET_FILE:benchmarkMultiplicationLarge>" "[benchmark][matrix][large][1000]")

target_link_libraries(benchmarkMultiplicationLarge PRIVATE lcns::algebra Catch2::Catch2WithMain)

target_compile_features(benchmarkMultiplicationLarge PUBLIC cxx_std_20)

set_target_properties(benchmarkMultiplicationLarge PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(benchmarkMultiplicationLarge PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(benchmarkMultiplicationLarge
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

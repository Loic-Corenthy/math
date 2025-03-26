

add_executable(benchmarkMultiplicationLarge)

target_sources(testMultiplicationLarge
    PRIVATE
        "TestMultiplicationLarge.cpp"
)

add_test(NAME "Benchmark large matrix with 256 rows" COMMAND "$<TARGET_FILE:testMultiplicationLarge>" "[benchmark][matrix][large][256]")
add_test(NAME "Benchmark large matrix with 1000 rows" COMMAND "$<TARGET_FILE:testMultiplicationLarge>" "[benchmark][matrix][large][1000]")
include(CheckCXXSourceCompiles)

set(AVX2_TEST_SOURCE "
#include <immintrin.h>
int main() {
    __m256 v = _mm256_set1_ps(1.0f);
    return 0;
}
")

set(CMAKE_REQUIRED_FLAGS -mavx2)
check_cxx_source_compiles("${AVX2_TEST_SOURCE}" AVX2_ENABLED_ON_CPU)

if (AVX2_ENABLED_ON_CPU)
    message(STATUS "AVX2 instructions supported")
else()
    message(STATUS "AVX2 instructions not supported")
endif()

# AVX512 Test
set(AVX512_TEST_SOURCE "
#include <immintrin.h>
int main() {
    __m512 v = _mm512_set1_ps(1.0f);
    return 0;
}
")

set(CMAKE_REQUIRED_FLAGS -mavx512f)
check_cxx_source_compiles("${AVX512_TEST_SOURCE}" AVX512_ENABLED_ON_CPU)

if (AVX512_ENABLED_ON_CPU)
    message(STATUS "AVX512 instructions supported")
else()
    message(STATUS "AVX512 instructions not supported")
endif()

unset(CMAKE_REQUIRED_FLAGS)
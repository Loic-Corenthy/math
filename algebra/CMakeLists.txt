add_library(lcnsAlgebra INTERFACE)

target_sources(lcnsAlgebra
  INTERFACE
    FILE_SET
      HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
      "include/algebra/Internal.hpp"
      "include/algebra/Vector.hpp"
      "include/algebra/Matrix.hpp"
      "include/algebra/Quaternion.hpp"
      "include/algebra/MappingFunctions.hpp"
      "include/algebra/MultiplicationLarge.hpp"
      "include/algebra/Algebra.hpp"
)

target_compile_features(lcnsAlgebra INTERFACE cxx_std_20)

if (${AVX512_ENABLED_ON_CPU})
  target_compile_options(lcnsAlgebra INTERFACE -mavx512f -mavx512dq -mavx512bw -mavx512vl)
  target_compile_definitions(lcnsAlgebra INTERFACE AVX_ENABLED_ON_CPU)
  target_compile_definitions(lcnsAlgebra INTERFACE AVX512_ENABLED)
elseif(${AVX2_ENABLED_ON_CPU})
  target_compile_options(lcnsAlgebra INTERFACE -mavx2 -mavx)
  target_compile_options(lcnsAlgebra INTERFACE "SHELL:-march=native")
  target_compile_definitions(lcnsAlgebra INTERFACE AVX_ENABLED_ON_CPU)
  target_compile_definitions(lcnsAlgebra INTERFACE AVX2_ENABLED)
endif()

set_target_properties(lcnsAlgebra PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lcnsAlgebra PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(lcnsAlgebra
  INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

add_library(lcns::algebra ALIAS lcnsAlgebra)

run_clang_tidy_on_interface(lcnsAlgebra lcns::algebra "algebra/Algebra.hpp")

add_subdirectory(tests)
add_subdirectory(benchmarks)

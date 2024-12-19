add_library(lcnsAlgebra INTERFACE)

target_sources(lcnsAlgebra
    INTERFACE
        "include/algebra/Internal.hpp"
        "include/algebra/Vector.hpp"
        "include/algebra/Matrix.hpp"
        "include/algebra/Quaternion.hpp"
        "include/algebra/MappingFunctions.hpp"
        "include/algebra/MultiplicationLarge.hpp"
        "include/algebra/Algebra.hpp"
)

target_include_directories(lcnsAlgebra INTERFACE "include")

target_compile_features(lcnsAlgebra INTERFACE cxx_std_20)

if (${AVX512_ENABLED_ON_CPU})
  target_compile_options(lcnsAlgebra INTERFACE -mavx512f)
  target_compile_definitions(lcnsAlgebra INTERFACE AVX_ENABLED_ON_CPU)
  target_compile_definitions(lcnsAlgebra INTERFACE AVX512_ENABLED)
elseif(${AVX2_ENABLED_ON_CPU})
  target_compile_options(lcnsAlgebra INTERFACE -mavx2)
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

add_library(lcnsAlgebra INTERFACE)

target_sources(lcnsAlgebra
    INTERFACE
        "include/algebra/Internal.hpp"
        "include/algebra/Vector.hpp"
        "include/algebra/Matrix.hpp"
        "include/algebra/Quaternion.hpp"
        "include/algebra/MappingFunctions.hpp"
        "include/algebra/Algebra.hpp"
)

target_include_directories(lcnsAlgebra INTERFACE "include")

target_compile_features(lcnsAlgebra INTERFACE cxx_std_20)

set_target_properties(lcnsAlgebra PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lcnsAlgebra PROPERTIES CXX_EXTENSIONS OFF)

add_library(lcns::algebra ALIAS lcnsAlgebra)

add_subdirectory(tests)
add_library(lcnsAlgebra)

target_sources(lcnsAlgebra
    PUBLIC
        "include/algebra/Internal.hpp"
        "include/algebra/Vector.hpp"
        "include/algebra/Matrix.hpp"
        "include/algebra/Quaternion.hpp"
        "include/algebra/MappingFunctions.hpp"
        "include/algebra/Algebra.hpp"
)

target_include_directories(lcnsAlgebra PUBLIC "include")

target_compile_features(lcnsAlgebra PUBLIC cxx_std_20)

set_target_properties(lcnsAlgebra PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lcnsAlgebra PROPERTIES CXX_EXTENSIONS OFF)

add_library(lcns::algebra ALIAS lcnsAlgebra)

add_subdirectory(tests)
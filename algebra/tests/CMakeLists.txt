add_executable(testVector)

target_sources(testVector
    PRIVATE
        "TestVector2.cpp"
        "TestVector3.cpp"
        "TestVector4.cpp"
)

target_link_libraries(testVector PRIVATE lcns::algebra Catch2::Catch2WithMain)

target_compile_features(testVector PUBLIC cxx_std_20)

set_target_properties(testVector PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(testVector PROPERTIES CXX_EXTENSIONS OFF)

add_test(NAME "Test vec2" COMMAND "$<TARGET_FILE:testVector>" "[algebra][vector][dim2]")
add_test(NAME "Test vec3" COMMAND "$<TARGET_FILE:testVector>" "[algebra][vector][dim3]")
add_test(NAME "Test vec4" COMMAND "$<TARGET_FILE:testVector>" "[algebra][vector][dim4]")

add_executable(testMatrix)

target_sources(testMatrix
    PRIVATE
        "Helper.hpp"
        "TestMatrix2x2.cpp"
        "TestMatrix3x3.cpp"
        "TestMatrix4x4.cpp"
        "TestMatrixMxN.cpp"
)

target_link_libraries(testMatrix PRIVATE lcns::algebra Catch2::Catch2WithMain)

target_compile_features(testMatrix PUBLIC cxx_std_20)

set_target_properties(testMatrix PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(testMatrix PROPERTIES CXX_EXTENSIONS OFF)

add_test(NAME "Test mat2" COMMAND "$<TARGET_FILE:testMatrix>" "[algebra][matrix][dim2]")
add_test(NAME "Test mat3" COMMAND "$<TARGET_FILE:testMatrix>" "[algebra][matrix][dim3]")
add_test(NAME "Test mat4" COMMAND "$<TARGET_FILE:testMatrix>" "[algebra][matrix][dim4]")

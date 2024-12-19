##########
# Vector #
##########
add_executable(testVector)

target_sources(testVector
    PRIVATE
        "TestVector2.cpp"
        "TestVector3.cpp"
        "TestVector4.cpp"
)

add_test(NAME "Test vec2" COMMAND "$<TARGET_FILE:testVector>" "[algebra][vector][dim2]")
add_test(NAME "Test vec3" COMMAND "$<TARGET_FILE:testVector>" "[algebra][vector][dim3]")
add_test(NAME "Test vec4" COMMAND "$<TARGET_FILE:testVector>" "[algebra][vector][dim4]")


##########
# Matrix #
##########
add_executable(testMatrix)

target_sources(testMatrix
    PRIVATE
        "Helper.hpp"
        "TestMatrix2x2.cpp"
        "TestMatrix3x3.cpp"
        "TestMatrix4x4.cpp"
        "TestMatrixMxN.cpp"
)

add_test(NAME "Test mat2" COMMAND "$<TARGET_FILE:testMatrix>" "[algebra][matrix][dim2]")
add_test(NAME "Test mat3" COMMAND "$<TARGET_FILE:testMatrix>" "[algebra][matrix][dim3]")
add_test(NAME "Test mat4" COMMAND "$<TARGET_FILE:testMatrix>" "[algebra][matrix][dim4]")


##############
# Quaternion #
##############
add_executable(testQuaternion)

target_sources(testQuaternion
    PRIVATE
        "Helper.hpp"
        "TestQuaternion.cpp"
)

add_test(NAME "Test quat" COMMAND "$<TARGET_FILE:testQuaternion>" "[algebra][quat]")


###########
# Mapping #
###########
add_executable(testMapping)

target_sources(testMapping
    PRIVATE
        "Helper.hpp"
        "TestMappingFunctions.cpp"
)

add_test(NAME "Test mapping functions" COMMAND "$<TARGET_FILE:testMapping>" "[algebra][mapping]")


########################
# Multiplication Large #
########################

add_executable(testMultiplicationLarge)

target_sources(testMultiplicationLarge
    PRIVATE
        "TestMultiplicationLarge.cpp"
)

add_test(NAME "Test multiplication with multithreading" COMMAND "$<TARGET_FILE:testMultiplicationLarge>" "[test][algebra][multiplication][multithreading]")
add_test(NAME "Test multiplication with simd" COMMAND "$<TARGET_FILE:testMultiplicationLarge>" "[test][algebra][multiplication][simd]")


####################################
# Setup common to all test targets #
####################################
set(ALL_TEST_TARGETS testVector testMatrix testQuaternion testMapping testMultiplicationLarge)

foreach(TEST_TARGET IN LISTS ALL_TEST_TARGETS)
    target_link_libraries(${TEST_TARGET} PRIVATE lcns::algebra Catch2::Catch2WithMain)

    target_compile_features(${TEST_TARGET} PUBLIC cxx_std_20)

    set_target_properties(${TEST_TARGET} PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(${TEST_TARGET} PROPERTIES CXX_EXTENSIONS OFF)

    target_compile_options(${TEST_TARGET}
      PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

endforeach()

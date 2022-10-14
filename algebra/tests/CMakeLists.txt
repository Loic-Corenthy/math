add_executable(testVector)

target_sources(testVector
               PRIVATE
               "TestVector2.cpp"
               "TestVector3.cpp"
               "TestVector4.cpp"
)

target_link_libraries(testVector PRIVATE lcns::algebra Catch2::Catch2WithMain)

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


include(CTest)
include(Catch)
catch_discover_tests(testVector)
catch_discover_tests(testMatrix)
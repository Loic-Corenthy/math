add_executable(testVector)

target_sources(testVector
               PRIVATE
               "TestVector2.cpp"
               "TestVector3.cpp"
)

target_link_libraries(testVector PRIVATE lcns::algebra Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(testVector)
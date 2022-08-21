add_executable(testVector "TestVector2.cpp")


include(CTest)
include(Catch)
target_link_libraries(testVector PRIVATE lcns::algebra Catch2::Catch2WithMain)
#include "large/Matrix.hpp"
#include "large/Multiplication.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <iostream>

using LCNS::Large::Matrix;
using LCNS::Large::multiply_classic;

using namespace std;

TEST_CASE("Multiplication", "[benchmark][matrix][large]")
{
    cout << "CTEST_FULL_OUTPUT\n";

    Matrix lhs(256, 512, true);
    Matrix rhs(512, 128, true);
    BENCHMARK("Simple multiplication")
    {
        const auto result = multiply_classic(lhs, rhs);

        cout << result(123, 34) << '\n';
        return 0;
    };
}

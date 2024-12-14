#include "large/Matrix.hpp"
#include "large/Multiplication.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include <random>

using LCNS::Large::Matrix;
using LCNS::Large::multiply_classic;

using Catch::Matchers::WithinAbs;

using namespace std;

class BenchmarkFixture
{
public:
    BenchmarkFixture()
    : lhs(256, 512, true)
    , rhs(512, 126, true)
    , gen(rd())
    {
        cout << "CTEST_FULL_OUTPUT\n";
    }

    int rand_index_row()
    {
        static std::uniform_int_distribution<> dis(0, 255);

        return dis(gen);
    }

    int rand_index_col()
    {
        static std::uniform_int_distribution<> dis(0, 126);

        return dis(gen);
    }

protected:
    Matrix lhs;
    Matrix rhs;

private:
    std::random_device rd;
    std::mt19937       gen;
};


TEST_CASE_METHOD(BenchmarkFixture, "Multiplication", "[benchmark][matrix][large]")
{
    Matrix res1(256, 126);
    Matrix res2(256, 126);
    Matrix res3(256, 126);

    vector<float> test_data1;
    vector<float> test_data2;

    BENCHMARK("Simple multiplication")
    {
        res1 = multiply_classic(lhs, rhs);

        return 0;
    };

    BENCHMARK("Simd multiplication")
    {
        res2 = multiply_simd(lhs, rhs);

        return 0;
    };

    BENCHMARK("Multithreaded multiplication")
    {
        res3 = multiply_concurrently(lhs, rhs);

        return 0;
    };

    for (size_t i = 0; i < 100; ++i)
    {
        const auto row_idx = rand_index_row();
        const auto col_idx = rand_index_col();
        CHECK_THAT(res1(row_idx, col_idx), WithinAbs(res2(row_idx, col_idx), 1e-3));
        CHECK_THAT(res1(row_idx, col_idx), WithinAbs(res3(row_idx, col_idx), 1e-3));
    }
}

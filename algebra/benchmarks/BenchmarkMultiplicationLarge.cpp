#include "algebra/Matrix.hpp"
#include "algebra/MultiplicationLarge.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include <random>

using Catch::Matchers::WithinAbs;

using namespace std;


template <size_t lhs_row_count, size_t lhs_col_count, size_t rhs_row_count, size_t rhs_col_count> 
class BenchmarkFixture
{
public:
    BenchmarkFixture()
    : _gen(_rd())
    {
        cout << "CTEST_FULL_OUTPUT\n";
    }

    int rand_index_row()
    {
        static std::uniform_int_distribution<> dis(0, lhs.row_count() - 1);

        return dis(_gen);
    }

    int rand_index_col()
    {
        static std::uniform_int_distribution<> dis(0, rhs.col_count() - 1);

        return dis(_gen);
    }

protected:
    LCNS::Algebra::Matrix<float, lhs_row_count, lhs_col_count> lhs;
    LCNS::Algebra::Matrix<float, rhs_row_count, rhs_col_count> rhs;

private:
    random_device _rd;
    mt19937       _gen;
};

TEST_CASE_METHOD(BenchmarkFixture<256, 512, 512, 126>, "Multiplication", "[benchmark][matrix][large][256]")
{
    LCNS::Algebra::Matrix<float, 256, 126> res1, res2, res3;

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


// TEST_CASE_METHOD(BenchmarkFixture1000, "Multiplication", "[benchmark][matrix][large][1000]")
// {
//     BENCHMARK("Simd multiplication")
//     {
//         const auto res = multiply_simd(lhs, rhs);

//         cout << res(345, 567) << '\n';
//         return 0;
//     };

//     BENCHMARK("Multithreading multiplication")
//     {
//         const auto res = multiply_concurrently(lhs, rhs);

//         cout << res(345, 567) << '\n';

//         return 0;
//     };
// }

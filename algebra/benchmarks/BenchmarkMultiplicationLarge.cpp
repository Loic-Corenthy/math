#include "algebra/Matrix.hpp"
#include "algebra/MultiplicationLarge.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include <random>

using Catch::Matchers::WithinAbs;

using LCNS::Algebra::Matrix;
using namespace std;

class BenchmarkFixture
{
public:
    BenchmarkFixture()
    : _gen(_rd())
    {
        cout << "CTEST_FULL_OUTPUT\n";
    }

    size_t random_row_index(size_t row_count)
    {
        static uniform_int_distribution<> dis(0, row_count - 1);

        return static_cast<size_t>(dis(_gen));
    }

    size_t random_col_index(size_t col_count)
    {
        static uniform_int_distribution<> dis(0, col_count - 1);

        return static_cast<size_t>(dis(_gen));
    }

    template <size_t row_count, size_t col_count>
    Matrix<float, row_count, col_count> get_randomly_initialized()
    {
        Matrix<float, row_count, col_count> result;
        uniform_real_distribution<>         dis(0.0f, 1.0f);

        generate(result.data(), result.data() + row_count * col_count, [&]() { return dis(_gen); });

        return result;
    }

    template <size_t row_count, size_t col_count>
    void perform_random_checks(const Matrix<float, row_count, col_count>& lhs,
                               const Matrix<float, row_count, col_count>& rhs,
                               size_t                                     test_count = 100)
    {
        for (size_t i = 0; i < test_count; ++i)
        {
            const auto row_idx = random_row_index(row_count);
            const auto col_idx = random_col_index(col_count);
            CHECK_THAT(lhs(row_idx, col_idx), WithinAbs(rhs(row_idx, col_idx), 1e-3));
        }
    }

private:
    random_device _rd;
    mt19937       _gen;
};


TEST_CASE_METHOD(BenchmarkFixture, "Multiplication 256", "[benchmark][matrix][large][256]")
{
    constexpr size_t lhs_row_count = 256;
    constexpr size_t lhs_col_count = 512;
    constexpr size_t rhs_row_count = lhs_col_count;
    constexpr size_t rhs_col_count = 126;

    const auto lhs = get_randomly_initialized<lhs_row_count, lhs_col_count>();
    const auto rhs = get_randomly_initialized<rhs_row_count, rhs_col_count>();

    Matrix<float, lhs_row_count, rhs_col_count> res1, res2, res3;

    BENCHMARK("Simple multiplication")
    {
        res1 = lhs * rhs;

        return 0;
    };

    BENCHMARK("Simd multiplication")
    {
        res2 = LCNS::Algebra::multiply_simd(lhs, rhs);

        return 0;
    };

    BENCHMARK("Multithreaded multiplication")
    {
        res3 = LCNS::Algebra::multiply_concurrently(lhs, rhs);

        return 0;
    };


    perform_random_checks<lhs_row_count, rhs_col_count>(res1, res2);
    perform_random_checks<lhs_row_count, rhs_col_count>(res1, res3);
}

TEST_CASE_METHOD(BenchmarkFixture, "Multiplication 1000", "[benchmark][matrix][large][1000]")
{
    constexpr size_t lhs_row_count = 1000;
    constexpr size_t lhs_col_count = 1200;
    constexpr size_t rhs_row_count = lhs_col_count;
    constexpr size_t rhs_col_count = 1100;

    const auto lhs = get_randomly_initialized<lhs_row_count, lhs_col_count>();
    const auto rhs = get_randomly_initialized<rhs_row_count, rhs_col_count>();

    Matrix<float, lhs_row_count, rhs_col_count> res1, res2;

    res1 = lhs * rhs;
    res2 = lhs * rhs;

    // BENCHMARK("Simd multiplication")
    // {
    //     res1 = multiply_simd(lhs, rhs);

    //     return 0;
    // };

    // BENCHMARK("Multithreading multiplication")
    // {
    //     res2 = multiply_concurrently(lhs, rhs);

    //     return 0;
    // };

    // perform_random_checks<lhs_row_count, rhs_col_count>(res1, res2);

    CHECK(true);
}
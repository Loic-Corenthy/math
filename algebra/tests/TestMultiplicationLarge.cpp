#include "algebra/Matrix.hpp"
#include "algebra/MultiplicationLarge.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include <random>
#include <algorithm>

using LCNS::Algebra::Matrix;
using LCNS::Algebra::multiply_concurrently;

using Catch::Matchers::WithinAbs;

using namespace std;

template <Coordinate coordinate, unsigned int rows, unsigned int cols>
Matrix<coordinate, rows, cols> generate_random_matrix()
{
    Matrix<coordinate, rows, cols> result;

    std::random_device               rd;
    std::mt19937                     gen(rd());
    std::uniform_real_distribution<> dis(0.0f, 1.0f);

    std::generate(result.data(), result.data() + rows * cols, [&]() { return dis(gen); });

    return result;
}

TEST_CASE("Test multiplication with multithreading", "[test][algebra][multiplication][multithreading]")
{
    cout << "CTEST_FULL_OUTPUT\n";

    const auto lhs = generate_random_matrix<float, 171, 229>();
    const auto rhs = generate_random_matrix<float, 229, 35>();

    const auto res1 = lhs * rhs;

    const auto [lhs_rows, lhs_cols] = lhs.dimensions();
    const auto [rhs_rows, rhs_cols] = rhs.dimensions();
    const auto [res1_rows, res1_cols] = res1.dimensions();

    CHECK(res1_rows == lhs_rows);
    CHECK(res1_cols == rhs_cols);

    const auto res2 = multiply_concurrently(lhs, rhs);
    const auto [res2_rows, res2_cols] = res2.dimensions();

    CHECK(res1_rows == res2_rows);
    CHECK(res1_cols == res2_cols);

    for (size_t i = 0u; i < res1_rows; ++i)
    {
        for (size_t j = 0u; j < res1_cols; ++j)
        {
            CHECK_THAT(res1(i, j), WithinAbs(res2(i, j), 1e-6));
        }
    }
}
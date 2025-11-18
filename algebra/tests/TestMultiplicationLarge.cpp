#include "algebra/Matrix.hpp"
#include "algebra/MultiplicationLarge.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <random>
#include <algorithm>
#include <type_traits>

using LCNS::Algebra::Matrix;
using LCNS::Algebra::multiply_concurrently;

using Catch::Matchers::WithinAbs;

using TestTypeAll      = std::tuple<short, int, long, float, double>;
using TestTypeInteger  = std::tuple<int64_t, uint64_t, int32_t, uint32_t, int16_t, uint16_t, long, unsigned long, int, unsigned int, short, unsigned short>;
using TestTypeFloating = std::tuple<float, double>;

using namespace std;

namespace
{
    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    Matrix<coordinate, rows, cols> generate_random_matrix(coordinate min, coordinate max)
    {
        Matrix<coordinate, rows, cols> result;

        std::random_device rd;
        std::mt19937       gen(rd());

        if constexpr (is_integral_v<coordinate>)
        {
            std::uniform_int_distribution<> dis(min, max);
            std::generate(result.data(), result.data() + rows * cols, [&]() { return static_cast<coordinate>(dis(gen)); });
        }
        else
        {
            std::uniform_real_distribution<> dis(min, max);
            std::generate(result.data(), result.data() + rows * cols, [&]() { return static_cast<coordinate>(dis(gen)); });
        }

        return result;
    }

    template <Coordinate coordinate>
    consteval double precision()
    {
        if constexpr (is_same_v<coordinate, float>)
        {
            return 1e-4;
        }
        else if constexpr (is_same_v<coordinate, double>)
        {
            return 1e-6;
        }
        else
        {
            static_assert(false && "Unexpected coordinate value");
        }
    }

    template <Coordinate coordinate>
    consteval std::tuple<coordinate, coordinate> get_min_max()
    {
        coordinate max{};

        if constexpr (is_same_v<make_signed_t<coordinate>, int64_t> || is_same_v<make_signed_t<coordinate>, int32_t>)
        {
            max = 1e4;
        }
        else if constexpr (is_same_v<make_signed_t<coordinate>, int16_t>)
        {
            max = 1e3;
        }
        else
        {
            static_assert(false && "Unexpected coordinate value");
        }

        const coordinate min = is_signed_v<coordinate> ? -max : 0;

        return make_tuple(min, max);
    }
}


TEMPLATE_LIST_TEST_CASE("Test multiplication with multithreading", "[test][algebra][multiplication][multithreading]", TestTypeAll)
{
    const TestType min = 0;
    const TestType max = is_floating_point_v<TestType> ? 1.0 : 10.0;

    const auto lhs = generate_random_matrix<TestType, 171, 229>(min, max);
    const auto rhs = generate_random_matrix<TestType, 229, 35>(min, max);

    const auto res1 = lhs * rhs;

    const auto [lhs_rows, lhs_cols]   = lhs.dimensions();
    const auto [rhs_rows, rhs_cols]   = rhs.dimensions();
    const auto [res1_rows, res1_cols] = res1.dimensions();

    CHECK(res1_rows == lhs_rows);
    CHECK(res1_cols == rhs_cols);

    const auto res2                   = multiply_concurrently(lhs, rhs);
    const auto [res2_rows, res2_cols] = res2.dimensions();

    CHECK(res1_rows == res2_rows);
    CHECK(res1_cols == res2_cols);

    for (size_t i = 0u; i < res1_rows; ++i)
    {
        for (size_t j = 0u; j < res1_cols; ++j)
        {
            if constexpr (is_integral_v<TestType>)
            {
                CHECK(res1(i, j) == res2(i, j));
            }
            else
            {
                CHECK_THAT(res1(i, j), WithinAbs(res2(i, j), 1e-4));
            }
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Test floating multiplication with simd", "[test][algebra][multiplication][simd]", TestTypeFloating)
{
    const TestType min = 0.0;
    const TestType max = 1.0;

    const auto lhs = generate_random_matrix<TestType, 17, 22>(min, max);
    const auto rhs = generate_random_matrix<TestType, 22, 15>(min, max);

    const auto res1 = lhs * rhs;

    const auto [lhs_rows, lhs_cols]   = lhs.dimensions();
    const auto [rhs_rows, rhs_cols]   = rhs.dimensions();
    const auto [res1_rows, res1_cols] = res1.dimensions();

    CHECK(res1_rows == lhs_rows);
    CHECK(res1_cols == rhs_cols);

    const auto res2                   = multiply_simd(lhs, rhs);
    const auto [res2_rows, res2_cols] = res2.dimensions();

    CHECK(res1_rows == res2_rows);
    CHECK(res1_cols == res2_cols);

    for (size_t i = 0u; i < res1_rows; ++i)
    {
        for (size_t j = 0u; j < res1_cols; ++j)
        {
            CHECK_THAT(res1(i, j), WithinAbs(res2(i, j), precision<TestType>()));
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Test integer multiplication with simd", "[test][algebra][multiplication][simd]", TestTypeInteger)
{
    const auto [min, max] = get_min_max<TestType>();

    const auto lhs = generate_random_matrix<TestType, 17, 31>(min, max);
    const auto rhs = generate_random_matrix<TestType, 31, 19>(min, max);

    const auto res1 = lhs * rhs;

    const auto [lhs_rows, lhs_cols]   = lhs.dimensions();
    const auto [rhs_rows, rhs_cols]   = rhs.dimensions();
    const auto [res1_rows, res1_cols] = res1.dimensions();

    CHECK(res1_rows == lhs_rows);
    CHECK(res1_cols == rhs_cols);

    const auto res2                   = multiply_simd(lhs, rhs);
    const auto [res2_rows, res2_cols] = res2.dimensions();

    CHECK(res1_rows == res2_rows);
    CHECK(res1_cols == res2_cols);

    for (size_t i = 0u; i < res1_rows; ++i)
    {
        for (size_t j = 0u; j < res1_cols; ++j)
        {
            CHECK(res1(i, j) == res2(i, j));
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Test floating multiplication with multithreading and simd", "[test][algebra][multiplication][multithreading][simd]", TestTypeFloating)
{
    const TestType min = 0.0;
    const TestType max = 1.0;

    const auto lhs = generate_random_matrix<TestType, 17, 22>(min, max);
    const auto rhs = generate_random_matrix<TestType, 22, 15>(min, max);

    const auto res1 = lhs * rhs;

    const auto [lhs_rows, lhs_cols]   = lhs.dimensions();
    const auto [rhs_rows, rhs_cols]   = rhs.dimensions();
    const auto [res1_rows, res1_cols] = res1.dimensions();

    CHECK(res1_rows == lhs_rows);
    CHECK(res1_cols == rhs_cols);

    const auto res2                   = multiply_concurrently_simd(lhs, rhs);
    const auto [res2_rows, res2_cols] = res2.dimensions();

    CHECK(res1_rows == res2_rows);
    CHECK(res1_cols == res2_cols);

    for (size_t i = 0u; i < res1_rows; ++i)
    {
        for (size_t j = 0u; j < res1_cols; ++j)
        {
            CHECK_THAT(res1(i, j), WithinAbs(res2(i, j), precision<TestType>()));
        }
    }
}


#include "large/Matrix.hpp"
#include "large/Multiplication.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using LCNS::Large::Matrix;
using LCNS::Large::multiply_classic;
using LCNS::Large::multiply_simd;

using Catch::Matchers::WithinAbs;

using namespace std;

TEST_CASE("Basic tests", "[test][matrix][large][basic]")
{
    GIVEN("A matrix of size 100x100")
    {
        Matrix mat(100, 45);

        THEN("row_count and col_count return the corresponding size")
        {
            CHECK(mat.row_count() == 100);
            CHECK(mat.col_count() == 45);
        }

        AND_THEN("All the elements are initialised to 0")
        {
            for (size_t i = 0; i < mat.row_count(); ++i)
            {
                for (size_t j = 0; j < mat.col_count(); ++j)
                {
                    CHECK(mat(i, j) == 0.0f);
                }
            }
        }
    }

    GIVEN("A matrix with coefficients initialised randomly")
    {
        Matrix rand_mat(200, 250, true);

        THEN("All its coefficients are between 0 and 1")
        {
            for (size_t i = 0; i < rand_mat.row_count(); ++i)
            {
                for (size_t j = 0; j < rand_mat.col_count(); ++j)
                {
                    CHECK(0.0f <= rand_mat(i, j));
                    CHECK(rand_mat(i, j) <= 1.0f);
                }
            }
        }
    }
}

TEST_CASE("Test classic multiplication", "[test][matrix][large][basic]")
{
    Matrix lhs(3, 5);

    // clang-format off
    lhs(0,0) = 1.0f; lhs(0,1) = 2.0f; lhs(0,2) = 3.0f; lhs(0,3) = 4.0f; lhs(0,4) = 5.0f; 
    lhs(1,0) = 5.0f; lhs(1,1) = 4.0f; lhs(1,2) = 3.0f; lhs(1,3) = 2.0f; lhs(1,4) = 1.0f; 
    lhs(2,0) = 2.0f; lhs(2,1) = 2.0f; lhs(2,2) = 3.0f; lhs(2,3) = 5.0f; lhs(2,4) = 5.0f;
    // clang-format on

    Matrix rhs(5, 3);

    // clang-format off
    rhs(0,0) =  1.0f; rhs(0,1) =  2.0f; rhs(0,2) =  3.0f;
    rhs(1,0) =  6.0f; rhs(1,1) =  5.0f; rhs(1,2) =  4.0f;
    rhs(2,0) =  7.0f; rhs(2,1) =  8.0f; rhs(2,2) =  9.0f;
    rhs(3,0) = 12.0f; rhs(3,1) = 11.0f; rhs(3,2) = 10.0f;
    rhs(4,0) = 13.0f; rhs(4,1) = 14.0f; rhs(4,2) = 15.0f;
    // clang-format on

    const auto res = multiply_classic(lhs, rhs);

    // clang-format off
    CHECK(res(0,0) == 147.0f); CHECK(res(0,1) == 150.0f); CHECK(res(0,2) == 153.0f);
    CHECK(res(1,0) ==  87.0f); CHECK(res(1,1) ==  90.0f); CHECK(res(1,2) ==  93.0f);
    CHECK(res(2,0) == 160.0f); CHECK(res(2,1) == 163.0f); CHECK(res(2,2) == 166.0f);
    // clang-format on
}

TEST_CASE("Test transpose", "[test][matrix][large][basic]")
{
    Matrix lhs(3, 5);

    // clang-format off
    lhs(0,0) = 1.0f; lhs(0,1) = 2.0f; lhs(0,2) = 3.0f; lhs(0,3) = 4.0f; lhs(0,4) = 5.0f; 
    lhs(1,0) = 5.0f; lhs(1,1) = 4.0f; lhs(1,2) = 3.0f; lhs(1,3) = 2.0f; lhs(1,4) = 1.0f; 
    lhs(2,0) = 2.0f; lhs(2,1) = 2.0f; lhs(2,2) = 3.0f; lhs(2,3) = 5.0f; lhs(2,4) = 5.0f;
    // clang-format on

    auto transposed = lhs.transpose();

    std::cout << transposed << '\n';

    for (size_t i = 0u; i < transposed.row_count(); ++i)
    {
        for (size_t j = 0u; j < transposed.col_count(); ++j)
        {
            CHECK(transposed(i, j) == lhs(j, i));
        }
    }
}

TEST_CASE("Test multiplication with simd", "[test][matrix][large][simd]")
{
    cout << "CTEST_FULL_OUTPUT\n";

    Matrix lhs(10, 13, true);
    Matrix rhs(13, 8, true);

    cout << "lhs is " << lhs.row_count() << " x " << lhs.col_count() << '\n';
    cout << "rhs is " << rhs.row_count() << " x " << rhs.col_count() << '\n';

    cout << "lhs is\n" << lhs << '\n';
    cout << "rhs is\n" << rhs << '\n';

    const auto res1 = multiply_simd(lhs, rhs);
    const auto res2 = multiply_classic(lhs, rhs);

    CHECK(res1.row_count() == res2.row_count());
    CHECK(res1.col_count() == res2.col_count());

    CHECK(res1.row_count() == lhs.row_count());
    CHECK(res1.col_count() == rhs.col_count());

    for (size_t i = 0u; i < res1.row_count(); ++i)
    {
        for (size_t j = 0u; j < res1.col_count(); ++j)
        {
            CHECK_THAT(res1(i, j), WithinAbs(res2(i, j), 1e-6));
        }
    }
}
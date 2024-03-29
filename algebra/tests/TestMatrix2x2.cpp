#include "algebra/Matrix.hpp"
#include "algebra/Vector.hpp"
#include "Helper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using LCNS::epsilonHighPrecision;
using LCNS::epsilonLowPrecision;
using LCNS::Algebra::Matrix;
using LCNS::Algebra::Vector;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType m00 = -1;
    constexpr TestType m01 = 123;
    constexpr TestType m10 = 19;
    constexpr TestType m11 = -10;

    constexpr Matrix<TestType, 2, 2> mat1 = { m00, m01, m10, m11 };

    static_assert(mat1(0, 0) == m00);
    static_assert(mat1(0, 1) == m01);
    static_assert(mat1(1, 0) == m10);
    static_assert(mat1(1, 1) == m11);

    CHECK(mat1(0, 0) == m00);
    CHECK(mat1(0, 1) == m01);
    CHECK(mat1(1, 0) == m10);
    CHECK(mat1(1, 1) == m11);

    Matrix<TestType, 2, 2> mat2;
    mat2(0, 0) = m11;
    mat2(0, 1) = m00;
    mat2(1, 0) = m01;
    mat2(1, 1) = m10;

    CHECK(mat2(0, 0) == m11);
    CHECK(mat2(0, 1) == m00);
    CHECK(mat2(1, 0) == m01);
    CHECK(mat2(1, 1) == m10);

    CHECK_THROWS(mat2(2, 0));
    CHECK_THROWS(mat2(0, 2));
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType m00 = -1.0;
    constexpr TestType m01 = 3123.77;
    constexpr TestType m10 = 55.12;
    constexpr TestType m11 = -10.0001;

    constexpr Matrix<TestType, 2, 2> mat1 = { m00, m01, m10, m11 };

    static_assert(mat1(0, 0) == m00);
    static_assert(mat1(0, 1) == m01);
    static_assert(mat1(1, 0) == m10);
    static_assert(mat1(1, 1) == m11);

    CHECK(mat1(0, 0) == m00);
    CHECK(mat1(0, 1) == m01);
    CHECK(mat1(1, 0) == m10);
    CHECK(mat1(1, 1) == m11);

    Matrix<TestType, 2, 2> mat2;
    mat2(0, 0) = m11;
    mat2(0, 1) = m00;
    mat2(1, 0) = m01;
    mat2(1, 1) = m10;

    CHECK(mat2(0, 0) == m11);
    CHECK(mat2(0, 1) == m00);
    CHECK(mat2(1, 0) == m01);
    CHECK(mat2(1, 1) == m10);

    CHECK_THROWS(mat2(2, 0));
    CHECK_THROWS(mat2(0, 2));
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dim2][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Matrix<TestType, 2, 2> mat;

    static_assert(mat(0, 0) == zero);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == zero);

    CHECK(mat(0, 0) == zero);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dim2][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Matrix<TestType, 2, 2> mat;

    static_assert(mat(0, 0) == zero);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == zero);

    CHECK(mat(0, 0) == zero);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dim2][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;
    constexpr TestType one  = 1;

    constexpr Matrix<TestType, 2, 2> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == one);

    CHECK(mat(0, 0) == one);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == one);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dim2][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;
    constexpr TestType one  = 1.0;

    constexpr Matrix<TestType, 2, 2> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == one);

    CHECK(mat(0, 0) == one);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == one);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][matrix][dim2][constructor]", IntegerTypes)
{
    constexpr TestType m00 = 1;
    constexpr TestType m01 = 4;
    constexpr TestType m10 = 27;
    constexpr TestType m11 = 256;

    constexpr Matrix<TestType, 2, 2> mat = { m00, m01, m10, m11 };

    static_assert(mat(0, 0) == m00);
    static_assert(mat(0, 1) == m01);
    static_assert(mat(1, 0) == m10);
    static_assert(mat(1, 1) == m11);

    CHECK(mat(0, 0) == m00);
    CHECK(mat(0, 1) == m01);
    CHECK(mat(1, 0) == m10);
    CHECK(mat(1, 1) == m11);

    CHECK_NOTHROW(Matrix<TestType, 2, 2>({}));
    CHECK_NOTHROW(Matrix<TestType, 2, 2>({ m00, m01, m10 }));
    CHECK_THROWS(Matrix<TestType, 2, 2>({ m00, m01, m10, m11, 0 }));
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][matrix][dim2][constructor]", FloatingTypes)
{
    constexpr TestType m00 = -18.1;
    constexpr TestType m01 = 19.2;
    constexpr TestType m10 = 20.3;
    constexpr TestType m11 = -21.4;

    constexpr Matrix<TestType, 2, 2> mat = { m00, m01, m10, m11 };

    static_assert(mat(0, 0) == m00);
    static_assert(mat(0, 1) == m01);
    static_assert(mat(1, 0) == m10);
    static_assert(mat(1, 1) == m11);

    CHECK(mat(0, 0) == m00);
    CHECK(mat(0, 1) == m01);
    CHECK(mat(1, 0) == m10);
    CHECK(mat(1, 1) == m11);

    CHECK_NOTHROW(Matrix<TestType, 2, 2>({}));
    CHECK_NOTHROW(Matrix<TestType, 2, 2>({ m00, m01, m10 }));
    CHECK_THROWS(Matrix<TestType, 2, 2>({ m00, m01, m10, m11, 0 }));
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType m00 = 1;
    constexpr TestType m01 = 4;
    constexpr TestType m10 = 27;
    constexpr TestType m11 = 256;

    constexpr Matrix<TestType, 2, 2> mat = { m00, m01, m10, m11 };

    constexpr auto copy1(mat);

    static_assert(mat(0, 0) == copy1(0, 0));
    static_assert(mat(0, 1) == copy1(0, 1));
    static_assert(mat(1, 0) == copy1(1, 0));
    static_assert(mat(1, 1) == copy1(1, 1));

    CHECK(mat(0, 0) == copy1(0, 0));
    CHECK(mat(0, 1) == copy1(0, 1));
    CHECK(mat(1, 0) == copy1(1, 0));
    CHECK(mat(1, 1) == copy1(1, 1));

    constexpr auto copy2 = mat;

    static_assert(mat(0, 0) == copy2(0, 0));
    static_assert(mat(0, 1) == copy2(0, 1));
    static_assert(mat(1, 0) == copy2(1, 0));
    static_assert(mat(1, 1) == copy2(1, 1));

    CHECK(mat(0, 0) == copy2(0, 0));
    CHECK(mat(0, 1) == copy2(0, 1));
    CHECK(mat(1, 0) == copy2(1, 0));
    CHECK(mat(1, 1) == copy2(1, 1));
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType m00 = -18.1;
    constexpr TestType m01 = 19.2;
    constexpr TestType m10 = 20.3;
    constexpr TestType m11 = -21.4;

    constexpr Matrix<TestType, 2, 2> mat = { m00, m01, m10, m11 };

    constexpr auto copy1(mat);

    static_assert(mat(0, 0) == copy1(0, 0));
    static_assert(mat(0, 1) == copy1(0, 1));
    static_assert(mat(1, 0) == copy1(1, 0));
    static_assert(mat(1, 1) == copy1(1, 1));

    CHECK(mat(0, 0) == copy1(0, 0));
    CHECK(mat(0, 1) == copy1(0, 1));
    CHECK(mat(1, 0) == copy1(1, 0));
    CHECK(mat(1, 1) == copy1(1, 1));

    constexpr auto copy2 = mat;

    static_assert(mat(0, 0) == copy2(0, 0));
    static_assert(mat(0, 1) == copy2(0, 1));
    static_assert(mat(1, 0) == copy2(1, 0));
    static_assert(mat(1, 1) == copy2(1, 1));

    CHECK(mat(0, 0) == copy2(0, 0));
    CHECK(mat(0, 1) == copy2(0, 1));
    CHECK(mat(1, 0) == copy2(1, 0));
    CHECK(mat(1, 1) == copy2(1, 1));
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType m00 = 1, m01 = 4, m10 = 27, m11 = 256;

    constexpr auto getMatrix = [=]() { return Matrix<TestType, 2, 2>({ m00, m01, m10, m11 }); };

    constexpr auto copy1(getMatrix());

    static_assert(copy1(0, 0) == m00);
    static_assert(copy1(0, 1) == m01);
    static_assert(copy1(1, 0) == m10);
    static_assert(copy1(1, 1) == m11);

    CHECK(copy1(0, 0) == m00);
    CHECK(copy1(0, 1) == m01);
    CHECK(copy1(1, 0) == m10);
    CHECK(copy1(1, 1) == m11);

    constexpr auto copy2 = getMatrix();

    static_assert(copy2(0, 0) == m00);
    static_assert(copy2(0, 1) == m01);
    static_assert(copy2(1, 0) == m10);
    static_assert(copy2(1, 1) == m11);

    CHECK(copy2(0, 0) == m00);
    CHECK(copy2(0, 1) == m01);
    CHECK(copy2(1, 0) == m10);
    CHECK(copy2(1, 1) == m11);
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType m00 = -18.1, m01 = 19.2, m10 = 20.3, m11 = -21.4;

    constexpr auto getMatrix = [=]() { return Matrix<TestType, 2, 2>({ m00, m01, m10, m11 }); };

    constexpr auto copy1(getMatrix());

    static_assert(copy1(0, 0) == m00);
    static_assert(copy1(0, 1) == m01);
    static_assert(copy1(1, 0) == m10);
    static_assert(copy1(1, 1) == m11);

    CHECK(copy1(0, 0) == m00);
    CHECK(copy1(0, 1) == m01);
    CHECK(copy1(1, 0) == m10);
    CHECK(copy1(1, 1) == m11);

    constexpr auto copy2 = getMatrix();

    static_assert(copy2(0, 0) == m00);
    static_assert(copy2(0, 1) == m01);
    static_assert(copy2(1, 0) == m10);
    static_assert(copy2(1, 1) == m11);

    CHECK(copy2(0, 0) == m00);
    CHECK(copy2(0, 1) == m01);
    CHECK(copy2(1, 0) == m10);
    CHECK(copy2(1, 1) == m11);
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType m00 = 321, m01 = 654, m10 = 987, m11 = -741;

    constexpr Matrix<TestType, 2, 2> mat       = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> identical = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> different = { m00, m11, m10, 0 };

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);

    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            Matrix<TestType, 2, 2> diff = mat;
            diff(i, j)                  = 0;

            CHECK(mat != diff);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType m00 = -0.1, m01 = 0.2, m10 = 0.3, m11 = -0.4;

    constexpr Matrix<TestType, 2, 2> mat       = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> identical = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> different = { m00, m11, m10, 0.0 };

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);

    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            Matrix<TestType, 2, 2> diff = mat;
            diff(i, j)                  = 0;

            CHECK(mat != diff);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType mat1_00 = 666, mat1_01 = 10, mat1_10 = 113, mat1_11 = -347;
    constexpr TestType mat2_00 = -16, mat2_01 = 31, mat2_10 = -98, mat2_11 = -300;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> sum  = mat1 + mat2;

    static_assert(sum(0, 0) == 650);
    static_assert(sum(0, 1) == 41);
    static_assert(sum(1, 0) == 15);
    static_assert(sum(1, 1) == -647);

    CHECK(sum(0, 0) == 650);
    CHECK(sum(0, 1) == 41);
    CHECK(sum(1, 0) == 15);
    CHECK(sum(1, 1) == -647);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType mat1_00 = -8.2, mat1_01 = 5864.1, mat1_10 = -77.12, mat1_11 = -3.5;
    constexpr TestType mat2_00 = 10.0, mat2_01 = 249.56, mat2_10 = -91.91, mat2_11 = 3.52;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> sum  = mat1 + mat2;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(sum(0, 0) - 1.8) < elp);
    static_assert(std::abs(sum(0, 1) - 6113.66) < elp);
    static_assert(std::abs(sum(1, 0) - -169.03) < elp);
    static_assert(std::abs(sum(1, 1) - 0.02) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(sum(0, 0) == Catch::Approx(1.8).epsilon(ehp));
    CHECK(sum(0, 1) == Catch::Approx(6113.66).epsilon(ehp));
    CHECK(sum(1, 0) == Catch::Approx(-169.03).epsilon(ehp));
    CHECK(sum(1, 1) == Catch::Approx(0.02).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Substraction operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType mat1_00 = 321, mat1_01 = 654, mat1_10 = 987, mat1_11 = -741;
    constexpr TestType mat2_00 = -54, mat2_01 = 111, mat2_10 = -98, mat2_11 = -900;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> diff = mat1 - mat2;

    static_assert(diff(0, 0) == 375);
    static_assert(diff(0, 1) == 543);
    static_assert(diff(1, 0) == 1085);
    static_assert(diff(1, 1) == 159);

    CHECK(diff(0, 0) == 375);
    CHECK(diff(0, 1) == 543);
    CHECK(diff(1, 0) == 1085);
    CHECK(diff(1, 1) == 159);
}

TEMPLATE_LIST_TEST_CASE("Substraction operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType mat1_00 = -11.990, mat1_01 = 584.137, mat1_10 = -77.12, mat1_11 = 853.08;
    constexpr TestType mat2_00 = -100.01, mat2_01 = -249.56, mat2_10 = -99.99, mat2_11 = 642.80;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> diff = mat1 - mat2;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(diff(0, 0) - 88.02) < elp);
    static_assert(std::abs(diff(0, 1) - 833.697) < elp);
    static_assert(std::abs(diff(1, 0) - 22.87) < elp);
    static_assert(std::abs(diff(1, 1) - 210.28) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(diff(0, 0) == Catch::Approx(88.02).epsilon(ehp));
    CHECK(diff(0, 1) == Catch::Approx(833.697).epsilon(ehp));
    CHECK(diff(1, 0) == Catch::Approx(22.87).epsilon(ehp));
    CHECK(diff(1, 1) == Catch::Approx(210.28).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    TestType mat_00 = 8, mat_01 = 9, mat_10 = 2022, mat_11 = 10;
    TestType scalar = 2;

    Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    mat *= scalar;

    CHECK(mat(0, 0) == 16);
    CHECK(mat(0, 1) == 18);
    CHECK(mat(1, 0) == 4044);
    CHECK(mat(1, 1) == 20);
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    TestType mat_00 = -77.3, mat_01 = 123.4, mat_10 = 10.01, mat_11 = -99.65;
    TestType scalar = 17.2;

    Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    mat *= scalar;

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mat(0, 0) == Catch::Approx(-1329.56).epsilon(ehp));
    CHECK(mat(0, 1) == Catch::Approx(2122.48).epsilon(ehp));
    CHECK(mat(1, 0) == Catch::Approx(172.172).epsilon(ehp));
    CHECK(mat(1, 1) == Catch::Approx(-1713.98).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    TestType mat_00 = 7, mat_01 = 21, mat_10 = -49, mat_11 = 707;
    TestType scalar = 7;

    Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    mat /= scalar;

    CHECK(mat(0, 0) == 1);
    CHECK(mat(0, 1) == 3);
    CHECK(mat(1, 0) == -7);
    CHECK(mat(1, 1) == 101);

    TestType zero = 0;
    CHECK_THROWS(mat /= zero);
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    TestType mat_00 = -55.4, mat_01 = 369.25, mat_10 = 159.75, mat_11 = 268.42;
    TestType scalar = -28.4;

    Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    mat /= scalar;

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mat(0, 0) == Catch::Approx(1.950704225).epsilon(ehp));
    CHECK(mat(0, 1) == Catch::Approx(-13.00176056).epsilon(ehp));
    CHECK(mat(1, 0) == Catch::Approx(-5.625).epsilon(ehp));
    CHECK(mat(1, 1) == Catch::Approx(-9.45140845).epsilon(ehp));

    TestType zero = 0.0;
    CHECK_THROWS(mat /= zero);
}

TEMPLATE_LIST_TEST_CASE("Dimensions", "[algebra][matrix][dim2][method]", IntegerTypes)
{
    constexpr Matrix<TestType, 2, 2> mat;

    constexpr auto dims = mat.dimensions();

    static_assert(std::get<0>(dims) == 2);
    static_assert(std::get<1>(dims) == 2);

    const auto [rows, cols] = mat.dimensions();

    CHECK(rows == 2);
    CHECK(cols == 2);
}

TEMPLATE_LIST_TEST_CASE("Dimensions", "[algebra][matrix][dim2][method]", FloatingTypes)
{
    constexpr Matrix<TestType, 2, 2> mat;

    constexpr auto dims = mat.dimensions();

    static_assert(std::get<0>(dims) == 2);
    static_assert(std::get<1>(dims) == 2);

    const auto [rows, cols] = mat.dimensions();

    CHECK(rows == 2);
    CHECK(cols == 2);
}

TEMPLATE_LIST_TEST_CASE("Internal data access", "[algebra][matrix][dim2][method]", IntegerTypes)
{
    TestType m00 = 321, m01 = 654, m10 = 987, m11 = -741;

    Matrix<TestType, 2, 2>       mat1 = { m00, m01, m10, m11 };
    const Matrix<TestType, 2, 2> mat2 = { m00, m01, m10, m11 };

    auto*       data1 = mat1.data();
    const auto* data2 = mat2.data();

    CHECK(data1[0] == 321);
    CHECK(data1[1] == 654);
    CHECK(data1[2] == 987);
    CHECK(data1[3] == -741);

    CHECK(data2[0] == 321);
    CHECK(data2[1] == 654);
    CHECK(data2[2] == 987);
    CHECK(data2[3] == -741);
}

TEMPLATE_LIST_TEST_CASE("Internal data access", "[algebra][matrix][dim2][method]", FloatingTypes)
{
    TestType m00 = 7.55, m01 = -96.25, m10 = -0.0001, m11 = 2.022;

    Matrix<TestType, 2, 2>       mat1 = { m00, m01, m10, m11 };
    const Matrix<TestType, 2, 2> mat2 = { m00, m01, m10, m11 };

    auto*       data1 = mat1.data();
    const auto* data2 = mat2.data();

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(data1[0] == Catch::Approx(7.55).epsilon(ehp));
    CHECK(data1[1] == Catch::Approx(-96.25).epsilon(ehp));
    CHECK(data1[2] == Catch::Approx(-0.0001).epsilon(ehp));
    CHECK(data1[3] == Catch::Approx(2.022).epsilon(ehp));

    CHECK(data2[0] == Catch::Approx(7.55).epsilon(ehp));
    CHECK(data2[1] == Catch::Approx(-96.25).epsilon(ehp));
    CHECK(data2[2] == Catch::Approx(-0.0001).epsilon(ehp));
    CHECK(data2[3] == Catch::Approx(2.022).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Transpose", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType mat1_00 = 97, mat1_01 = 288, mat1_10 = -666, mat1_11 = 89;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };

    constexpr Matrix<TestType, 2, 2> transposed = mat1.transposed();

    static_assert(transposed(0, 0) == 97);
    static_assert(transposed(0, 1) == -666);
    static_assert(transposed(1, 0) == 288);
    static_assert(transposed(1, 1) == 89);

    static_assert(transposed.transposed() == mat1);

    Matrix<TestType, 2, 2> mat2 = { mat1_00, mat1_01, mat1_10, mat1_11 };

    mat2.transpose();

    CHECK(mat2(0, 0) == 97);
    CHECK(mat2(0, 1) == -666);
    CHECK(mat2(1, 0) == 288);
    CHECK(mat2(1, 1) == 89);

    mat2.transpose();

    CHECK(mat2 == mat1);
}

TEMPLATE_LIST_TEST_CASE("Transpose", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType mat1_00 = 97.0, mat1_01 = 288.0, mat1_10 = -666.0, mat1_11 = 89.0;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };

    constexpr Matrix<TestType, 2, 2> transposed = mat1.transposed();

    static_assert(transposed(0, 0) == 97.0);
    static_assert(transposed(0, 1) == -666.0);
    static_assert(transposed(1, 0) == 288.0);
    static_assert(transposed(1, 1) == 89.0);

    static_assert(transposed.transposed() == mat1);

    Matrix<TestType, 2, 2> mat2 = { mat1_00, mat1_01, mat1_10, mat1_11 };

    mat2.transpose();

    CHECK(mat2(0, 0) == 97.0);
    CHECK(mat2(0, 1) == -666.0);
    CHECK(mat2(1, 0) == 288.0);
    CHECK(mat2(1, 1) == 89.0);

    mat2.transpose();

    CHECK(mat2 == mat1);
}

TEMPLATE_LIST_TEST_CASE("Determinant", "[algebra][matrix][dim2][method]", IntegerTypes)
{
    constexpr TestType mat1_00 = 3, mat1_01 = 7, mat1_10 = -2, mat1_11 = 13;
    constexpr TestType mat2_00 = 1, mat2_01 = 2, mat2_10 = -5, mat2_11 = -10;
    constexpr TestType one = 1;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> mat3(one);

    constexpr TestType det1 = mat1.determinant();
    constexpr TestType det2 = mat2.determinant();
    constexpr TestType det3 = mat3.determinant();

    static_assert(det1 == 53);
    static_assert(det2 == 0);
    static_assert(det3 == 1);

    CHECK(det1 == 53);
    CHECK(det2 == 0);
    CHECK(det3 == 1);
}

TEMPLATE_LIST_TEST_CASE("Determinant", "[algebra][matrix][dim2][method]", FloatingTypes)
{
    constexpr TestType mat1_00 = 2.18, mat1_01 = -9.3, mat1_10 = -5.55, mat1_11 = -0.5;
    constexpr TestType mat2_00 = 4.2, mat2_01 = 10.5, mat2_10 = 0.1, mat2_11 = 0.25;
    constexpr TestType one = 1.0;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> mat3(one);

    constexpr TestType det1 = mat1.determinant();
    constexpr TestType det2 = mat2.determinant();
    constexpr TestType det3 = mat3.determinant();

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(det1 - -52.705) < elp);
    static_assert(std::abs(det2 - 0.0) < elp);
    static_assert(std::abs(det3 - 1.0) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(det1 == Catch::Approx(-52.705).epsilon(ehp));
    CHECK(std::abs(det2 - 0.0) < ehp);  // error: -0.0f == Approx( 0.0 )
    CHECK(det3 == Catch::Approx(1.0).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Trace", "[algebra][matrix][dim2][method]", IntegerTypes)
{
    constexpr TestType mat1_00 = 8, mat1_01 = 9, mat1_10 = -42, mat1_11 = 998;
    constexpr TestType one = 1;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2(one);

    constexpr TestType tr1 = mat1.trace();
    constexpr TestType tr2 = mat2.trace();

    static_assert(tr1 == 1006);
    static_assert(tr2 == 2);

    const auto [rows, cols] = mat2.dimensions();
    CHECK(tr1 == 1006);
    CHECK(tr2 == rows);
    CHECK(tr2 == cols);
}

TEMPLATE_LIST_TEST_CASE("Trace", "[algebra][matrix][dim2][method]", FloatingTypes)
{
    constexpr TestType mat1_00 = 8.20, mat1_01 = -9.33, mat1_10 = -42.55, mat1_11 = 2.8;
    constexpr TestType one = 1.0;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2(one);

    constexpr TestType tr1 = mat1.trace();
    constexpr TestType tr2 = mat2.trace();

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(tr1 - 11.0) < elp);
    static_assert(std::abs(tr2 - 2.0) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    const auto [rows, cols] = mat2.dimensions();

    CHECK(std::abs(tr1 - 11.0) < ehp);
    CHECK(tr2 == static_cast<TestType>(rows));
    CHECK(tr2 == static_cast<TestType>(cols));
}

TEMPLATE_LIST_TEST_CASE("Inverse", "[algebra][matrix][dim2][method]", FloatingTypes)
{
    constexpr TestType mat_00 = 3.20, mat_01 = -1.33, mat_10 = -4.55, mat_11 = 2.8;

    Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    mat.inverse();

    constexpr auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mat(0, 0) == Catch::Approx(0.9626955475).epsilon(ehp));
    CHECK(mat(0, 1) == Catch::Approx(0.4572803851).epsilon(ehp));
    CHECK(mat(1, 0) == Catch::Approx(1.5643802647).epsilon(ehp));
    CHECK(mat(1, 1) == Catch::Approx(1.1002234829).epsilon(ehp));

    constexpr Matrix<TestType, 2, 2> mat2 = { mat_00, mat_01, mat_10, mat_11 };

    constexpr auto inv = mat2.inversed();

    static_assert(std::abs(inv(0, 0) - 0.9626955475) < ehp);
    static_assert(std::abs(inv(0, 1) - 0.4572803851) < ehp);
    static_assert(std::abs(inv(1, 0) - 1.5643802647) < ehp);
    static_assert(std::abs(inv(1, 1) - 1.1002234829) < ehp);

    CHECK(inv(0, 0) == Catch::Approx(0.9626955475).epsilon(ehp));
    CHECK(inv(0, 1) == Catch::Approx(0.4572803851).epsilon(ehp));
    CHECK(inv(1, 0) == Catch::Approx(1.5643802647).epsilon(ehp));
    CHECK(inv(1, 1) == Catch::Approx(1.1002234829).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Is null?", "[algebra][matrix][dim2][method]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 8,   mat1_01 = 0,
                       mat1_10 = -42, mat1_11 = 0;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01,
                                              mat1_10, mat1_11 };
    // clang-format on

    constexpr TestType               zero = 0;
    constexpr Matrix<TestType, 2, 2> mat2;
    constexpr Matrix<TestType, 2, 2> mat3 = mat1 * zero;
    constexpr Matrix<TestType, 2, 2> mat4 = mat1 - mat1;

    static_assert(!mat1.isNull());
    static_assert(mat2.isNull());
    static_assert(mat3.isNull());
    static_assert(mat4.isNull());

    CHECK_FALSE(mat1.isNull());
    CHECK(mat2.isNull());
    CHECK(mat3.isNull());
    CHECK(mat4.isNull());
}

TEMPLATE_LIST_TEST_CASE("Is null?", "[algebra][matrix][dim2][method]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 0.0,    mat1_01 = -9.33,
                       mat1_10 = -42.55, mat1_11 = 2.8;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01,
                                              mat1_10, mat1_11 };
    // clang-format on

    constexpr TestType               zero = 0.0;
    constexpr Matrix<TestType, 2, 2> mat2;
    constexpr Matrix<TestType, 2, 2> mat3 = mat1 * zero;
    constexpr Matrix<TestType, 2, 2> mat4 = mat1 - mat1;

    static_assert(!mat1.isNull());
    static_assert(mat2.isNull());
    static_assert(mat3.isNull());
    static_assert(mat4.isNull());

    CHECK_FALSE(mat1.isNull());
    CHECK(mat2.isNull());
    CHECK(mat3.isNull());
    CHECK(mat4.isNull());
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType mat_00 = 8, mat_01 = 9, mat_10 = 2022, mat_11 = 10;
    constexpr TestType scalar = 2;

    constexpr Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    constexpr Matrix<TestType, 2, 2> scaled1 = scalar * mat;
    constexpr Matrix<TestType, 2, 2> scaled2 = mat * scalar;

    static_assert(scaled1(0, 0) == 16);
    static_assert(scaled1(0, 1) == 18);
    static_assert(scaled1(1, 0) == 4044);
    static_assert(scaled1(1, 1) == 20);

    static_assert(scaled2(0, 0) == 16);
    static_assert(scaled2(0, 1) == 18);
    static_assert(scaled2(1, 0) == 4044);
    static_assert(scaled2(1, 1) == 20);

    CHECK(scaled1(0, 0) == 16);
    CHECK(scaled1(0, 1) == 18);
    CHECK(scaled1(1, 0) == 4044);
    CHECK(scaled1(1, 1) == 20);

    CHECK(scaled2(0, 0) == 16);
    CHECK(scaled2(0, 1) == 18);
    CHECK(scaled2(1, 0) == 4044);
    CHECK(scaled2(1, 1) == 20);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType mat_00 = -77.3, mat_01 = 123.4, mat_10 = 10.01, mat_11 = -99.65;
    constexpr TestType scalar = 17.2;

    constexpr Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    constexpr Matrix<TestType, 2, 2> scaled1 = scalar * mat;
    constexpr Matrix<TestType, 2, 2> scaled2 = mat * scalar;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(scaled1(0, 0) - -1329.56) < elp);
    static_assert(std::abs(scaled1(0, 1) - 2122.48) < elp);
    static_assert(std::abs(scaled1(1, 0) - 172.172) < elp);
    static_assert(std::abs(scaled1(1, 1) - -1713.98) < elp);

    static_assert(std::abs(scaled2(0, 0) - -1329.56) < elp);
    static_assert(std::abs(scaled2(0, 1) - 2122.48) < elp);
    static_assert(std::abs(scaled2(1, 0) - 172.172) < elp);
    static_assert(std::abs(scaled2(1, 1) - -1713.98) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(scaled1(0, 0) == Catch::Approx(-1329.56).epsilon(ehp));
    CHECK(scaled1(0, 1) == Catch::Approx(2122.48).epsilon(ehp));
    CHECK(scaled1(1, 0) == Catch::Approx(172.172).epsilon(ehp));
    CHECK(scaled1(1, 1) == Catch::Approx(-1713.98).epsilon(ehp));

    CHECK(scaled2(0, 0) == Catch::Approx(-1329.56).epsilon(ehp));
    CHECK(scaled2(0, 1) == Catch::Approx(2122.48).epsilon(ehp));
    CHECK(scaled2(1, 0) == Catch::Approx(172.172).epsilon(ehp));
    CHECK(scaled2(1, 1) == Catch::Approx(-1713.98).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Matrix multiplication operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType mat1_00 = 3, mat1_01 = 5, mat1_10 = -9, mat1_11 = 0;
    constexpr TestType mat2_00 = 5, mat2_01 = 7, mat2_10 = 12, mat2_11 = 1;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> mul  = mat1 * mat2;

    static_assert(mul(0, 0) == 75);
    static_assert(mul(0, 1) == 26);
    static_assert(mul(1, 0) == -45);
    static_assert(mul(1, 1) == -63);

    CHECK(mul(0, 0) == 75);
    CHECK(mul(0, 1) == 26);
    CHECK(mul(1, 0) == -45);
    CHECK(mul(1, 1) == -63);
}

TEMPLATE_LIST_TEST_CASE("Matrix multiplication operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType mat1_00 = 0.16, mat1_01 = 12.2, mat1_10 = 3.33, mat1_11 = 0.5;
    constexpr TestType mat2_00 = -0.8, mat2_01 = -2.5, mat2_10 = -0.1, mat2_11 = 0.2;

    constexpr Matrix<TestType, 2, 2> mat1 = { mat1_00, mat1_01, mat1_10, mat1_11 };
    constexpr Matrix<TestType, 2, 2> mat2 = { mat2_00, mat2_01, mat2_10, mat2_11 };
    constexpr Matrix<TestType, 2, 2> mul  = mat1 * mat2;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(mul(0, 0) - -1.348) < elp);
    static_assert(std::abs(mul(0, 1) - 2.04) < elp);
    static_assert(std::abs(mul(1, 0) - -2.714) < elp);
    static_assert(std::abs(mul(1, 1) - -8.225) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mul(0, 0) == Catch::Approx(-1.348).epsilon(ehp));
    CHECK(mul(0, 1) == Catch::Approx(2.04).epsilon(ehp));
    CHECK(mul(1, 0) == Catch::Approx(-2.714).epsilon(ehp));
    CHECK(mul(1, 1) == Catch::Approx(-8.225).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Matrix vector multiplication", "[algebra][matrix][dim2][method]", IntegerTypes)
{
    constexpr TestType mat_00 = 8, mat_01 = 9, mat_10 = -42, mat_11 = -17;
    constexpr TestType vec_0 = 5, vec_1 = 11;

    constexpr Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };
    constexpr Vector<TestType, 2>    vec = { vec_0, vec_1 };

    constexpr Vector<TestType, 2> mul = mat * vec;

    static_assert(mul[0] == 139);
    static_assert(mul[1] == -397);

    CHECK(mul[0] == 139);
    CHECK(mul[1] == -397);
}

TEMPLATE_LIST_TEST_CASE("Matrix vector multiplication", "[algebra][matrix][dim2][method]", FloatingTypes)
{
    constexpr TestType mat_00 = 2.3, mat_01 = 12.1, mat_10 = 6.7, mat_11 = 9.66;
    constexpr TestType vec_0 = -7.3, vec_1 = 10.2;

    constexpr Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };
    constexpr Vector<TestType, 2>    vec = { vec_0, vec_1 };

    constexpr Vector<TestType, 2> mul = mat * vec;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(mul[0] - 106.63) < elp);
    static_assert(std::abs(mul[1] - 49.622) < elp);

    constexpr auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mul[0] == Catch::Approx(106.63).epsilon(ehp));
    CHECK(mul[1] == Catch::Approx(49.622).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType mat_00 = 7, mat_01 = 21, mat_10 = -49, mat_11 = 707;
    constexpr TestType scalar = 7;

    constexpr Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    constexpr Matrix<TestType, 2, 2> scaled = mat / scalar;

    static_assert(scaled(0, 0) == 1);
    static_assert(scaled(0, 1) == 3);
    static_assert(scaled(1, 0) == -7);
    static_assert(scaled(1, 1) == 101);

    CHECK(scaled(0, 0) == 1);
    CHECK(scaled(0, 1) == 3);
    CHECK(scaled(1, 0) == -7);
    CHECK(scaled(1, 1) == 101);

    const TestType zero = 0;
    CHECK_THROWS(mat / zero);
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType mat_00 = -55.4, mat_01 = 369.25, mat_10 = 159.75, mat_11 = 268.42;
    constexpr TestType scalar = -28.4;

    constexpr Matrix<TestType, 2, 2> mat = { mat_00, mat_01, mat_10, mat_11 };

    constexpr Matrix<TestType, 2, 2> scaled2 = mat / scalar;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(scaled2(0, 0) - 1.950704225) < elp);
    static_assert(std::abs(scaled2(0, 1) - -13.00176056) < elp);
    static_assert(std::abs(scaled2(1, 0) - -5.625) < elp);
    static_assert(std::abs(scaled2(1, 1) - -9.45140845) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(scaled2(0, 0) == Catch::Approx(1.950704225).epsilon(ehp));
    CHECK(scaled2(0, 1) == Catch::Approx(-13.00176056).epsilon(ehp));
    CHECK(scaled2(1, 0) == Catch::Approx(-5.625).epsilon(ehp));
    CHECK(scaled2(1, 1) == Catch::Approx(-9.45140845).epsilon(ehp));

    const TestType zero = 0.0;
    CHECK_THROWS(mat / zero);
}

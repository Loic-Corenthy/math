#include "algebra/Matrix.hpp"

#include "Helper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <iostream>

using LCNS::epsilonHighPrecision;
using LCNS::epsilonLowPrecision;
using LCNS::Algebra::Matrix;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim4][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  100, mat_01 =  101, mat_02 = -102, mat_03 = -103,
                       mat_10 = -110, mat_11 = -111, mat_12 = -112, mat_13 =  113,
                       mat_20 =  120, mat_21 =  121, mat_22 = -122, mat_23 =  123,
                       mat_30 =  130, mat_31 =  131, mat_32 = -132, mat_33 =  133;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03, 
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };
    // clang-format on

    static_assert(mat(0, 0) == mat_00);
    static_assert(mat(1, 0) == mat_10);
    static_assert(mat(2, 0) == mat_20);
    static_assert(mat(3, 0) == mat_30);

    static_assert(mat(0, 1) == mat_01);
    static_assert(mat(1, 1) == mat_11);
    static_assert(mat(2, 1) == mat_21);
    static_assert(mat(3, 1) == mat_31);

    static_assert(mat(0, 2) == mat_02);
    static_assert(mat(1, 2) == mat_12);
    static_assert(mat(2, 2) == mat_22);
    static_assert(mat(3, 2) == mat_32);

    static_assert(mat(0, 3) == mat_03);
    static_assert(mat(1, 3) == mat_13);
    static_assert(mat(2, 3) == mat_23);
    static_assert(mat(3, 3) == mat_33);

    CHECK(mat(0, 0) == mat_00);
    CHECK(mat(1, 0) == mat_10);
    CHECK(mat(2, 0) == mat_20);
    CHECK(mat(3, 0) == mat_30);

    CHECK(mat(0, 1) == mat_01);
    CHECK(mat(1, 1) == mat_11);
    CHECK(mat(2, 1) == mat_21);
    CHECK(mat(3, 1) == mat_31);

    CHECK(mat(0, 2) == mat_02);
    CHECK(mat(1, 2) == mat_12);
    CHECK(mat(2, 2) == mat_22);
    CHECK(mat(3, 2) == mat_32);

    CHECK(mat(0, 3) == mat_03);
    CHECK(mat(1, 3) == mat_13);
    CHECK(mat(2, 3) == mat_23);
    CHECK(mat(3, 3) == mat_33);

    // clang-format off
    Matrix<TestType, 4, 4> mat2;
    mat2(0, 0) = mat_00; mat2(0, 1) = mat_01; mat2(0, 2) = mat_02; mat2(0, 3) = mat_03;
    mat2(1, 0) = mat_10; mat2(1, 1) = mat_11; mat2(1, 2) = mat_12; mat2(1, 3) = mat_13;
    mat2(2, 0) = mat_20; mat2(2, 1) = mat_21; mat2(2, 2) = mat_22; mat2(2, 3) = mat_23;
    mat2(3, 0) = mat_30; mat2(3, 1) = mat_31; mat2(3, 2) = mat_32; mat2(3, 3) = mat_33;
    // clang-format on

    CHECK(mat2(0, 0) == mat_00);
    CHECK(mat2(1, 0) == mat_10);
    CHECK(mat2(2, 0) == mat_20);
    CHECK(mat2(3, 0) == mat_30);

    CHECK(mat2(0, 1) == mat_01);
    CHECK(mat2(1, 1) == mat_11);
    CHECK(mat2(2, 1) == mat_21);
    CHECK(mat2(3, 1) == mat_31);

    CHECK(mat2(0, 2) == mat_02);
    CHECK(mat2(1, 2) == mat_12);
    CHECK(mat2(2, 2) == mat_22);
    CHECK(mat2(3, 2) == mat_32);

    CHECK(mat2(0, 3) == mat_03);
    CHECK(mat2(1, 3) == mat_13);
    CHECK(mat2(2, 3) == mat_23);
    CHECK(mat2(3, 3) == mat_33);

    CHECK_THROWS(mat2(4, 0));
    CHECK_THROWS(mat2(0, 4));
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim4][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  100.1, mat_01 =  101.2, mat_02 = -102.3, mat_03 = -103.4,
                       mat_10 = -110.1, mat_11 = -111.2, mat_12 = -112.3, mat_13 =  113.4,
                       mat_20 =  120.1, mat_21 =  121.2, mat_22 = -122.3, mat_23 =  123.4,
                       mat_30 =  130.1, mat_31 =  131.2, mat_32 = -132.3, mat_33 =  133.4;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03, 
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };
    // clang-format on
    static_assert(mat(0, 0) == mat_00);
    static_assert(mat(1, 0) == mat_10);
    static_assert(mat(2, 0) == mat_20);
    static_assert(mat(3, 0) == mat_30);

    static_assert(mat(0, 1) == mat_01);
    static_assert(mat(1, 1) == mat_11);
    static_assert(mat(2, 1) == mat_21);
    static_assert(mat(3, 1) == mat_31);

    static_assert(mat(0, 2) == mat_02);
    static_assert(mat(1, 2) == mat_12);
    static_assert(mat(2, 2) == mat_22);
    static_assert(mat(3, 2) == mat_32);

    static_assert(mat(0, 3) == mat_03);
    static_assert(mat(1, 3) == mat_13);
    static_assert(mat(2, 3) == mat_23);
    static_assert(mat(3, 3) == mat_33);

    CHECK(mat(0, 0) == mat_00);
    CHECK(mat(1, 0) == mat_10);
    CHECK(mat(2, 0) == mat_20);
    CHECK(mat(3, 0) == mat_30);

    CHECK(mat(0, 1) == mat_01);
    CHECK(mat(1, 1) == mat_11);
    CHECK(mat(2, 1) == mat_21);
    CHECK(mat(3, 1) == mat_31);

    CHECK(mat(0, 2) == mat_02);
    CHECK(mat(1, 2) == mat_12);
    CHECK(mat(2, 2) == mat_22);
    CHECK(mat(3, 2) == mat_32);

    CHECK(mat(0, 3) == mat_03);
    CHECK(mat(1, 3) == mat_13);
    CHECK(mat(2, 3) == mat_23);
    CHECK(mat(3, 3) == mat_33);

    // clang-format off
    Matrix<TestType, 4, 4> mat2;
    mat2(0, 0) = mat_00; mat2(0, 1) = mat_01; mat2(0, 2) = mat_02; mat2(0, 3) = mat_03;
    mat2(1, 0) = mat_10; mat2(1, 1) = mat_11; mat2(1, 2) = mat_12; mat2(1, 3) = mat_13;
    mat2(2, 0) = mat_20; mat2(2, 1) = mat_21; mat2(2, 2) = mat_22; mat2(2, 3) = mat_23;
    mat2(3, 0) = mat_30; mat2(3, 1) = mat_31; mat2(3, 2) = mat_32; mat2(3, 3) = mat_33;
    // clang-format on

    CHECK(mat2(0, 0) == mat_00);
    CHECK(mat2(1, 0) == mat_10);
    CHECK(mat2(2, 0) == mat_20);
    CHECK(mat2(3, 0) == mat_30);

    CHECK(mat2(0, 1) == mat_01);
    CHECK(mat2(1, 1) == mat_11);
    CHECK(mat2(2, 1) == mat_21);
    CHECK(mat2(3, 1) == mat_31);

    CHECK(mat2(0, 2) == mat_02);
    CHECK(mat2(1, 2) == mat_12);
    CHECK(mat2(2, 2) == mat_22);
    CHECK(mat2(3, 2) == mat_32);

    CHECK(mat2(0, 3) == mat_03);
    CHECK(mat2(1, 3) == mat_13);
    CHECK(mat2(2, 3) == mat_23);
    CHECK(mat2(3, 3) == mat_33);

    CHECK_THROWS(mat2(4, 0));
    CHECK_THROWS(mat2(0, 4));
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dim4][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Matrix<TestType, 4, 4> mat;

    static_assert(mat(0, 0) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(2, 0) == zero);
    static_assert(mat(3, 0) == zero);

    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 1) == zero);
    static_assert(mat(2, 1) == zero);
    static_assert(mat(3, 1) == zero);

    static_assert(mat(0, 2) == zero);
    static_assert(mat(1, 2) == zero);
    static_assert(mat(2, 2) == zero);
    static_assert(mat(3, 2) == zero);

    static_assert(mat(0, 3) == zero);
    static_assert(mat(1, 3) == zero);
    static_assert(mat(2, 3) == zero);
    static_assert(mat(3, 3) == zero);

    CHECK(mat(0, 0) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(2, 0) == zero);
    CHECK(mat(3, 0) == zero);

    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 1) == zero);
    CHECK(mat(2, 1) == zero);
    CHECK(mat(3, 1) == zero);

    CHECK(mat(0, 2) == zero);
    CHECK(mat(1, 2) == zero);
    CHECK(mat(2, 2) == zero);
    CHECK(mat(3, 2) == zero);

    CHECK(mat(0, 3) == zero);
    CHECK(mat(1, 3) == zero);
    CHECK(mat(2, 3) == zero);
    CHECK(mat(3, 3) == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dim4][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Matrix<TestType, 4, 4> mat;

    static_assert(mat(0, 0) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(2, 0) == zero);
    static_assert(mat(3, 0) == zero);

    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 1) == zero);
    static_assert(mat(2, 1) == zero);
    static_assert(mat(3, 1) == zero);

    static_assert(mat(0, 2) == zero);
    static_assert(mat(1, 2) == zero);
    static_assert(mat(2, 2) == zero);
    static_assert(mat(3, 2) == zero);

    static_assert(mat(0, 3) == zero);
    static_assert(mat(1, 3) == zero);
    static_assert(mat(2, 3) == zero);
    static_assert(mat(3, 3) == zero);

    CHECK(mat(0, 0) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(2, 0) == zero);
    CHECK(mat(3, 0) == zero);

    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 1) == zero);
    CHECK(mat(2, 1) == zero);
    CHECK(mat(3, 1) == zero);

    CHECK(mat(0, 2) == zero);
    CHECK(mat(1, 2) == zero);
    CHECK(mat(2, 2) == zero);
    CHECK(mat(3, 2) == zero);

    CHECK(mat(0, 3) == zero);
    CHECK(mat(1, 3) == zero);
    CHECK(mat(2, 3) == zero);
    CHECK(mat(3, 3) == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dim4][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;
    constexpr TestType one  = 1;

    constexpr Matrix<TestType, 4, 4> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(2, 0) == zero);
    static_assert(mat(3, 0) == zero);

    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 1) == one);
    static_assert(mat(2, 1) == zero);
    static_assert(mat(3, 1) == zero);

    static_assert(mat(0, 2) == zero);
    static_assert(mat(1, 2) == zero);
    static_assert(mat(2, 2) == one);
    static_assert(mat(3, 2) == zero);

    static_assert(mat(0, 3) == zero);
    static_assert(mat(1, 3) == zero);
    static_assert(mat(2, 3) == zero);
    static_assert(mat(3, 3) == one);

    CHECK(mat(0, 0) == one);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(2, 0) == zero);
    CHECK(mat(3, 0) == zero);

    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 1) == one);
    CHECK(mat(2, 1) == zero);
    CHECK(mat(3, 1) == zero);

    CHECK(mat(0, 2) == zero);
    CHECK(mat(1, 2) == zero);
    CHECK(mat(2, 2) == one);
    CHECK(mat(3, 2) == zero);

    CHECK(mat(0, 3) == zero);
    CHECK(mat(1, 3) == zero);
    CHECK(mat(2, 3) == zero);
    CHECK(mat(3, 3) == one);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dim4][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;
    constexpr TestType one  = 1.0;

    constexpr Matrix<TestType, 4, 4> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(2, 0) == zero);
    static_assert(mat(3, 0) == zero);

    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 1) == one);
    static_assert(mat(2, 1) == zero);
    static_assert(mat(3, 1) == zero);

    static_assert(mat(0, 2) == zero);
    static_assert(mat(1, 2) == zero);
    static_assert(mat(2, 2) == one);
    static_assert(mat(3, 2) == zero);

    static_assert(mat(0, 3) == zero);
    static_assert(mat(1, 3) == zero);
    static_assert(mat(2, 3) == zero);
    static_assert(mat(3, 3) == one);


    CHECK(mat(0, 0) == one);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(2, 0) == zero);
    CHECK(mat(3, 0) == zero);

    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 1) == one);
    CHECK(mat(2, 1) == zero);
    CHECK(mat(3, 1) == zero);

    CHECK(mat(0, 2) == zero);
    CHECK(mat(1, 2) == zero);
    CHECK(mat(2, 2) == one);
    CHECK(mat(3, 2) == zero);

    CHECK(mat(0, 3) == zero);
    CHECK(mat(1, 3) == zero);
    CHECK(mat(2, 3) == zero);
    CHECK(mat(3, 3) == one);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][matrix][dim4][constructor]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 0, mat_01 = -1, mat_02 = -9, mat_03 =  5,
                       mat_10 = 3, mat_11 =  2, mat_12 = -1, mat_13 = -8,
                       mat_20 = 4, mat_21 =  2, mat_22 =  0, mat_23 =  5,
                       mat_30 = 1, mat_31 =  2, mat_32 =  7, mat_33 =  5;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03, 
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };
    // clang-format on

    static_assert(mat(0, 0) == mat_00);
    static_assert(mat(1, 0) == mat_10);
    static_assert(mat(2, 0) == mat_20);
    static_assert(mat(3, 0) == mat_30);

    static_assert(mat(0, 1) == mat_01);
    static_assert(mat(1, 1) == mat_11);
    static_assert(mat(2, 1) == mat_21);
    static_assert(mat(3, 1) == mat_31);

    static_assert(mat(0, 2) == mat_02);
    static_assert(mat(1, 2) == mat_12);
    static_assert(mat(2, 2) == mat_22);
    static_assert(mat(3, 2) == mat_32);

    static_assert(mat(0, 3) == mat_03);
    static_assert(mat(1, 3) == mat_13);
    static_assert(mat(2, 3) == mat_23);
    static_assert(mat(3, 3) == mat_33);

    CHECK(mat(0, 0) == mat_00);
    CHECK(mat(1, 0) == mat_10);
    CHECK(mat(2, 0) == mat_20);
    CHECK(mat(3, 0) == mat_30);

    CHECK(mat(0, 1) == mat_01);
    CHECK(mat(1, 1) == mat_11);
    CHECK(mat(2, 1) == mat_21);
    CHECK(mat(3, 1) == mat_31);

    CHECK(mat(0, 2) == mat_02);
    CHECK(mat(1, 2) == mat_12);
    CHECK(mat(2, 2) == mat_22);
    CHECK(mat(3, 2) == mat_32);

    CHECK(mat(0, 3) == mat_03);
    CHECK(mat(1, 3) == mat_13);
    CHECK(mat(2, 3) == mat_23);
    CHECK(mat(3, 3) == mat_33);

    CHECK_NOTHROW(Matrix<TestType, 4, 4>({}));
    CHECK_NOTHROW(Matrix<TestType, 4, 4>({ mat_00, mat_01, mat_02, mat_03 }));

    // clang-format off
    CHECK_THROWS(Matrix<TestType, 4, 4>({ mat_00, mat_01, mat_02, mat_03,
                                          mat_10, mat_11, mat_12, mat_13,
                                          mat_20, mat_21, mat_22, mat_23,
                                          mat_30, mat_31, mat_32, mat_33,
                                          mat_30, mat_31, mat_32, mat_33 }));
    // clang-format on
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][matrix][dim4][constructor]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 0.88, mat_01 = -1.98, mat_02 = -9.88, mat_03 =  5.68,
                       mat_10 = 3.23, mat_11 =  2.45, mat_12 = -1.25, mat_13 = -8.46,
                       mat_20 = 4.74, mat_21 =  2.37, mat_22 =  0.36, mat_23 =  5.72,
                       mat_30 = 1.12, mat_31 =  2.11, mat_32 =  7.94, mat_33 =  5.97;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };
    // clang-format on

    static_assert(mat(0, 0) == mat_00);
    static_assert(mat(1, 0) == mat_10);
    static_assert(mat(2, 0) == mat_20);
    static_assert(mat(3, 0) == mat_30);

    static_assert(mat(0, 1) == mat_01);
    static_assert(mat(1, 1) == mat_11);
    static_assert(mat(2, 1) == mat_21);
    static_assert(mat(3, 1) == mat_31);

    static_assert(mat(0, 2) == mat_02);
    static_assert(mat(1, 2) == mat_12);
    static_assert(mat(2, 2) == mat_22);
    static_assert(mat(3, 2) == mat_32);

    static_assert(mat(0, 3) == mat_03);
    static_assert(mat(1, 3) == mat_13);
    static_assert(mat(2, 3) == mat_23);
    static_assert(mat(3, 3) == mat_33);

    CHECK(mat(0, 0) == mat_00);
    CHECK(mat(1, 0) == mat_10);
    CHECK(mat(2, 0) == mat_20);
    CHECK(mat(3, 0) == mat_30);

    CHECK(mat(0, 1) == mat_01);
    CHECK(mat(1, 1) == mat_11);
    CHECK(mat(2, 1) == mat_21);
    CHECK(mat(3, 1) == mat_31);

    CHECK(mat(0, 2) == mat_02);
    CHECK(mat(1, 2) == mat_12);
    CHECK(mat(2, 2) == mat_22);
    CHECK(mat(3, 2) == mat_32);

    CHECK(mat(0, 3) == mat_03);
    CHECK(mat(1, 3) == mat_13);
    CHECK(mat(2, 3) == mat_23);
    CHECK(mat(3, 3) == mat_33);

    CHECK_NOTHROW(Matrix<TestType, 4, 4>({}));
    CHECK_NOTHROW(Matrix<TestType, 4, 4>({ mat_00, mat_01, mat_02, mat_03 }));

    // clang-format off
    CHECK_THROWS(Matrix<TestType, 4, 4>({ mat_00, mat_01, mat_02, mat_03,
                                          mat_10, mat_11, mat_12, mat_13,
                                          mat_20, mat_21, mat_22, mat_23,
                                          mat_30, mat_31, mat_32, mat_33,
                                          mat_30, mat_31, mat_32, mat_33 }));
    // clang-format on
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dim4][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  98, mat_01 = -56, mat_02 = -97, mat_03 =  55,
                       mat_10 = -45, mat_11 =  23, mat_12 = -45, mat_13 = -88,
                       mat_20 =  78, mat_21 =  23, mat_22 =  20, mat_23 =  55,
                       mat_30 =  12, mat_31 =  23, mat_32 =  70, mat_33 =  55;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };
    // clang-format on

    constexpr auto copy1(mat);

    static_assert(mat(0, 0) == copy1(0, 0));
    static_assert(mat(1, 0) == copy1(1, 0));
    static_assert(mat(2, 0) == copy1(2, 0));
    static_assert(mat(3, 0) == copy1(3, 0));

    static_assert(mat(0, 1) == copy1(0, 1));
    static_assert(mat(1, 1) == copy1(1, 1));
    static_assert(mat(2, 1) == copy1(2, 1));
    static_assert(mat(3, 1) == copy1(3, 1));

    static_assert(mat(0, 2) == copy1(0, 2));
    static_assert(mat(1, 2) == copy1(1, 2));
    static_assert(mat(2, 2) == copy1(2, 2));
    static_assert(mat(3, 2) == copy1(3, 2));

    static_assert(mat(0, 3) == copy1(0, 3));
    static_assert(mat(1, 3) == copy1(1, 3));
    static_assert(mat(2, 3) == copy1(2, 3));
    static_assert(mat(3, 3) == copy1(3, 3));

    CHECK(mat(0, 0) == copy1(0, 0));
    CHECK(mat(1, 0) == copy1(1, 0));
    CHECK(mat(2, 0) == copy1(2, 0));
    CHECK(mat(3, 0) == copy1(3, 0));

    CHECK(mat(0, 1) == copy1(0, 1));
    CHECK(mat(1, 1) == copy1(1, 1));
    CHECK(mat(2, 1) == copy1(2, 1));
    CHECK(mat(3, 1) == copy1(3, 1));


    CHECK(mat(0, 2) == copy1(0, 2));
    CHECK(mat(1, 2) == copy1(1, 2));
    CHECK(mat(2, 2) == copy1(2, 2));
    CHECK(mat(3, 2) == copy1(3, 2));

    CHECK(mat(0, 3) == copy1(0, 3));
    CHECK(mat(1, 3) == copy1(1, 3));
    CHECK(mat(2, 3) == copy1(2, 3));
    CHECK(mat(3, 3) == copy1(3, 3));

    constexpr auto copy2 = mat;

    static_assert(mat(0, 0) == copy2(0, 0));
    static_assert(mat(1, 0) == copy2(1, 0));
    static_assert(mat(2, 0) == copy2(2, 0));
    static_assert(mat(3, 0) == copy2(3, 0));

    static_assert(mat(0, 1) == copy2(0, 1));
    static_assert(mat(1, 1) == copy2(1, 1));
    static_assert(mat(2, 1) == copy2(2, 1));
    static_assert(mat(3, 1) == copy2(3, 1));

    static_assert(mat(0, 2) == copy2(0, 2));
    static_assert(mat(1, 2) == copy2(1, 2));
    static_assert(mat(2, 2) == copy2(2, 2));
    static_assert(mat(3, 2) == copy2(3, 2));

    static_assert(mat(0, 3) == copy2(0, 3));
    static_assert(mat(1, 3) == copy2(1, 3));
    static_assert(mat(2, 3) == copy2(2, 3));
    static_assert(mat(3, 3) == copy2(3, 3));

    CHECK(mat(0, 0) == copy2(0, 0));
    CHECK(mat(1, 0) == copy2(1, 0));
    CHECK(mat(2, 0) == copy2(2, 0));
    CHECK(mat(3, 0) == copy2(3, 0));

    CHECK(mat(0, 1) == copy2(0, 1));
    CHECK(mat(1, 1) == copy2(1, 1));
    CHECK(mat(2, 1) == copy2(2, 1));
    CHECK(mat(3, 1) == copy2(3, 1));

    CHECK(mat(0, 2) == copy2(0, 2));
    CHECK(mat(1, 2) == copy2(1, 2));
    CHECK(mat(2, 2) == copy2(2, 2));
    CHECK(mat(3, 2) == copy2(3, 2));

    CHECK(mat(0, 3) == copy2(0, 3));
    CHECK(mat(1, 3) == copy2(1, 3));
    CHECK(mat(2, 3) == copy2(2, 3));
    CHECK(mat(3, 3) == copy2(3, 3));
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dim4][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  98.56, mat_01 = -56.98, mat_02 = -97.55, mat_03 =  55.97,
                       mat_10 =  45.23, mat_11 =  23.45, mat_12 = -45.88, mat_13 = -88.45,
                       mat_20 =  78.23, mat_21 = -23.78, mat_22 =  20.55, mat_23 =  55.20,
                       mat_30 = -12.23, mat_31 =  23.12, mat_32 =  70.55, mat_33 =  55.70;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };
    // clang-format on

    constexpr auto copy1(mat);

    static_assert(mat(0, 0) == copy1(0, 0));
    static_assert(mat(1, 0) == copy1(1, 0));
    static_assert(mat(2, 0) == copy1(2, 0));
    static_assert(mat(3, 0) == copy1(3, 0));

    static_assert(mat(0, 1) == copy1(0, 1));
    static_assert(mat(1, 1) == copy1(1, 1));
    static_assert(mat(2, 1) == copy1(2, 1));
    static_assert(mat(3, 1) == copy1(3, 1));

    static_assert(mat(0, 2) == copy1(0, 2));
    static_assert(mat(1, 2) == copy1(1, 2));
    static_assert(mat(2, 2) == copy1(2, 2));
    static_assert(mat(3, 2) == copy1(3, 2));

    static_assert(mat(0, 3) == copy1(0, 3));
    static_assert(mat(1, 3) == copy1(1, 3));
    static_assert(mat(2, 3) == copy1(2, 3));
    static_assert(mat(3, 3) == copy1(3, 3));

    CHECK(mat(0, 0) == copy1(0, 0));
    CHECK(mat(1, 0) == copy1(1, 0));
    CHECK(mat(2, 0) == copy1(2, 0));
    CHECK(mat(3, 0) == copy1(3, 0));

    CHECK(mat(0, 1) == copy1(0, 1));
    CHECK(mat(1, 1) == copy1(1, 1));
    CHECK(mat(2, 1) == copy1(2, 1));
    CHECK(mat(3, 1) == copy1(3, 1));

    CHECK(mat(0, 2) == copy1(0, 2));
    CHECK(mat(1, 2) == copy1(1, 2));
    CHECK(mat(2, 2) == copy1(2, 2));
    CHECK(mat(3, 2) == copy1(3, 2));

    CHECK(mat(0, 3) == copy1(0, 3));
    CHECK(mat(1, 3) == copy1(1, 3));
    CHECK(mat(2, 3) == copy1(2, 3));
    CHECK(mat(3, 3) == copy1(3, 3));

    constexpr auto copy2 = mat;

    static_assert(mat(0, 0) == copy2(0, 0));
    static_assert(mat(1, 0) == copy2(1, 0));
    static_assert(mat(2, 0) == copy2(2, 0));
    static_assert(mat(3, 0) == copy2(3, 0));

    static_assert(mat(0, 1) == copy2(0, 1));
    static_assert(mat(1, 1) == copy2(1, 1));
    static_assert(mat(2, 1) == copy2(2, 1));
    static_assert(mat(3, 1) == copy2(3, 1));

    static_assert(mat(0, 2) == copy2(0, 2));
    static_assert(mat(1, 2) == copy2(1, 2));
    static_assert(mat(2, 2) == copy2(2, 2));
    static_assert(mat(3, 2) == copy2(3, 2));

    static_assert(mat(0, 3) == copy2(0, 3));
    static_assert(mat(1, 3) == copy2(1, 3));
    static_assert(mat(2, 3) == copy2(2, 3));
    static_assert(mat(3, 3) == copy2(3, 3));

    CHECK(mat(0, 0) == copy2(0, 0));
    CHECK(mat(1, 0) == copy2(1, 0));
    CHECK(mat(2, 0) == copy2(2, 0));
    CHECK(mat(3, 0) == copy2(3, 0));

    CHECK(mat(0, 1) == copy2(0, 1));
    CHECK(mat(1, 1) == copy2(1, 1));
    CHECK(mat(2, 1) == copy2(2, 1));
    CHECK(mat(3, 1) == copy2(3, 1));

    CHECK(mat(0, 2) == copy2(0, 2));
    CHECK(mat(1, 2) == copy2(1, 2));
    CHECK(mat(2, 2) == copy2(2, 2));
    CHECK(mat(3, 2) == copy2(3, 2));

    CHECK(mat(0, 3) == copy2(0, 3));
    CHECK(mat(1, 3) == copy2(1, 3));
    CHECK(mat(2, 3) == copy2(2, 3));
    CHECK(mat(3, 3) == copy2(3, 3));
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dim4][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  19, mat_01 = -56, mat_02 = -97, mat_03 = -95,
                       mat_10 = -56, mat_11 =  23, mat_12 = -45, mat_13 = -88,
                       mat_20 =  78, mat_21 =  98, mat_22 = 456, mat_23 =  55,
                       mat_30 =  23, mat_31 = 687, mat_32 =  70, mat_33 = 222;

    constexpr auto getMatrix = [=]()
    {
        return Matrix<TestType, 4, 4>({ mat_00, mat_01, mat_02, mat_03,
                                        mat_10, mat_11, mat_12, mat_13,
                                        mat_20, mat_21, mat_22, mat_23,
                                        mat_30, mat_31, mat_32, mat_33 });
    };
    // clang-format on

    constexpr auto copy1(getMatrix());

    static_assert(copy1(0, 0) == mat_00);
    static_assert(copy1(1, 0) == mat_10);
    static_assert(copy1(2, 0) == mat_20);
    static_assert(copy1(3, 0) == mat_30);

    static_assert(copy1(0, 1) == mat_01);
    static_assert(copy1(1, 1) == mat_11);
    static_assert(copy1(2, 1) == mat_21);
    static_assert(copy1(3, 1) == mat_31);

    static_assert(copy1(0, 2) == mat_02);
    static_assert(copy1(1, 2) == mat_12);
    static_assert(copy1(2, 2) == mat_22);
    static_assert(copy1(3, 2) == mat_32);

    static_assert(copy1(0, 3) == mat_03);
    static_assert(copy1(1, 3) == mat_13);
    static_assert(copy1(2, 3) == mat_23);
    static_assert(copy1(3, 3) == mat_33);

    CHECK(copy1(0, 0) == mat_00);
    CHECK(copy1(1, 0) == mat_10);
    CHECK(copy1(2, 0) == mat_20);
    CHECK(copy1(3, 0) == mat_30);

    CHECK(copy1(0, 1) == mat_01);
    CHECK(copy1(1, 1) == mat_11);
    CHECK(copy1(2, 1) == mat_21);
    CHECK(copy1(3, 1) == mat_31);

    CHECK(copy1(0, 2) == mat_02);
    CHECK(copy1(1, 2) == mat_12);
    CHECK(copy1(2, 2) == mat_22);
    CHECK(copy1(3, 2) == mat_32);

    CHECK(copy1(0, 3) == mat_03);
    CHECK(copy1(1, 3) == mat_13);
    CHECK(copy1(2, 3) == mat_23);
    CHECK(copy1(3, 3) == mat_33);

    constexpr auto copy2 = getMatrix();

    static_assert(copy2(0, 0) == mat_00);
    static_assert(copy2(1, 0) == mat_10);
    static_assert(copy2(2, 0) == mat_20);
    static_assert(copy2(3, 0) == mat_30);

    static_assert(copy2(0, 1) == mat_01);
    static_assert(copy2(1, 1) == mat_11);
    static_assert(copy2(2, 1) == mat_21);
    static_assert(copy2(3, 1) == mat_31);

    static_assert(copy2(0, 2) == mat_02);
    static_assert(copy2(1, 2) == mat_12);
    static_assert(copy2(2, 2) == mat_22);
    static_assert(copy2(3, 2) == mat_32);

    static_assert(copy2(0, 3) == mat_03);
    static_assert(copy2(1, 3) == mat_13);
    static_assert(copy2(2, 3) == mat_23);
    static_assert(copy2(3, 3) == mat_33);

    CHECK(copy2(0, 0) == mat_00);
    CHECK(copy2(1, 0) == mat_10);
    CHECK(copy2(2, 0) == mat_20);
    CHECK(copy2(3, 0) == mat_30);

    CHECK(copy2(0, 1) == mat_01);
    CHECK(copy2(1, 1) == mat_11);
    CHECK(copy2(2, 1) == mat_21);
    CHECK(copy2(3, 1) == mat_31);

    CHECK(copy2(0, 2) == mat_02);
    CHECK(copy2(1, 2) == mat_12);
    CHECK(copy2(2, 2) == mat_22);
    CHECK(copy2(3, 2) == mat_32);

    CHECK(copy2(0, 3) == mat_03);
    CHECK(copy2(1, 3) == mat_13);
    CHECK(copy2(2, 3) == mat_23);
    CHECK(copy2(3, 3) == mat_33);
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dim4][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 6405.1, mat_01 = 5630.7, mat_02 = -97.79, mat_03 = 95.659,
                       mat_10 = -563.9, mat_11 = -23.74, mat_12 = 45.028, mat_13 = -88.34,
                       mat_20 = 789.99, mat_21 = -98.22, mat_22 = 4563.3, mat_23 = -57.14,
                       mat_30 = 223.80, mat_31 = 687.25, mat_32 = -70.05, mat_33 = 222.20;

    constexpr auto getMatrix = [=]()
    {
        return Matrix<TestType, 4, 4>({ mat_00, mat_01, mat_02, mat_03, 
                                        mat_10, mat_11, mat_12, mat_13,
                                        mat_20, mat_21, mat_22, mat_23,
                                        mat_30, mat_31, mat_32, mat_33 });
    };
    // clang-format on

    constexpr auto copy1(getMatrix());

    static_assert(copy1(0, 0) == mat_00);
    static_assert(copy1(1, 0) == mat_10);
    static_assert(copy1(2, 0) == mat_20);
    static_assert(copy1(3, 0) == mat_30);

    static_assert(copy1(0, 1) == mat_01);
    static_assert(copy1(1, 1) == mat_11);
    static_assert(copy1(2, 1) == mat_21);
    static_assert(copy1(3, 1) == mat_31);

    static_assert(copy1(0, 2) == mat_02);
    static_assert(copy1(1, 2) == mat_12);
    static_assert(copy1(2, 2) == mat_22);
    static_assert(copy1(3, 2) == mat_32);

    static_assert(copy1(0, 3) == mat_03);
    static_assert(copy1(1, 3) == mat_13);
    static_assert(copy1(2, 3) == mat_23);
    static_assert(copy1(3, 3) == mat_33);

    CHECK(copy1(0, 0) == mat_00);
    CHECK(copy1(1, 0) == mat_10);
    CHECK(copy1(2, 0) == mat_20);
    CHECK(copy1(3, 0) == mat_30);

    CHECK(copy1(0, 1) == mat_01);
    CHECK(copy1(1, 1) == mat_11);
    CHECK(copy1(2, 1) == mat_21);
    CHECK(copy1(3, 1) == mat_31);

    CHECK(copy1(0, 2) == mat_02);
    CHECK(copy1(1, 2) == mat_12);
    CHECK(copy1(2, 2) == mat_22);
    CHECK(copy1(3, 2) == mat_32);

    CHECK(copy1(0, 3) == mat_03);
    CHECK(copy1(1, 3) == mat_13);
    CHECK(copy1(2, 3) == mat_23);
    CHECK(copy1(3, 3) == mat_33);

    constexpr auto copy2 = getMatrix();

    static_assert(copy2(0, 0) == mat_00);
    static_assert(copy2(1, 0) == mat_10);
    static_assert(copy2(2, 0) == mat_20);
    static_assert(copy2(3, 0) == mat_30);

    static_assert(copy2(0, 1) == mat_01);
    static_assert(copy2(1, 1) == mat_11);
    static_assert(copy2(2, 1) == mat_21);
    static_assert(copy2(3, 1) == mat_31);

    static_assert(copy2(0, 2) == mat_02);
    static_assert(copy2(1, 2) == mat_12);
    static_assert(copy2(2, 2) == mat_22);
    static_assert(copy2(3, 2) == mat_32);

    static_assert(copy2(0, 3) == mat_03);
    static_assert(copy2(1, 3) == mat_13);
    static_assert(copy2(2, 3) == mat_23);
    static_assert(copy2(3, 3) == mat_33);

    CHECK(copy2(0, 0) == mat_00);
    CHECK(copy2(1, 0) == mat_10);
    CHECK(copy2(2, 0) == mat_20);
    CHECK(copy2(3, 0) == mat_30);

    CHECK(copy2(0, 1) == mat_01);
    CHECK(copy2(1, 1) == mat_11);
    CHECK(copy2(2, 1) == mat_21);
    CHECK(copy2(3, 1) == mat_31);

    CHECK(copy2(0, 2) == mat_02);
    CHECK(copy2(1, 2) == mat_12);
    CHECK(copy2(2, 2) == mat_22);
    CHECK(copy2(3, 2) == mat_32);

    CHECK(copy2(0, 3) == mat_03);
    CHECK(copy2(1, 3) == mat_13);
    CHECK(copy2(2, 3) == mat_23);
    CHECK(copy2(3, 3) == mat_33);
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim4][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  19, mat_01 = -56, mat_02 = -97, mat_03 = -95,
              mat_10 = -56, mat_11 =  23, mat_12 = -45, mat_13 = -88,
              mat_20 =  78, mat_21 =  98, mat_22 = 456, mat_23 =  55,
              mat_30 =  23, mat_31 = 687, mat_32 =  70, mat_33 = 222;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };

    constexpr Matrix<TestType, 4, 4> identical = { mat_00, mat_01, mat_02, mat_03,
                                                   mat_10, mat_11, mat_12, mat_13,
                                                   mat_20, mat_21, mat_22, mat_23,
                                                   mat_30, mat_31, mat_32, mat_33 };

    constexpr Matrix<TestType, 4, 4> different = {      0, mat_01, mat_02, mat_03,
                                                   mat_10, mat_11, mat_12, mat_13,
                                                   mat_20, mat_21, mat_22, mat_23,
                                                   mat_30, mat_31, mat_32, mat_33 };
    // clang-format on

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            Matrix<TestType, 4, 4> diff = mat;
            diff(i, j)                  = 0;

            CHECK(mat != diff);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim4][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 6405.1, mat_01 = 5630.7, mat_02 = -97.79, mat_03 = 95.659,
                       mat_10 = -563.9, mat_11 = -23.74, mat_12 = 45.028, mat_13 = -88.34,
                       mat_20 = 789.99, mat_21 = -98.22, mat_22 = 4563.3, mat_23 = -57.14,
                       mat_30 = 223.80, mat_31 = 687.25, mat_32 = -70.05, mat_33 = 222.20;

    constexpr Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };

    constexpr Matrix<TestType, 4, 4> identical = { mat_00, mat_01, mat_02, mat_03,
                                                   mat_10, mat_11, mat_12, mat_13,
                                                   mat_20, mat_21, mat_22, mat_23,
                                                   mat_30, mat_31, mat_32, mat_33 };

    constexpr Matrix<TestType, 4, 4> different = {      0, mat_01, mat_02, mat_03,
                                                   mat_10, mat_11, mat_12, mat_13,
                                                   mat_20, mat_21, mat_22, mat_23,
                                                   mat_30, mat_31, mat_32, mat_33 };
    // clang-format on

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            Matrix<TestType, 4, 4> diff = mat;
            diff(i, j)                  = 0;

            CHECK(mat != diff);
        }
    }
}


TEMPLATE_LIST_TEST_CASE("Determinant", "[algebra][matrix][dim4][method]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat1_00 =  4.0, mat1_01 = -5.1, mat1_02 = -9.9, mat1_03 =  5.5,
                       mat1_10 = -8.3, mat1_11 =  4.2, mat1_12 = -1.1, mat1_13 = -9.8,
                       mat1_20 =  6.4, mat1_21 =  3.2, mat1_22 =  7.0, mat1_23 =  7.5,
                       mat1_30 = -9.1, mat1_31 =  7.2, mat1_32 =  8.7, mat1_33 =  5.5;

    constexpr Matrix<TestType, 4, 4> mat1 = { mat1_00, mat1_01, mat1_02, mat1_03, 
                                              mat1_10, mat1_11, mat1_12, mat1_13,
                                              mat1_20, mat1_21, mat1_22, mat1_23,
                                              mat1_30, mat1_31, mat1_32, mat1_33 };

    constexpr TestType det1 = mat1.determinant();

    static_assert(std::abs(det1 - 6810.0026) < 0.002); // Can't get a better precision than 0.002 with float

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(det1 == Catch::Approx(6810.0026).epsilon(ehp));
    // clang-format on
}

TEMPLATE_LIST_TEST_CASE("Transpose", "[algebra][matrix][dim4][method]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 1.0, mat1_01 = 2.0, mat1_02 = 3.0, mat1_03 = 4.0,
                       mat1_10 = 5.0, mat1_11 = 6.0, mat1_12 = 7.0, mat1_13 = 8.0,
                       mat1_20 = 9.0, mat1_21 = 10., mat1_22 = 11., mat1_23 = 12.,
                       mat1_30 = 13., mat1_31 = 14., mat1_32 = 15., mat1_33 = 16.;

    Matrix<TestType, 4, 4> mat1 = { mat1_00, mat1_01, mat1_02, mat1_03, 
                                    mat1_10, mat1_11, mat1_12, mat1_13,
                                    mat1_20, mat1_21, mat1_22, mat1_23,
                                    mat1_30, mat1_31, mat1_32, mat1_33 };

    std::cout << "mat is \n" << mat1 << '\n';
    mat1.transpose();
    std::cout << "mat transpose is \n" << mat1 << '\n';
    // clang-format on

    Matrix<TestType, 3, 4> test = { mat1_00, mat1_01, mat1_02, mat1_03, mat1_10, mat1_11, mat1_12, mat1_13, mat1_20, mat1_21, mat1_22, mat1_23 };

    std::cout << "Rectangular matrix  is \n" << test << '\n';

    std::cout << "mat transpose is \n" << test.transposed() << '\n';
}

TEMPLATE_LIST_TEST_CASE("Inverse", "[algebra][matrix][dim4][method]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  4.0, mat_01 = -5.1, mat_02 = -9.9, mat_03 =  5.5,
                       mat_10 = -8.3, mat_11 =  4.2, mat_12 = -1.1, mat_13 = -9.8,
                       mat_20 =  6.4, mat_21 =  3.2, mat_22 =  7.0, mat_23 =  7.5,
                       mat_30 = -9.1, mat_31 =  7.2, mat_32 =  8.7, mat_33 =  5.5;

    Matrix<TestType, 4, 4> mat = { mat_00, mat_01, mat_02, mat_03, 
                                   mat_10, mat_11, mat_12, mat_13,
                                   mat_20, mat_21, mat_22, mat_23,
                                   mat_30, mat_31, mat_32, mat_33 };

    mat.inverse();

    constexpr auto elp = epsilonLowPrecision<TestType>();

    CHECK(std::abs(mat(0,0) -  0.0100878)  < elp);
    CHECK(std::abs(mat(1,0) -  0.122482)   < elp);
    CHECK(std::abs(mat(2,0) - -0.127655)   < elp);
    CHECK(std::abs(mat(3,0) -  0.0582772)  < elp);

    CHECK(std::abs(mat(0,1) -  0.0511035)  < elp);
    CHECK(std::abs(mat(1,1) -  0.231093)   < elp);
    CHECK(std::abs(mat(2,1) - -0.116827)   < elp);
    CHECK(std::abs(mat(3,1) - -0.0331692)  < elp);

    CHECK(std::abs(mat(0,2) -  0.112745)   < elp);
    CHECK(std::abs(mat(1,2) -  0.215886)   < elp);
    CHECK(std::abs(mat(2,2) - -0.0633572)  < elp);
    CHECK(std::abs(mat(3,2) -  0.00414625) < elp);

    CHECK(std::abs(mat(0,3) - -0.0727737)  < elp);
    CHECK(std::abs(mat(1,3) - -0.00510675) < elp);
    CHECK(std::abs(mat(2,3) -  0.0058859)  < elp);
    CHECK(std::abs(mat(3,3) -  0.0587856)  < elp);

    constexpr Matrix<TestType, 4, 4> mat2 = { mat_00, mat_01, mat_02, mat_03, 
                                              mat_10, mat_11, mat_12, mat_13,
                                              mat_20, mat_21, mat_22, mat_23,
                                              mat_30, mat_31, mat_32, mat_33 };

    constexpr auto inv = mat2.inversed();

    static_assert(std::abs(inv(0,0) -  0.0100878)  < elp);
    static_assert(std::abs(inv(1,0) -  0.122482)   < elp);
    static_assert(std::abs(inv(2,0) - -0.127655)   < elp);
    static_assert(std::abs(inv(3,0) -  0.0582772)  < elp);

    static_assert(std::abs(inv(0,1) -  0.0511035)  < elp);
    static_assert(std::abs(inv(1,1) -  0.231093)   < elp);
    static_assert(std::abs(inv(2,1) - -0.116827)   < elp);
    static_assert(std::abs(inv(3,1) - -0.0331692)  < elp);

    static_assert(std::abs(inv(0,2) -  0.112745)   < elp);
    static_assert(std::abs(inv(1,2) -  0.215886)   < elp);
    static_assert(std::abs(inv(2,2) - -0.0633572)  < elp);
    static_assert(std::abs(inv(3,2) -  0.00414625) < elp);

    static_assert(std::abs(inv(0,3) - -0.0727737)  < elp);
    static_assert(std::abs(inv(1,3) - -0.00510675) < elp);
    static_assert(std::abs(inv(2,3) -  0.0058859)  < elp);
    static_assert(std::abs(inv(3,3) -  0.0587856)  < elp);

    CHECK(std::abs(inv(0,0) -  0.0100878)  < elp);
    CHECK(std::abs(inv(1,0) -  0.122482)   < elp);
    CHECK(std::abs(inv(2,0) - -0.127655)   < elp);
    CHECK(std::abs(inv(3,0) -  0.0582772)  < elp);

    CHECK(std::abs(inv(0,1) -  0.0511035)  < elp);
    CHECK(std::abs(inv(1,1) -  0.231093)   < elp);
    CHECK(std::abs(inv(2,1) - -0.116827)   < elp);
    CHECK(std::abs(inv(3,1) - -0.0331692)  < elp);

    CHECK(std::abs(inv(0,2) -  0.112745)   < elp);
    CHECK(std::abs(inv(1,2) -  0.215886)   < elp);
    CHECK(std::abs(inv(2,2) - -0.0633572)  < elp);
    CHECK(std::abs(inv(3,2) -  0.00414625) < elp);

    CHECK(std::abs(inv(0,3) - -0.0727737)  < elp);
    CHECK(std::abs(inv(1,3) - -0.00510675) < elp);
    CHECK(std::abs(inv(2,3) -  0.0058859)  < elp);
    CHECK(std::abs(inv(3,3) -  0.0587856)  < elp);
    // clang-format on
}

#include "algebra/Matrix.hpp"

#include "Helper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/generators/catch_generators_random.hpp>

#include <iostream>

using LCNS::epsilonHighPrecision;
using LCNS::epsilonLowPrecision;
using LCNS::Algebra::Matrix;
using LCNS::Algebra::Vector;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  100, mat_01 =  101, mat_02 = -102, mat_03 = -103,
                       mat_10 = -110, mat_11 = -111, mat_12 = -112, mat_13 =  113,
                       mat_20 =  120, mat_21 =  121, mat_22 = -122, mat_23 =  123,
                       mat_30 =  130, mat_31 =  131, mat_32 = -132, mat_33 =  133,
                       mat_40 =  140, mat_41 =  141, mat_42 = -142, mat_43 =  143;

    constexpr Matrix<TestType, 5, 4> mat = { mat_00, mat_01, mat_02, mat_03, 
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33,
                                             mat_40, mat_41, mat_42, mat_43 };
    // clang-format on

    static_assert(mat(0, 0) == mat_00);
    static_assert(mat(1, 0) == mat_10);
    static_assert(mat(2, 0) == mat_20);
    static_assert(mat(3, 0) == mat_30);
    static_assert(mat(4, 0) == mat_40);

    static_assert(mat(0, 1) == mat_01);
    static_assert(mat(1, 1) == mat_11);
    static_assert(mat(2, 1) == mat_21);
    static_assert(mat(3, 1) == mat_31);
    static_assert(mat(4, 1) == mat_41);

    static_assert(mat(0, 2) == mat_02);
    static_assert(mat(1, 2) == mat_12);
    static_assert(mat(2, 2) == mat_22);
    static_assert(mat(3, 2) == mat_32);
    static_assert(mat(4, 2) == mat_42);

    static_assert(mat(0, 3) == mat_03);
    static_assert(mat(1, 3) == mat_13);
    static_assert(mat(2, 3) == mat_23);
    static_assert(mat(3, 3) == mat_33);
    static_assert(mat(4, 3) == mat_43);

    CHECK(mat(0, 0) == mat_00);
    CHECK(mat(1, 0) == mat_10);
    CHECK(mat(2, 0) == mat_20);
    CHECK(mat(3, 0) == mat_30);
    CHECK(mat(4, 0) == mat_40);

    CHECK(mat(0, 1) == mat_01);
    CHECK(mat(1, 1) == mat_11);
    CHECK(mat(2, 1) == mat_21);
    CHECK(mat(3, 1) == mat_31);
    CHECK(mat(4, 1) == mat_41);

    CHECK(mat(0, 2) == mat_02);
    CHECK(mat(1, 2) == mat_12);
    CHECK(mat(2, 2) == mat_22);
    CHECK(mat(3, 2) == mat_32);
    CHECK(mat(4, 2) == mat_42);

    CHECK(mat(0, 3) == mat_03);
    CHECK(mat(1, 3) == mat_13);
    CHECK(mat(2, 3) == mat_23);
    CHECK(mat(3, 3) == mat_33);
    CHECK(mat(4, 3) == mat_43);

    // clang-format off
    Matrix<TestType, 5, 4> mat2;
    mat2(0, 0) = mat_00; mat2(0, 1) = mat_01; mat2(0, 2) = mat_02; mat2(0, 3) = mat_03;
    mat2(1, 0) = mat_10; mat2(1, 1) = mat_11; mat2(1, 2) = mat_12; mat2(1, 3) = mat_13;
    mat2(2, 0) = mat_20; mat2(2, 1) = mat_21; mat2(2, 2) = mat_22; mat2(2, 3) = mat_23;
    mat2(3, 0) = mat_30; mat2(3, 1) = mat_31; mat2(3, 2) = mat_32; mat2(3, 3) = mat_33;
    mat2(4, 0) = mat_40; mat2(4, 1) = mat_41; mat2(4, 2) = mat_42; mat2(4, 3) = mat_43;
    // clang-format on

    CHECK(mat2(0, 0) == mat_00);
    CHECK(mat2(1, 0) == mat_10);
    CHECK(mat2(2, 0) == mat_20);
    CHECK(mat2(3, 0) == mat_30);
    CHECK(mat2(4, 0) == mat_40);

    CHECK(mat2(0, 1) == mat_01);
    CHECK(mat2(1, 1) == mat_11);
    CHECK(mat2(2, 1) == mat_21);
    CHECK(mat2(3, 1) == mat_31);
    CHECK(mat2(4, 1) == mat_41);

    CHECK(mat2(0, 2) == mat_02);
    CHECK(mat2(1, 2) == mat_12);
    CHECK(mat2(2, 2) == mat_22);
    CHECK(mat2(3, 2) == mat_32);
    CHECK(mat2(4, 2) == mat_42);

    CHECK(mat2(0, 3) == mat_03);
    CHECK(mat2(1, 3) == mat_13);
    CHECK(mat2(2, 3) == mat_23);
    CHECK(mat2(3, 3) == mat_33);
    CHECK(mat2(4, 3) == mat_43);

    CHECK_THROWS(mat2(5, 0));
    CHECK_THROWS(mat2(0, 4));
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  100.1, mat_01 =  101.2, mat_02 = -102.3, mat_03 = -103.4, mat_04 = -104.4,
                       mat_10 = -110.1, mat_11 = -111.2, mat_12 = -112.3, mat_13 =  113.4, mat_14 =  114.4,
                       mat_20 =  120.1, mat_21 =  121.2, mat_22 = -122.3, mat_23 =  123.4, mat_24 =  124.4,
                       mat_30 =  130.1, mat_31 =  131.2, mat_32 = -132.3, mat_33 =  133.4, mat_34 =  134.4;

    constexpr Matrix<TestType, 4, 5> mat = { mat_00, mat_01, mat_02, mat_03, mat_04,
                                             mat_10, mat_11, mat_12, mat_13, mat_14,
                                             mat_20, mat_21, mat_22, mat_23, mat_24,
                                             mat_30, mat_31, mat_32, mat_33, mat_34 };
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

    static_assert(mat(0, 4) == mat_04);
    static_assert(mat(1, 4) == mat_14);
    static_assert(mat(2, 4) == mat_24);
    static_assert(mat(3, 4) == mat_34);

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

    CHECK(mat(0, 4) == mat_04);
    CHECK(mat(1, 4) == mat_14);
    CHECK(mat(2, 4) == mat_24);
    CHECK(mat(3, 4) == mat_34);

    // clang-format off
    Matrix<TestType, 4, 5> mat2;
    mat2(0, 0) = mat_00; mat2(0, 1) = mat_01; mat2(0, 2) = mat_02; mat2(0, 3) = mat_03;  mat2(0, 4) = mat_04;
    mat2(1, 0) = mat_10; mat2(1, 1) = mat_11; mat2(1, 2) = mat_12; mat2(1, 3) = mat_13;  mat2(1, 4) = mat_14;
    mat2(2, 0) = mat_20; mat2(2, 1) = mat_21; mat2(2, 2) = mat_22; mat2(2, 3) = mat_23;  mat2(2, 4) = mat_24;
    mat2(3, 0) = mat_30; mat2(3, 1) = mat_31; mat2(3, 2) = mat_32; mat2(3, 3) = mat_33;  mat2(3, 4) = mat_34;
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

    CHECK(mat2(0, 4) == mat_04);
    CHECK(mat2(1, 4) == mat_14);
    CHECK(mat2(2, 4) == mat_24);
    CHECK(mat2(3, 4) == mat_34);

    CHECK_THROWS(mat2(4, 0));
    CHECK_THROWS(mat2(0, 5));
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dimMxN][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Matrix<TestType, 4, 6> mat;

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

    static_assert(mat(0, 4) == zero);
    static_assert(mat(1, 4) == zero);
    static_assert(mat(2, 4) == zero);
    static_assert(mat(3, 4) == zero);

    static_assert(mat(0, 5) == zero);
    static_assert(mat(1, 5) == zero);
    static_assert(mat(2, 5) == zero);
    static_assert(mat(3, 5) == zero);

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

    CHECK(mat(0, 4) == zero);
    CHECK(mat(1, 4) == zero);
    CHECK(mat(2, 4) == zero);
    CHECK(mat(3, 4) == zero);

    CHECK(mat(0, 5) == zero);
    CHECK(mat(1, 5) == zero);
    CHECK(mat(2, 5) == zero);
    CHECK(mat(3, 5) == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dimMxN][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Matrix<TestType, 6, 4> mat;

    static_assert(mat(0, 0) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(2, 0) == zero);
    static_assert(mat(3, 0) == zero);
    static_assert(mat(4, 0) == zero);
    static_assert(mat(5, 0) == zero);

    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 1) == zero);
    static_assert(mat(2, 1) == zero);
    static_assert(mat(3, 1) == zero);
    static_assert(mat(4, 1) == zero);
    static_assert(mat(5, 1) == zero);

    static_assert(mat(0, 2) == zero);
    static_assert(mat(1, 2) == zero);
    static_assert(mat(2, 2) == zero);
    static_assert(mat(3, 2) == zero);
    static_assert(mat(4, 2) == zero);
    static_assert(mat(5, 2) == zero);

    static_assert(mat(0, 3) == zero);
    static_assert(mat(1, 3) == zero);
    static_assert(mat(2, 3) == zero);
    static_assert(mat(3, 3) == zero);
    static_assert(mat(4, 3) == zero);
    static_assert(mat(5, 3) == zero);

    CHECK(mat(0, 0) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(2, 0) == zero);
    CHECK(mat(3, 0) == zero);
    CHECK(mat(4, 0) == zero);
    CHECK(mat(5, 0) == zero);

    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 1) == zero);
    CHECK(mat(2, 1) == zero);
    CHECK(mat(3, 1) == zero);
    CHECK(mat(4, 1) == zero);
    CHECK(mat(5, 1) == zero);

    CHECK(mat(0, 2) == zero);
    CHECK(mat(1, 2) == zero);
    CHECK(mat(2, 2) == zero);
    CHECK(mat(3, 2) == zero);
    CHECK(mat(4, 2) == zero);
    CHECK(mat(5, 2) == zero);

    CHECK(mat(0, 3) == zero);
    CHECK(mat(1, 3) == zero);
    CHECK(mat(2, 3) == zero);
    CHECK(mat(3, 3) == zero);
    CHECK(mat(4, 3) == zero);
    CHECK(mat(5, 3) == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dimMxN][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;
    constexpr TestType one  = 1;

    constexpr Matrix<TestType, 3, 5> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(2, 0) == zero);

    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 1) == one);
    static_assert(mat(2, 1) == zero);

    static_assert(mat(0, 2) == zero);
    static_assert(mat(1, 2) == zero);
    static_assert(mat(2, 2) == one);

    static_assert(mat(0, 3) == zero);
    static_assert(mat(1, 3) == zero);
    static_assert(mat(2, 3) == zero);

    static_assert(mat(0, 4) == zero);
    static_assert(mat(1, 4) == zero);
    static_assert(mat(2, 4) == zero);

    CHECK(mat(0, 0) == one);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(2, 0) == zero);

    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 1) == one);
    CHECK(mat(2, 1) == zero);

    CHECK(mat(0, 2) == zero);
    CHECK(mat(1, 2) == zero);
    CHECK(mat(2, 2) == one);

    CHECK(mat(0, 3) == zero);
    CHECK(mat(1, 3) == zero);
    CHECK(mat(2, 3) == zero);

    CHECK(mat(0, 4) == zero);
    CHECK(mat(1, 4) == zero);
    CHECK(mat(2, 4) == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dimMxN][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;
    constexpr TestType one  = 1.0;

    constexpr Matrix<TestType, 5, 3> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(2, 0) == zero);
    static_assert(mat(3, 0) == zero);
    static_assert(mat(4, 0) == zero);

    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 1) == one);
    static_assert(mat(2, 1) == zero);
    static_assert(mat(3, 1) == zero);
    static_assert(mat(4, 1) == zero);

    static_assert(mat(0, 2) == zero);
    static_assert(mat(1, 2) == zero);
    static_assert(mat(2, 2) == one);
    static_assert(mat(3, 2) == zero);
    static_assert(mat(4, 2) == zero);

    CHECK(mat(0, 0) == one);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(2, 0) == zero);
    CHECK(mat(3, 0) == zero);
    CHECK(mat(4, 0) == zero);

    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 1) == one);
    CHECK(mat(2, 1) == zero);
    CHECK(mat(3, 1) == zero);
    CHECK(mat(4, 1) == zero);

    CHECK(mat(0, 2) == zero);
    CHECK(mat(1, 2) == zero);
    CHECK(mat(2, 2) == one);
    CHECK(mat(3, 2) == zero);
    CHECK(mat(4, 2) == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][matrix][dimMxN][constructor]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 0, mat_01 = -1, mat_02 = -9, mat_03 =  5,
                       mat_10 = 3, mat_11 =  2, mat_12 = -1, mat_13 = -8;

    constexpr Matrix<TestType, 2, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13 };
    // clang-format on

    static_assert(mat(0, 0) == mat_00);
    static_assert(mat(1, 0) == mat_10);

    static_assert(mat(0, 1) == mat_01);
    static_assert(mat(1, 1) == mat_11);

    static_assert(mat(0, 2) == mat_02);
    static_assert(mat(1, 2) == mat_12);

    static_assert(mat(0, 3) == mat_03);
    static_assert(mat(1, 3) == mat_13);

    CHECK(mat(0, 0) == mat_00);
    CHECK(mat(1, 0) == mat_10);

    CHECK(mat(0, 1) == mat_01);
    CHECK(mat(1, 1) == mat_11);

    CHECK(mat(0, 2) == mat_02);
    CHECK(mat(1, 2) == mat_12);

    CHECK(mat(0, 3) == mat_03);
    CHECK(mat(1, 3) == mat_13);

    CHECK_NOTHROW(Matrix<TestType, 2, 4>({}));
    CHECK_NOTHROW(Matrix<TestType, 2, 4>({ mat_00, mat_01, mat_02, mat_03 }));

    // clang-format off
    CHECK_THROWS(Matrix<TestType, 2, 4>({ mat_00, mat_01, mat_02, mat_03,
                                          mat_10, mat_11, mat_12, mat_13,
                                          mat_10, mat_11 }));
    // clang-format on
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][matrix][dimMxN][constructor]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 0.88, mat_01 = -1.98,
                       mat_10 = 3.23, mat_11 =  2.45,
                       mat_20 = 4.74, mat_21 =  2.37,
                       mat_30 = 1.12, mat_31 =  2.11;

    constexpr Matrix<TestType, 4, 2> mat = { mat_00, mat_01,
                                             mat_10, mat_11,
                                             mat_20, mat_21,
                                             mat_30, mat_31 };
    // clang-format on

    static_assert(mat(0, 0) == mat_00);
    static_assert(mat(1, 0) == mat_10);
    static_assert(mat(2, 0) == mat_20);
    static_assert(mat(3, 0) == mat_30);

    static_assert(mat(0, 1) == mat_01);
    static_assert(mat(1, 1) == mat_11);
    static_assert(mat(2, 1) == mat_21);
    static_assert(mat(3, 1) == mat_31);

    CHECK(mat(0, 0) == mat_00);
    CHECK(mat(1, 0) == mat_10);
    CHECK(mat(2, 0) == mat_20);
    CHECK(mat(3, 0) == mat_30);

    CHECK(mat(0, 1) == mat_01);
    CHECK(mat(1, 1) == mat_11);
    CHECK(mat(2, 1) == mat_21);
    CHECK(mat(3, 1) == mat_31);


    CHECK_NOTHROW(Matrix<TestType, 4, 2>({}));
    CHECK_NOTHROW(Matrix<TestType, 4, 2>({ mat_00, mat_01, mat_10, mat_11 }));

    // clang-format off
    CHECK_THROWS(Matrix<TestType, 4, 2>({ mat_00, mat_01, mat_01,
                                          mat_10, mat_11, mat_11,
                                          mat_20, mat_21,
                                          mat_30, mat_31, }));
    // clang-format on
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  98, mat_01 = -56, mat_02 = -97, mat_03 =  55,
                       mat_10 = -45, mat_11 =  23, mat_12 = -45, mat_13 = -88,
                       mat_20 =  78, mat_21 =  23, mat_22 =  20, mat_23 =  55;

    constexpr Matrix<TestType, 3, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23 };
    // clang-format on

    constexpr auto copy1(mat);

    static_assert(mat(0, 0) == copy1(0, 0));
    static_assert(mat(1, 0) == copy1(1, 0));
    static_assert(mat(2, 0) == copy1(2, 0));

    static_assert(mat(0, 1) == copy1(0, 1));
    static_assert(mat(1, 1) == copy1(1, 1));
    static_assert(mat(2, 1) == copy1(2, 1));

    static_assert(mat(0, 2) == copy1(0, 2));
    static_assert(mat(1, 2) == copy1(1, 2));
    static_assert(mat(2, 2) == copy1(2, 2));

    static_assert(mat(0, 3) == copy1(0, 3));
    static_assert(mat(1, 3) == copy1(1, 3));
    static_assert(mat(2, 3) == copy1(2, 3));

    CHECK(mat(0, 0) == copy1(0, 0));
    CHECK(mat(1, 0) == copy1(1, 0));
    CHECK(mat(2, 0) == copy1(2, 0));

    CHECK(mat(0, 1) == copy1(0, 1));
    CHECK(mat(1, 1) == copy1(1, 1));
    CHECK(mat(2, 1) == copy1(2, 1));

    CHECK(mat(0, 2) == copy1(0, 2));
    CHECK(mat(1, 2) == copy1(1, 2));
    CHECK(mat(2, 2) == copy1(2, 2));

    CHECK(mat(0, 3) == copy1(0, 3));
    CHECK(mat(1, 3) == copy1(1, 3));
    CHECK(mat(2, 3) == copy1(2, 3));

    constexpr auto copy2 = mat;

    static_assert(mat(0, 0) == copy2(0, 0));
    static_assert(mat(1, 0) == copy2(1, 0));
    static_assert(mat(2, 0) == copy2(2, 0));

    static_assert(mat(0, 1) == copy2(0, 1));
    static_assert(mat(1, 1) == copy2(1, 1));
    static_assert(mat(2, 1) == copy2(2, 1));

    static_assert(mat(0, 2) == copy2(0, 2));
    static_assert(mat(1, 2) == copy2(1, 2));
    static_assert(mat(2, 2) == copy2(2, 2));

    static_assert(mat(0, 3) == copy2(0, 3));
    static_assert(mat(1, 3) == copy2(1, 3));
    static_assert(mat(2, 3) == copy2(2, 3));

    CHECK(mat(0, 0) == copy2(0, 0));
    CHECK(mat(1, 0) == copy2(1, 0));
    CHECK(mat(2, 0) == copy2(2, 0));

    CHECK(mat(0, 1) == copy2(0, 1));
    CHECK(mat(1, 1) == copy2(1, 1));
    CHECK(mat(2, 1) == copy2(2, 1));

    CHECK(mat(0, 2) == copy2(0, 2));
    CHECK(mat(1, 2) == copy2(1, 2));
    CHECK(mat(2, 2) == copy2(2, 2));

    CHECK(mat(0, 3) == copy2(0, 3));
    CHECK(mat(1, 3) == copy2(1, 3));
    CHECK(mat(2, 3) == copy2(2, 3));
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  98.56, mat_01 = -56.98, mat_02 = -97.55,
                       mat_10 =  45.23, mat_11 =  23.45, mat_12 = -45.88,
                       mat_20 =  78.23, mat_21 = -23.78, mat_22 =  20.55,
                       mat_30 = -12.23, mat_31 =  23.12, mat_32 =  70.55;

    constexpr Matrix<TestType, 4, 3> mat = { mat_00, mat_01, mat_02,
                                             mat_10, mat_11, mat_12,
                                             mat_20, mat_21, mat_22,
                                             mat_30, mat_31, mat_32 };
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
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  19,
                       mat_10 = -56,
                       mat_20 =  78,
                       mat_30 =  23;

    constexpr auto getMatrix = [=]()
    {
        return Matrix<TestType, 4, 1>({ mat_00,
                                        mat_10,
                                        mat_20,
                                        mat_30 });
    };
    // clang-format on

    constexpr auto copy1(getMatrix());

    static_assert(copy1(0, 0) == mat_00);
    static_assert(copy1(1, 0) == mat_10);
    static_assert(copy1(2, 0) == mat_20);
    static_assert(copy1(3, 0) == mat_30);

    CHECK(copy1(0, 0) == mat_00);
    CHECK(copy1(1, 0) == mat_10);
    CHECK(copy1(2, 0) == mat_20);
    CHECK(copy1(3, 0) == mat_30);

    constexpr auto copy2 = getMatrix();

    static_assert(copy2(0, 0) == mat_00);
    static_assert(copy2(1, 0) == mat_10);
    static_assert(copy2(2, 0) == mat_20);
    static_assert(copy2(3, 0) == mat_30);

    CHECK(copy2(0, 0) == mat_00);
    CHECK(copy2(1, 0) == mat_10);
    CHECK(copy2(2, 0) == mat_20);
    CHECK(copy2(3, 0) == mat_30);
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 6405.1, mat_01 = 5630.7, mat_02 = -97.79, mat_03 = 95.659;

    constexpr auto getMatrix = [=]()
    {
        return Matrix<TestType, 1, 4>({ mat_00, mat_01, mat_02, mat_03 });
    };
    // clang-format on

    constexpr auto copy1(getMatrix());

    static_assert(copy1(0, 0) == mat_00);

    static_assert(copy1(0, 1) == mat_01);

    static_assert(copy1(0, 2) == mat_02);

    static_assert(copy1(0, 3) == mat_03);

    CHECK(copy1(0, 0) == mat_00);

    CHECK(copy1(0, 1) == mat_01);

    CHECK(copy1(0, 2) == mat_02);

    CHECK(copy1(0, 3) == mat_03);

    constexpr auto copy2 = getMatrix();

    static_assert(copy2(0, 0) == mat_00);

    static_assert(copy2(0, 1) == mat_01);

    static_assert(copy2(0, 2) == mat_02);

    static_assert(copy2(0, 3) == mat_03);

    CHECK(copy2(0, 0) == mat_00);

    CHECK(copy2(0, 1) == mat_01);

    CHECK(copy2(0, 2) == mat_02);

    CHECK(copy2(0, 3) == mat_03);
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  19, mat_01 = -56, mat_02 = -97,
                       mat_10 = -56, mat_11 =  23, mat_12 = -45,
                       mat_20 =  78, mat_21 =  98, mat_22 = 456,
                       mat_30 =  23, mat_31 = 687, mat_32 =  70;

    constexpr Matrix<TestType, 4, 3> mat = { mat_00, mat_01, mat_02,
                                             mat_10, mat_11, mat_12,
                                             mat_20, mat_21, mat_22,
                                             mat_30, mat_31, mat_32 };

    constexpr Matrix<TestType, 4, 3> identical = { mat_00, mat_01, mat_02,
                                                   mat_10, mat_11, mat_12,
                                                   mat_20, mat_21, mat_22,
                                                   mat_30, mat_31, mat_32 };

    constexpr Matrix<TestType, 4, 3> different = {      0, mat_01, mat_02,
                                                   mat_10, mat_11, mat_12,
                                                   mat_20, mat_21, mat_22,
                                                   mat_30, mat_31, mat_32 };
    // clang-format on

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            Matrix<TestType, 4, 3> diff = mat;
            diff(i, j)                  = 0;

            CHECK(mat != diff);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 6405.1, mat_01 = 5630.7, mat_02 = -97.79, mat_03 = 95.659,
                       mat_10 = -563.9, mat_11 = -23.74, mat_12 = 45.028, mat_13 = -88.34,
                       mat_20 = 789.99, mat_21 = -98.22, mat_22 = 4563.3, mat_23 = -57.14;

    constexpr Matrix<TestType, 3, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23 };

    constexpr Matrix<TestType, 3, 4> identical = { mat_00, mat_01, mat_02, mat_03,
                                                   mat_10, mat_11, mat_12, mat_13,
                                                   mat_20, mat_21, mat_22, mat_23 };

    constexpr Matrix<TestType, 3, 4> different = {    0.0, mat_01, mat_02, mat_03,
                                                   mat_10, mat_11, mat_12, mat_13,
                                                   mat_20, mat_21, mat_22, mat_23 };
    // clang-format on

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            Matrix<TestType, 3, 4> diff = mat;
            diff(i, j)                  = 0;

            CHECK(mat != diff);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 854, mat1_01 =    7,
                       mat1_10 = 333, mat1_11 = -274,
                       mat1_20 = -98, mat1_21 = -982,
                       mat1_30 = 199, mat1_31 = 2532;

    constexpr TestType mat2_00 =   -5, mat2_01 = -607,
                       mat2_10 = -563, mat2_11 = -274,
                       mat2_20 = 1178, mat2_21 =  974,
                       mat2_30 = 2230, mat2_31 = -439;

    constexpr Matrix<TestType, 4, 2> mat1 = { mat1_00, mat1_01,
                                              mat1_10, mat1_11,
                                              mat1_20, mat1_21,
                                              mat1_30, mat1_31 };

    constexpr Matrix<TestType, 4, 2> mat2 = { mat2_00, mat2_01,
                                              mat2_10, mat2_11,
                                              mat2_20, mat2_21,
                                              mat2_30, mat2_31 };
    // clang-format on

    constexpr Matrix<TestType, 4, 2> sum = mat1 + mat2;

    static_assert(sum(0, 0) == 849);
    static_assert(sum(1, 0) == -230);
    static_assert(sum(2, 0) == 1080);
    static_assert(sum(3, 0) == 2429);

    static_assert(sum(0, 1) == -600);
    static_assert(sum(1, 1) == -548);
    static_assert(sum(2, 1) == -8);
    static_assert(sum(3, 1) == 2093);

    CHECK(sum(0, 0) == 849);
    CHECK(sum(1, 0) == -230);
    CHECK(sum(2, 0) == 1080);
    CHECK(sum(3, 0) == 2429);

    CHECK(sum(0, 1) == -600);
    CHECK(sum(1, 1) == -548);
    CHECK(sum(2, 1) == -8);
    CHECK(sum(3, 1) == 2093);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 85.4, mat1_01 =   7.1, mat1_02 = 9.49, mat1_03 =  1.1,
                       mat1_10 = 33.3, mat1_11 = -27.4, mat1_12 = 4.78, mat1_13 = -3.8,
                       mat1_20 = -9.8, mat1_21 = -82.7, mat1_22 = -5.3, mat1_23 =  4.4;

    constexpr TestType mat2_00 =  -5.1, mat2_01 = -60.7, mat2_02 = -9.7, mat2_03 = 101.0,
                       mat2_10 = -63.3, mat2_11 = -27.4, mat2_12 = 40.2, mat2_13 = -65.4,
                       mat2_20 = 178.7, mat2_21 =  97.4, mat2_22 = 45.6, mat2_23 = -51.4;

    constexpr Matrix<TestType, 3, 4> mat1 = { mat1_00, mat1_01, mat1_02, mat1_03,
                                              mat1_10, mat1_11, mat1_12, mat1_13,
                                              mat1_20, mat1_21, mat1_22, mat1_23 };

    constexpr Matrix<TestType, 3, 4> mat2 = { mat2_00, mat2_01, mat2_02, mat2_03,
                                              mat2_10, mat2_11, mat2_12, mat2_13,
                                              mat2_20, mat2_21, mat2_22, mat2_23 };
    // clang-format on
    constexpr Matrix<TestType, 3, 4> sum = mat1 + mat2;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(sum(0, 0) - 80.3) < elp);
    static_assert(std::abs(sum(1, 0) - -30.0) < elp);
    static_assert(std::abs(sum(2, 0) - 168.9) < elp);

    static_assert(std::abs(sum(0, 1) - -53.6) < elp);
    static_assert(std::abs(sum(1, 1) - -54.8) < elp);
    static_assert(std::abs(sum(2, 1) - 14.7) < elp);

    static_assert(std::abs(sum(0, 2) - -0.21) < elp);
    static_assert(std::abs(sum(1, 2) - 44.98) < elp);
    static_assert(std::abs(sum(2, 2) - 40.3) < elp);

    static_assert(std::abs(sum(0, 3) - 102.1) < elp);
    static_assert(std::abs(sum(1, 3) - -69.2) < elp);
    static_assert(std::abs(sum(2, 3) - -47.0) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(sum(0, 0) == Catch::Approx(80.3).epsilon(ehp));
    CHECK(sum(1, 0) == Catch::Approx(-30.0).epsilon(ehp));
    CHECK(sum(2, 0) == Catch::Approx(168.9).epsilon(ehp));

    CHECK(sum(0, 1) == Catch::Approx(-53.6).epsilon(ehp));
    CHECK(sum(1, 1) == Catch::Approx(-54.8).epsilon(ehp));
    CHECK(sum(2, 1) == Catch::Approx(14.7).epsilon(ehp));

    CHECK(sum(0, 2) == Catch::Approx(-0.21).epsilon(ehp));
    CHECK(sum(1, 2) == Catch::Approx(44.98).epsilon(ehp));
    CHECK(sum(2, 2) == Catch::Approx(40.3).epsilon(ehp));

    CHECK(sum(0, 3) == Catch::Approx(102.1).epsilon(ehp));
    CHECK(sum(1, 3) == Catch::Approx(-69.2).epsilon(ehp));
    CHECK(sum(2, 3) == Catch::Approx(-47.0).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Substraction operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 854, mat1_01 =    7, mat1_02 = 9449, mat1_03 = 1659,
                       mat1_10 = 333, mat1_11 = -274, mat1_12 = 4528, mat1_13 = -379,
                       mat1_20 = -98, mat1_21 = -982, mat1_22 = -563, mat1_23 = 4714;

    constexpr TestType mat2_00 =   -5, mat2_01 = -607, mat2_02 = -979, mat2_03 = 1010,
                       mat2_10 = -563, mat2_11 = -274, mat2_12 = 4028, mat2_13 = -654,
                       mat2_20 = 1178, mat2_21 =  974, mat2_22 = 4563, mat2_23 = -514;

    constexpr Matrix<TestType, 4, 4> mat1 = { mat1_00, mat1_01, mat1_02, mat1_03,
                                              mat1_10, mat1_11, mat1_12, mat1_13,
                                              mat1_20, mat1_21, mat1_22, mat1_23 };

    constexpr Matrix<TestType, 4, 4> mat2 = { mat2_00, mat2_01, mat2_02, mat2_03,
                                              mat2_10, mat2_11, mat2_12, mat2_13,
                                              mat2_20, mat2_21, mat2_22, mat2_23 };
    // clang-format on

    constexpr Matrix<TestType, 4, 4> diff = mat1 - mat2;

    static_assert(diff(0, 0) == 859);
    static_assert(diff(1, 0) == 896);
    static_assert(diff(2, 0) == -1276);

    static_assert(diff(0, 1) == 614);
    static_assert(diff(1, 1) == 0);
    static_assert(diff(2, 1) == -1956);

    static_assert(diff(0, 2) == 10428);
    static_assert(diff(1, 2) == 500);
    static_assert(diff(2, 2) == -5126);

    static_assert(diff(0, 3) == 649);
    static_assert(diff(1, 3) == 275);
    static_assert(diff(2, 3) == 5228);

    CHECK(diff(0, 0) == 859);
    CHECK(diff(1, 0) == 896);
    CHECK(diff(2, 0) == -1276);

    CHECK(diff(0, 1) == 614);
    CHECK(diff(1, 1) == 0);
    CHECK(diff(2, 1) == -1956);

    CHECK(diff(0, 2) == 10428);
    CHECK(diff(1, 2) == 500);
    CHECK(diff(2, 2) == -5126);

    CHECK(diff(0, 3) == 649);
    CHECK(diff(1, 3) == 275);
    CHECK(diff(2, 3) == 5228);
}

TEMPLATE_LIST_TEST_CASE("Substraction operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 85.4, mat1_01 =   7.1, mat1_02 = 9.49,
                       mat1_10 = 33.3, mat1_11 = -27.4, mat1_12 = 4.78,
                       mat1_20 = -9.8, mat1_21 = -82.7, mat1_22 = -5.3,
                       mat1_30 = 19.9, mat1_31 = 253.2, mat1_32 = -7.0;

    constexpr TestType mat2_00 =  -5.1, mat2_01 = -60.7, mat2_02 = -9.7,
                       mat2_10 = -63.3, mat2_11 = -27.4, mat2_12 = 40.2,
                       mat2_20 = 178.7, mat2_21 =  97.4, mat2_22 = 45.6,
                       mat2_30 = 220.5, mat2_31 = -43.9, mat2_32 =  7.0;

    constexpr Matrix<TestType, 4, 3> mat1 = { mat1_00, mat1_01, mat1_02,
                                              mat1_10, mat1_11, mat1_12,
                                              mat1_20, mat1_21, mat1_22,
                                              mat1_30, mat1_31, mat1_32 };

    constexpr Matrix<TestType, 4, 3> mat2 = { mat2_00, mat2_01, mat2_02,
                                              mat2_10, mat2_11, mat2_12,
                                              mat2_20, mat2_21, mat2_22,
                                              mat2_30, mat2_31, mat2_32 };
    // clang-format on
    constexpr Matrix<TestType, 4, 3> diff = mat1 - mat2;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(diff(0, 0) - 90.5) < elp);
    static_assert(std::abs(diff(1, 0) - 96.6) < elp);
    static_assert(std::abs(diff(2, 0) - -188.5) < elp);
    static_assert(std::abs(diff(3, 0) - -200.6) < elp);

    static_assert(std::abs(diff(0, 1) - 67.8) < elp);
    static_assert(std::abs(diff(1, 1) - 0.0) < elp);
    static_assert(std::abs(diff(2, 1) - -180.1) < elp);
    static_assert(std::abs(diff(3, 1) - 297.1) < elp);

    static_assert(std::abs(diff(0, 2) - 19.19) < elp);
    static_assert(std::abs(diff(1, 2) - -35.42) < elp);
    static_assert(std::abs(diff(2, 2) - -50.9) < elp);
    static_assert(std::abs(diff(3, 2) - -14.0) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(diff(0, 0) == Catch::Approx(90.5).epsilon(ehp));
    CHECK(diff(1, 0) == Catch::Approx(96.6).epsilon(ehp));
    CHECK(diff(2, 0) == Catch::Approx(-188.5).epsilon(ehp));
    CHECK(diff(3, 0) == Catch::Approx(-200.6).epsilon(ehp));

    CHECK(diff(0, 1) == Catch::Approx(67.8).epsilon(ehp));
    CHECK(diff(1, 1) == Catch::Approx(0.0).epsilon(ehp));
    CHECK(diff(2, 1) == Catch::Approx(-180.1).epsilon(ehp));
    CHECK(diff(3, 1) == Catch::Approx(297.1).epsilon(ehp));

    CHECK(diff(0, 2) == Catch::Approx(19.19).epsilon(ehp));
    CHECK(diff(1, 2) == Catch::Approx(-35.42).epsilon(ehp));
    CHECK(diff(2, 2) == Catch::Approx(-50.9).epsilon(ehp));
    CHECK(diff(3, 2) == Catch::Approx(-14.0).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Times equal", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    TestType mat_00 =  1, mat_01 =  5, mat_02 =   9, mat_03 =  13, mat_04 = 17,
             mat_10 = -2, mat_11 = -6, mat_12 = -10, mat_13 = -14, mat_14 = 18,
             mat_20 =  3, mat_21 =  7, mat_22 =  11, mat_23 =  15, mat_24 = 19,
             mat_30 = -4, mat_31 = -8, mat_32 = -12, mat_33 = -16, mat_34 = 20;

    TestType scalar = 5;

    Matrix<TestType, 4, 5> mat = { mat_00, mat_01, mat_02, mat_03, mat_04,
                                   mat_10, mat_11, mat_12, mat_13, mat_14,
                                   mat_20, mat_21, mat_22, mat_23, mat_24,
                                   mat_30, mat_31, mat_32, mat_33, mat_34 };
    // clang-format on

    mat *= scalar;

    CHECK(mat(0, 0) == 5);
    CHECK(mat(1, 0) == -10);
    CHECK(mat(2, 0) == 15);
    CHECK(mat(3, 0) == -20);

    CHECK(mat(0, 1) == 25);
    CHECK(mat(1, 1) == -30);
    CHECK(mat(2, 1) == 35);
    CHECK(mat(3, 1) == -40);

    CHECK(mat(0, 2) == 45);
    CHECK(mat(1, 2) == -50);
    CHECK(mat(2, 2) == 55);
    CHECK(mat(3, 2) == -60);

    CHECK(mat(0, 3) == 65);
    CHECK(mat(1, 3) == -70);
    CHECK(mat(2, 3) == 75);
    CHECK(mat(3, 3) == -80);

    CHECK(mat(0, 4) == 85);
    CHECK(mat(1, 4) == 90);
    CHECK(mat(2, 4) == 95);
    CHECK(mat(3, 4) == 100);
}

TEMPLATE_LIST_TEST_CASE("Times equal", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    TestType mat_00 = 9.49, mat_01 =  1.1, mat_02 = 85.4,
             mat_10 = 4.78, mat_11 = -3.8, mat_12 = 33.3,
             mat_20 = -5.3, mat_21 =  4.4, mat_22 = -9.8,
             mat_30 =  7.1, mat_31 = 3.21, mat_32 = 19.9,
             mat_40 = 17.1, mat_41 = 7.21, mat_42 = 46.4,
             mat_50 = 27.1, mat_51 = 3.21, mat_52 = 14.7,
             mat_60 = 37.1, mat_61 = 3.29, mat_62 = 37.2;

    TestType scalar = 8.6;

    Matrix<TestType, 7, 3> mat = { mat_00, mat_01, mat_02,
                                   mat_10, mat_11, mat_12,
                                   mat_20, mat_21, mat_22,
                                   mat_30, mat_31, mat_32, 
                                   mat_40, mat_41, mat_42,
                                   mat_50, mat_51, mat_52,
                                   mat_60, mat_61, mat_62 };
    // clang-format on

    mat *= scalar;

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mat(0, 0) == Catch::Approx(81.614).epsilon(ehp));
    CHECK(mat(1, 0) == Catch::Approx(41.108).epsilon(ehp));
    CHECK(mat(2, 0) == Catch::Approx(-45.58).epsilon(ehp));
    CHECK(mat(3, 0) == Catch::Approx(61.06).epsilon(ehp));
    CHECK(mat(4, 0) == Catch::Approx(147.06).epsilon(ehp));
    CHECK(mat(5, 0) == Catch::Approx(233.06).epsilon(ehp));
    CHECK(mat(6, 0) == Catch::Approx(319.06).epsilon(ehp));

    CHECK(mat(0, 1) == Catch::Approx(9.46).epsilon(ehp));
    CHECK(mat(1, 1) == Catch::Approx(-32.68).epsilon(ehp));
    CHECK(mat(2, 1) == Catch::Approx(37.84).epsilon(ehp));
    CHECK(mat(3, 1) == Catch::Approx(27.606).epsilon(ehp));
    CHECK(mat(4, 1) == Catch::Approx(62.006).epsilon(ehp));
    CHECK(mat(5, 1) == Catch::Approx(27.606).epsilon(ehp));
    CHECK(mat(6, 1) == Catch::Approx(28.294).epsilon(ehp));

    CHECK(mat(0, 2) == Catch::Approx(734.44).epsilon(ehp));
    CHECK(mat(1, 2) == Catch::Approx(286.38).epsilon(ehp));
    CHECK(mat(2, 2) == Catch::Approx(-84.28).epsilon(ehp));
    CHECK(mat(3, 2) == Catch::Approx(171.14).epsilon(ehp));
    CHECK(mat(4, 2) == Catch::Approx(399.04).epsilon(ehp));
    CHECK(mat(5, 2) == Catch::Approx(126.42).epsilon(ehp));
    CHECK(mat(6, 2) == Catch::Approx(319.92).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Divide equal", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    TestType mat_00 =  10, mat_01 =  50, mat_02 =   90, mat_03 =  130, mat_04 =  160, mat_05 =  190, mat_06 =  220,
             mat_10 = -20, mat_11 = -60, mat_12 = -100, mat_13 = -140, mat_14 = -170, mat_15 = -200, mat_16 = -230,
             mat_20 =  30, mat_21 =  70, mat_22 =  110, mat_23 =  150, mat_24 =  180, mat_25 =  210, mat_26 =  240;

    TestType scalar = -2;

    Matrix<TestType, 3, 7> mat = { mat_00, mat_01, mat_02, mat_03, mat_04, mat_05, mat_06,
                                   mat_10, mat_11, mat_12, mat_13, mat_14, mat_15, mat_16,
                                   mat_20, mat_21, mat_22, mat_23, mat_24, mat_25, mat_26 };
    // clang-format on

    mat /= scalar;

    CHECK(mat(0, 0) == -5);
    CHECK(mat(1, 0) == 10);
    CHECK(mat(2, 0) == -15);

    CHECK(mat(0, 1) == -25);
    CHECK(mat(1, 1) == 30);
    CHECK(mat(2, 1) == -35);

    CHECK(mat(0, 2) == -45);
    CHECK(mat(1, 2) == 50);
    CHECK(mat(2, 2) == -55);

    CHECK(mat(0, 3) == -65);
    CHECK(mat(1, 3) == 70);
    CHECK(mat(2, 3) == -75);

    CHECK(mat(0, 4) == -80);
    CHECK(mat(1, 4) == 85);
    CHECK(mat(2, 4) == -90);

    CHECK(mat(0, 5) == -95);
    CHECK(mat(1, 5) == 100);
    CHECK(mat(2, 5) == -105);

    CHECK(mat(0, 6) == -110);
    CHECK(mat(1, 6) == 115);
    CHECK(mat(2, 6) == -120);

    TestType zero = 0;
    CHECK_THROWS(mat /= zero);
}

TEMPLATE_LIST_TEST_CASE("Divide equal", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    TestType mat_00 = 9.49, mat_01 = 1.18, mat_02 = 85.42,
             mat_10 = 4.78, mat_11 = -3.8, mat_12 = 33.37,
             mat_20 = -5.3, mat_21 = 4.45, mat_22 = -9.89,
             mat_30 =  7.1, mat_31 = 3.21, mat_32 = 19.91,
             mat_40 = 56.1, mat_41 = 22.4, mat_42 = -8.54,
             mat_50 = 36.8, mat_51 = 97.4, mat_52 = -6.38,
             mat_60 = -6.4, mat_61 = 1.02, mat_62 = 9.337;

    TestType scalar = 8.6;

    Matrix<TestType, 7, 3> mat = { mat_00, mat_01, mat_02,
                                   mat_10, mat_11, mat_12,
                                   mat_20, mat_21, mat_22,
                                   mat_30, mat_31, mat_32,
                                   mat_40, mat_41, mat_42,
                                   mat_50, mat_51, mat_52,
                                   mat_60, mat_61, mat_62 };
    // clang-format on

    mat /= scalar;

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mat(0, 0) == Catch::Approx(1.10348837209302).epsilon(ehp));
    CHECK(mat(1, 0) == Catch::Approx(0.555813953488372).epsilon(ehp));
    CHECK(mat(2, 0) == Catch::Approx(-0.616279069767442).epsilon(ehp));
    CHECK(mat(3, 0) == Catch::Approx(0.825581395348837).epsilon(ehp));
    CHECK(mat(4, 0) == Catch::Approx(6.52325581395349).epsilon(ehp));
    CHECK(mat(5, 0) == Catch::Approx(4.27906976744186).epsilon(ehp));
    CHECK(mat(6, 0) == Catch::Approx(-0.744186046511628).epsilon(ehp));

    CHECK(mat(0, 1) == Catch::Approx(0.137209302325581).epsilon(ehp));
    CHECK(mat(1, 1) == Catch::Approx(-0.441860465116279).epsilon(ehp));
    CHECK(mat(2, 1) == Catch::Approx(0.517441860465116).epsilon(ehp));
    CHECK(mat(3, 1) == Catch::Approx(0.373255813953488).epsilon(ehp));
    CHECK(mat(4, 1) == Catch::Approx(2.6046511627907).epsilon(ehp));
    CHECK(mat(5, 1) == Catch::Approx(11.3255813953488).epsilon(ehp));
    CHECK(mat(6, 1) == Catch::Approx(0.118604651162791).epsilon(ehp));

    CHECK(mat(0, 2) == Catch::Approx(9.93255813953489).epsilon(ehp));
    CHECK(mat(1, 2) == Catch::Approx(3.88023255813954).epsilon(ehp));
    CHECK(mat(2, 2) == Catch::Approx(-1.15).epsilon(ehp));
    CHECK(mat(3, 2) == Catch::Approx(2.31511627906977).epsilon(ehp));
    CHECK(mat(4, 2) == Catch::Approx(-0.993023255813954).epsilon(ehp));
    CHECK(mat(5, 2) == Catch::Approx(-0.741860465116279).epsilon(ehp));
    CHECK(mat(6, 2) == Catch::Approx(1.0856976744186).epsilon(ehp));

    TestType zero = 0.0;
    CHECK_THROWS(mat /= zero);
}

TEMPLATE_LIST_TEST_CASE("Dimensions", "[algebra][matrix][dimMxN][method]", IntegerTypes)
{
    constexpr Matrix<TestType, 49, 37> mat;

    constexpr auto dims = mat.dimensions();

    static_assert(std::get<0>(dims) == 49);
    static_assert(std::get<1>(dims) == 37);

    const auto [rows, cols] = mat.dimensions();

    CHECK(rows == 49);
    CHECK(cols == 37);
}

TEMPLATE_LIST_TEST_CASE("Dimensions", "[algebra][matrix][dimMxN][method]", FloatingTypes)
{
    constexpr Matrix<TestType, 17, 105> mat;

    constexpr auto dims = mat.dimensions();

    static_assert(std::get<0>(dims) == 17);
    static_assert(std::get<1>(dims) == 105);

    const auto [rows, cols] = mat.dimensions();

    CHECK(rows == 17);
    CHECK(cols == 105);
}

TEMPLATE_LIST_TEST_CASE("Internal data access", "[algebra][matrix][dimMxN][method]", IntegerTypes)
{
    TestType mat_00 = 1, mat_01 = 5, mat_02 = 9, mat_03 = 13;

    // clang-format off
    Matrix<TestType, 1, 4> mat1 = { mat_00, mat_01, mat_02, mat_03 };

    const Matrix<TestType, 1, 4> mat2 = { mat_00, mat_01, mat_02, mat_03 };
    // clang-format on

    auto*       data1 = mat1.data();
    const auto* data2 = mat2.data();

    CHECK(data1[0] == 1);
    CHECK(data1[1] == 5);
    CHECK(data1[2] == 9);
    CHECK(data1[3] == 13);

    CHECK(data2[0] == 1);
    CHECK(data2[1] == 5);
    CHECK(data2[2] == 9);
    CHECK(data2[3] == 13);
}

TEMPLATE_LIST_TEST_CASE("Internal data access", "[algebra][matrix][dimMxN][method]", FloatingTypes)
{
    TestType mat_00 = 1.0, mat_10 = 2.0, mat_20 = 3.0, mat_30 = 4.0;

    // clang-format off
    Matrix<TestType, 4, 1> mat1 = { mat_00,
                                    mat_10,
                                    mat_20,
                                    mat_30 };

    const Matrix<TestType, 4, 1> mat2 = { mat_00,
                                          mat_10,
                                          mat_20,
                                          mat_30 };
    // clang-format on

    auto*       data1 = mat1.data();
    const auto* data2 = mat2.data();

    CHECK(data1[0] == 1.0);
    CHECK(data1[1] == 2.0);
    CHECK(data1[2] == 3.0);
    CHECK(data1[3] == 4.0);

    CHECK(data2[0] == 1.0);
    CHECK(data2[1] == 2.0);
    CHECK(data2[2] == 3.0);
    CHECK(data2[3] == 4.0);
}

TEMPLATE_LIST_TEST_CASE("Transpose", "[algebra][matrix][dimMxN][method]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  1, mat_01 =  2, mat_02 =  3, mat_03 =  4,
                       mat_10 =  5, mat_11 =  6, mat_12 =  7, mat_13 =  8;

    constexpr Matrix<TestType, 2, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13 };
    // clang-format on

    constexpr Matrix<TestType, 4, 2> transposed = mat.transposed();

    static_assert(transposed(0, 0) == mat(0, 0));
    static_assert(transposed(1, 0) == mat(0, 1));
    static_assert(transposed(2, 0) == mat(0, 2));
    static_assert(transposed(3, 0) == mat(0, 3));

    static_assert(transposed(0, 1) == mat(1, 0));
    static_assert(transposed(1, 1) == mat(1, 1));
    static_assert(transposed(2, 1) == mat(1, 2));
    static_assert(transposed(3, 1) == mat(1, 3));

    CHECK(transposed(0, 0) == mat(0, 0));
    CHECK(transposed(1, 0) == mat(0, 1));
    CHECK(transposed(2, 0) == mat(0, 2));
    CHECK(transposed(3, 0) == mat(0, 3));

    CHECK(transposed(0, 1) == mat(1, 0));
    CHECK(transposed(1, 1) == mat(1, 1));
    CHECK(transposed(2, 1) == mat(1, 2));
    CHECK(transposed(3, 1) == mat(1, 3));
}

TEMPLATE_LIST_TEST_CASE("Transpose", "[algebra][matrix][dimMxN][method]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 =  -1.0, mat_01 =  -2.0,
                       mat_10 =  -5.0, mat_11 =  -6.0,
                       mat_20 =  -9.0, mat_21 = -10.0,
                       mat_30 = -13.0, mat_31 = -14.0;

    constexpr Matrix<TestType, 4, 2> mat = { mat_00, mat_01,
                                             mat_10, mat_11,
                                             mat_20, mat_21,
                                             mat_30, mat_31 };
    // clang-format on

    constexpr Matrix<TestType, 2, 4> transposed = mat.transposed();

    static_assert(transposed(0, 0) == mat(0, 0));
    static_assert(transposed(1, 0) == mat(0, 1));

    static_assert(transposed(0, 1) == mat(1, 0));
    static_assert(transposed(1, 1) == mat(1, 1));

    static_assert(transposed(0, 2) == mat(2, 0));
    static_assert(transposed(1, 2) == mat(2, 1));

    static_assert(transposed(0, 3) == mat(3, 0));
    static_assert(transposed(1, 3) == mat(3, 1));

    CHECK(transposed(0, 0) == mat(0, 0));
    CHECK(transposed(1, 0) == mat(0, 1));

    CHECK(transposed(0, 1) == mat(1, 0));
    CHECK(transposed(1, 1) == mat(1, 1));

    CHECK(transposed(0, 2) == mat(2, 0));
    CHECK(transposed(1, 2) == mat(2, 1));

    CHECK(transposed(0, 3) == mat(3, 0));
    CHECK(transposed(1, 3) == mat(3, 1));
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 163, mat_01 = -57, mat_02 = 694,
                       mat_10 = -28, mat_11 = -61, mat_12 = 107,
                       mat_20 = 355, mat_21 = 271, mat_22 = 311,
                       mat_30 = -42, mat_31 = -80, mat_32 = 129;

    constexpr TestType scalar = 19;

    constexpr Matrix<TestType, 4, 3> mat = { mat_00, mat_01, mat_02,
                                             mat_10, mat_11, mat_12,
                                             mat_20, mat_21, mat_22,
                                             mat_30, mat_31, mat_32 };
    // clang-format on

    constexpr Matrix<TestType, 4, 3> scaled1 = scalar * mat;
    constexpr Matrix<TestType, 4, 3> scaled2 = mat * scalar;

    static_assert(scaled1(0, 0) == 3097);
    static_assert(scaled1(1, 0) == -532);
    static_assert(scaled1(2, 0) == 6745);
    static_assert(scaled1(3, 0) == -798);

    static_assert(scaled1(0, 1) == -1083);
    static_assert(scaled1(1, 1) == -1159);
    static_assert(scaled1(2, 1) == 5149);
    static_assert(scaled1(3, 1) == -1520);

    static_assert(scaled1(0, 2) == 13186);
    static_assert(scaled1(1, 2) == 2033);
    static_assert(scaled1(2, 2) == 5909);
    static_assert(scaled1(3, 2) == 2451);

    static_assert(scaled2(0, 0) == 3097);
    static_assert(scaled2(1, 0) == -532);
    static_assert(scaled2(2, 0) == 6745);
    static_assert(scaled2(3, 0) == -798);

    static_assert(scaled2(0, 1) == -1083);
    static_assert(scaled2(1, 1) == -1159);
    static_assert(scaled2(2, 1) == 5149);
    static_assert(scaled2(3, 1) == -1520);

    static_assert(scaled2(0, 2) == 13186);
    static_assert(scaled2(1, 2) == 2033);
    static_assert(scaled2(2, 2) == 5909);
    static_assert(scaled2(3, 2) == 2451);

    CHECK(scaled1(0, 0) == 3097);
    CHECK(scaled1(1, 0) == -532);
    CHECK(scaled1(2, 0) == 6745);
    CHECK(scaled1(3, 0) == -798);

    CHECK(scaled1(0, 1) == -1083);
    CHECK(scaled1(1, 1) == -1159);
    CHECK(scaled1(2, 1) == 5149);
    CHECK(scaled1(3, 1) == -1520);

    CHECK(scaled1(0, 2) == 13186);
    CHECK(scaled1(1, 2) == 2033);
    CHECK(scaled1(2, 2) == 5909);
    CHECK(scaled1(3, 2) == 2451);

    CHECK(scaled2(0, 0) == 3097);
    CHECK(scaled2(1, 0) == -532);
    CHECK(scaled2(2, 0) == 6745);
    CHECK(scaled2(3, 0) == -798);

    CHECK(scaled2(0, 1) == -1083);
    CHECK(scaled2(1, 1) == -1159);
    CHECK(scaled2(2, 1) == 5149);
    CHECK(scaled2(3, 1) == -1520);

    CHECK(scaled2(0, 2) == 13186);
    CHECK(scaled2(1, 2) == 2033);
    CHECK(scaled2(2, 2) == 5909);
    CHECK(scaled2(3, 2) == 2451);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 9.49, mat_01 = 1.18, mat_02 = 85.42, mat_03 =  -7.08,
                       mat_10 = 4.78, mat_11 = -3.8, mat_12 = 33.37, mat_13 = -27.40,
                       mat_20 = -5.3, mat_21 = 4.45, mat_22 = -9.89, mat_23 = -82.73;

    constexpr TestType scalar = -3.45;

    constexpr Matrix<TestType, 3, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23 };
    // clang-format on

    constexpr Matrix<TestType, 3, 4> scaled1 = scalar * mat;
    constexpr Matrix<TestType, 3, 4> scaled2 = mat * scalar;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(scaled1(0, 0) - -32.7405) < elp);
    static_assert(std::abs(scaled1(1, 0) - -16.491) < elp);
    static_assert(std::abs(scaled1(2, 0) - 18.285) < elp);

    static_assert(std::abs(scaled1(0, 1) - -4.071) < elp);
    static_assert(std::abs(scaled1(1, 1) - 13.11) < elp);
    static_assert(std::abs(scaled1(2, 1) - -15.3525) < elp);

    static_assert(std::abs(scaled1(0, 2) - -294.699) < elp);
    static_assert(std::abs(scaled1(1, 2) - -115.1265) < elp);
    static_assert(std::abs(scaled1(2, 2) - 34.1205) < elp);

    static_assert(std::abs(scaled1(0, 3) - 24.426) < elp);
    static_assert(std::abs(scaled1(1, 3) - 94.53) < elp);
    static_assert(std::abs(scaled1(2, 3) - 285.4185) < elp);

    static_assert(std::abs(scaled2(0, 0) - -32.7405) < elp);
    static_assert(std::abs(scaled2(1, 0) - -16.491) < elp);
    static_assert(std::abs(scaled2(2, 0) - 18.285) < elp);

    static_assert(std::abs(scaled2(0, 1) - -4.071) < elp);
    static_assert(std::abs(scaled2(1, 1) - 13.11) < elp);
    static_assert(std::abs(scaled2(2, 1) - -15.3525) < elp);

    static_assert(std::abs(scaled2(0, 2) - -294.699) < elp);
    static_assert(std::abs(scaled2(1, 2) - -115.1265) < elp);
    static_assert(std::abs(scaled2(2, 2) - 34.1205) < elp);

    static_assert(std::abs(scaled2(0, 3) - 24.426) < elp);
    static_assert(std::abs(scaled2(1, 3) - 94.53) < elp);
    static_assert(std::abs(scaled2(2, 3) - 285.4185) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(scaled1(0, 0) == Catch::Approx(-32.7405).epsilon(ehp));
    CHECK(scaled1(1, 0) == Catch::Approx(-16.491).epsilon(ehp));
    CHECK(scaled1(2, 0) == Catch::Approx(18.285).epsilon(ehp));

    CHECK(scaled1(0, 1) == Catch::Approx(-4.071).epsilon(ehp));
    CHECK(scaled1(1, 1) == Catch::Approx(13.11).epsilon(ehp));
    CHECK(scaled1(2, 1) == Catch::Approx(-15.3525).epsilon(ehp));

    CHECK(scaled1(0, 2) == Catch::Approx(-294.699).epsilon(ehp));
    CHECK(scaled1(1, 2) == Catch::Approx(-115.1265).epsilon(ehp));
    CHECK(scaled1(2, 2) == Catch::Approx(34.1205).epsilon(ehp));

    CHECK(scaled1(0, 3) == Catch::Approx(24.426).epsilon(ehp));
    CHECK(scaled1(1, 3) == Catch::Approx(94.53).epsilon(ehp));
    CHECK(scaled1(2, 3) == Catch::Approx(285.4185).epsilon(ehp));

    CHECK(scaled2(0, 0) == Catch::Approx(-32.7405).epsilon(ehp));
    CHECK(scaled2(1, 0) == Catch::Approx(-16.491).epsilon(ehp));
    CHECK(scaled2(2, 0) == Catch::Approx(18.285).epsilon(ehp));

    CHECK(scaled2(0, 1) == Catch::Approx(-4.071).epsilon(ehp));
    CHECK(scaled2(1, 1) == Catch::Approx(13.11).epsilon(ehp));
    CHECK(scaled2(2, 1) == Catch::Approx(-15.3525).epsilon(ehp));

    CHECK(scaled2(0, 2) == Catch::Approx(-294.699).epsilon(ehp));
    CHECK(scaled2(1, 2) == Catch::Approx(-115.1265).epsilon(ehp));
    CHECK(scaled2(2, 2) == Catch::Approx(34.1205).epsilon(ehp));

    CHECK(scaled2(0, 3) == Catch::Approx(24.426).epsilon(ehp));
    CHECK(scaled2(1, 3) == Catch::Approx(94.53).epsilon(ehp));
    CHECK(scaled2(2, 3) == Catch::Approx(285.4185).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Matrix multiplication operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 14, mat1_01 =   1, mat1_02 =  19, mat1_03 = 15,
                       mat1_10 = 13, mat1_11 = -27, mat1_12 =  18, mat1_13 = -3;

    constexpr TestType mat2_00 = -5, mat2_01 = -6, mat2_02 = -9,
                       mat2_10 = -5, mat2_11 = -2, mat2_12 = 21,
                       mat2_20 = 11, mat2_21 =  4, mat2_22 = -3,
                       mat2_30 = 23, mat2_31 = -4, mat2_32 = -5;

    constexpr Matrix<TestType, 2, 4> mat1 = { mat1_00, mat1_01, mat1_02, mat1_03,
                                              mat1_10, mat1_11, mat1_12, mat1_13 };

    constexpr Matrix<TestType, 4, 3> mat2 = { mat2_00, mat2_01, mat2_02,
                                              mat2_10, mat2_11, mat2_12,
                                              mat2_20, mat2_21, mat2_22,
                                              mat2_30, mat2_31, mat2_32 };
    // clang-format on

    constexpr Matrix<TestType, 2, 3> mul = mat1 * mat2;

    static_assert(mul(0, 0) == 479);
    static_assert(mul(1, 0) == 199);

    static_assert(mul(0, 1) == -70);
    static_assert(mul(1, 1) == 60);

    static_assert(mul(0, 2) == -237);
    static_assert(mul(1, 2) == -723);

    CHECK(mul(0, 0) == 479);
    CHECK(mul(1, 0) == 199);

    CHECK(mul(0, 1) == -70);
    CHECK(mul(1, 1) == 60);

    CHECK(mul(0, 2) == -237);
    CHECK(mul(1, 2) == -723);
}

TEMPLATE_LIST_TEST_CASE("Matrix multiplication operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat1_00 = 14.9, mat1_01 =   1.0,
                       mat1_10 = 13.8, mat1_11 = -27.1,
                       mat1_20 = -8.3, mat1_21 = -18.2,
                       mat1_30 = 19.4, mat1_31 =  13.3;

    constexpr TestType mat2_00 = -5.0, mat2_01 = -6.9, mat2_02 = -9.5, mat2_03 = 10.7, mat2_04 = 52.1,
                       mat2_10 = -5.1, mat2_11 = -2.8, mat2_12 = 21.3, mat2_13 = -4.3, mat2_14 = -8.2;

    constexpr Matrix<TestType, 4, 2> mat1 = { mat1_00, mat1_01,
                                              mat1_10, mat1_11,
                                              mat1_20, mat1_21,
                                              mat1_30, mat1_31 };

    constexpr Matrix<TestType, 2, 5> mat2 = { mat2_00, mat2_01, mat2_02, mat2_03, mat2_04,
                                              mat2_10, mat2_11, mat2_12, mat2_13, mat2_14 };
    // clang-format on

    constexpr Matrix<TestType, 4, 5> mul = mat1 * mat2;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(mul(0, 0) - -79.6) < elp);
    static_assert(std::abs(mul(1, 0) - 69.21) < elp);
    static_assert(std::abs(mul(2, 0) - 134.32) < elp);
    static_assert(std::abs(mul(3, 0) - -164.83) < elp);

    static_assert(std::abs(mul(0, 1) - -105.61) < elp);
    static_assert(std::abs(mul(1, 1) - -19.34) < elp);
    static_assert(std::abs(mul(2, 1) - 108.23) < elp);
    static_assert(std::abs(mul(3, 1) - -171.1) < elp);

    static_assert(std::abs(mul(0, 2) - -120.25) < elp);
    static_assert(std::abs(mul(1, 2) - -708.33) < elp);
    static_assert(std::abs(mul(2, 2) - -308.81) < elp);
    static_assert(std::abs(mul(3, 2) - 98.99) < elp);

    static_assert(std::abs(mul(0, 3) - 155.13) < elp);
    static_assert(std::abs(mul(1, 3) - 264.19) < elp);
    static_assert(std::abs(mul(2, 3) - -10.55) < elp);
    static_assert(std::abs(mul(3, 3) - 150.39) < elp);

    static_assert(std::abs(mul(0, 4) - 768.09) < elp);
    static_assert(std::abs(mul(1, 4) - 941.2) < elp);
    static_assert(std::abs(mul(2, 4) - -283.19) < elp);
    static_assert(std::abs(mul(3, 4) - 901.68) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mul(0, 0) == Catch::Approx(-79.6).epsilon(ehp));
    CHECK(mul(1, 0) == Catch::Approx(69.21).epsilon(ehp));
    CHECK(mul(2, 0) == Catch::Approx(134.32).epsilon(ehp));
    CHECK(mul(3, 0) == Catch::Approx(-164.83).epsilon(ehp));

    CHECK(mul(0, 1) == Catch::Approx(-105.61).epsilon(ehp));
    CHECK(mul(1, 1) == Catch::Approx(-19.34).epsilon(ehp));
    CHECK(mul(2, 1) == Catch::Approx(108.23).epsilon(ehp));
    CHECK(mul(3, 1) == Catch::Approx(-171.1).epsilon(ehp));

    CHECK(mul(0, 2) == Catch::Approx(-120.25).epsilon(ehp));
    CHECK(mul(1, 2) == Catch::Approx(-708.33).epsilon(ehp));
    CHECK(mul(2, 2) == Catch::Approx(-308.81).epsilon(ehp));
    CHECK(mul(3, 2) == Catch::Approx(98.99).epsilon(ehp));

    CHECK(mul(0, 3) == Catch::Approx(155.13).epsilon(ehp));
    CHECK(mul(1, 3) == Catch::Approx(264.19).epsilon(ehp));
    CHECK(mul(2, 3) == Catch::Approx(-10.55).epsilon(elp));  // Cannot achieve ehp precision with float
    CHECK(mul(3, 3) == Catch::Approx(150.39).epsilon(ehp));

    CHECK(mul(0, 4) == Catch::Approx(768.09).epsilon(ehp));
    CHECK(mul(1, 4) == Catch::Approx(941.2).epsilon(ehp));
    CHECK(mul(2, 4) == Catch::Approx(-283.19).epsilon(ehp));
    CHECK(mul(3, 4) == Catch::Approx(901.68).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Matrix vector multiplication", "[algebra][matrix][dimMxN][method]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 14, mat_01 =   1, mat_02 =  19, mat_03 = 15,
                       mat_10 = 13, mat_11 = -27, mat_12 =  18, mat_13 = -3,
                       mat_20 = -8, mat_21 = -18, mat_22 = -23, mat_23 = 21,
                       mat_30 = 19, mat_31 =  13, mat_32 = -10, mat_33 = 12;

    constexpr TestType vec_0 = -1, vec_1 = 7, vec_2 = 0, vec_3 = 3;

    constexpr Matrix<TestType, 4, 4> mat1 = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33 };

    constexpr Matrix<TestType, 2, 4> mat2 = { mat_00, mat_01, mat_02, mat_03,
                                              mat_10, mat_11, mat_12, mat_13 };

    constexpr Vector<TestType, 4> vec = { vec_0, vec_1, vec_2, vec_3 };
    // clang-format on

    constexpr Vector<TestType, 4> mul1 = mat1 * vec;
    constexpr Vector<TestType, 2> mul2 = mat2 * vec;

    static_assert(mul1[0] == 38);
    static_assert(mul1[1] == -211);
    static_assert(mul1[2] == -55);
    static_assert(mul1[3] == 108);

    static_assert(mul1[0] == 38);
    static_assert(mul1[1] == -211);

    CHECK(mul1[0] == 38);
    CHECK(mul1[1] == -211);
    CHECK(mul1[2] == -55);
    CHECK(mul1[3] == 108);

    CHECK(mul2[0] == 38);
    CHECK(mul2[1] == -211);
}

TEMPLATE_LIST_TEST_CASE("Matrix vector multiplication", "[algebra][matrix][dimMxN][method]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 14.10, mat_01 =   1.14, mat_02 =  19.18, mat_03 = 15.22,
                       mat_10 = 13.11, mat_11 = -27.15, mat_12 =  18.19, mat_13 = -3.23,
                       mat_20 = -8.12, mat_21 = -18.16, mat_22 = -23.20, mat_23 = 21.24,
                       mat_30 = 19.13, mat_31 =  13.17, mat_32 = -10.21, mat_33 = 12.25,
                       mat_40 = 14.10, mat_41 = -27.15, mat_42 = -23.20, mat_43 = 12.25;

    constexpr TestType vec_0 = -1.26, vec_1 = 0.0, vec_2 = 5.28, vec_3 = 3.29;

    constexpr Matrix<TestType, 4, 4> mat1 = { mat_00, mat_01, mat_02, mat_03,
                                              mat_10, mat_11, mat_12, mat_13,
                                              mat_20, mat_21, mat_22, mat_23,
                                              mat_30, mat_31, mat_32, mat_33 };

    constexpr Matrix<TestType, 5, 4> mat2 = { mat_00, mat_01, mat_02, mat_03,
                                              mat_10, mat_11, mat_12, mat_13,
                                              mat_20, mat_21, mat_22, mat_23,
                                              mat_30, mat_31, mat_32, mat_33,
                                              mat_40, mat_41, mat_42, mat_43 };

    constexpr Vector<TestType, 4> vec = { vec_0, vec_1, vec_2, vec_3 };
    // clang-format on

    constexpr Vector<TestType, 4> mul1 = mat1 * vec;
    constexpr Vector<TestType, 5> mul2 = mat2 * vec;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(mul1[0] - 133.5782) < elp);
    static_assert(std::abs(mul1[1] - 68.8979) < elp);
    static_assert(std::abs(mul1[2] - -42.3852) < elp);
    static_assert(std::abs(mul1[3] - -37.7101) < elp);

    static_assert(std::abs(mul2[0] - 133.5782) < elp);
    static_assert(std::abs(mul2[1] - 68.8979) < elp);
    static_assert(std::abs(mul2[2] - -42.3852) < elp);
    static_assert(std::abs(mul2[3] - -37.7101) < elp);
    static_assert(std::abs(mul2[4] - -99.9595) < elp);

    constexpr auto ehp = epsilonHighPrecision<TestType>();

    CHECK(mul1[0] == Catch::Approx(133.5782).epsilon(ehp));
    CHECK(mul1[1] == Catch::Approx(68.8979).epsilon(ehp));
    CHECK(mul1[2] == Catch::Approx(-42.3852).epsilon(ehp));
    CHECK(mul1[3] == Catch::Approx(-37.7101).epsilon(ehp));

    CHECK(mul2[0] == Catch::Approx(133.5782).epsilon(ehp));
    CHECK(mul2[1] == Catch::Approx(68.8979).epsilon(ehp));
    CHECK(mul2[2] == Catch::Approx(-42.3852).epsilon(ehp));
    CHECK(mul2[3] == Catch::Approx(-37.7101).epsilon(ehp));
    CHECK(mul2[4] == Catch::Approx(-99.9595).epsilon(ehp));
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][matrix][dimMxN][operator]", IntegerTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 165, mat_01 = -57, mat_02 = 693, mat_03 = -33,
                       mat_10 = -27, mat_11 = -63, mat_12 = 117, mat_13 = -15,
                       mat_20 = 351, mat_21 = 270, mat_22 = 312, mat_23 = -96,
                       mat_30 = -42, mat_31 = -81, mat_32 = 129, mat_33 =   0,
                       mat_40 = 333, mat_41 = 666, mat_42 = 999, mat_43 = 123;

    constexpr TestType scalar = 3;

    constexpr Matrix<TestType, 5, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13,
                                             mat_20, mat_21, mat_22, mat_23,
                                             mat_30, mat_31, mat_32, mat_33,
                                             mat_40, mat_41, mat_42, mat_43 };
    // clang-format on

    constexpr Matrix<TestType, 5, 4> scaled = mat / scalar;

    static_assert(scaled(0, 0) == 55);
    static_assert(scaled(1, 0) == -9);
    static_assert(scaled(2, 0) == 117);
    static_assert(scaled(3, 0) == -14);
    static_assert(scaled(4, 0) == 111);

    static_assert(scaled(0, 1) == -19);
    static_assert(scaled(1, 1) == -21);
    static_assert(scaled(2, 1) == 90);
    static_assert(scaled(3, 1) == -27);
    static_assert(scaled(4, 1) == 222);

    static_assert(scaled(0, 2) == 231);
    static_assert(scaled(1, 2) == 39);
    static_assert(scaled(2, 2) == 104);
    static_assert(scaled(3, 2) == 43);
    static_assert(scaled(4, 2) == 333);

    static_assert(scaled(0, 3) == -11);
    static_assert(scaled(1, 3) == -5);
    static_assert(scaled(2, 3) == -32);
    static_assert(scaled(3, 3) == 0);
    static_assert(scaled(4, 3) == 41);

    CHECK(scaled(0, 0) == 55);
    CHECK(scaled(1, 0) == -9);
    CHECK(scaled(2, 0) == 117);
    CHECK(scaled(3, 0) == -14);
    CHECK(scaled(4, 0) == 111);

    CHECK(scaled(0, 1) == -19);
    CHECK(scaled(1, 1) == -21);
    CHECK(scaled(2, 1) == 90);
    CHECK(scaled(3, 1) == -27);
    CHECK(scaled(4, 1) == 222);

    CHECK(scaled(0, 2) == 231);
    CHECK(scaled(1, 2) == 39);
    CHECK(scaled(2, 2) == 104);
    CHECK(scaled(3, 2) == 43);
    CHECK(scaled(4, 2) == 333);

    CHECK(scaled(0, 3) == -11);
    CHECK(scaled(1, 3) == -5);
    CHECK(scaled(2, 3) == -32);
    CHECK(scaled(3, 3) == 0);
    CHECK(scaled(4, 3) == 41);

    const TestType zero = 0;
    CHECK_THROWS(mat / zero);
}

TEMPLATE_LIST_TEST_CASE("division operator", "[algebra][matrix][dimMxN][operator]", FloatingTypes)
{
    // clang-format off
    constexpr TestType mat_00 = 9.49, mat_01 = 1.18, mat_02 = 85.42, mat_03 =  -7.08,
                       mat_10 = 4.78, mat_11 = -3.8, mat_12 = 33.37, mat_13 = -27.40;

    constexpr TestType scalar = -3.45;

    constexpr Matrix<TestType, 2, 4> mat = { mat_00, mat_01, mat_02, mat_03,
                                             mat_10, mat_11, mat_12, mat_13 };
    // clang-format on

    constexpr Matrix<TestType, 2, 4> scaled = mat / scalar;

    constexpr auto elp = epsilonLowPrecision<TestType>();

    static_assert(std::abs(scaled(0, 0) - -2.75072463768116) < elp);
    static_assert(std::abs(scaled(1, 0) - -1.38550724637681) < elp);

    static_assert(std::abs(scaled(0, 1) - -0.342028985507246) < elp);
    static_assert(std::abs(scaled(1, 1) - 1.10144927536232) < elp);

    static_assert(std::abs(scaled(0, 2) - -24.7594202898551) < elp);
    static_assert(std::abs(scaled(1, 2) - -9.67246376811594) < elp);

    static_assert(std::abs(scaled(0, 3) - 2.05217391304348) < elp);
    static_assert(std::abs(scaled(1, 3) - 7.94202898550725) < elp);

    const auto ehp = epsilonHighPrecision<TestType>();

    CHECK(scaled(0, 0) == Catch::Approx(-2.75072463768116).epsilon(ehp));
    CHECK(scaled(1, 0) == Catch::Approx(-1.38550724637681).epsilon(ehp));

    CHECK(scaled(0, 1) == Catch::Approx(-0.342028985507246).epsilon(ehp));
    CHECK(scaled(1, 1) == Catch::Approx(1.10144927536232).epsilon(ehp));

    CHECK(scaled(0, 2) == Catch::Approx(-24.7594202898551).epsilon(ehp));
    CHECK(scaled(1, 2) == Catch::Approx(-9.67246376811594).epsilon(ehp));

    CHECK(scaled(0, 3) == Catch::Approx(2.05217391304348).epsilon(ehp));
    CHECK(scaled(1, 3) == Catch::Approx(7.94202898550725).epsilon(ehp));

    const TestType zero = 0.0;
    CHECK_THROWS(mat / zero);
}

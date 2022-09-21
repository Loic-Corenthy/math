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

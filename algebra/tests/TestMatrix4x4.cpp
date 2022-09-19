#include "algebra/Matrix.hpp"

#include "Helper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <iostream>

using LCNS::compileTimeEpsilon;
using LCNS::runTimeEpsilon;
using LCNS::Algebra::Matrix;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double, long double>;

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

    const auto rte = runTimeEpsilon<TestType>();

    CHECK(det1 == Catch::Approx(6810.0026).epsilon(rte));
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
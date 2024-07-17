#include "algebra/Algebra.hpp"

#include "Helper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <numbers>

using LCNS::epsilonHighPrecision;
using LCNS::epsilonLowPrecision;
using LCNS::epsilonVeryLowPrecision;
using LCNS::Algebra::Matrix;
using LCNS::Algebra::Quaternion;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double>;

using std::numbers::pi;

consteval double DegToRad(double deg) { return deg * pi / 180.0; }

void CheckMatricesAreEqual(const auto& lhs, const auto& rhs, const auto precision)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            CHECK(lhs(i, j) == Catch::Approx(rhs(i, j)).epsilon(precision));
        }
    }
}

TEMPLATE_LIST_TEST_CASE("Euler angles from 3x3 rotation matrix", "[algebra][mapping]", FloatingTypes)
{
    SECTION("Example 1: (Rz,Ry,Rx)=(20, 15, 30)")
    {
        // clang-format off
        constexpr TestType mat_00 =  0.9076734, mat_01 = -0.1745930, mat_02 =  0.3816364,
                           mat_10 =  0.3303661, mat_11 =  0.8580583, mat_12 = -0.3931846,
                           mat_20 = -0.2588190, mat_21 =  0.4829629, mat_22 =  0.8365163;

        constexpr Matrix<TestType, 3, 3> mat = { mat_00, mat_01, mat_02,
                                                 mat_10, mat_11, mat_12,
                                                 mat_20, mat_21, mat_22 };
        // clang-format on

        const auto [psi, theta, phi] = EulerAnglesFromRotationMatrix(mat);

        const auto elp = epsilonLowPrecision<TestType>();
        CHECK(psi == Catch::Approx(DegToRad(30.0)).epsilon(elp));
        CHECK(theta == Catch::Approx(DegToRad(15.0)).epsilon(elp));
        CHECK(phi == Catch::Approx(DegToRad(20.0)).epsilon(elp));
    }

    SECTION("Example 2: (Rz,Ry,Rx)=(-17, 81.5, -1.3)")
    {
        // clang-format off
        constexpr TestType mat_00 =  0.1477714, mat_01 = -0.2673898, mat_02 = 0.9521903,
                           mat_10 = -0.0033534, mat_11 =  0.9626189, mat_12 = 0.2708388,
                           mat_20 = -0.9890159, mat_21 = -0.0432153, mat_22 = 0.1413508;

        constexpr Matrix<TestType, 3, 3> mat = { mat_00, mat_01, mat_02,
                                                 mat_10, mat_11, mat_12,
                                                 mat_20, mat_21, mat_22 };
        // clang-format on

        const auto [psi, theta, phi] = EulerAnglesFromRotationMatrix(mat);

        const auto elp = epsilonLowPrecision<TestType>();
        CHECK(psi == Catch::Approx(DegToRad(-17.0)).epsilon(elp));
        CHECK(theta == Catch::Approx(DegToRad(81.5)).epsilon(elp));
        CHECK(phi == Catch::Approx(DegToRad(-1.3)).epsilon(elp));
    }
}

TEMPLATE_LIST_TEST_CASE("Quaternion from 3x3 rotation matrix", "[algebra][mapping]", FloatingTypes)
{
    SECTION("Example 1: (Rz,Ry,Rx)=(20, 15, 30)")
    {
        // clang-format off
        constexpr TestType mat_00 =  0.9076734, mat_01 = -0.1745930, mat_02 =  0.3816364,
                           mat_10 =  0.3303661, mat_11 =  0.8580583, mat_12 = -0.3931846,
                           mat_20 = -0.2588190, mat_21 =  0.4829629, mat_22 =  0.8365163;

        constexpr Matrix<TestType, 3, 3> mat = { mat_00, mat_01, mat_02,
                                                 mat_10, mat_11, mat_12,
                                                 mat_20, mat_21, mat_22 };
        // clang-format on

        const auto quat = RotationMatrixAsQuaternion(mat);

        const auto elp = epsilonLowPrecision<TestType>();
        CHECK(quat.x() == Catch::Approx(0.2308131).epsilon(elp));
        CHECK(quat.y() == Catch::Approx(0.1687222).epsilon(elp));
        CHECK(quat.z() == Catch::Approx(0.1330269).epsilon(elp));
        CHECK(quat.w() == Catch::Approx(0.9489795).epsilon(elp));
    }

    SECTION("Example 2: (Rz,Ry,Rx)=(-17, 81.5, -1.3)")
    {
        // clang-format off
        constexpr TestType mat_00 =  0.1477714, mat_01 = -0.2673898, mat_02 = 0.9521903,
                           mat_10 = -0.0033534, mat_11 =  0.9626189, mat_12 = 0.2708388,
                           mat_20 = -0.9890159, mat_21 = -0.0432153, mat_22 = 0.1413508;

        constexpr Matrix<TestType, 3, 3> mat = { mat_00, mat_01, mat_02,
                                                 mat_10, mat_11, mat_12,
                                                 mat_20, mat_21, mat_22 };
        // clang-format on

        const auto quat = RotationMatrixAsQuaternion(mat);

        const auto elp = epsilonLowPrecision<TestType>();
        CHECK(quat.x() == Catch::Approx(-0.1046442).epsilon(elp));
        CHECK(quat.y() == Catch::Approx(0.6468185).epsilon(elp));
        CHECK(quat.z() == Catch::Approx(0.0879781).epsilon(elp));
        CHECK(quat.w() == Catch::Approx(0.7502901).epsilon(elp));
    }
}

TEMPLATE_LIST_TEST_CASE("3x3 rotation matrix from quaternion", "[algebra][mapping]", FloatingTypes)
{
    const auto elp  = epsilonLowPrecision<TestType>();
    const auto evlp = epsilonVeryLowPrecision<TestType>();

    SECTION("Example 1: (Rz,Ry,Rx)=(-17, 81.5, -1.3)")
    {
        const TestType x = -0.1046442;
        const TestType y = 0.6468185;
        const TestType z = 0.0879781;
        const TestType w = 0.7502901;

        const Quaternion<TestType> quat(x, y, z, w);

        // clang-format off
        constexpr TestType mat_00 =  0.1477714, mat_01 = -0.2673898, mat_02 = 0.9521903,
                           mat_10 = -0.0033534, mat_11 =  0.9626189, mat_12 = 0.2708388,
                           mat_20 = -0.9890159, mat_21 = -0.0432153, mat_22 = 0.1413508;

        constexpr Matrix<TestType, 3, 3> expected_result = { mat_00, mat_01, mat_02,
                                                             mat_10, mat_11, mat_12,
                                                             mat_20, mat_21, mat_22 };
        // clang-format on

        const auto mat = QuaternionAsRotationMatrix(quat);

        CheckMatricesAreEqual(mat, expected_result, evlp);
    }

    SECTION("Example 2: (Rz,Ry,Rx)=(167.2, -56.5, 123.0)")
    {
        const TestType x = 0.464072;
        const TestType y = 0.7441422;
        const TestType z = 0.3107339;
        const TestType w = -0.366516;

        const Quaternion<TestType> quat(x, y, z, w);

        // clang-format off
        constexpr TestType mat_00 = -0.3006064, mat_01 = 0.9184490, mat_02 = -0.2570742,
                           mat_10 =  0.4628933, mat_11 = 0.3761632, mat_12 =  0.8026400,
                           mat_20 =  0.8338858, mat_21 = 0.1222808, mat_22 = -0.5382210;

        constexpr Matrix<TestType, 3, 3> expected_result = { mat_00, mat_01, mat_02,
                                                             mat_10, mat_11, mat_12,
                                                             mat_20, mat_21, mat_22 };
        // clang-format on

        const auto mat = QuaternionAsRotationMatrix(quat);

        CheckMatricesAreEqual(mat, expected_result, elp);
    }
}

TEMPLATE_LIST_TEST_CASE("3x3 matrix to quaternion to 3x3 matrix", "[algebra][mapping]", FloatingTypes)
{
    const auto evlp = epsilonVeryLowPrecision<TestType>();

    SECTION("Example 1: Null matrix")
    {
        constexpr Matrix<TestType, 3, 3> nullMatrix;

        const auto quat          = RotationMatrixAsQuaternion(nullMatrix);
        const auto reconstructed = QuaternionAsRotationMatrix(quat);

        CheckMatricesAreEqual(nullMatrix, reconstructed, evlp);
    }

    SECTION("Example 2: (Rz,Ry,Rx)=(0, 0, 0)")
    {
        constexpr Matrix<TestType, 3, 3> identityRotationMatrix;

        const auto quat          = RotationMatrixAsQuaternion(identityRotationMatrix);
        const auto reconstructed = QuaternionAsRotationMatrix(quat);

        CheckMatricesAreEqual(identityRotationMatrix, reconstructed, evlp);
    }

    SECTION("Example 3: (Rz,Ry,Rx)=(-17, 81.5, -1.3)")
    {
        // clang-format off
        constexpr TestType mat_00 =  0.1477714, mat_01 = -0.2673898, mat_02 = 0.9521903,
                           mat_10 = -0.0033534, mat_11 =  0.9626189, mat_12 = 0.2708388,
                           mat_20 = -0.9890159, mat_21 = -0.0432153, mat_22 = 0.1413508;

        constexpr Matrix<TestType, 3, 3> original = { mat_00, mat_01, mat_02,
                                                      mat_10, mat_11, mat_12,
                                                      mat_20, mat_21, mat_22 };
        // clang-format on

        const auto quat          = RotationMatrixAsQuaternion(original);
        const auto reconstructed = QuaternionAsRotationMatrix(quat);

        CheckMatricesAreEqual(original, reconstructed, evlp);
    }

    SECTION("Example 2: (Rz,Ry,Rx)=(167.2, -56.5, 123.0)")
    {
        // clang-format off
        constexpr TestType mat_00 = -0.3006064, mat_01 = 0.9184490, mat_02 = -0.2570742,
                           mat_10 =  0.4628933, mat_11 = 0.3761632, mat_12 =  0.8026400,
                           mat_20 =  0.8338858, mat_21 = 0.1222808, mat_22 = -0.5382210;

        constexpr Matrix<TestType, 3, 3> original = { mat_00, mat_01, mat_02,
                                                      mat_10, mat_11, mat_12,
                                                      mat_20, mat_21, mat_22 };
        // clang-format on

        const auto quat          = RotationMatrixAsQuaternion(original);
        const auto reconstructed = QuaternionAsRotationMatrix(quat);

        CheckMatricesAreEqual(original, reconstructed, evlp);
    }
}

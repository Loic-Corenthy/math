#include "algebra/Algebra.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/generators/catch_generators_random.hpp>

#include <numbers>

using Catch::Generators::random;
using LCNS::Algebra::Quaternion;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double>;

using std::numbers::pi;

TEMPLATE_LIST_TEST_CASE("Accessor operator (read only)", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x = -1;
    constexpr TestType y = 123;
    constexpr TestType z = 555;
    constexpr TestType w = -77;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    static_assert(quat[0] == x);
    static_assert(quat[1] == y);
    static_assert(quat[2] == z);
    static_assert(quat[3] == w);

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator (read only)", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 123.0;
    constexpr TestType z = 555.138;
    constexpr TestType w = -0.00932;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    static_assert(quat[0] == x);
    static_assert(quat[1] == y);
    static_assert(quat[2] == z);
    static_assert(quat[3] == w);

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator (read/write)", "[algebra][quat][operator]", IntegerTypes)
{
    Quaternion<TestType> quat;

    TestType x = -1;
    TestType y = 123;
    TestType z = 555;
    TestType w = -77;

    quat[0] = x;
    quat[1] = y;
    quat[2] = z;
    quat[3] = w;

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator (read/write)", "[algebra][quat][operator]", FloatingTypes)
{
    Quaternion<TestType> quat;

    TestType x = -1.0;
    TestType y = 123.0;
    TestType z = 555.138;
    TestType w = -0.00932;

    quat[0] = x;
    quat[1] = y;
    quat[2] = z;
    quat[3] = w;

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][quat][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Quaternion<TestType> quat;

    static_assert(quat[0] == zero);
    static_assert(quat[1] == zero);
    static_assert(quat[2] == zero);
    static_assert(quat[3] == zero);

    CHECK(quat[0] == zero);
    CHECK(quat[1] == zero);
    CHECK(quat[2] == zero);
    CHECK(quat[3] == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][quat][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Quaternion<TestType> quat;

    static_assert(quat[0] == zero);
    static_assert(quat[1] == zero);
    static_assert(quat[2] == zero);
    static_assert(quat[3] == zero);

    CHECK(quat[0] == zero);
    CHECK(quat[1] == zero);
    CHECK(quat[2] == zero);
    CHECK(quat[3] == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][quat][constructor]", IntegerTypes)
{
    constexpr TestType x = 1000;
    constexpr TestType y = -456;
    constexpr TestType z = 7;
    constexpr TestType w = -9991;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    static_assert(quat[0] == x);
    static_assert(quat[1] == y);
    static_assert(quat[2] == z);
    static_assert(quat[3] == w);

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][quat][constructor]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 0.001;
    constexpr TestType z = 69.548;
    constexpr TestType w = 110.011;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    static_assert(quat[0] == x);
    static_assert(quat[1] == y);
    static_assert(quat[2] == z);
    static_assert(quat[3] == w);

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][quat][constructor]", IntegerTypes)
{
    constexpr TestType x = 22;
    constexpr TestType y = 77;
    constexpr TestType z = -15974;
    constexpr TestType w = 0;

    constexpr Quaternion<TestType> quat = { x, y, z, w };

    static_assert(quat[0] == x);
    static_assert(quat[1] == y);
    static_assert(quat[2] == z);
    static_assert(quat[3] == w);

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][quat][constructor]", FloatingTypes)
{
    constexpr TestType x = -9.35;
    constexpr TestType y = -2022.2108;
    constexpr TestType z = 84309.3;
    constexpr TestType w = 2188888455.1;

    constexpr Quaternion<TestType> quat = { x, y, z, w };

    static_assert(quat[0] == x);
    static_assert(quat[1] == y);
    static_assert(quat[2] == z);
    static_assert(quat[3] == w);

    CHECK(quat[0] == x);
    CHECK(quat[1] == y);
    CHECK(quat[2] == z);
    CHECK(quat[3] == w);
}

TEMPLATE_LIST_TEST_CASE("Comparison operator", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x1    = 32199;
    constexpr TestType y1    = -11111;
    constexpr TestType z1    = 28;
    constexpr TestType w1    = -1249;
    constexpr TestType other = -47;

    constexpr Quaternion<TestType> quat(x1, y1, z1, w1);
    constexpr Quaternion<TestType> identical(x1, y1, z1, w1);
    constexpr Quaternion<TestType> different1(other, y1, z1, w1);
    constexpr Quaternion<TestType> different2(x1, other, z1, w1);
    constexpr Quaternion<TestType> different3(x1, y1, other, w1);
    constexpr Quaternion<TestType> different4(x1, y1, z1, other);

    static_assert(quat == identical);
    static_assert(quat != different1);
    static_assert(quat != different2);
    static_assert(quat != different3);
    static_assert(quat != different4);

    CHECK(quat == identical);
    CHECK(quat != different1);
    CHECK(quat != different2);
    CHECK(quat != different3);
    CHECK(quat != different4);
}

TEMPLATE_LIST_TEST_CASE("Comparison operator", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x1    = -7456.2345;
    constexpr TestType y1    = 4899.88888;
    constexpr TestType z1    = 6713.0;
    constexpr TestType w1    = 0.0;
    constexpr TestType other = -0.0001;

    constexpr Quaternion<TestType> quat(x1, y1, z1, w1);
    constexpr Quaternion<TestType> identical(x1, y1, z1, w1);
    constexpr Quaternion<TestType> different1(other, y1, z1, w1);
    constexpr Quaternion<TestType> different2(x1, other, z1, w1);
    constexpr Quaternion<TestType> different3(x1, y1, other, w1);
    constexpr Quaternion<TestType> different4(x1, y1, z1, other);

    static_assert(quat == identical);
    static_assert(quat != different1);
    static_assert(quat != different2);
    static_assert(quat != different3);
    static_assert(quat != different4);

    CHECK(quat == identical);
    CHECK(quat != different1);
    CHECK(quat != different2);
    CHECK(quat != different3);
    CHECK(quat != different4);
}

TEMPLATE_LIST_TEST_CASE("Spaceship operator", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x1 = 12;
    constexpr TestType y1 = 67;
    constexpr TestType z1 = 5;
    constexpr TestType w1 = -35;
    constexpr TestType x2 = 78;
    constexpr TestType y2 = -999;
    constexpr TestType z2 = 0;
    constexpr TestType w2 = 17;

    constexpr Quaternion<TestType> smaller(x1, y1, z1, w1);
    constexpr Quaternion<TestType> bigger(x2, y2, z2, w2);

    static_assert(smaller <= bigger);
    static_assert(smaller < bigger);

    CHECK(smaller <= bigger);
    CHECK(smaller < bigger);
}

TEMPLATE_LIST_TEST_CASE("Spaceship operator", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x1 = 12.1;
    constexpr TestType y1 = 67.22;
    constexpr TestType z1 = 2.4;
    constexpr TestType w1 = -2.4;
    constexpr TestType x2 = 78.333;
    constexpr TestType y2 = -999.4444;
    constexpr TestType z2 = 4.2;
    constexpr TestType w2 = -4.2;

    constexpr Quaternion<TestType> smaller(x1, y1, z1, w1);
    constexpr Quaternion<TestType> bigger(x2, y2, z2, w2);

    static_assert(smaller <= bigger);
    static_assert(smaller < bigger);

    CHECK(smaller <= bigger);
    CHECK(smaller < bigger);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x1 = 776;
    constexpr TestType y1 = 145;
    constexpr TestType z1 = -999;
    constexpr TestType w1 = -23555;
    constexpr TestType x2 = 4;
    constexpr TestType y2 = -146;
    constexpr TestType z2 = 565;
    constexpr TestType w2 = -1917;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr Quaternion<TestType> quat2(x2, y2, z2, w2);
    constexpr Quaternion<TestType> sum = quat1 + quat2;

    static_assert(sum[0] == 780);
    static_assert(sum[1] == -1);
    static_assert(sum[2] == -434);
    static_assert(sum[2] == -434);

    CHECK(sum[0] == 780);
    CHECK(sum[1] == -1);
    CHECK(sum[2] == -434);
    CHECK(sum[2] == -434);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x1 = 1.0;
    constexpr TestType y1 = -2.0;
    constexpr TestType z1 = 16.25;
    constexpr TestType w1 = 160000.25;
    constexpr TestType x2 = 23.76;
    constexpr TestType y2 = -55.11;
    constexpr TestType z2 = -32.25;
    constexpr TestType w2 = 150000.25;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr Quaternion<TestType> quat2(x2, y2, z2, w2);
    constexpr Quaternion<TestType> sum = quat1 + quat2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(sum[0] - 24.76) < epsilon);
    static_assert(std::abs(sum[1] - -57.11) < epsilon);
    static_assert(std::abs(sum[2] - -16.0) < epsilon);
    static_assert(std::abs(sum[3] - 310000.5) < epsilon);

    const auto sumX = Catch::Approx(24.76).epsilon(epsilon);
    const auto sumY = Catch::Approx(-57.11).epsilon(epsilon);
    const auto sumZ = Catch::Approx(-16.0).epsilon(epsilon);
    const auto sumW = Catch::Approx(310000.5).epsilon(epsilon);

    CHECK(sum[0] == sumX);
    CHECK(sum[1] == sumY);
    CHECK(sum[2] == sumZ);
    CHECK(sum[3] == sumW);
}

TEMPLATE_LIST_TEST_CASE("Subtraction operator", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x1 = 6;
    constexpr TestType y1 = 100;
    constexpr TestType z1 = 256;
    constexpr TestType w1 = 1024;
    constexpr TestType x2 = -4;
    constexpr TestType y2 = 146;
    constexpr TestType z2 = 146;
    constexpr TestType w2 = 1024;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr Quaternion<TestType> quat2(x2, y2, z2, w2);
    constexpr Quaternion<TestType> sub = quat1 - quat2;

    static_assert(sub[0] == 10);
    static_assert(sub[1] == -46);
    static_assert(sub[2] == 110);
    static_assert(sub[3] == 0);

    CHECK(sub[0] == 10);
    CHECK(sub[1] == -46);
    CHECK(sub[2] == 110);
    CHECK(sub[3] == 0);
}

TEMPLATE_LIST_TEST_CASE("Subtraction  operator", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x1 = 24567.957;
    constexpr TestType y1 = -2.0;
    constexpr TestType z1 = -92.0;
    constexpr TestType w1 = 150000.7;
    constexpr TestType x2 = 24266.957;
    constexpr TestType y2 = -55.11;
    constexpr TestType z2 = 10.0;
    constexpr TestType w2 = 150000.7;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr Quaternion<TestType> quat2(x2, y2, z2, w2);
    constexpr Quaternion<TestType> sub = quat1 - quat2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(sub[0] - 301.0) < epsilon);
    static_assert(std::abs(sub[1] - 53.11) < epsilon);
    static_assert(std::abs(sub[2] - -102.0) < epsilon);
    static_assert(std::abs(sub[3] - 0.0) < epsilon);

    const auto sumX = Catch::Approx(301.0).epsilon(epsilon);
    const auto sumY = Catch::Approx(53.11).epsilon(epsilon);
    const auto sumZ = Catch::Approx(-102.0).epsilon(epsilon);
    const auto sumW = Catch::Approx(0.0).epsilon(epsilon);

    CHECK(sub[0] == sumX);
    CHECK(sub[1] == sumY);
    CHECK(sub[2] == sumZ);
    CHECK(sub[3] == sumW);
}

TEMPLATE_LIST_TEST_CASE("Accessors", "[algebra][quat][accessor]", IntegerTypes)
{
    constexpr TestType x1 = 684;
    constexpr TestType y1 = -1;
    constexpr TestType z1 = -19874;
    constexpr TestType w1 = 32767;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);

    static_assert(quat1.x() == x1);
    static_assert(quat1.y() == y1);
    static_assert(quat1.z() == z1);
    static_assert(quat1.w() == w1);

    CHECK(quat1.x() == x1);
    CHECK(quat1.y() == y1);
    CHECK(quat1.z() == z1);
    CHECK(quat1.w() == w1);

    const TestType x2 = -321;
    const TestType y2 = -199;
    const TestType z2 = 31687;
    const TestType w2 = -32768;

    Quaternion<TestType> quat2;
    quat2.x() = x2;
    quat2.y() = y2;
    quat2.z() = z2;
    quat2.w() = w2;

    CHECK(quat2.x() == x2);
    CHECK(quat2.y() == y2);
    CHECK(quat2.z() == z2);
    CHECK(quat2.w() == w2);
}

TEMPLATE_LIST_TEST_CASE("Accessors", "[algebra][quat][accessor]", FloatingTypes)
{
    constexpr TestType x1 = 248.7;
    constexpr TestType y1 = -1000.0;
    constexpr TestType z1 = 1000.0;
    constexpr TestType w1 = 3.402823e+38;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);

    static_assert(quat1.x() == x1);
    static_assert(quat1.y() == y1);
    static_assert(quat1.z() == z1);
    static_assert(quat1.w() == w1);

    CHECK(quat1.x() == x1);
    CHECK(quat1.y() == y1);
    CHECK(quat1.z() == z1);
    CHECK(quat1.w() == w1);

    const TestType x2 = -77.986;
    const TestType y2 = -765.239;
    const TestType z2 = 8822.33;
    const TestType w2 = 1.175494e-38;

    Quaternion<TestType> quat2;
    quat2.x() = x2;
    quat2.y() = y2;
    quat2.z() = z2;
    quat2.w() = w2;

    CHECK(quat2.x() == x2);
    CHECK(quat2.y() == y2);
    CHECK(quat2.z() == z2);
    CHECK(quat2.w() == w2);
}

TEMPLATE_LIST_TEST_CASE("Hamilton product", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x1   = 3;
    constexpr TestType y1   = 4;
    constexpr TestType z1   = 3;
    constexpr TestType w1   = 7;
    constexpr TestType x2   = 9;
    constexpr TestType y2   = -1;
    constexpr TestType z2   = -3;
    constexpr TestType w2   = 4;
    constexpr TestType resX = 66;
    constexpr TestType resY = 45;
    constexpr TestType resZ = -48;
    constexpr TestType resW = 14;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr Quaternion<TestType> quat2(x2, y2, z2, w2);

    constexpr Quaternion<TestType> hamiltonProduct = quat1 * quat2;

    static_assert(hamiltonProduct.x() == resX);
    static_assert(hamiltonProduct.y() == resY);
    static_assert(hamiltonProduct.z() == resZ);
    static_assert(hamiltonProduct.w() == resW);

    CHECK(hamiltonProduct.x() == resX);
    CHECK(hamiltonProduct.y() == resY);
    CHECK(hamiltonProduct.z() == resZ);
    CHECK(hamiltonProduct.w() == resW);
}

TEMPLATE_LIST_TEST_CASE("Hamilton product", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x1   = 3.2;
    constexpr TestType y1   = 4.1;
    constexpr TestType z1   = -2.3;
    constexpr TestType w1   = pi / 4.0;
    constexpr TestType x2   = 0.9;
    constexpr TestType y2   = -1.8;
    constexpr TestType z2   = -3.5;
    constexpr TestType w2   = pi / 3.0;
    constexpr TestType resX = -14.4321;
    constexpr TestType resY = 12.0098;
    constexpr TestType resZ = -14.6074;
    constexpr TestType resW = -2.72753;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr Quaternion<TestType> quat2(x2, y2, z2, w2);

    constexpr Quaternion<TestType> hamiltonProduct = quat1 * quat2;

    // Couldn't easily find more precise external results for the product:
    // limiting the required precision to the value below for now
    constexpr auto epsilon = 1e-4;

    static_assert(std::abs(hamiltonProduct.x() - resX) < epsilon);
    static_assert(std::abs(hamiltonProduct.y() - resY) < epsilon);
    static_assert(std::abs(hamiltonProduct.z() - resZ) < epsilon);
    static_assert(std::abs(hamiltonProduct.w() - resW) < epsilon);

    CHECK(std::abs(hamiltonProduct.x() - resX) < epsilon);
    CHECK(std::abs(hamiltonProduct.y() - resY) < epsilon);
    CHECK(std::abs(hamiltonProduct.z() - resZ) < epsilon);
    CHECK(std::abs(hamiltonProduct.w() - resW) < epsilon);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x      = 15;
    constexpr TestType y      = 97;
    constexpr TestType z      = -9;
    constexpr TestType w      = -19;
    constexpr TestType scalar = 66;

    constexpr Quaternion<TestType> quat(x, y, z, w);
    constexpr Quaternion<TestType> scaled = quat * scalar;

    static_assert(scaled[0] == 990);
    static_assert(scaled[1] == 6402);
    static_assert(scaled[2] == -594);
    static_assert(scaled[2] == -594);

    CHECK(scaled[0] == 990);
    CHECK(scaled[1] == 6402);
    CHECK(scaled[2] == -594);
    CHECK(scaled[2] == -594);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x      = 1.5;
    constexpr TestType y      = 9.5;
    constexpr TestType z      = -99.5;
    constexpr TestType w      = 1459.5;
    constexpr TestType scalar = 10.0;

    constexpr Quaternion<TestType> quat(x, y, z, w);
    constexpr Quaternion<TestType> scaled = quat * scalar;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(scaled[0] == 15.0);
    static_assert(scaled[1] == 95.0);
    static_assert(scaled[2] == -995.0);
    static_assert(scaled[3] == 14595.0);

    const auto scaledX = Catch::Approx(15.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(95.0).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(-995.0).epsilon(epsilon);
    const auto scaledW = Catch::Approx(14595.0).epsilon(epsilon);

    CHECK(scaled[0] == scaledX);
    CHECK(scaled[1] == scaledY);
    CHECK(scaled[2] == scaledZ);
    CHECK(scaled[3] == scaledW);
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][quat][operator]", IntegerTypes)
{
    constexpr TestType x = -85;
    constexpr TestType y = 155;
    constexpr TestType z = 32000;
    constexpr TestType w = 0;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    TestType zero = 0;
    CHECK_THROWS(quat / zero);

    constexpr TestType scalar = 5;

    constexpr Quaternion<TestType> scaled = quat / scalar;

    static_assert(scaled[0] == -17);
    static_assert(scaled[1] == 31);
    static_assert(scaled[2] == 6400);
    static_assert(scaled[3] == 0);

    CHECK(scaled[0] == -17);
    CHECK(scaled[1] == 31);
    CHECK(scaled[2] == 6400);
    CHECK(scaled[3] == 0);
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][quat][operator]", FloatingTypes)
{
    constexpr TestType x = -85.0;
    constexpr TestType y = 155.0;
    constexpr TestType z = 32000.0;
    constexpr TestType w = -16000.0;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    TestType zero = 0.0;
    CHECK_THROWS(quat / zero);

    constexpr TestType scalar = 5.0;

    constexpr Quaternion<TestType> scaled = quat / scalar;

    static_assert(scaled[0] == -17.0);
    static_assert(scaled[1] == 31.0);
    static_assert(scaled[2] == 6400.0);
    static_assert(scaled[3] == -3200.0);

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(-17.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(31.0).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(6400.0).epsilon(epsilon);
    const auto scaledW = Catch::Approx(-3200.0).epsilon(epsilon);

    CHECK(scaled[0] == scaledX);
    CHECK(scaled[1] == scaledY);
    CHECK(scaled[2] == scaledZ);
    CHECK(scaled[3] == scaledW);
}

TEMPLATE_LIST_TEST_CASE("Plus equal operator", "[algebra][quat][operator]", IntegerTypes)
{
    const TestType x1 = 776;
    const TestType y1 = 145;
    const TestType z1 = -354;
    const TestType w1 = -1000;
    const TestType x2 = 4;
    const TestType y2 = -146;
    const TestType z2 = 333;
    const TestType w2 = 10000;

    Quaternion<TestType> quat1(x1, y1, z1, w1);
    Quaternion<TestType> quat2(x2, y2, z2, w2);
    quat1 += quat2;

    CHECK(quat1[0] == 780);
    CHECK(quat1[1] == -1);
    CHECK(quat1[2] == -21);
    CHECK(quat1[3] == 9000);
}

TEMPLATE_LIST_TEST_CASE("Plus equal operator", "[algebra][quat][operator]", FloatingTypes)
{
    const TestType x1 = 18.643;
    const TestType y1 = -288.349;
    const TestType z1 = 1234.5;
    const TestType w1 = 889915.3;
    const TestType x2 = 23.767;
    const TestType y2 = 5500.1763;
    const TestType z2 = 9876.5;
    const TestType w2 = -1.3;

    Quaternion<TestType> quat1(x1, y1, z1, w1);
    Quaternion<TestType> quat2(x2, y2, z2, w2);
    quat1 += quat2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto sumX = Catch::Approx(42.410).epsilon(epsilon);
    const auto sumY = Catch::Approx(5211.8273).epsilon(epsilon);
    const auto sumZ = Catch::Approx(11111.0).epsilon(epsilon);
    const auto sumW = Catch::Approx(889914.0).epsilon(epsilon);

    CHECK(quat1[0] == sumX);
    CHECK(quat1[1] == sumY);
    CHECK(quat1[2] == sumZ);
    CHECK(quat1[3] == sumW);
}

TEMPLATE_LIST_TEST_CASE("Minus equal operator", "[algebra][quat][operator]", IntegerTypes)
{
    const TestType x1 = 776;
    const TestType y1 = 145;
    const TestType z1 = -1;
    const TestType w1 = 55;
    const TestType x2 = 4;
    const TestType y2 = -146;
    const TestType z2 = 0;
    const TestType w2 = 49;

    Quaternion<TestType> quat1(x1, y1, z1, w1);
    Quaternion<TestType> quat2(x2, y2, z2, w2);
    quat1 -= quat2;

    CHECK(quat1[0] == 772);
    CHECK(quat1[1] == 291);
    CHECK(quat1[2] == -1);
    CHECK(quat1[3] == 6);
}

TEMPLATE_LIST_TEST_CASE("Minus equal operator", "[algebra][quat][operator]", FloatingTypes)
{
    const TestType x1 = 23.325;
    const TestType y1 = -288.349;
    const TestType z1 = 2648.0;
    const TestType w1 = 2332.0;
    const TestType x2 = 20.665;
    const TestType y2 = 5500.1763;
    const TestType z2 = -52.3;
    const TestType w2 = 300.0;

    Quaternion<TestType> quat1(x1, y1, z1, w1);
    Quaternion<TestType> quat2(x2, y2, z2, w2);
    quat1 -= quat2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto subX = Catch::Approx(2.660).epsilon(epsilon);
    const auto subY = Catch::Approx(-5788.5253).epsilon(epsilon);
    const auto subZ = Catch::Approx(2700.3).epsilon(epsilon);
    const auto subW = Catch::Approx(2032.0).epsilon(epsilon);

    CHECK(quat1[0] == subX);
    CHECK(quat1[1] == subY);
    CHECK(quat1[2] == subZ);
    CHECK(quat1[3] == subW);
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][quat][operator]", IntegerTypes)
{
    const TestType x      = 15;
    const TestType y      = 97;
    const TestType z      = -444;
    const TestType w      = -6551;
    const TestType scalar = 3;

    Quaternion<TestType> quat(x, y, z, w);
    quat *= scalar;

    CHECK(quat[0] == 45);
    CHECK(quat[1] == 291);
    CHECK(quat[2] == -1332);
    CHECK(quat[3] == -19653);
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][quat][operator]", FloatingTypes)
{
    const TestType x      = 1.5;
    const TestType y      = 9.5;
    const TestType z      = -646.5;
    const TestType w      = -1.2;
    const TestType scalar = 31.22;

    Quaternion<TestType> quat(x, y, z, w);
    quat *= scalar;

    const auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(46.83).epsilon(epsilon);
    const auto scaledY = Catch::Approx(296.59).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(-20183.73).epsilon(epsilon);
    const auto scaledW = Catch::Approx(-37.464).epsilon(epsilon);

    CHECK(quat[0] == scaledX);
    CHECK(quat[1] == scaledY);
    CHECK(quat[2] == scaledZ);
    CHECK(quat[3] == scaledW);
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][quat][operator]", IntegerTypes)
{
    const TestType x = 15;
    const TestType y = 99;
    const TestType z = -72;
    const TestType w = -1020;

    Quaternion<TestType> quat(x, y, z, w);

    const TestType zero = 0;
    CHECK_THROWS(quat / zero);

    const TestType scalar = 3;
    quat /= scalar;

    CHECK(quat[0] == 5);
    CHECK(quat[1] == 33);
    CHECK(quat[2] == -24);
    CHECK(quat[3] == -340);
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][quat][operator]", FloatingTypes)
{
    const TestType x = 1.5;
    const TestType y = 9.5;
    const TestType z = -175.5;
    const TestType w = -0.51;

    Quaternion<TestType> quat(x, y, z, w);

    const TestType zero = 0.0;
    CHECK_THROWS(quat / zero);

    const TestType scalar = 0.1;
    quat /= scalar;

    const auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(15.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(95).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(-1755.0).epsilon(epsilon);
    const auto scaledW = Catch::Approx(-5.1).epsilon(epsilon);

    CHECK(quat[0] == scaledX);
    CHECK(quat[1] == scaledY);
    CHECK(quat[2] == scaledZ);
    CHECK(quat[3] == scaledW);
}

TEMPLATE_LIST_TEST_CASE("Square length", "[algebra][quat][accessor]", IntegerTypes)
{
    constexpr TestType x = 3;
    constexpr TestType y = 4;
    constexpr TestType z = 5;
    constexpr TestType w = -6;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    static_assert(quat.sqrLength() == 86);

    CHECK(quat.sqrLength() == 86);
}

TEMPLATE_LIST_TEST_CASE("Square length", "[algebra][quat][accessor]", FloatingTypes)
{
    constexpr TestType x = 69.0;
    constexpr TestType y = 260.0;
    constexpr TestType z = -2.1;
    constexpr TestType w = -1.0;

    constexpr Quaternion<TestType> quat(x, y, z, w);

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(quat.sqrLength() - 72366.41) < epsilon);

    const auto approxSqrLength = Catch::Approx(72366.41).epsilon(epsilon);

    CHECK(quat.sqrLength() == approxSqrLength);
}

TEMPLATE_LIST_TEST_CASE("Length", "[algebra][quat][accessor]", IntegerTypes)
{
    const TestType x = 3;
    const TestType y = 4;
    const TestType z = 5;
    const TestType w = 6;

    const Quaternion<TestType> quat(x, y, z, w);

    const auto approxLength = Catch::Approx(9.27361849549).epsilon(1e-9);

    CHECK(quat.length() == approxLength);
}

TEMPLATE_LIST_TEST_CASE("Length", "[algebra][quat][accessor]", FloatingTypes)
{
    const TestType x = 69.0;
    const TestType y = 260.0;
    const TestType z = -0.5;
    const TestType w = -2.33;

    const Quaternion<TestType> quat(x, y, z, w);

    const auto approxLength = Catch::Approx(269.0105553691).epsilon(1e-9);

    CHECK(quat.length() == approxLength);
}

TEMPLATE_LIST_TEST_CASE("Normalize", "[algebra][quat][accessor]", FloatingTypes)
{
    const TestType x = 69.0;
    const TestType y = 260.0;
    const TestType z = -66.9;
    const TestType w = 17.3;

    Quaternion<TestType> quat(x, y, z, w);
    quat.normalize();

    const auto one = Catch::Approx(1.0).epsilon(1e-6);

    CHECK(quat.length() == one);
}

TEMPLATE_LIST_TEST_CASE("Normalized", "[algebra][quat][accessor]", FloatingTypes)
{
    const TestType x = -69.0;
    const TestType y = -260.0;
    const TestType z = 19.7;
    const TestType w = -19.7;

    const Quaternion<TestType> quat(x, y, z, w);
    const Quaternion<TestType> normalized = quat.normalized();

    const auto one = Catch::Approx(1.0).epsilon(1e-6);

    CHECK(normalized.length() == one);
}

TEMPLATE_LIST_TEST_CASE("Is null?", "[algebra][quat][method]", IntegerTypes)
{
    constexpr TestType x    = 3;
    constexpr TestType y    = 0;
    constexpr TestType z    = 0;
    constexpr TestType w    = 1;
    constexpr TestType zero = 0;

    constexpr Quaternion<TestType> quat1(x, y, z, w);
    constexpr Quaternion<TestType> quat2;
    constexpr Quaternion<TestType> quat3 = quat1 * zero;
    constexpr Quaternion<TestType> quat4 = quat1 - quat1;

    static_assert(!quat1.isNull());
    static_assert(quat2.isNull());
    static_assert(quat3.isNull());
    static_assert(quat4.isNull());

    CHECK_FALSE(quat1.isNull());
    CHECK(quat2.isNull());
    CHECK(quat3.isNull());
    CHECK(quat4.isNull());
}

TEMPLATE_LIST_TEST_CASE("Is null?", "[algebra][quat][method]", FloatingTypes)
{
    constexpr TestType x    = -69.0;
    constexpr TestType y    = -0.0;
    constexpr TestType z    = 19.7;
    constexpr TestType w    = -19.7;
    constexpr TestType zero = 0.0;

    constexpr Quaternion<TestType> quat1(x, y, z, w);
    constexpr Quaternion<TestType> quat2;
    constexpr Quaternion<TestType> quat3 = quat1 * zero;
    constexpr Quaternion<TestType> quat4 = quat1 - quat1;

    static_assert(!quat1.isNull());
    static_assert(quat2.isNull());
    static_assert(quat3.isNull());
    static_assert(quat4.isNull());

    CHECK_FALSE(quat1.isNull());
    CHECK(quat2.isNull());
    CHECK(quat3.isNull());
    CHECK(quat4.isNull());
}

TEMPLATE_LIST_TEST_CASE("Conjugate", "[algebra][quat][method]", IntegerTypes)
{
    constexpr TestType x1 = 159;
    constexpr TestType y1 = -88;
    constexpr TestType z1 = 23;
    constexpr TestType w1 = 55;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr auto                 conjugated = quat1.conjugated();

    STATIC_CHECK(conjugated.x() == -x1);
    STATIC_CHECK(conjugated.y() == -y1);
    STATIC_CHECK(conjugated.z() == -z1);
    STATIC_CHECK(conjugated.w() == w1);

    CHECK(conjugated.x() == -x1);
    CHECK(conjugated.y() == -y1);
    CHECK(conjugated.z() == -z1);
    CHECK(conjugated.w() == w1);

    constexpr auto same = conjugated.conjugated();

    STATIC_CHECK(same == quat1);
    CHECK(same == quat1);

    const TestType min = -100;
    const TestType max = 100;
    const auto     x2  = random(min, max).get();
    const auto     y2  = random(min, max).get();
    const auto     z2  = random(min, max).get();
    const auto     w2  = random(min, max).get();

    Quaternion<TestType> quat(x2, y2, z2, w2);
    quat.conjugate();

    CHECK(quat.x() == -x2);
    CHECK(quat.y() == -y2);
    CHECK(quat.z() == -z2);
    CHECK(quat.w() == w2);

    quat.conjugate();

    CHECK(quat.x() == x2);
    CHECK(quat.y() == y2);
    CHECK(quat.z() == z2);
    CHECK(quat.w() == w2);
}

TEMPLATE_LIST_TEST_CASE("Conjugate", "[algebra][quat][method]", FloatingTypes)
{
    constexpr TestType x1 = 0.88;
    constexpr TestType y1 = -88.99;
    constexpr TestType z1 = 147.0;
    constexpr TestType w1 = -6.1;

    constexpr Quaternion<TestType> quat1(x1, y1, z1, w1);
    constexpr Quaternion<TestType> conjugated = quat1.conjugated();

    STATIC_CHECK(conjugated.x() == -x1);
    STATIC_CHECK(conjugated.y() == -y1);
    STATIC_CHECK(conjugated.z() == -z1);
    STATIC_CHECK(conjugated.w() == w1);

    CHECK(conjugated.x() == -x1);
    CHECK(conjugated.y() == -y1);
    CHECK(conjugated.z() == -z1);
    CHECK(conjugated.w() == w1);

    constexpr auto same = conjugated.conjugated();

    STATIC_CHECK(same == quat1);
    CHECK(same == quat1);

    const TestType min = -100.0;
    const TestType max = 100.0;
    const auto     x2  = random(min, max).get();
    const auto     y2  = random(min, max).get();
    const auto     z2  = random(min, max).get();
    const auto     w2  = random(min, max).get();

    Quaternion<TestType> quat(x2, y2, z2, w2);
    quat.conjugate();

    CHECK(quat.x() == -x2);
    CHECK(quat.y() == -y2);
    CHECK(quat.z() == -z2);
    CHECK(quat.w() == w2);

    quat.conjugate();

    CHECK(quat.x() == x2);
    CHECK(quat.y() == y2);
    CHECK(quat.z() == z2);
    CHECK(quat.w() == w2);
}

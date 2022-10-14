#include "algebra/Algebra.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using LCNS::Algebra::Vector;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x = -1;
    constexpr TestType y = 123;
    constexpr TestType z = 555;

    constexpr Vector<TestType, 3> vec(x, y, z);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);
    static_assert(vec[2] == z);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
    CHECK(vec[2] == z);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 123.0;
    constexpr TestType z = 555.138;

    constexpr Vector<TestType, 3> vec(x, y, z);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);
    static_assert(vec[2] == z);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
    CHECK(vec[2] == z);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim3][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Vector<TestType, 3> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);
    static_assert(vec[2] == zero);

    CHECK(vec[0] == zero);
    CHECK(vec[1] == zero);
    CHECK(vec[2] == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim3][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Vector<TestType, 3> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);
    static_assert(vec[2] == zero);

    CHECK(vec[0] == zero);
    CHECK(vec[1] == zero);
    CHECK(vec[2] == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim3][constructor]", IntegerTypes)
{
    constexpr TestType x = 1000;
    constexpr TestType y = -456;
    constexpr TestType z = 7;

    constexpr Vector<TestType, 3> vec(x, y, z);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);
    static_assert(vec[2] == z);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
    CHECK(vec[2] == z);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim3][constructor]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 0.001;
    constexpr TestType z = 69.548;

    constexpr Vector<TestType, 3> vec(x, y, z);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);
    static_assert(vec[2] == z);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
    CHECK(vec[2] == z);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim3][constructor]", IntegerTypes)
{
    constexpr TestType x = 22;
    constexpr TestType y = 77;
    constexpr TestType z = -15974;

    constexpr Vector<TestType, 3> vec = { x, y, z };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);
    static_assert(vec[2] == z);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
    CHECK(vec[2] == z);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim3][constructor]", FloatingTypes)
{
    constexpr TestType x = -9.35;
    constexpr TestType y = -2022.2108;
    constexpr TestType z = 84309.3;

    constexpr Vector<TestType, 3> vec = { x, y, z };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);
    static_assert(vec[2] == z);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
    CHECK(vec[2] == z);
}

TEMPLATE_LIST_TEST_CASE("Comparison operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x1 = 32199;
    constexpr TestType y1 = -11111;
    constexpr TestType z1 = 28;
    constexpr TestType x2 = -47;

    constexpr Vector<TestType, 3> vec(x1, y1, z1);
    constexpr Vector<TestType, 3> identical(x1, y1, z1);
    constexpr Vector<TestType, 3> different(x2, y1, z1);

    static_assert(vec == identical);
    static_assert(vec != different);

    CHECK(vec == identical);
    CHECK(vec != different);
}

TEMPLATE_LIST_TEST_CASE("Comparison operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x1 = -7456.2345;
    constexpr TestType y1 = 4899.88888;
    constexpr TestType z1 = 6713.0;
    constexpr TestType x2 = 7456.2345;

    constexpr Vector<TestType, 3> vec(x1, y1, z1);
    constexpr Vector<TestType, 3> identical(x1, y1, z1);
    constexpr Vector<TestType, 3> different(x2, y1, z1);

    static_assert(vec == identical);
    static_assert(vec != different);

    CHECK(vec == identical);
    CHECK(vec != different);
}

TEMPLATE_LIST_TEST_CASE("Spaceship operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x1 = 12;
    constexpr TestType y1 = 67;
    constexpr TestType z1 = 5;
    constexpr TestType x2 = 78;
    constexpr TestType y2 = -999;
    constexpr TestType z2 = 0;

    constexpr Vector<TestType, 3> smaller(x1, y1, z1);
    constexpr Vector<TestType, 3> bigger(x2, y2, z2);

    static_assert(smaller <= bigger);
    static_assert(smaller < bigger);

    CHECK(smaller <= bigger);
    CHECK(smaller < bigger);
}

TEMPLATE_LIST_TEST_CASE("Spaceship operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x1 = 12.1;
    constexpr TestType y1 = 67.22;
    constexpr TestType z1 = 2.4;
    constexpr TestType x2 = 78.333;
    constexpr TestType y2 = -999.4444;
    constexpr TestType z2 = 4.2;

    constexpr Vector<TestType, 3> smaller(x1, y1, z1);
    constexpr Vector<TestType, 3> bigger(x2, y2, z2);

    static_assert(smaller <= bigger);
    static_assert(smaller < bigger);

    CHECK(smaller <= bigger);
    CHECK(smaller < bigger);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x1 = 776;
    constexpr TestType y1 = 145;
    constexpr TestType z1 = -999;
    constexpr TestType x2 = 4;
    constexpr TestType y2 = -146;
    constexpr TestType z2 = 565;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);
    constexpr Vector<TestType, 3> sum = vec1 + vec2;

    static_assert(sum[0] == 780);
    static_assert(sum[1] == -1);
    static_assert(sum[2] == -434);

    CHECK(sum[0] == 780);
    CHECK(sum[1] == -1);
    CHECK(sum[2] == -434);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x1 = 1.0;
    constexpr TestType y1 = -2.0;
    constexpr TestType z1 = 16.25;
    constexpr TestType x2 = 23.76;
    constexpr TestType y2 = -55.11;
    constexpr TestType z2 = -32.25;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);
    constexpr Vector<TestType, 3> sum = vec1 + vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(sum[0] - 24.76) < epsilon);
    static_assert(std::abs(sum[1] - -57.11) < epsilon);
    static_assert(std::abs(sum[2] - -16.0) < epsilon);

    const auto sumX = Catch::Approx(24.76).epsilon(epsilon);
    const auto sumY = Catch::Approx(-57.11).epsilon(epsilon);
    const auto sumZ = Catch::Approx(-16.0).epsilon(epsilon);

    CHECK(sum[0] == sumX);
    CHECK(sum[1] == sumY);
    CHECK(sum[2] == sumZ);
}

TEMPLATE_LIST_TEST_CASE("Subtraction operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x1 = 6;
    constexpr TestType y1 = 100;
    constexpr TestType z1 = 256;
    constexpr TestType x2 = -4;
    constexpr TestType y2 = 146;
    constexpr TestType z2 = 146;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);
    constexpr Vector<TestType, 3> sub = vec1 - vec2;

    static_assert(sub[0] == 10);
    static_assert(sub[1] == -46);
    static_assert(sub[2] == 110);

    CHECK(sub[0] == 10);
    CHECK(sub[1] == -46);
    CHECK(sub[2] == 110);
}

TEMPLATE_LIST_TEST_CASE("Subtraction  operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x1 = 24567.957;
    constexpr TestType y1 = -2.0;
    constexpr TestType z1 = -92.0;
    constexpr TestType x2 = 24266.957;
    constexpr TestType y2 = -55.11;
    constexpr TestType z2 = 10.0;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);
    constexpr Vector<TestType, 3> sub = vec1 - vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(sub[0] - 301.0) < epsilon);
    static_assert(std::abs(sub[1] - 53.11) < epsilon);
    static_assert(std::abs(sub[2] - -102.0) < epsilon);

    const auto sumX = Catch::Approx(301.0).epsilon(epsilon);
    const auto sumY = Catch::Approx(53.11).epsilon(epsilon);
    const auto sumZ = Catch::Approx(-102.0).epsilon(epsilon);

    CHECK(sub[0] == sumX);
    CHECK(sub[1] == sumY);
    CHECK(sub[2] == sumZ);
}

TEMPLATE_LIST_TEST_CASE("Dot product", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x1 = 15;
    constexpr TestType y1 = 97;
    constexpr TestType z1 = 23;
    constexpr TestType x2 = -97;
    constexpr TestType y2 = 15;
    constexpr TestType z2 = 24;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);

    constexpr TestType dotProduct = vec1 * vec2;

    static_assert(dotProduct == 552);

    CHECK(dotProduct == 552);
}

TEMPLATE_LIST_TEST_CASE("Dot product", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x1 = 3.0;
    constexpr TestType y1 = 5.0;
    constexpr TestType z1 = 7.0;
    constexpr TestType x2 = 4.0;
    constexpr TestType y2 = 1.0;
    constexpr TestType z2 = -2.0;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);

    constexpr TestType dotProduct = vec1 * vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(dotProduct - 3.0) < epsilon);

    const auto dotProductApprox = Catch::Approx(3.0).epsilon(epsilon);

    CHECK(dotProduct == dotProductApprox);
}

TEMPLATE_LIST_TEST_CASE("Cross product", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x1 = 15;
    constexpr TestType y1 = 97;
    constexpr TestType z1 = 23;
    constexpr TestType x2 = -97;
    constexpr TestType y2 = 15;
    constexpr TestType z2 = 24;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);

    constexpr Vector<TestType, 3> crossProduct = vec1 ^ vec2;

    static_assert(crossProduct[0] == 1983);
    static_assert(crossProduct[1] == -2591);
    static_assert(crossProduct[2] == 9634);

    static_assert(crossProduct * vec1 == 0);
    static_assert(crossProduct * vec2 == 0);

    CHECK(crossProduct[0] == 1983);
    CHECK(crossProduct[1] == -2591);
    CHECK(crossProduct[2] == 9634);

    CHECK(crossProduct * vec1 == 0);
    CHECK(crossProduct * vec2 == 0);
}

TEMPLATE_LIST_TEST_CASE("Cross product", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x1 = 3.0;
    constexpr TestType y1 = 5.0;
    constexpr TestType z1 = 7.0;
    constexpr TestType x2 = 4.0;
    constexpr TestType y2 = 1.0;
    constexpr TestType z2 = -2.0;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);
    constexpr Vector<TestType, 3> vec2(x2, y2, z2);

    constexpr Vector<TestType, 3> crossProduct = vec1 ^ vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(crossProduct[0] - -17.0) < epsilon);
    static_assert(std::abs(crossProduct[1] - 34.0) < epsilon);
    static_assert(std::abs(crossProduct[2] - -17.0) < epsilon);

    static_assert(crossProduct * vec1 == 0.0);
    static_assert(crossProduct * vec2 == 0.0);

    const auto crossProductX = Catch::Approx(-17.0).epsilon(epsilon);
    const auto crossProductY = Catch::Approx(34.0).epsilon(epsilon);
    const auto crossProductZ = Catch::Approx(-17.0).epsilon(epsilon);

    CHECK(crossProduct[0] == crossProductX);
    CHECK(crossProduct[1] == crossProductY);
    CHECK(crossProduct[2] == crossProductZ);

    CHECK(crossProduct * vec1 == 0);
    CHECK(crossProduct * vec2 == 0);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x      = 15;
    constexpr TestType y      = 97;
    constexpr TestType z      = -9;
    constexpr TestType scalar = 66;

    constexpr Vector<TestType, 3> vec(x, y, z);
    constexpr Vector<TestType, 3> scaled = vec * scalar;

    static_assert(scaled[0] == 990);
    static_assert(scaled[1] == 6402);
    static_assert(scaled[2] == -594);

    CHECK(scaled[0] == 990);
    CHECK(scaled[1] == 6402);
    CHECK(scaled[2] == -594);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x      = 1.5;
    constexpr TestType y      = 9.5;
    constexpr TestType z      = -99.5;
    constexpr TestType scalar = 10.0;

    constexpr Vector<TestType, 3> vec(x, y, z);
    constexpr Vector<TestType, 3> scaled = vec * scalar;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(scaled[0] == 15.0);
    static_assert(scaled[1] == 95.0);
    static_assert(scaled[2] == -995.0);

    const auto scaledX = Catch::Approx(15.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(95.0).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(-995.0).epsilon(epsilon);

    CHECK(scaled[0] == scaledX);
    CHECK(scaled[1] == scaledY);
    CHECK(scaled[2] == scaledZ);
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    constexpr TestType x = -85;
    constexpr TestType y = 155;
    constexpr TestType z = 32000;

    constexpr Vector<TestType, 3> vec(x, y, z);

    TestType zero = 0;
    CHECK_THROWS(vec / zero);

    constexpr TestType scalar = 5;

    constexpr Vector<TestType, 3> scaled = vec / scalar;

    static_assert(scaled[0] == -17);
    static_assert(scaled[1] == 31);
    static_assert(scaled[2] == 6400);

    CHECK(scaled[0] == -17);
    CHECK(scaled[1] == 31);
    CHECK(scaled[2] == 6400);
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    constexpr TestType x = -85.0;
    constexpr TestType y = 155.0;
    constexpr TestType z = 32000.0;

    constexpr Vector<TestType, 3> vec(x, y, z);

    TestType zero = 0.0;
    CHECK_THROWS(vec / zero);

    constexpr TestType scalar = 5.0;

    constexpr Vector<TestType, 3> scaled = vec / scalar;

    static_assert(scaled[0] == -17.0);
    static_assert(scaled[1] == 31.0);
    static_assert(scaled[2] == 6400.0);

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(-17.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(31.0).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(6400.0).epsilon(epsilon);

    CHECK(scaled[0] == scaledX);
    CHECK(scaled[1] == scaledY);
    CHECK(scaled[2] == scaledZ);
}

TEMPLATE_LIST_TEST_CASE("Plus equal operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    const TestType x1 = 776;
    const TestType y1 = 145;
    const TestType z1 = -354;
    const TestType x2 = 4;
    const TestType y2 = -146;
    const TestType z2 = 333;

    Vector<TestType, 3> vec1(x1, y1, z1);
    Vector<TestType, 3> vec2(x2, y2, z2);
    vec1 += vec2;

    CHECK(vec1[0] == 780);
    CHECK(vec1[1] == -1);
    CHECK(vec1[2] == -21);
}

TEMPLATE_LIST_TEST_CASE("Plus equal operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    const TestType x1 = 18.643;
    const TestType y1 = -288.349;
    const TestType z1 = 1234.5;
    const TestType x2 = 23.767;
    const TestType y2 = 5500.1763;
    const TestType z2 = 9876.5;

    Vector<TestType, 3> vec1(x1, y1, z1);
    Vector<TestType, 3> vec2(x2, y2, z2);
    vec1 += vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto sumX = Catch::Approx(42.410).epsilon(epsilon);
    const auto sumY = Catch::Approx(5211.8273).epsilon(epsilon);
    const auto sumZ = Catch::Approx(11111.0).epsilon(epsilon);

    CHECK(vec1[0] == sumX);
    CHECK(vec1[1] == sumY);
    CHECK(vec1[2] == sumZ);
}

TEMPLATE_LIST_TEST_CASE("Minus equal operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    const TestType x1 = 776;
    const TestType y1 = 145;
    const TestType z1 = -1;
    const TestType x2 = 4;
    const TestType y2 = -146;
    const TestType z2 = 0;

    Vector<TestType, 3> vec1(x1, y1, z1);
    Vector<TestType, 3> vec2(x2, y2, z2);
    vec1 -= vec2;

    CHECK(vec1[0] == 772);
    CHECK(vec1[1] == 291);
    CHECK(vec1[2] == -1);
}

TEMPLATE_LIST_TEST_CASE("Minus equal operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    const TestType x1 = 23.325;
    const TestType y1 = -288.349;
    const TestType z1 = 2648.0;
    const TestType x2 = 20.665;
    const TestType y2 = 5500.1763;
    const TestType z2 = -52.3;

    Vector<TestType, 3> vec1(x1, y1, z1);
    Vector<TestType, 3> vec2(x2, y2, z2);
    vec1 -= vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto subX = Catch::Approx(2.660).epsilon(epsilon);
    const auto subY = Catch::Approx(-5788.5253).epsilon(epsilon);
    const auto subZ = Catch::Approx(2700.3).epsilon(epsilon);

    CHECK(vec1[0] == subX);
    CHECK(vec1[1] == subY);
    CHECK(vec1[2] == subZ);
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    const TestType x      = 15;
    const TestType y      = 97;
    const TestType z      = -444;
    const TestType scalar = 3;

    Vector<TestType, 3> vec(x, y, z);
    vec *= scalar;

    CHECK(vec[0] == 45);
    CHECK(vec[1] == 291);
    CHECK(vec[2] == -1332);
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    const TestType x      = 1.5;
    const TestType y      = 9.5;
    const TestType z      = -646.5;
    const TestType scalar = 31.22;

    Vector<TestType, 3> vec(x, y, z);
    vec *= scalar;

    const auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(46.83).epsilon(epsilon);
    const auto scaledY = Catch::Approx(296.59).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(-20183.73).epsilon(epsilon);

    CHECK(vec[0] == scaledX);
    CHECK(vec[1] == scaledY);
    CHECK(vec[2] == scaledZ);
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][vector][dim3][operator]", IntegerTypes)
{
    const TestType x = 15;
    const TestType y = 99;
    const TestType z = -72;

    Vector<TestType, 3> vec(x, y, z);

    const TestType zero = 0;
    CHECK_THROWS(vec / zero);

    const TestType scalar = 3;
    vec /= scalar;

    CHECK(vec[0] == 5);
    CHECK(vec[1] == 33);
    CHECK(vec[2] == -24);
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][vector][dim3][operator]", FloatingTypes)
{
    const TestType x = 1.5;
    const TestType y = 9.5;
    const TestType z = -175.5;

    Vector<TestType, 3> vec(x, y, z);

    const TestType zero = 0.0;
    CHECK_THROWS(vec / zero);

    const TestType scalar = 0.1;
    vec /= scalar;

    const auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(15.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(95).epsilon(epsilon);
    const auto scaledZ = Catch::Approx(-1755.0).epsilon(epsilon);

    CHECK(vec[0] == scaledX);
    CHECK(vec[1] == scaledY);
    CHECK(vec[2] == scaledZ);
}

TEMPLATE_LIST_TEST_CASE("Accessors", "[algebra][vector][dim3][accessor]", IntegerTypes)
{
    constexpr TestType x1 = 684;
    constexpr TestType y1 = -1;
    constexpr TestType z1 = -19874;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);

    static_assert(vec1.x() == x1);
    static_assert(vec1.y() == y1);
    static_assert(vec1.z() == z1);

    CHECK(vec1.x() == x1);
    CHECK(vec1.y() == y1);
    CHECK(vec1.z() == z1);

    const TestType x2 = -321;
    const TestType y2 = -199;
    const TestType z2 = 31687;

    Vector<TestType, 3> vec2;
    vec2.x() = x2;
    vec2.y() = y2;
    vec2.z() = z2;

    CHECK(vec2.x() == x2);
    CHECK(vec2.y() == y2);
    CHECK(vec2.z() == z2);
}

TEMPLATE_LIST_TEST_CASE("Accessors", "[algebra][vector][dim3][accessor]", FloatingTypes)
{
    constexpr TestType x1 = 248.7;
    constexpr TestType y1 = -1000.0;
    constexpr TestType z1 = 1000.0;

    constexpr Vector<TestType, 3> vec1(x1, y1, z1);

    static_assert(vec1.x() == x1);
    static_assert(vec1.y() == y1);
    static_assert(vec1.z() == z1);

    CHECK(vec1.x() == x1);
    CHECK(vec1.y() == y1);
    CHECK(vec1.z() == z1);

    const TestType x2 = -77.986;
    const TestType y2 = -765.239;
    const TestType z2 = 8822.33;

    Vector<TestType, 3> vec2;
    vec2.x() = x2;
    vec2.y() = y2;
    vec2.z() = z2;

    CHECK(vec2.x() == x2);
    CHECK(vec2.y() == y2);
    CHECK(vec2.z() == z2);
}

TEMPLATE_LIST_TEST_CASE("Square length", "[algebra][vector][dim3][accessor]", IntegerTypes)
{
    constexpr TestType x = 3;
    constexpr TestType y = 4;
    constexpr TestType z = 5;

    constexpr Vector<TestType, 3> vec(x, y, z);

    static_assert(vec.sqrLength() == 50);

    CHECK(vec.sqrLength() == 50);
}

TEMPLATE_LIST_TEST_CASE("Square length", "[algebra][vector][dim3][accessor]", FloatingTypes)
{
    constexpr TestType x = 69.0;
    constexpr TestType y = 260.0;
    constexpr TestType z = -2.1;

    constexpr Vector<TestType, 3> vec(x, y, z);

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(vec.sqrLength() - 72365.41) < epsilon);

    const auto approxSqrLength = Catch::Approx(72365.41).epsilon(epsilon);

    CHECK(vec.sqrLength() == approxSqrLength);
}

TEMPLATE_LIST_TEST_CASE("Length", "[algebra][vector][dim3][accessor]", IntegerTypes)
{
    const TestType x = 3;
    const TestType y = 4;
    const TestType z = 5;

    const Vector<TestType, 3> vec(x, y, z);

    const auto approxLength = Catch::Approx(7.071067811).epsilon(0.000000001);

    CHECK(vec.length() == approxLength);
}

TEMPLATE_LIST_TEST_CASE("Length", "[algebra][vector][dim3][accessor]", FloatingTypes)
{
    const TestType x = 69.0;
    const TestType y = 260.0;
    const TestType z = -0.5;

    const Vector<TestType, 3> vec(x, y, z);

    const auto approxLength = Catch::Approx(269.0004646836).epsilon(0.000000001);

    CHECK(vec.length() == approxLength);
}

TEMPLATE_LIST_TEST_CASE("Normalize", "[algebra][vector][dim3][accessor]", FloatingTypes)
{
    const TestType x = 69.0;
    const TestType y = 260.0;
    const TestType z = -66.9;

    Vector<TestType, 3> vec(x, y, z);
    vec.normalize();

    const auto one = Catch::Approx(1.0).epsilon(0.000001);

    CHECK(vec.length() == one);
}

TEMPLATE_LIST_TEST_CASE("Normalized", "[algebra][vector][dim3][accessor]", FloatingTypes)
{
    const TestType x = -69.0;
    const TestType y = -260.0;
    const TestType z = 19.7;

    const Vector<TestType, 3> vec(x, y, z);
    const Vector<TestType, 3> normalized = vec.normalized();

    const auto one = Catch::Approx(1.0).epsilon(0.000001);

    CHECK(normalized.length() == one);
}

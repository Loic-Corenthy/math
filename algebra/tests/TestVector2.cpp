#include "algebra/Algebra.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using LCNS::Algebra::Vector;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x = -1;
    constexpr TestType y = 123;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 123.0;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim2][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Vector<TestType, 2> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);

    CHECK(vec[0] == zero);
    CHECK(vec[1] == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim2][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Vector<TestType, 2> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);

    CHECK(vec[0] == zero);
    CHECK(vec[1] == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim2][constructor]", IntegerTypes)
{
    constexpr TestType x = 1000;
    constexpr TestType y = -456;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim2][constructor]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 0.001;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim2][constructor]", IntegerTypes)
{
    constexpr TestType x = 22;
    constexpr TestType y = 77;

    constexpr Vector<TestType, 2> vec = { x, y };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim2][constructor]", FloatingTypes)
{
    constexpr TestType x = -9.35;
    constexpr TestType y = -2022.2108;

    constexpr Vector<TestType, 2> vec = { x, y };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    CHECK(vec[0] == x);
    CHECK(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Comparison operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = 32199;
    constexpr TestType y1 = -11111;
    constexpr TestType y2 = -11110;

    constexpr Vector<TestType, 2> vec(x1, y1);
    constexpr Vector<TestType, 2> identical(x1, y1);
    constexpr Vector<TestType, 2> different(x1, y2);

    static_assert(vec == identical);
    static_assert(vec != different);

    CHECK(vec == identical);
    CHECK(vec != different);
}

TEMPLATE_LIST_TEST_CASE("Comparison operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = -7456.2345;
    constexpr TestType y1 = 4899.88888;
    constexpr TestType y2 = 4899.888;  // 4899.88880 would fail the test!

    constexpr Vector<TestType, 2> vec(x1, y1);
    constexpr Vector<TestType, 2> identical(x1, y1);
    constexpr Vector<TestType, 2> different(x1, y2);

    static_assert(vec == identical);
    static_assert(vec != different);

    CHECK(vec == identical);
    CHECK(vec != different);
}

TEMPLATE_LIST_TEST_CASE("Spaceship operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = 12;
    constexpr TestType y1 = 67;
    constexpr TestType x2 = 78;
    constexpr TestType y2 = -999;

    constexpr Vector<TestType, 2> smaller(x1, y1);
    constexpr Vector<TestType, 2> bigger(x2, y2);

    static_assert(smaller <= bigger);
    static_assert(smaller < bigger);

    CHECK(smaller <= bigger);
    CHECK(smaller < bigger);
}

TEMPLATE_LIST_TEST_CASE("Spaceship operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = 12.1;
    constexpr TestType y1 = 67.22;
    constexpr TestType x2 = 78.333;
    constexpr TestType y2 = -999.4444;

    constexpr Vector<TestType, 2> smaller(x1, y1);
    constexpr Vector<TestType, 2> bigger(x2, y2);

    static_assert(smaller <= bigger);
    static_assert(smaller < bigger);

    CHECK(smaller <= bigger);
    CHECK(smaller < bigger);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = 776;
    constexpr TestType y1 = 145;
    constexpr TestType x2 = 4;
    constexpr TestType y2 = -146;

    constexpr Vector<TestType, 2> vec1(x1, y1);
    constexpr Vector<TestType, 2> vec2(x2, y2);
    constexpr Vector<TestType, 2> sum = vec1 + vec2;

    static_assert(sum[0] == 780);
    static_assert(sum[1] == -1);

    CHECK(sum[0] == 780);
    CHECK(sum[1] == -1);
}

TEMPLATE_LIST_TEST_CASE("Addition operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = 1.0;
    constexpr TestType y1 = -2.0;
    constexpr TestType x2 = 23.76;
    constexpr TestType y2 = -55.11;

    constexpr Vector<TestType, 2> vec1(x1, y1);
    constexpr Vector<TestType, 2> vec2(x2, y2);
    constexpr Vector<TestType, 2> sum = vec1 + vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(sum[0] - 24.76) < epsilon);
    static_assert(std::abs(sum[1] - -57.11) < epsilon);

    const auto sumX = Catch::Approx(24.76).epsilon(epsilon);
    const auto sumY = Catch::Approx(-57.11).epsilon(epsilon);

    CHECK(sum[0] == sumX);
    CHECK(sum[1] == sumY);
}

TEMPLATE_LIST_TEST_CASE("Subtraction operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = 6;
    constexpr TestType y1 = 100;
    constexpr TestType x2 = -4;
    constexpr TestType y2 = 146;

    constexpr Vector<TestType, 2> vec1(x1, y1);
    constexpr Vector<TestType, 2> vec2(x2, y2);
    constexpr Vector<TestType, 2> sub = vec1 - vec2;

    static_assert(sub[0] == 10);
    static_assert(sub[1] == -46);

    CHECK(sub[0] == 10);
    CHECK(sub[1] == -46);
}

TEMPLATE_LIST_TEST_CASE("Subtraction  operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = 24567.957;
    constexpr TestType y1 = -2.0;
    constexpr TestType x2 = 24266.957;
    constexpr TestType y2 = -55.11;

    constexpr Vector<TestType, 2> vec1(x1, y1);
    constexpr Vector<TestType, 2> vec2(x2, y2);
    constexpr Vector<TestType, 2> sub = vec1 - vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(sub[0] - 301.0) < epsilon);
    static_assert(std::abs(sub[1] - 53.11) < epsilon);

    const auto sumX = Catch::Approx(301.0).epsilon(epsilon);
    const auto sumY = Catch::Approx(53.11).epsilon(epsilon);

    CHECK(sub[0] == sumX);
    CHECK(sub[1] == sumY);
}

TEMPLATE_LIST_TEST_CASE("Dot product", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = 15;
    constexpr TestType y1 = 97;
    constexpr TestType x2 = -97;
    constexpr TestType y2 = 15;

    constexpr Vector<TestType, 2> vec1(x1, y1);
    constexpr Vector<TestType, 2> vec2(x2, y2);

    constexpr TestType dotProduct = vec1 * vec2;

    static_assert(dotProduct == 0);

    CHECK(dotProduct == 0);
}

TEMPLATE_LIST_TEST_CASE("Dot product", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = 3.0;
    constexpr TestType y1 = 5.0;
    constexpr TestType x2 = 4.0;
    constexpr TestType y2 = 1.0;

    constexpr Vector<TestType, 2> vec1(x1, y1);
    constexpr Vector<TestType, 2> vec2(x2, y2);

    constexpr TestType dotProduct = vec1 * vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(dotProduct - 17.0) < epsilon);

    const auto dotProductApprox = Catch::Approx(17.0).epsilon(epsilon);

    CHECK(dotProduct == dotProductApprox);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x      = 15;
    constexpr TestType y      = 97;
    constexpr TestType scalar = 66;

    constexpr Vector<TestType, 2> vec(x, y);
    constexpr Vector<TestType, 2> scaled = vec * scalar;

    static_assert(scaled[0] == 990);
    static_assert(scaled[1] == 6402);

    CHECK(scaled[0] == 990);
    CHECK(scaled[1] == 6402);
}

TEMPLATE_LIST_TEST_CASE("Scalar multiplication operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x      = 1.5;
    constexpr TestType y      = 9.5;
    constexpr TestType scalar = 10.0;

    constexpr Vector<TestType, 2> vec(x, y);
    constexpr Vector<TestType, 2> scaled = vec * scalar;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(scaled[0] == 15.0);
    static_assert(scaled[1] == 95.0);

    const auto scaledX = Catch::Approx(15.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(95.0).epsilon(epsilon);

    CHECK(scaled[0] == scaledX);
    CHECK(scaled[1] == scaledY);
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType            x = -85;
    constexpr TestType            y = 155;
    constexpr Vector<TestType, 2> vec(x, y);

    TestType zero = 0;
    CHECK_THROWS(vec / zero);

    constexpr TestType scalar = 5;

    constexpr Vector<TestType, 2> scaled = vec / scalar;

    static_assert(scaled[0] == -17);
    static_assert(scaled[1] == 31);

    CHECK(scaled[0] == -17);
    CHECK(scaled[1] == 31);
}

TEMPLATE_LIST_TEST_CASE("Scalar division operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType            x = -85.0;
    constexpr TestType            y = 155.0;
    constexpr Vector<TestType, 2> vec(x, y);

    TestType zero = 0.0;
    CHECK_THROWS(vec / zero);

    constexpr TestType scalar = 5.0;

    constexpr Vector<TestType, 2> scaled = vec / scalar;

    static_assert(scaled[0] == -17.0);
    static_assert(scaled[1] == 31.0);

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(-17.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(31.0).epsilon(epsilon);

    CHECK(scaled[0] == scaledX);
    CHECK(scaled[1] == scaledY);
}

TEMPLATE_LIST_TEST_CASE("Plus equal operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    const TestType x1 = 776;
    const TestType y1 = 145;
    const TestType x2 = 4;
    const TestType y2 = -146;

    Vector<TestType, 2> vec1(x1, y1);
    Vector<TestType, 2> vec2(x2, y2);
    vec1 += vec2;

    CHECK(vec1[0] == 780);
    CHECK(vec1[1] == -1);
}

TEMPLATE_LIST_TEST_CASE("Plus equal operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    const TestType x1 = 18.643;
    const TestType y1 = -288.349;
    const TestType x2 = 23.767;
    const TestType y2 = 5500.1763;

    Vector<TestType, 2> vec1(x1, y1);
    Vector<TestType, 2> vec2(x2, y2);
    vec1 += vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto sumX = Catch::Approx(42.410).epsilon(epsilon);
    const auto sumY = Catch::Approx(5211.8273).epsilon(epsilon);

    CHECK(vec1[0] == sumX);
    CHECK(vec1[1] == sumY);
}

TEMPLATE_LIST_TEST_CASE("Minus equal operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    const TestType x1 = 776;
    const TestType y1 = 145;
    const TestType x2 = 4;
    const TestType y2 = -146;

    Vector<TestType, 2> vec1(x1, y1);
    Vector<TestType, 2> vec2(x2, y2);
    vec1 -= vec2;

    CHECK(vec1[0] == 772);
    CHECK(vec1[1] == 291);
}

TEMPLATE_LIST_TEST_CASE("Minus equal operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    const TestType x1 = 23.325;
    const TestType y1 = -288.349;
    const TestType x2 = 20.665;
    const TestType y2 = 5500.1763;

    Vector<TestType, 2> vec1(x1, y1);
    Vector<TestType, 2> vec2(x2, y2);
    vec1 -= vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto subX = Catch::Approx(2.660).epsilon(epsilon);
    const auto subY = Catch::Approx(-5788.5253).epsilon(epsilon);

    CHECK(vec1[0] == subX);
    CHECK(vec1[1] == subY);
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    const TestType x      = 15;
    const TestType y      = 97;
    const TestType scalar = 3;

    Vector<TestType, 2> vec(x, y);
    vec *= scalar;

    CHECK(vec[0] == 45);
    CHECK(vec[1] == 291);
}

TEMPLATE_LIST_TEST_CASE("Times equal operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    const TestType x      = 1.5;
    const TestType y      = 9.5;
    const TestType scalar = 31.22;

    Vector<TestType, 2> vec(x, y);
    vec *= scalar;

    const auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(46.83).epsilon(epsilon);
    const auto scaledY = Catch::Approx(296.59).epsilon(epsilon);

    CHECK(vec[0] == scaledX);
    CHECK(vec[1] == scaledY);
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    const TestType x = 15;
    const TestType y = 99;

    Vector<TestType, 2> vec(x, y);

    const TestType zero = 0;
    CHECK_THROWS(vec / zero);

    const TestType scalar = 3;
    vec /= scalar;

    CHECK(vec[0] == 5);
    CHECK(vec[1] == 33);
}

TEMPLATE_LIST_TEST_CASE("Divide equal operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    const TestType x = 1.5;
    const TestType y = 9.5;

    Vector<TestType, 2> vec(x, y);

    const TestType zero = 0.0;
    CHECK_THROWS(vec / zero);

    const TestType scalar = 0.1;
    vec /= scalar;

    const auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    const auto scaledX = Catch::Approx(15.0).epsilon(epsilon);
    const auto scaledY = Catch::Approx(95).epsilon(epsilon);

    CHECK(vec[0] == scaledX);
    CHECK(vec[1] == scaledY);
}

TEMPLATE_LIST_TEST_CASE("Accessors", "[algebra][vector][dim2][accessor]", IntegerTypes)
{
    constexpr TestType x1 = 684;
    constexpr TestType y1 = -1;

    constexpr Vector<TestType, 2> vec1(x1, y1);

    static_assert(vec1.x() == x1);
    static_assert(vec1.y() == y1);

    CHECK(vec1.x() == x1);
    CHECK(vec1.y() == y1);

    const TestType x2 = -321;
    const TestType y2 = -199;

    Vector<TestType, 2> vec2;
    vec2.x() = x2;
    vec2.y() = y2;

    CHECK(vec2.x() == x2);
    CHECK(vec2.y() == y2);
}

TEMPLATE_LIST_TEST_CASE("Accessors", "[algebra][vector][dim2][accessor]", FloatingTypes)
{
    constexpr TestType x1 = 248.7;
    constexpr TestType y1 = -1000.0;

    constexpr Vector<TestType, 2> vec1(x1, y1);

    static_assert(vec1.x() == x1);
    static_assert(vec1.y() == y1);

    CHECK(vec1.x() == x1);
    CHECK(vec1.y() == y1);

    const TestType x2 = -77.986;
    const TestType y2 = -765.239;

    Vector<TestType, 2> vec2;
    vec2.x() = x2;
    vec2.y() = y2;

    CHECK(vec2.x() == x2);
    CHECK(vec2.y() == y2);
}

TEMPLATE_LIST_TEST_CASE("Square length", "[algebra][vector][dim2][accessor]", IntegerTypes)
{
    constexpr TestType x = 3;
    constexpr TestType y = 4;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec.sqrLength() == 25);

    CHECK(vec.sqrLength() == 25);
}

TEMPLATE_LIST_TEST_CASE("Square length", "[algebra][vector][dim2][accessor]", FloatingTypes)
{
    constexpr TestType x = 69.0;
    constexpr TestType y = 260.0;

    constexpr Vector<TestType, 2> vec(x, y);

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    static_assert(std::abs(vec.sqrLength() - 72361.0) < epsilon);

    const auto approxSqrLength = Catch::Approx(72361.0).epsilon(epsilon);

    CHECK(vec.sqrLength() == approxSqrLength);
}

TEMPLATE_LIST_TEST_CASE("Length", "[algebra][vector][dim2][accessor]", IntegerTypes)
{
    const TestType x = 3;
    const TestType y = 4;

    const Vector<TestType, 2> vec(x, y);

    CHECK(vec.length() == 5);
}

TEMPLATE_LIST_TEST_CASE("Length", "[algebra][vector][dim2][accessor]", FloatingTypes)
{
    const TestType x = 69.0;
    const TestType y = 260.0;

    const Vector<TestType, 2> vec(x, y);

    const auto approxLength = Catch::Approx(269.0).epsilon(std::numeric_limits<TestType>::epsilon() * 100);

    CHECK(vec.length() == approxLength);
}

TEMPLATE_LIST_TEST_CASE("Normalize", "[algebra][vector][dim2][accessor]", FloatingTypes)
{
    const TestType x = 69.0;
    const TestType y = 260.0;

    Vector<TestType, 2> vec(x, y);
    vec.normalize();

    const auto one = Catch::Approx(1.0).epsilon(std::numeric_limits<TestType>::epsilon() * 100);

    CHECK(vec.length() == one);
}

TEMPLATE_LIST_TEST_CASE("Normalized", "[algebra][vector][dim2][accessor]", FloatingTypes)
{
    const TestType x = -69.0;
    const TestType y = -260.0;

    const Vector<TestType, 2> vec(x, y);
    const Vector<TestType, 2> normalized = vec.normalized();

    const auto one = Catch::Approx(1.0).epsilon(std::numeric_limits<TestType>::epsilon() * 100);

    CHECK(normalized.length() == one);
}
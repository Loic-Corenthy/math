#include "algebra/Algebra.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using LCNS::Algebra::Vector;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double, long double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x = -1;
    constexpr TestType y = 123;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    REQUIRE(vec[0] == x);
    REQUIRE(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 123.0;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    Catch::Approx targetX = Catch::Approx(x).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    Catch::Approx targetY = Catch::Approx(y).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == targetX);
    REQUIRE(vec[1] == targetY);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim2][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Vector<TestType, 2> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);

    REQUIRE(vec[0] == zero);
    REQUIRE(vec[1] == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim2][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Vector<TestType, 2> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);

    Catch::Approx target = Catch::Approx(0).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == target);
    REQUIRE(vec[1] == target);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim2][constructor]", IntegerTypes)
{
    constexpr TestType x = 1000;
    constexpr TestType y = -456;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    REQUIRE(vec[0] == x);
    REQUIRE(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim2][constructor]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 0.001;

    constexpr Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    Catch::Approx targetX = Catch::Approx(x).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    Catch::Approx targetY = Catch::Approx(y).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == targetX);
    REQUIRE(vec[1] == targetY);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim2][constructor]", IntegerTypes)
{
    constexpr TestType x = 22;
    constexpr TestType y = 77;

    constexpr Vector<TestType, 2> vec = { x, y };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    REQUIRE(vec[0] == x);
    REQUIRE(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim2][constructor]", FloatingTypes)
{
    constexpr TestType x = -9.35;
    constexpr TestType y = -2022.2108;

    constexpr Vector<TestType, 2> vec = { x, y };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    Catch::Approx targetX = Catch::Approx(x).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    Catch::Approx targetY = Catch::Approx(y).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == targetX);
    REQUIRE(vec[1] == targetY);
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

    REQUIRE(vec == identical);
    REQUIRE(vec != different);
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

    REQUIRE(vec == identical);
    REQUIRE(vec != different);
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

    REQUIRE(smaller <= bigger);
    REQUIRE(smaller < bigger);
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

    REQUIRE(smaller <= bigger);
    REQUIRE(smaller < bigger);
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

    REQUIRE(sum[0] == 780);
    REQUIRE(sum[1] == -1);
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

    REQUIRE(sum[0] == sumX);
    REQUIRE(sum[1] == sumY);
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

    REQUIRE(sub[0] == 10);
    REQUIRE(sub[1] == -46);
}

TEMPLATE_LIST_TEST_CASE("Subtraction  operator", "[algebra][vector][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = 23.7;
    constexpr TestType y1 = -2.0;
    constexpr TestType x2 = 23.6;
    constexpr TestType y2 = -55.11;

    constexpr Vector<TestType, 2> vec1(x1, y1);
    constexpr Vector<TestType, 2> vec2(x2, y2);
    constexpr Vector<TestType, 2> sub = vec1 - vec2;

    constexpr auto epsilon = std::numeric_limits<TestType>::epsilon() * 100;

    // static_assert(std::abs(sub[0] - 0.1) < epsilon);
    static_assert(std::abs(sub[1] - 53.11) < epsilon);

    const auto sumX = Catch::Approx(0.1).epsilon(epsilon);
    const auto sumY = Catch::Approx(53.11).epsilon(epsilon);

    REQUIRE(sub[0] == sumX);
    REQUIRE(sub[1] == sumY);
}
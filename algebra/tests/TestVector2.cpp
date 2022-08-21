#include "algebra/Algebra.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using IntegerTypes  = std::tuple<short, unsigned short, int, unsigned int, long, unsigned long>;
using FloatingTypes = std::tuple<float, double, long double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim2]", IntegerTypes)
{
    constexpr TestType x = 1;
    constexpr TestType y = 123;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    REQUIRE(vec[0] == x);
    REQUIRE(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim2]", FloatingTypes)
{
    constexpr TestType x = 1.0;
    constexpr TestType y = 123.0;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    Catch::Approx targetX = Catch::Approx(x).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    Catch::Approx targetY = Catch::Approx(y).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == targetX);
    REQUIRE(vec[1] == targetY);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim2]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);

    REQUIRE(vec[0] == zero);
    REQUIRE(vec[1] == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][vector][dim2]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec;

    static_assert(vec[0] == zero);
    static_assert(vec[1] == zero);

    Catch::Approx target = Catch::Approx(0).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == target);
    REQUIRE(vec[1] == target);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim2]", IntegerTypes)
{
    constexpr TestType x = 1000;
    constexpr TestType y = 456;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    REQUIRE(vec[0] == x);
    REQUIRE(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Constructor with parameters", "[algebra][vector][dim2]", FloatingTypes)
{
    constexpr TestType x = -1.0;
    constexpr TestType y = 0.001;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec(x, y);

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    Catch::Approx targetX = Catch::Approx(x).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    Catch::Approx targetY = Catch::Approx(y).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == targetX);
    REQUIRE(vec[1] == targetY);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim2]", IntegerTypes)
{
    constexpr TestType x = 22;
    constexpr TestType y = 77;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec = { x, y };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    REQUIRE(vec[0] == x);
    REQUIRE(vec[1] == y);
}

TEMPLATE_LIST_TEST_CASE("Constructor with initializer list", "[algebra][vector][dim2]", FloatingTypes)
{
    constexpr TestType x = -9.35;
    constexpr TestType y = -2022.2108;

    constexpr LCNS::Algebra::Vector<TestType, 2> vec = { x, y };

    static_assert(vec[0] == x);
    static_assert(vec[1] == y);

    Catch::Approx targetX = Catch::Approx(x).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    Catch::Approx targetY = Catch::Approx(y).epsilon(std::numeric_limits<TestType>::epsilon() * 100);
    REQUIRE(vec[0] == targetX);
    REQUIRE(vec[1] == targetY);
}

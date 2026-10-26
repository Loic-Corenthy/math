#include "large/MatrixLarge.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <tuple>

using LCNS::large::MatrixLarge;

// 1. Define the fixture template to accept a product type (which wraps (Key, Value))
template <typename Tuple>
struct KeyValueFixture;

// Specialize or write the fixture template to destructure/handle the pair of types
template <typename coordinate, typename rows, typename cols>
struct KeyValueFixture<std::tuple<coordinate, rows, cols>>
{
    // Instantiate the production class with the two template arguments
    MatrixLarge<coordinate, 3, 4> store;

    KeyValueFixture()
    : store()
    {
    }

    size_t internalSize()
    { return store._coeff.size(); }
};

TEMPLATE_PRODUCT_TEST_CASE_METHOD(KeyValueFixture,
                                  "KeyValueStore private members can be accessed via friend fixture",
                                  "[template][fixture][product]",
                                  (std::tuple),
                                  ((int, 3, 4), (int, 9, 13)))
{  // Check size first
    REQUIRE(this->internalSize() == 8 * 4);
}

// TEMPLATE_TEST_CASE_METHOD(MatrixLargeTestPeer, "Default constructor", "[large][matrix][padding]", (int, 3, 4))
// {
//     MatrixLarge<int, 3, 4> mat;
//
//     // You can call the helper method inherited from the fixture
//     CHECK(internalSize(mat) == (64 / 4) * 4);
// }

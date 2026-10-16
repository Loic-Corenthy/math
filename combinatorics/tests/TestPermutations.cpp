#include "combinatorics/Permutations.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::generate;
using std::set;
using std::vector;

consteval unsigned int factoriel(unsigned int n)
{
    if (n == 0)
    {
        return 1;
    }

    unsigned int res = n;

    while (--n > 1)
    {
        res *= n;
    }

    return res;
}

TEST_CASE("Test permutations", "[perm1]")
{
    vector<int> integers(1, 0);

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    CHECK(allPermutations.size() == 1ULL);
    const vector<int> set0 = { 0 };

    CHECK(*allPermutations.cbegin() == set0);
}

TEST_CASE("Test permutations", "[perm2]")
{
    vector<int> integers(2);
    generate(integers.begin(), integers.end(), [num = 0]() mutable { return num++; });

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    CHECK(allPermutations.size() == static_cast<size_t>(factoriel(2)));
    const vector<int> set0 = { 0, 1 };
    const vector<int> set1 = { 1, 0 };

    auto resIt = allPermutations.cbegin();
    CHECK(*resIt++ == set0);
    CHECK(*resIt++ == set1);
}

TEST_CASE("Test permutations", "[perm3]")
{
    vector<int> integers(3);
    generate(integers.begin(), integers.end(), [num = 0]() mutable { return num++; });

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    CHECK(allPermutations.size() == static_cast<size_t>(factoriel(3)));
    const vector<int> set0 = { 0, 1, 2 };
    const vector<int> set1 = { 0, 2, 1 };
    const vector<int> set2 = { 1, 0, 2 };
    const vector<int> set3 = { 1, 2, 0 };
    const vector<int> set4 = { 2, 0, 1 };
    const vector<int> set5 = { 2, 1, 0 };

    auto resIt = allPermutations.cbegin();
    CHECK(*resIt++ == set0);
    CHECK(*resIt++ == set1);
    CHECK(*resIt++ == set2);
    CHECK(*resIt++ == set3);
    CHECK(*resIt++ == set4);
    CHECK(*resIt++ == set5);
}

TEST_CASE("Test permutations", "[perm4]")
{
    vector<int> integers(4);
    generate(integers.begin(), integers.end(), [num = 0]() mutable { return num++; });

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    CHECK(allPermutations.size() == static_cast<size_t>(factoriel(4)));
    const vector<int> set00 = { 0, 1, 2, 3 };
    const vector<int> set01 = { 0, 1, 3, 2 };
    const vector<int> set02 = { 0, 2, 1, 3 };
    const vector<int> set03 = { 0, 2, 3, 1 };
    const vector<int> set04 = { 0, 3, 1, 2 };
    const vector<int> set05 = { 0, 3, 2, 1 };
    const vector<int> set06 = { 1, 0, 2, 3 };
    const vector<int> set07 = { 1, 0, 3, 2 };
    const vector<int> set08 = { 1, 2, 0, 3 };
    const vector<int> set09 = { 1, 2, 3, 0 };
    const vector<int> set10 = { 1, 3, 0, 2 };
    const vector<int> set11 = { 1, 3, 2, 0 };
    const vector<int> set12 = { 2, 0, 1, 3 };
    const vector<int> set13 = { 2, 0, 3, 1 };
    const vector<int> set14 = { 2, 1, 0, 3 };
    const vector<int> set15 = { 2, 1, 3, 0 };
    const vector<int> set16 = { 2, 3, 0, 1 };
    const vector<int> set17 = { 2, 3, 1, 0 };
    const vector<int> set18 = { 3, 0, 1, 2 };
    const vector<int> set19 = { 3, 0, 2, 1 };
    const vector<int> set20 = { 3, 1, 0, 2 };
    const vector<int> set21 = { 3, 1, 2, 0 };
    const vector<int> set22 = { 3, 2, 0, 1 };
    const vector<int> set23 = { 3, 2, 1, 0 };

    auto resIt = allPermutations.cbegin();
    CHECK(*resIt++ == set00);
    CHECK(*resIt++ == set01);
    CHECK(*resIt++ == set02);
    CHECK(*resIt++ == set03);
    CHECK(*resIt++ == set04);
    CHECK(*resIt++ == set05);
    CHECK(*resIt++ == set06);
    CHECK(*resIt++ == set07);
    CHECK(*resIt++ == set08);
    CHECK(*resIt++ == set09);
    CHECK(*resIt++ == set10);
    CHECK(*resIt++ == set11);
    CHECK(*resIt++ == set12);
    CHECK(*resIt++ == set13);
    CHECK(*resIt++ == set14);
    CHECK(*resIt++ == set15);
    CHECK(*resIt++ == set16);
    CHECK(*resIt++ == set17);
    CHECK(*resIt++ == set18);
    CHECK(*resIt++ == set19);
    CHECK(*resIt++ == set20);
    CHECK(*resIt++ == set21);
    CHECK(*resIt++ == set22);
    CHECK(*resIt++ == set23);
}

TEST_CASE("Test permutations", "[Perm5]")
{
    vector<int> integers(5);
    generate(integers.begin(), integers.end(), [num = 0]() mutable { return num++; });

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    CHECK(allPermutations.size() == static_cast<size_t>(factoriel(5)));
}

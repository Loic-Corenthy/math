#pragma once

#include "combinatorics/Concepts.hpp"

#include <cstddef>
#include <vector>
#include <set>

namespace LCNS::Combinatorics
{
    template <Container Set>
    std::set<Set> permutations(const Set& input)
    {
        std::set<Set> allPermutations;

        allPermutations.insert(input);

        size_t pivot = 0;

        while (pivot < input.size() - 1)
        {
            auto currentLevelPermutations = allPermutations;

            for (auto currentPermutation = currentLevelPermutations.begin(); currentPermutation != currentLevelPermutations.end();
                 currentPermutation++)
            {
                size_t idx  = pivot;
                auto   copy = *currentPermutation;
                while (idx < input.size())
                {
                    std::swap(copy[pivot], copy[idx]);
                    allPermutations.insert(copy);
                    std::swap(copy[pivot], copy[idx]);
                    ++idx;
                }
            }

            ++pivot;
        }

        return allPermutations;
    }

}  // namespace LCNS::Combinatorics
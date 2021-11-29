#pragma once

#include "LCNSConcepts.hpp"

#include <cstddef>
#include <vector>
#include <set>

namespace LCNS::Combinatorics
{    
    template <Container Set>
    std::set<Set> permutations(const Set & input)
    {
        std::set<Set> allPermutations;

        allPermutations.insert(input);

        size_t pivot = 0;

        while (pivot < input.size() - 1)
        {
            auto currentLevelPermutations = allPermutations;

            for (auto currentPermutation = currentLevelPermutations.begin(); currentPermutation != currentLevelPermutations.end(); currentPermutation++)
            {
                size_t i = pivot;
                auto copy = *currentPermutation;
                while (i < input.size())
                {
                    std::swap(copy[pivot], copy[i]);
                    allPermutations.insert(copy);
                    std::swap(copy[pivot], copy[i]);
                    ++i;
                }
            }

            ++pivot;
        }

        return allPermutations;
    }

} // namespace LCNS::Combinatorics
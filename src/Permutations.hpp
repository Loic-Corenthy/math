#pragma once

#include <cstddef>
#include <vector>
#include <set>

namespace LCNS::Combinatorics
{
    template <typename Set>
    class Permutations
    {
    public:
        explicit Permutations(const Set & set);

        std::set<Set> generate(void);

    private:
        constexpr std::vector<size_t> generateJumps(size_t n) const;

    private:
        Set _set;
    };
    
    template <typename Set>
    std::set<Set> Permutations<Set>::generate(void)
    {
        return std::set<Set>();
    }

    template <typename Set>
    constexpr std::vector<size_t> Permutations<Set>::generateJumps(size_t n) const
    {
        if (n < 3)
        {
            return vector<size_t>{1};
        }

        std::vector<size_t> result;
        result.reserve(n-1);

        result.push_back(1);

        // Start at n - 1
        --n;
        while (n > 1)
        {
            result.push_back(result.back() * n);
            --n;
        }

        return result;
    }

} // namespace LCNS::Combinatorics
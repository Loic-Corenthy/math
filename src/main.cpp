#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <set>

using namespace std;

vector<int> createListOfInteger(size_t n)
{
    vector<int> res(n, 0);

    for (size_t i = 1; i <= n; ++i)
    {
        res[i - 1] = i;
    }

    return res;
}

template <typename Container>
void printContainer(const Container &v)
{
    for (const auto it : v)
    {
        cout << it << " ";
    }
    cout << endl;
}

template <typename Container>
void printListOfContainers(const Container &list)
{
    size_t i = 0;
    for (const auto container : list)
    {
        cout << ++i << "\t[ ";
        for (const auto it : container)
        {
            cout << it << " ";
        }
        cout << "]\n";
    }
}

auto generateJumps(size_t n)
{
    if (n < 3)
    {
        return vector<size_t>{1};
    }

    vector<size_t> result;

    result.push_back(1);

    // Start at n - 1
    --n;
    while(n > 1)
    {
        result.push_back(result.back() * n);
        --n;
    }

    return result;
}

auto generatePermutations(const vector<int> &integers)
{
    set<vector<int>> allPermutations;

    allPermutations.insert(integers);

    size_t pivot = 0;

    auto jumps = generateJumps(integers.size());

    while (pivot < integers.size() - 1)
    {
        auto currentLevelPermutations = allPermutations;
        
        cout << "pivot " << pivot << " with " << currentLevelPermutations.size() << " permutations to process\n";

        for (auto currentPermutation = currentLevelPermutations.begin(); currentPermutation != currentLevelPermutations.end(); currentPermutation++)
        {
            size_t i = pivot;
            auto copy = *currentPermutation;
            while (i < integers.size())
            {
                swap(copy[pivot], copy[i]);
                allPermutations.insert(copy);
                swap(copy[pivot], copy[i]);
                ++i;
            }
        }

        printListOfContainers(allPermutations);
        ++pivot;
    }

    return allPermutations;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage:\n ./permutation 5";
        return 0;
    }

    const auto integers = createListOfInteger(atoi(argv[1]));

    cout << "list of integers\n";
    printContainer(integers);

    const auto allPermutations = generatePermutations(integers);

    cout << "all permutations\n";
    printListOfContainers(allPermutations);

    cout << "number of permutations " << allPermutations.size() << "\n";

    return EXIT_SUCCESS;
}

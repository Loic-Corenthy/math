#include "Permutations.hpp"

#include <iostream>
#include <vector>

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

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    cout << "all permutations\n";
    printListOfContainers(allPermutations);

    cout << "number of permutations " << allPermutations.size() << "\n";

    return EXIT_SUCCESS;
}

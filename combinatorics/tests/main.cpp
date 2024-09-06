#include <combinatorics/Permutations.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Container>
void printContainer(const Container& v)
{
    for (const auto it : v)
    {
        cout << it << " ";
    }
    cout << endl;
}

template <typename Container>
void printListOfContainers(const Container& list)
{
    size_t i = 0;
    for (const auto& container : list)
    {
        cout << ++i << "\t[ ";
        for (const auto it : container)
        {
            cout << it << " ";
        }
        cout << "]\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Usage:\n ./permutation 5";
        return EXIT_FAILURE;
    }

    vector<int> integers(atoi(argv[1]));
    std::generate(integers.begin(), integers.end(), [n = 0]() mutable { return n++; });

    cout << "list of integers\n";
    printContainer(integers);

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    cout << "all permutations\n";
    printListOfContainers(allPermutations);

    cout << "number of permutations " << allPermutations.size() << "\n";

    return EXIT_SUCCESS;
}

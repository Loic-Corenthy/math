#include <combinatorics/Permutations.hpp>

#include <algorithm>
#include <iostream>
#include <vector>
#include <span>

using namespace std;

template <typename Container>
void printContainer(const Container& ctnr)
{
    for (const auto& val : ctnr)
    {
        cout << val << " ";
    }
    cout << '\n';
}

template <typename Container>
void printListOfContainers(const Container& list)
{
    size_t index = 0;
    for (const auto& container : list)
    {
        cout << ++index << "\t[ ";
        for (const auto itr : container)
        {
            cout << itr << " ";
        }
        cout << "]\n";
    }
}

int main(int argc, char* argv[])
{
    const auto input_args = span(argv, argc);

    if (input_args.size() < 2)
    {
        cout << "Usage:\n ./permutation 5";
        return EXIT_FAILURE;
    }

    vector<int> integers(atoi(input_args[1]));
    generate(integers.begin(), integers.end(), [num = 0]() mutable { return num++; });

    cout << "list of integers\n";
    printContainer(integers);

    const auto allPermutations = LCNS::Combinatorics::permutations(integers);

    cout << "all permutations\n";
    printListOfContainers(allPermutations);

    cout << "number of permutations " << allPermutations.size() << "\n";

    return EXIT_SUCCESS;
}

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
       res[i-1] = i;
    }

    return res;
}

template<typename Container>
void printContainer(const Container & v)
{
    for (const auto it : v)
    {
        cout << it << " ";
    }
    cout << endl;
}

template<typename Container>
void printListOfContainers(const Container & list)
{
    size_t i = 0;
    for (const auto container : list)
    {
        cout << ++i << "\t[";
        for (const auto it : container)
        {
            cout << it << " ";
        }
        cout << "]\n";
    }
}

vector<vector<int>> implementation1(const vector<int> & integers)
{
    vector<vector<int>> allPermutations;

    auto copy  = integers;
    auto copy2 = integers;

    for (unsigned int op = 0; op < integers.size(); ++op)
    {
         size_t i = copy.size() - 2;
         size_t j = i + 1;

         size_t debug = 0;
         bool computeNextPermutation = true;

         while (debug++ < 100 && computeNextPermutation)
         {
            swap(copy[i], copy[j]);
            allPermutations.push_back(copy);

            --i;
            --j;

            if (i == 0)
            {
               i = copy.size() - 1;
            }

            if (j == 0)
            {
               j = copy.size() - 1;
            }


            if (allPermutations.back() == copy2)
            {
                computeNextPermutation = false;
            }
         }

         auto front = copy.front();

         for (unsigned int k = 0; k < copy.size() - 1; ++k)
         {
            copy[k] = copy[k+1];
         }
         copy.back() = front;

         copy2 = copy;
    }

    return allPermutations;
}

auto implementation2(const vector<int> & integers)
{
    vector<vector<int>> allPermutations;
    //allPermutations.push_back(integers);

    auto copy = integers;
    auto copy2 = copy;

    int k = 1;
    bool process = true;
    // for (unsigned int k = 1; k < integers.size(); ++k)
    while (process)
    {
        int j = static_cast<int>(copy.size() - 1);
        int i = j - 1;

        do
        {
            swap(copy[i], copy[j]);
            allPermutations.push_back(copy);

            --i;
            --j;

            if (i < 0)
            {
               i = copy.size() - 1;
            }

            if (j < 0)
            {
               j = copy.size() - 1;
            }

        }
        while(copy != copy2);

        if(k != integers.size())
        {
            copy2 = integers;
            swap(copy2[0], copy2[k]);
            copy = copy2;
            ++k;
        }
        else
        {
            process = false;
        }

    }

    return allPermutations;
}



int main (int argc, char* argv[])
{
    if (argc < 2)
    {
       cout << "Usage:\n ./permutation 5";
       return 0;
    }

    const auto integers = createListOfInteger(atoi(argv[1]));

    cout << "list of integers\n";
    printContainer(integers);

    // const auto allPermutations = implementation1(integers);
    const auto allPermutations = implementation2(integers);

    cout << "all permutations\n";
    printListOfContainers(allPermutations);

    cout << "number of permutations " << allPermutations.size() << "\n";

    return EXIT_SUCCESS;
}



//     auto comp = [](const vector<int> & v2, const vector<int> & v1)
//     {
//         if (v1.size() < v2.size())
//         {
//             return true;
//         }

//         for (unsigned int i = 0; i < v1.size(); ++i)
//         {
//            if (v1[i] < v2[i])
//            {
//                return true;
//            }
//         }

//         return false;
//     };


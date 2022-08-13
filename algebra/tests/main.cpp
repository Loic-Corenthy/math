#include "algebra/Vector.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    using vec1f = LCNS::Vector<float, 1>;
    using vec2d = LCNS::Vector<double, 2>;

    vec1f v11(1.0f);

    cout << v11.x() << endl;

    vec1f v12(2.0f);

    cout << v12.x() << endl;

    vec2d v21(1.0, 2.0);

    cout << v21.x() << " " << v21[1] << endl;

    vec2d v22(2., 3.0);

    return 0;
}
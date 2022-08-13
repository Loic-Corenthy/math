#include "algebra/Vector.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    using vec1f = LCNS::Algebra::Vector<float, 1>;
    using vec2d = LCNS::Algebra::Vector<double, 2>;

    vec1f v11(1.0f);

    cout << v11.x() << endl;

    vec1f v12(2.0f);

    cout << v12.x() << endl;

    constexpr vec1f v13;
    static_assert(v13.x() == 0.0f);
    static_assert(v13[0] == 0.0f);


    vec2d v21(1.0, 2.0);

    cout << v21.x() << " " << v21[1] << endl;

    vec2d v22(2., 3.0);

    constexpr vec2d v23(1.0, 2.0);
    constexpr vec2d v24(2.0, -1.0);

    static_assert(v23.sqrLength() == v24.sqrLength());
    static_assert(v23.dot(v24) == 0.0f);

    using vec0i = LCNS::Algebra::Vector<int, 0>;

    vec0i bob;

    return 0;
}
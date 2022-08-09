#include <concepts>

template <typename T>
concept Container = requires(T c)
{
    // any `c` that is a Container
    c.size();   // must have c.size()
    c.begin();  // and c.begin()
    c.end();    // and c.end()
};

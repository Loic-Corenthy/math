#include "large/Multiplication.hpp"

#include <stdexcept>

using LCNS::Large::Matrix;

using std::runtime_error;

Matrix LCNS::Large::multiply_classic(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.col_count() != rhs.row_count())
    {
        throw runtime_error("Invalid matrix dimensions for multiplication");
    }

    Matrix result(lhs.row_count(), rhs.col_count());
    for (unsigned int i = 0; i < lhs.row_count(); ++i)
    {
        for (unsigned int j = 0; j < rhs.col_count(); ++j)
        {
            for (unsigned int k = 0; k < lhs.col_count(); ++k)
            {
                const auto a = lhs(i, k);
                const auto b = rhs(k, j);
                result(i, j) += a * b;
            }
        }
    }

    return result;
}
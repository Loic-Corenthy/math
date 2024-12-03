#include "large/Matrix.hpp"

#include <random>
#include <algorithm>

using LCNS::Large::Matrix;

Matrix::Matrix(unsigned int row_count, unsigned int col_count, bool random_coeffs)
: _coeff(row_count * col_count, 0.0f)
, _rows(row_count)
, _cols(col_count)
{
    if (random_coeffs)
    {
        std::random_device               rd;
        std::mt19937                     gen(rd());
        std::uniform_real_distribution<> dis(0.0f, 1.0f);

        std::generate(_coeff.begin(), _coeff.end(), [&]() { return dis(gen); });
    }
}

float& Matrix::operator()(unsigned int i, unsigned int j)
{
    return _coeff.at(i * _cols + j);
}

float Matrix::operator()(unsigned int i, unsigned int j) const
{
    return _coeff.at(i * _cols + j);
}

unsigned int Matrix::row_count() const
{
    return _rows;
}

unsigned int Matrix::col_count() const
{
    return _cols;
}

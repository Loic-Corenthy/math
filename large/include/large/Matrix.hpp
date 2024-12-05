#pragma once

#include <vector>
#include <iostream>

namespace LCNS::Large
{
    class Matrix
    {
    public:
        Matrix(unsigned int row_count, unsigned int col_count, bool random_coeffs = false);

        float& operator()(unsigned int i, unsigned int j);
        float  operator()(unsigned int i, unsigned int j) const;

        unsigned int row_count() const;
        unsigned int col_count() const;

        const float* data() const;

        Matrix transpose() const;

    private:
        std::vector<float> _coeff = {};

        unsigned int _rows = 0u;
        unsigned int _cols = 0u;
    };

}  // namespace LCNS::Large

std::ostream& operator<<(std::ostream& os, const LCNS::Large::Matrix& m);

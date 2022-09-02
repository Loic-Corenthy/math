#pragma once

#include "algebra/Internal.hpp"

#include <cmath>
#include <array>
#include <stdexcept>

namespace LCNS::Algebra
{
    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    class Matrix
    {
    public:
        /*!
         * \brief Default constructor.
         */
        constexpr Matrix() = default;

        /*!
         * \brief Constructor with scalar parameter.
         * @param scalar is the scalar value that will be set to the diagonal coefficients
         */
        constexpr Matrix(const auto scalar);

        /*!
         * \brief Constructor with initializer list parameter.
         * @param coeffs contains the coefficients of the matrix, row by row
         */
        constexpr Matrix(const std::initializer_list<coordinate>& coeffs);

        /*!
         * \brief Accessor (read/write)
         * @param row in the index of the row where to find the coefficient to access
         * @param col in the index of the column where to find the coefficient to access
         * @return a reference on the corresponding coefficient
         */
        constexpr coordinate& operator()(unsigned int row, unsigned int col);

        /*!
         * \brief Accessor (read only)
         * @param row in the index of the row where to find the coefficient to access
         * @param col in the index of the column where to find the coefficient to access
         * @return the corresponding coefficient
         */
        constexpr coordinate operator()(unsigned int row, unsigned int col) const;

    private:
        coordinate _coeff[rows][cols] = {};

    };  // class Matrix

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols>::Matrix(const auto scalar)
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        for (unsigned int i = 0; i < rows; ++i)
            for (unsigned int j = 0; j < cols; ++j)
                _coeff[i][j] = (i == j) ? scalar : static_cast<coordinate>(0);
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols>::Matrix(const std::initializer_list<coordinate>& coeffs)
    {
        unsigned int i = 0;
        unsigned int j = 0;

        for (auto it = coeffs.begin(); it < coeffs.end(); it++)
        {
            _coeff[i][j] = *it;
            j++;
            if (j == cols)
            {
                i++;
                j = 0;
            }
        }
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate& Matrix<coordinate, rows, cols>::operator()(unsigned int row, unsigned int col)
    {
        return _coeff[row][col];
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate Matrix<coordinate, rows, cols>::operator()(unsigned int row, unsigned int col) const
    {
        return _coeff[row][col];
    }
}  // namespace LCNS::Algebra
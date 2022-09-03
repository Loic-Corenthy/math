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
        constexpr Matrix(auto scalar);

        /*!
         * \brief Constructor with initializer list parameter.
         * @param coeffs contains the coefficients of the matrix, row by row
         */
        constexpr Matrix(const std::initializer_list<coordinate>& coeffs);

        /*!
         * \brief Accessor (read/write)
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return a reference on the corresponding coefficient
         */
        coordinate& operator()(unsigned int i, unsigned int j);

        /*!
         * \brief Accessor (read only)
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return the corresponding coefficient
         */
        constexpr coordinate operator()(unsigned int i, unsigned int j) const;

        /*!
         * \brief Comparision operator
         * @param rhs is the matrix to compare coefficients from
         * @return true if all coordinates of this matrix and rhs are equal
         */
        constexpr bool operator==(const Matrix<coordinate, rows, cols>& rhs) const;

    private:
        /*!
         * \brief Unnamed helper function to get the 1D equalent of i and j
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return the equivalent index to access the coefficient in _coeff
         */
        constexpr unsigned int _(unsigned int i, unsigned int j) const;

    private:
        std::array<coordinate, rows* cols> _coeff = {};

    };  // class Matrix

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols>::Matrix(auto scalar)
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        for (unsigned int i = 0; i < rows; ++i)
            for (unsigned int j = 0; j < cols; ++j)
                _coeff[_(i, j)] = (i == j) ? scalar : static_cast<coordinate>(0);
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols>::Matrix(const std::initializer_list<coordinate>& coeffs)
    {
        unsigned int i = 0;
        for (auto it = coeffs.begin(); it < coeffs.end(); it++)
        {
            _coeff[i++] = *it;
        }
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    coordinate& Matrix<coordinate, rows, cols>::operator()(unsigned int i, unsigned int j)
    {
        return _coeff[_(i, j)];
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate Matrix<coordinate, rows, cols>::operator()(unsigned int i, unsigned int j) const
    {
        return _coeff[_(i, j)];
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr bool Matrix<coordinate, rows, cols>::operator==(const Matrix<coordinate, rows, cols>& rhs) const
    {
        return _coeff == rhs._coeff;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    inline constexpr unsigned int Matrix<coordinate, rows, cols>::_(unsigned int i, unsigned int j) const
    {
        return i * cols + j;
    }
}  // namespace LCNS::Algebra
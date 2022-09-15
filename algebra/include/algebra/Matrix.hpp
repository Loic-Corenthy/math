#pragma once

#include "algebra/Internal.hpp"

#include <cmath>
#include <array>
#include <stdexcept>
#include <ostream>
#include <iomanip>

namespace LCNS::Algebra
{
    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    class Matrix
    {
    public:
        /*!
         * @brief Default constructor.
         */
        constexpr Matrix() = default;

        /*!
         * @brief Constructor with scalar parameter.
         * @param scalar is the scalar value that will be set to the diagonal coefficients
         */
        constexpr explicit Matrix(auto scalar);

        /*!
         * @brief Constructor with initializer list parameter.
         * @param coeffs contains the coefficients of the matrix, row by row
         */
        constexpr Matrix(const std::initializer_list<coordinate>& coeffs);

        /*!
         * @brief Accessor (read/write)
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return a reference on the corresponding coefficient
         */
        constexpr coordinate& operator()(unsigned int i, unsigned int j);

        /*!
         * @brief Accessor (read only)
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return the corresponding coefficient
         */
        constexpr coordinate operator()(unsigned int i, unsigned int j) const;

        /*!
         * @brief Comparision operator
         * @param rhs is the matrix to compare coefficients from
         * @return true if all coordinates of this matrix and rhs are equal
         */
        constexpr bool operator==(const Matrix<coordinate, rows, cols>& rhs) const;

        /*!
         * @brief Addition operator. Do not modify this object.
         * @param rhs is the matrix to add to this one
         * @return a matrix corresponding to the addition: this + rhs
         */
        constexpr Matrix<coordinate, rows, cols> operator+(const Matrix<coordinate, rows, cols>& rhs) const;

        /*!
         * @brief Substraction operator. Do not modify this object.
         * @param rhs is the matrix to substract from this one
         * @return a matrix corresponding to the substraction: this - rhs
         */
        constexpr Matrix<coordinate, rows, cols> operator-(const Matrix<coordinate, rows, cols>& rhs) const;

        /*!
         * @brief Multiplication by a scalar operator
         * @param scalar is the scalar value that will multiply all the coefficients
         * @return a reference on this object after the operation
         */
        Matrix<coordinate, rows, cols>& operator*=(auto scalar);

        /*!
         * @brief Division by a scalar operator
         * @param scalar is the scalar value from which all the coefficients will be divided
         * @return a reference on this object after the operation
         */
        Matrix<coordinate, rows, cols>& operator/=(auto scalar);

        /*! Other operations are achieved using an external operator, see below */

        /*!
         * @brief Transpose this matrix
         * @return a reference on this object after the operation
         */
        constexpr Matrix<coordinate, rows, cols>& transpose();

        /*!
         * @brief Create a matrix that is the transpose of this
         * @return a new matrix
         */
        constexpr Matrix<coordinate, cols, rows> transposed() const;

        /*!
         * @brief Compute the determinant of this matrix. Only works for square matrices of size 1,2,3 or 4
         * @return the determinant of this matrix.
         */
        constexpr coordinate det() const requires(rows == cols && (0 < rows && rows < 5));

    private:
        /*!
         * @brief Unnamed helper function to get the 1D equalent of i and j
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return the equivalent index to access the coefficient in _coeff
         */
        constexpr unsigned int _(unsigned int i, unsigned int j) const;

    private:
        std::array<coordinate, rows* cols> _coeff = {};

        unsigned int _rows = rows;
        unsigned int _cols = cols;

    };  // class Matrix

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols>::Matrix(auto scalar)
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        const auto diag = std::min(_rows, _cols);

        for (unsigned int i = 0; i < diag; ++i)
            for (unsigned int j = 0; j < diag; ++j)
                _coeff[_(i, j)] = (i == j) ? scalar : static_cast<coordinate>(0);
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols>::Matrix(const std::initializer_list<coordinate>& coeffs)
    {
        if (coeffs.size() > _coeff.size())
        {
            throw std::out_of_range("Too many coefficients in the initializer list for this size of matrix");
        }

        unsigned int i = 0;
        for (auto it = coeffs.begin(); it < coeffs.end(); it++)
        {
            _coeff[i++] = *it;
        }
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate& Matrix<coordinate, rows, cols>::operator()(unsigned int i, unsigned int j)
    {
        if (rows <= i || cols <= j)
        {
            throw std::out_of_range("Index out of range to access matrix coefficient");
        }

        return _coeff[_(i, j)];
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate Matrix<coordinate, rows, cols>::operator()(unsigned int i, unsigned int j) const
    {
        if (rows <= i || cols <= j)
        {
            throw std::out_of_range("Index out of range to access matrix coefficient");
        }

        return _coeff[_(i, j)];
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr bool Matrix<coordinate, rows, cols>::operator==(const Matrix<coordinate, rows, cols>& rhs) const
    {
        return _coeff == rhs._coeff;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols> Matrix<coordinate, rows, cols>::operator+(const Matrix<coordinate, rows, cols>& rhs) const
    {
        if (_rows != rhs._rows || _cols != rhs._cols)
        {
            throw std::runtime_error("Addition requires matrices of equal dimentions");
        }

        auto result = *this;

        for (unsigned int i = 0; i < rows * cols; ++i)
        {
            result._coeff[i] += rhs._coeff[i];
        }

        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols> Matrix<coordinate, rows, cols>::operator-(const Matrix<coordinate, rows, cols>& rhs) const
    {
        if (_rows != rhs._rows || _cols != rhs._cols)
        {
            throw std::runtime_error("Substraction requires matrices of equal dimentions");
        }

        auto result = *this;

        for (unsigned int i = 0; i < rows * cols; ++i)
        {
            result._coeff[i] -= rhs._coeff[i];
        }

        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    Matrix<coordinate, rows, cols>& Matrix<coordinate, rows, cols>::operator*=(auto scalar)
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        for (auto& c : _coeff)
        {
            c *= scalar;
        }

        return *this;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    Matrix<coordinate, rows, cols>& Matrix<coordinate, rows, cols>::operator/=(auto scalar)
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        if (scalar == static_cast<coordinate>(0))
        {
            throw std::runtime_error("Divide by zero");
        }

        for (auto& c : _coeff)
        {
            c /= scalar;
        }

        return *this;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols>& Matrix<coordinate, rows, cols>::transpose()
    {
        std::swap(_rows, _cols);

        for (unsigned int i = 0; i < rows; ++i)
            for (unsigned int j = i + 1; j < cols; ++j)
                std::swap(_coeff[_(i, j)], _coeff[_(j, i)]);

        return *this;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, cols, rows> Matrix<coordinate, rows, cols>::transposed() const
    {
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate Matrix<coordinate, rows, cols>::det() const requires(rows == cols && (0 < rows && rows < 5))
    {
        // clang-format off
        if constexpr (rows == 1)
        {
            return _coeff[0];
        }
        else if constexpr (rows == 2)
        {
            return _coeff[0] * _coeff[3] - _coeff[1] * _coeff[2];
        }
        else if constexpr (rows == 3)
        {
            return   _coeff[0] * _coeff[4] * _coeff[8] + _coeff[1] * _coeff[5] * _coeff[6] + _coeff[2] * _coeff[3] * _coeff[7]
                   - _coeff[2] * _coeff[4] * _coeff[6] - _coeff[1] * _coeff[3] * _coeff[8] - _coeff[0] * _coeff[5] * _coeff[7];
        }
        else if constexpr (rows == 4)
        {
            return  ( _coeff[ 3] * _coeff[ 6] * _coeff[ 9] * _coeff[12] - _coeff[ 2] * _coeff[ 7] * _coeff[ 9] * _coeff[12] - _coeff[ 3] * _coeff[ 5] * _coeff[10] * _coeff[12] + _coeff[ 1] * _coeff[ 7] * _coeff[10] * _coeff[12]
                    + _coeff[ 2] * _coeff[ 5] * _coeff[11] * _coeff[12] - _coeff[ 1] * _coeff[ 6] * _coeff[11] * _coeff[12] - _coeff[ 3] * _coeff[ 6] * _coeff[ 8] * _coeff[13] + _coeff[ 2] * _coeff[ 7] * _coeff[ 8] * _coeff[13]
                    + _coeff[ 3] * _coeff[ 4] * _coeff[10] * _coeff[13] - _coeff[ 0] * _coeff[ 7] * _coeff[10] * _coeff[13] - _coeff[ 2] * _coeff[ 4] * _coeff[11] * _coeff[13] + _coeff[ 0] * _coeff[ 6] * _coeff[11] * _coeff[13]
                    + _coeff[ 3] * _coeff[ 5] * _coeff[ 8] * _coeff[14] - _coeff[ 1] * _coeff[ 7] * _coeff[ 8] * _coeff[14] - _coeff[ 3] * _coeff[ 4] * _coeff[ 9] * _coeff[14] + _coeff[ 0] * _coeff[ 7] * _coeff[ 9] * _coeff[14]
                    + _coeff[ 1] * _coeff[ 4] * _coeff[11] * _coeff[14] - _coeff[ 0] * _coeff[ 5] * _coeff[11] * _coeff[14] - _coeff[ 2] * _coeff[ 5] * _coeff[ 8] * _coeff[15] + _coeff[ 1] * _coeff[ 6] * _coeff[ 8] * _coeff[15]
                    + _coeff[ 2] * _coeff[ 4] * _coeff[ 9] * _coeff[15] - _coeff[ 0] * _coeff[ 6] * _coeff[ 9] * _coeff[15] - _coeff[ 1] * _coeff[ 4] * _coeff[10] * _coeff[15] + _coeff[ 0] * _coeff[ 5] * _coeff[10] * _coeff[15]);
        }
        // clang-format on
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    inline constexpr unsigned int Matrix<coordinate, rows, cols>::_(unsigned int i, unsigned int j) const
    {
        return i * cols + j;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols> operator*(const Matrix<coordinate, rows, cols>& lhs, const coordinate rhs)
    {
        Matrix<coordinate, rows, cols> result;

        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result(i, j) = lhs(i, j) * rhs;

        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols> operator*(const coordinate lhs, const Matrix<coordinate, rows, cols>& rhs)
    {
        Matrix<coordinate, rows, cols> result;

        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result(i, j) = lhs * rhs(i, j);

        return result;
    }

    template <Coordinate coordinate, unsigned int rows_lhs, unsigned int cols_lhs, unsigned int rows_rhs, unsigned int cols_rhs>
    constexpr Matrix<coordinate, rows_rhs, cols_lhs> operator*(const Matrix<coordinate, rows_lhs, cols_lhs>& lhs,
                                                               const Matrix<coordinate, rows_rhs, cols_rhs>& rhs)
    {
        if (cols_lhs != rows_rhs)
        {
            throw std::runtime_error("Multiplication requires the number of column of this matrix to match the number of rows of rhs");
        }

        Matrix<coordinate, rows_rhs, cols_lhs> result;

        for (size_t i = 0; i < rows_rhs; ++i)
            for (size_t j = 0; j < cols_lhs; ++j)
                for (size_t k = 0; k < cols_lhs; ++k)
                    result(i, j) += lhs(i, k) * rhs(k, j);

        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols> operator/(Matrix<coordinate, rows, cols>& lhs, auto rhs)
    {
        static_assert(std::is_same_v<decltype(rhs), coordinate>);

        if (rhs == static_cast<coordinate>(0))
        {
            throw std::runtime_error("Divide by zero");
        }

        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                lhs(i, j) /= rhs;

        return lhs;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    std::ostream& operator<<(std::ostream& os, const Matrix<coordinate, rows, cols>& m)
    {
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                os << std::setw(sizeof(coordinate)) << m(i, j) << " ";
            }

            os << '\n';
        }

        return os;
    }
}  // namespace LCNS::Algebra
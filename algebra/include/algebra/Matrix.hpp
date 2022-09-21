#pragma once

#include "algebra/Internal.hpp"

#include <cmath>
#include <cstring>
#include <array>
#include <stdexcept>
#include <ostream>
#include <iomanip>
#include <tuple>

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
         * @brief Get the matrix dimentions
         * @return a tuple with the row and column counts. To be used as `const auto [rows, cols] = matrix.dimensions();`
         */
        constexpr std::tuple<unsigned int, unsigned int> dimensions() const;

        /*!
         * @brief Get a pointer to the internal coefficients (read/write)
         * @return a pointer to the first element of _coeff
         */
        coordinate* data();

        /*!
         * @brief Get a pointer to the internal coefficients (read only)
         * @return a pointer to the first element of _coeff
         */
        coordinate* data() const;

        /*!
         * @brief Transpose this matrix if it's a square matrix
         * @return a reference on this object after the operation
         */
        Matrix<coordinate, rows, cols>& transpose() requires(rows == cols);

        /*!
         * @brief Create a matrix that is the transpose of this, also works for rectangular matrices
         * @return a new matrix
         */
        Matrix<coordinate, cols, rows> transposed() const;

        /*!
         * @brief Compute the determinant of this matrix. Only works for square matrices of size 1,2,3 or 4
         * @return the determinant of this matrix.
         */
        constexpr coordinate determinant() const requires(rows == cols && (0 < rows && rows < 5));

        /*!
         * @brief Compute the trace of this matrix if it's a square matrix
         * @return the sum of the diagonal coefficients
         */
        constexpr coordinate trace() const requires(rows == cols);

        /*!
         * @brief Inverse this matrix if it's a square matrix of floating point coordinates and if its determinant is not null
         * @return a reference to this
         */
        Matrix<coordinate, rows, cols>& inverse() requires(rows == cols && (0 < rows && rows < 5) && std::is_floating_point_v<coordinate>);

        /*!
         * @brief Compute the inverse of this matrix if it's a square matrix of floating point coordinates and if its determinant is not null
         * @return a new matrix that is the inverse of this matrix if the operation is successful, a null matrix otherwise
         */
        constexpr Matrix<coordinate, rows, cols> inversed() const
        requires(rows == cols && (0 < rows && rows < 5) && std::is_floating_point_v<coordinate>);

    private:
        /*!
         * @brief Unnamed helper function to get the 1D equalent of i and j
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return the equivalent index to access the coefficient in _coeff
         */
        constexpr unsigned int _(unsigned int i, unsigned int j) const;

        /*!
         * @brief Helper method to compute the matrix inverse
         * @param copy takes the coefficients of this matrix as a copy
         * @param det is the determinant of this matrix
         */
        constexpr void _inverseImpl(std::array<coordinate, rows * cols> copy,
                                    coordinate det) requires(rows == cols && (0 < rows && rows < 5) && std::is_floating_point_v<coordinate>);

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
        if (_rows <= i || _cols <= j)
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
    constexpr std::tuple<unsigned int, unsigned int> Matrix<coordinate, rows, cols>::dimensions() const
    {
        return std::make_tuple(_rows, _cols);
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    coordinate* Matrix<coordinate, rows, cols>::data()
    {
        return _coeff.data();
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    coordinate* Matrix<coordinate, rows, cols>::data() const
    {
        return _coeff.data();
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    Matrix<coordinate, rows, cols>& Matrix<coordinate, rows, cols>::transpose() requires(rows == cols)
    {
        for (unsigned int i = 0; i < _rows; ++i)
            for (unsigned int j = i + 1; j < _cols; ++j)
                std::swap(_coeff[_(i, j)], _coeff[_(j, i)]);

        return *this;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    Matrix<coordinate, cols, rows> Matrix<coordinate, rows, cols>::transposed() const
    {
        Matrix<coordinate, cols, rows> result;

        for (unsigned int i = 0; i < _rows; ++i)
            for (unsigned int j = 0; j < _cols; ++j)
                result(j, i) = _coeff[_(i, j)];

        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate Matrix<coordinate, rows, cols>::determinant() const requires(rows == cols && (0 < rows && rows < 5))
    {
        if constexpr (rows == 1)
        {
            return _coeff[0];
        }

        // clang-format off
        if constexpr (std::is_same_v<coordinate,float>)
        {
            if constexpr (rows == 2)
            {
                    return static_cast<coordinate>(static_cast<double>(_coeff[0]) * static_cast<double>(_coeff[3]) - static_cast<double>(_coeff[1]) * static_cast<double>(_coeff[2]));
            }
            else if constexpr (rows == 3)
            {
                return static_cast<coordinate>(  static_cast<double>(_coeff[0]) * static_cast<double>(_coeff[4]) * static_cast<double>(_coeff[8]) + static_cast<double>(_coeff[1]) * static_cast<double>(_coeff[5]) * static_cast<double>(_coeff[6]) + static_cast<double>(_coeff[2]) * static_cast<double>(_coeff[3]) * static_cast<double>(_coeff[7])
                                               - static_cast<double>(_coeff[2]) * static_cast<double>(_coeff[4]) * static_cast<double>(_coeff[6]) - static_cast<double>(_coeff[1]) * static_cast<double>(_coeff[3]) * static_cast<double>(_coeff[8]) - static_cast<double>(_coeff[0]) * static_cast<double>(_coeff[5]) * static_cast<double>(_coeff[7]));
            }
            else if constexpr (rows == 4)
            {
                return  static_cast<coordinate>(  static_cast<double>(_coeff[ 3]) * static_cast<double>(_coeff[ 6]) * static_cast<double>(_coeff[ 9]) * static_cast<double>(_coeff[12]) - static_cast<double>(_coeff[ 2]) * static_cast<double>(_coeff[ 7]) * static_cast<double>(_coeff[ 9]) * static_cast<double>(_coeff[12]) - static_cast<double>(_coeff[ 3]) * static_cast<double>(_coeff[ 5]) * static_cast<double>(_coeff[10]) * static_cast<double>(_coeff[12]) + static_cast<double>(_coeff[ 1]) * static_cast<double>(_coeff[ 7]) * static_cast<double>(_coeff[10]) * static_cast<double>(_coeff[12])
                                                + static_cast<double>(_coeff[ 2]) * static_cast<double>(_coeff[ 5]) * static_cast<double>(_coeff[11]) * static_cast<double>(_coeff[12]) - static_cast<double>(_coeff[ 1]) * static_cast<double>(_coeff[ 6]) * static_cast<double>(_coeff[11]) * static_cast<double>(_coeff[12]) - static_cast<double>(_coeff[ 3]) * static_cast<double>(_coeff[ 6]) * static_cast<double>(_coeff[ 8]) * static_cast<double>(_coeff[13]) + static_cast<double>(_coeff[ 2]) * static_cast<double>(_coeff[ 7]) * static_cast<double>(_coeff[ 8]) * static_cast<double>(_coeff[13])
                                                + static_cast<double>(_coeff[ 3]) * static_cast<double>(_coeff[ 4]) * static_cast<double>(_coeff[10]) * static_cast<double>(_coeff[13]) - static_cast<double>(_coeff[ 0]) * static_cast<double>(_coeff[ 7]) * static_cast<double>(_coeff[10]) * static_cast<double>(_coeff[13]) - static_cast<double>(_coeff[ 2]) * static_cast<double>(_coeff[ 4]) * static_cast<double>(_coeff[11]) * static_cast<double>(_coeff[13]) + static_cast<double>(_coeff[ 0]) * static_cast<double>(_coeff[ 6]) * static_cast<double>(_coeff[11]) * static_cast<double>(_coeff[13])
                                                + static_cast<double>(_coeff[ 3]) * static_cast<double>(_coeff[ 5]) * static_cast<double>(_coeff[ 8]) * static_cast<double>(_coeff[14]) - static_cast<double>(_coeff[ 1]) * static_cast<double>(_coeff[ 7]) * static_cast<double>(_coeff[ 8]) * static_cast<double>(_coeff[14]) - static_cast<double>(_coeff[ 3]) * static_cast<double>(_coeff[ 4]) * static_cast<double>(_coeff[ 9]) * static_cast<double>(_coeff[14]) + static_cast<double>(_coeff[ 0]) * static_cast<double>(_coeff[ 7]) * static_cast<double>(_coeff[ 9]) * static_cast<double>(_coeff[14])
                                                + static_cast<double>(_coeff[ 1]) * static_cast<double>(_coeff[ 4]) * static_cast<double>(_coeff[11]) * static_cast<double>(_coeff[14]) - static_cast<double>(_coeff[ 0]) * static_cast<double>(_coeff[ 5]) * static_cast<double>(_coeff[11]) * static_cast<double>(_coeff[14]) - static_cast<double>(_coeff[ 2]) * static_cast<double>(_coeff[ 5]) * static_cast<double>(_coeff[ 8]) * static_cast<double>(_coeff[15]) + static_cast<double>(_coeff[ 1]) * static_cast<double>(_coeff[ 6]) * static_cast<double>(_coeff[ 8]) * static_cast<double>(_coeff[15])
                                                + static_cast<double>(_coeff[ 2]) * static_cast<double>(_coeff[ 4]) * static_cast<double>(_coeff[ 9]) * static_cast<double>(_coeff[15]) - static_cast<double>(_coeff[ 0]) * static_cast<double>(_coeff[ 6]) * static_cast<double>(_coeff[ 9]) * static_cast<double>(_coeff[15]) - static_cast<double>(_coeff[ 1]) * static_cast<double>(_coeff[ 4]) * static_cast<double>(_coeff[10]) * static_cast<double>(_coeff[15]) + static_cast<double>(_coeff[ 0]) * static_cast<double>(_coeff[ 5]) * static_cast<double>(_coeff[10]) * static_cast<double>(_coeff[15]));
            }
        }
        else
        {
            if constexpr (rows == 2)
            {
                return _coeff[0] * _coeff[3] - _coeff[1] * _coeff[2];
            }
            else if constexpr (rows == 3)
            {
                return ( _coeff[0] * _coeff[4] * _coeff[8] + _coeff[1] * _coeff[5] * _coeff[6] + _coeff[2] * _coeff[3] * _coeff[7]
                       - _coeff[2] * _coeff[4] * _coeff[6] - _coeff[1] * _coeff[3] * _coeff[8] - _coeff[0] * _coeff[5] * _coeff[7]);
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
        }

        // clang-format on
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate Matrix<coordinate, rows, cols>::trace() const requires(rows == cols)
    {
        coordinate result = 0;

        for (unsigned int i = 0; i < rows; ++i)
            result += _coeff[_(i, i)];

        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    Matrix<coordinate, rows, cols>& Matrix<coordinate, rows, cols>::inverse() requires(rows == cols && (0 < rows && rows < 5)
                                                                                       && std::is_floating_point_v<coordinate>)
    {
        if (const auto det = determinant(); std::abs(det) > 0.000'000'001)
        {
            _inverseImpl(_coeff, det);
        }

        return *this;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr Matrix<coordinate, rows, cols> Matrix<coordinate, rows, cols>::inversed() const
    requires(rows == cols && (0 < rows && rows < 5) && std::is_floating_point_v<coordinate>)
    {
        Matrix<coordinate, rows, cols> result;

        if (const auto det = determinant(); std::abs(det) > 0.000'000'001)
        {
            result._inverseImpl(_coeff, det);
        }

        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    inline constexpr unsigned int Matrix<coordinate, rows, cols>::_(unsigned int i, unsigned int j) const
    {
        return i * _cols + j;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr void Matrix<coordinate, rows, cols>::_inverseImpl(std::array<coordinate, rows * cols> copy,
                                                                coordinate det) requires(rows == cols && (0 < rows && rows < 5)
                                                                                         && std::is_floating_point_v<coordinate>)
    {
        if constexpr (rows == 1)
        {
            _coeff[0] = 1.0 / _coeff[0];
        }
        else if constexpr (rows == 2)
        {
            // clang-format off
            _coeff[0] =  copy[3] / det;
            _coeff[2] = -copy[2] / det;

            _coeff[1] = -copy[1] / det;
            _coeff[3] =  copy[0] / det;
            // clang-format on
        }
        else if constexpr (rows == 3)
        {
            // clang-format off
            _coeff[0] =  (copy[4] * copy[8] - copy[7] * copy[5]) / det;
            _coeff[3] = -(copy[3] * copy[8] - copy[6] * copy[5]) / det;
            _coeff[6] =  (copy[3] * copy[7] - copy[6] * copy[4]) / det;

            _coeff[1] = -(copy[1] * copy[8] - copy[7] * copy[2]) / det;
            _coeff[4] =  (copy[0] * copy[8] - copy[6] * copy[2]) / det;
            _coeff[7] = -(copy[0] * copy[7] - copy[6] * copy[1]) / det;

            _coeff[2] =  (copy[1] * copy[5] - copy[4] * copy[2]) / det;
            _coeff[5] = -(copy[0] * copy[5] - copy[3] * copy[2]) / det;
            _coeff[8] =  (copy[0] * copy[4] - copy[3] * copy[1]) / det;
            // clang-format on
        }
        else if constexpr (rows == 4)
        {
            // clang-format off
            _coeff[ 0] = (-copy[ 7] * copy[10] * copy[13]  +  copy[ 6] * copy[11] * copy[13]  +  copy[ 7] * copy[ 9] * copy[14]  -  copy[ 5] * copy[11] * copy[14]  -  copy[ 6] * copy[ 9] * copy[15]  +  copy[ 5] * copy[10] * copy[15]) / det;
            _coeff[ 4] = ( copy[ 7] * copy[10] * copy[12]  -  copy[ 6] * copy[11] * copy[12]  -  copy[ 7] * copy[ 8] * copy[14]  +  copy[ 4] * copy[11] * copy[14]  +  copy[ 6] * copy[ 8] * copy[15]  -  copy[ 4] * copy[10] * copy[15]) / det;
            _coeff[ 8] = (-copy[ 7] * copy[ 9] * copy[12]  +  copy[ 5] * copy[11] * copy[12]  +  copy[ 7] * copy[ 8] * copy[13]  -  copy[ 4] * copy[11] * copy[13]  -  copy[ 5] * copy[ 8] * copy[15]  +  copy[ 4] * copy[ 9] * copy[15]) / det;
            _coeff[12] = ( copy[ 6] * copy[ 9] * copy[12]  -  copy[ 5] * copy[10] * copy[12]  -  copy[ 6] * copy[ 8] * copy[13]  +  copy[ 4] * copy[10] * copy[13]  +  copy[ 5] * copy[ 8] * copy[14]  -  copy[ 4] * copy[ 9] * copy[14]) / det;

            _coeff[ 1] = ( copy[ 3] * copy[10] * copy[13]  -  copy[ 2] * copy[11] * copy[13]  -  copy[ 3] * copy[ 9] * copy[14]  +  copy[ 1] * copy[11] * copy[14]  +  copy[ 2] * copy[ 9] * copy[15]  -  copy[ 1] * copy[10] * copy[15]) / det;
            _coeff[ 5] = (-copy[ 3] * copy[10] * copy[12]  +  copy[ 2] * copy[11] * copy[12]  +  copy[ 3] * copy[ 8] * copy[14]  -  copy[ 0] * copy[11] * copy[14]  -  copy[ 2] * copy[ 8] * copy[15]  +  copy[ 0] * copy[10] * copy[15]) / det;
            _coeff[ 9] = ( copy[ 3] * copy[ 9] * copy[12]  -  copy[ 1] * copy[11] * copy[12]  -  copy[ 3] * copy[ 8] * copy[13]  +  copy[ 0] * copy[11] * copy[13]  +  copy[ 1] * copy[ 8] * copy[15]  -  copy[ 0] * copy[ 9] * copy[15]) / det;
            _coeff[13] = (-copy[ 2] * copy[ 9] * copy[12]  +  copy[ 1] * copy[10] * copy[12]  +  copy[ 2] * copy[ 8] * copy[13]  -  copy[ 0] * copy[10] * copy[13]  -  copy[ 1] * copy[ 8] * copy[14]  +  copy[ 0] * copy[ 9] * copy[14]) / det;

            _coeff[ 2] = (-copy[ 3] * copy[ 6] * copy[13]  +  copy[ 2] * copy[ 7] * copy[13]  +  copy[ 3] * copy[ 5] * copy[14]  -  copy[ 1] * copy[ 7] * copy[14]  -  copy[ 2] * copy[ 5] * copy[15]  +  copy[ 1] * copy[ 6] * copy[15]) / det;
            _coeff[ 6] = ( copy[ 3] * copy[ 6] * copy[12]  -  copy[ 2] * copy[ 7] * copy[12]  -  copy[ 3] * copy[ 4] * copy[14]  +  copy[ 0] * copy[ 7] * copy[14]  +  copy[ 2] * copy[ 4] * copy[15]  -  copy[ 0] * copy[ 6] * copy[15]) / det;
            _coeff[10] = (-copy[ 3] * copy[ 5] * copy[12]  +  copy[ 1] * copy[ 7] * copy[12]  +  copy[ 3] * copy[ 4] * copy[13]  -  copy[ 0] * copy[ 7] * copy[13]  -  copy[ 1] * copy[ 4] * copy[15]  +  copy[ 0] * copy[ 5] * copy[15]) / det;
            _coeff[14] = ( copy[ 2] * copy[ 5] * copy[12]  -  copy[ 1] * copy[ 6] * copy[12]  -  copy[ 2] * copy[ 4] * copy[13]  +  copy[ 0] * copy[ 6] * copy[13]  +  copy[ 1] * copy[ 4] * copy[14]  -  copy[ 0] * copy[ 5] * copy[14]) / det;

            _coeff[ 3] = ( copy[ 3] * copy[ 6] * copy[ 9]  -  copy[ 2] * copy[ 7] * copy[ 9]  -  copy[ 3] * copy[ 5] * copy[10]  +  copy[ 1] * copy[ 7] * copy[10]  +  copy[ 2] * copy[ 5] * copy[11]  -  copy[ 1] * copy[ 6] * copy[11]) / det;
            _coeff[ 7] = (-copy[ 3] * copy[ 6] * copy[ 8]  +  copy[ 2] * copy[ 7] * copy[ 8]  +  copy[ 3] * copy[ 4] * copy[10]  -  copy[ 0] * copy[ 7] * copy[10]  -  copy[ 2] * copy[ 4] * copy[11]  +  copy[ 0] * copy[ 6] * copy[11]) / det;
            _coeff[11] = ( copy[ 3] * copy[ 5] * copy[ 8]  -  copy[ 1] * copy[ 7] * copy[ 8]  -  copy[ 3] * copy[ 4] * copy[ 9]  +  copy[ 0] * copy[ 7] * copy[ 9]  +  copy[ 1] * copy[ 4] * copy[11]  -  copy[ 0] * copy[ 5] * copy[11]) / det;
            _coeff[15] = (-copy[ 2] * copy[ 5] * copy[ 8]  +  copy[ 1] * copy[ 6] * copy[ 8]  +  copy[ 2] * copy[ 4] * copy[ 9]  -  copy[ 0] * copy[ 6] * copy[ 9]  -  copy[ 1] * copy[ 4] * copy[10]  +  copy[ 0] * copy[ 5] * copy[10]) / det;
            // clang-format on
        }
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
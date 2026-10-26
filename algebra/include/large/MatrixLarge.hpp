#pragma once

#include "algebra/Internal.hpp"

#include <array>
#include <cstdlib>
#include <stdexcept>

namespace LCNS::large
{
    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
#if defined(AVX512_ENABLED)
    class alignas(64) MatrixLarge
#elif defined(AVX2_ENBALED)
    class alignas(32) MatrixLarge
#else
    class MatrixLarge
#endif
    {
    public:
        constexpr MatrixLarge() = default;

        /*!
         * @brief Accessor (read/write)
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return a reference on the corresponding coefficient
         */
        [[nodiscard]] constexpr coordinate& operator()(unsigned int i, unsigned int j);

        /*!
         * @brief Accessor (read only)
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return the corresponding coefficient
         */
        [[nodiscard]] constexpr coordinate operator()(unsigned int i, unsigned int j) const;

        /*!
         * @brief Get the matrix dimentions
         * @return a tuple with the row and column counts. To be used as `const auto [rows, cols] = matrix.dimensions();`
         */
        [[nodiscard]] constexpr std::tuple<unsigned int, unsigned int> dimensions() const;

    private:
        /*!
         * @brief Compute the num of elements in each row of the matrix including padding
         * @return The next number following cols that is a multiple of the aligned memory size
         */
        static consteval unsigned int paddedRows()
        {
            constexpr auto numElements = static_cast<int>(64 / sizeof(coordinate));

            // Remember that cols determine the number of elements in a row!!
            // constexpr auto res = std::div(static_cast<int>(cols), numElements);
            constexpr auto res = static_cast<int>(cols) / numElements;

            return (res + 1) * numElements;
        }

        /*!
         * @brief Unnamed helper function to get the 1D equalent of i and j
         * @param i is the index of the row where to find the coefficient to access
         * @param j is the index of the column where to find the coefficient to access
         * @return the equivalent index to access the coefficient in _coeff
         */
        constexpr unsigned int to1D(unsigned int i, unsigned int j) const;

    private:
        unsigned int _rows = rows;
        unsigned int _cols = cols;

        std::array<coordinate, paddedRows() * cols> _coeff{};

        // Grant friendship to a dedicated test peer class
        template <typename X, unsigned int Y, unsigned int Z>
        friend class MatrixLargeTestPeer;
    };

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr unsigned int MatrixLarge<coordinate, rows, cols>::to1D(unsigned int i, unsigned int j) const
    {
        auto result = (i * _cols) + j;
        return result;
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate& MatrixLarge<coordinate, rows, cols>::operator()(unsigned int i, unsigned int j)
    {
        if (rows <= i || cols <= j)
        {
            throw std::out_of_range("Index out of range to access matrix coefficient");
        }

        return _coeff[to1D(i, j)];
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr coordinate MatrixLarge<coordinate, rows, cols>::operator()(unsigned int i, unsigned int j) const
    {
        if (rows <= i || cols <= j)
        {
            throw std::out_of_range("Index out of range to access matrix coefficient");
        }

        return _coeff[to1D(i, j)];
    }

    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
    constexpr std::tuple<unsigned int, unsigned int> MatrixLarge<coordinate, rows, cols>::dimensions() const
    { return std::make_tuple(_rows, _cols); }


}

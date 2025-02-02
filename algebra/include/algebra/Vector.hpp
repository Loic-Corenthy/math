#pragma once

#include "algebra/Internal.hpp"

#include <cmath>
#include <array>
#include <stdexcept>

namespace LCNS::Algebra
{
    /*!
     *  \brief This class is the template class for vectors of different sizes
     */
    template <Coordinate coordinate, unsigned int size>
    class Vector
    {
    public:
        /*!
         * \brief Default constructor
         */
        constexpr Vector() = default;

        /*!
         * \brief Specific constructor for 1D vectors
         * @param x is the x coordinate
         */
        constexpr Vector(auto x) requires(size == 1);

        /*!
         * \brief Specific constructor for 2D vectors
         * @param x is the x coordinate
         * @param y is the y coordinate
         */
        constexpr Vector(auto x, auto y) requires(size == 2);

        /*!
         * \brief Specific constructor for 3D vectors
         * @param x is the x coordinate
         * @param y is the y coordinate
         * @param z is the z coordinate
         */
        constexpr Vector(auto x, auto y, auto z) requires(size == 3);

        /*!
         * \brief Specific constructor for 4D vectors
         * @param x is the x coordinate
         * @param y is the y coordinate
         * @param z is the z coordinate
         * @param w is the w coordinate
         */
        constexpr Vector(auto x, auto y, auto z, auto w) requires(size == 4);

        /*!
         * \brief Accessor (read only)
         * @param index is the index of the coordinate to access
         * @return a copy of the corresponding coordinate
         */
        constexpr coordinate operator[](unsigned int index) const;

        /*!
         * \brief Accessor (read/write)
         * @param index is the index of the coordinate to access
         * @return a reference to the corresponding coordinate
         */
        constexpr coordinate& operator[](unsigned int index);

        /*!
         * \brief Comparision operator
         * @param rhs is the vector to compare coordinates with
         * @return true if all coordinates of this vector and rhs are equal, false otherwise
         */
        constexpr bool operator==(const Vector<coordinate, size>& rhs) const;

        /*!
         * \brief Spaceship operator
         * @param rhs is the vector to compare with
         * @return true if the length of this vector is <, <=, >, >= than the length of rhs, false otherwise
         */
        constexpr auto operator<=>(const Vector<coordinate, size>& rhs) const;

        /*!
         * \brief Addition operator. Do not modify this object.
         * @param rhs is the vector to add to this one
         * @return a vector corresponding to this vector plus rhs
         */
        constexpr Vector<coordinate, size> operator+(const Vector<coordinate, size>& rhs) const noexcept;

        /*!
         * \brief Substraction operator. Do not modify this object.
         * @param rhs is the vector to substract from this one
         * @return a vector corresponding to this vector minus rhs
         */
        constexpr Vector<coordinate, size> operator-(const Vector<coordinate, size>& rhs) const noexcept;

        /*!
         * \brief Dot product. Does not modify this object.
         * @param rhs is the right hand side of the operation
         * @return a scalar value, equal to 0 if the 2 vectors are perpendicual to each other.
         */
        constexpr coordinate operator*(const Vector<coordinate, size>& rhs) const noexcept;

        /*!
         * \brief Cross product. Does not modify this object.
         * @param rhs must be a vector of 3 dimensions
         * @return a vector perpendicular to both this and rhs.
         */
        constexpr Vector<coordinate, size> operator^(const Vector<coordinate, size>& rhs) const noexcept requires(size == 3);

        /*!
         * \brief Multiplication operator. Do not modify this object.
         * @param scalar is the value that will multiply each coordinate of this object
         * @return a vector with the same direction and a length multiplied by scalar
         */
        constexpr Vector<coordinate, size> operator*(auto scalar) const noexcept;

        /*!
         * \brief Division operator. Do not modify this object.
         * @param scalar is the value that will divide each coordinate of this object
         * @return a vector with the same direction and a length divided by scalar
         */
        constexpr Vector<coordinate, size> operator/(auto scalar) const;

        /*!
         * \brief Addition with a vector. Modify this object
         * @param rhs is the vector to add to this one
         * @return a reference on this object after the operation
         */
        Vector<coordinate, size>& operator+=(const Vector<coordinate, size>& rhs) noexcept;

        /*!
         * \brief Substraction operator. Do not modify this object.
         * @param rhs is the vector to substract from this one
         * @return a reference on this object after the operation
         */
        Vector<coordinate, size>& operator-=(const Vector<coordinate, size>& rhs) noexcept;

        /*!
         * \brief Multiplication by a scalar operator
         * @param scalar is the value that will multiply all the coordinates
         * @return a reference on this object after the operation
         */
        Vector<coordinate, size>& operator*=(auto scalar) noexcept;

        /*!
         * \brief Division by a scalar operator
         * @param scalar is the value from which all the coordinates will be divided
         * @return a reference on this object after the operation
         */
        Vector<coordinate, size>& operator/=(auto scalar);

        /*!
         * \brief Get the first coordinate (read only)
         * @return the value of the first coordinate
         */
        constexpr coordinate x() const noexcept;

        /*!
         * \brief Get the first coordinate (read/write)
         * @return the value of the first coordinate
         */
        coordinate& x() noexcept;

        /*!
         * \brief Get the second coordinate (read only)
         * @return the value of the second coordinate
         */
        constexpr coordinate y() const noexcept requires(size > 1);

        /*!
         * \brief Get the second coordinate (read/write)
         * @return the value of the second coordinate
         */
        coordinate& y() noexcept requires(size > 1);

        /*!
         * \brief Get the third coordinate (read only)
         * @return the value of the third coordinate
         */
        constexpr coordinate z() const noexcept requires(size > 2);

        /*!
         * \brief Get the third coordinate (read/write)
         * @return the value of the third coordinate
         */
        coordinate& z() noexcept requires(size > 2);

        /*!
         * \brief Get the fourth coordinate (read only)
         * @return the value of the fourth coordinate
         */
        constexpr coordinate w() const noexcept requires(size > 3);

        /*!
         * \brief Get the fourth coordinate (read/write)
         * @return the value of the fourth coordinate
         */
        coordinate& w() noexcept requires(size > 3);

        /*!
         * \brief Compute the square length of the vector
         * @return the length of the vector squared
         */
        constexpr double sqrLength() const noexcept;

        /*!
         * \brief Compute the length of the vector
         * @return the length of the vector
         */
        double length() const;

        /*!
         * \brief Normalize this vector
         */
        void normalize() requires(std::is_floating_point_v<coordinate>);

        /*!
         * \brief Create a new vector which corresponds to the normalized version of this vector.
         *        Does not modify this object.
         * @return a vector of length 1 with the same direction
         */
        Vector<coordinate, size> normalized() const requires(std::is_floating_point_v<coordinate>);

        /*!
         * @brief Check if this vector is the null vector
         * @return true if all the coordinates are 0, false otherwise
         */
        [[nodiscard]] constexpr bool isNull() const noexcept;

    private:
        std::array<coordinate, size> _coords = {};
    };  // class Vector

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x) requires(size == 1)
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);

        _coords[0] = x;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x, auto y) requires(size == 2)
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);
        static_assert(std::is_same_v<decltype(y), coordinate>);

        _coords[0] = x;
        _coords[1] = y;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x, auto y, auto z) requires(size == 3)
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);
        static_assert(std::is_same_v<decltype(y), coordinate>);
        static_assert(std::is_same_v<decltype(z), coordinate>);

        _coords[0] = x;
        _coords[1] = y;
        _coords[2] = z;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x, auto y, auto z, auto w) requires(size == 4)
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);
        static_assert(std::is_same_v<decltype(y), coordinate>);
        static_assert(std::is_same_v<decltype(z), coordinate>);
        static_assert(std::is_same_v<decltype(w), coordinate>);

        _coords[0] = x;
        _coords[1] = y;
        _coords[2] = z;
        _coords[3] = w;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::operator[](unsigned int index) const
    {
        return _coords[index];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate& Vector<coordinate, size>::operator[](unsigned int index)
    {
        return _coords[index];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr bool Vector<coordinate, size>::operator==(const Vector<coordinate, size>& rhs) const
    {
        return _coords == rhs._coords;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr auto Vector<coordinate, size>::operator<=>(const Vector<coordinate, size>& rhs) const
    {
        return sqrLength() <=> rhs.sqrLength();
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size> Vector<coordinate, size>::operator+(const Vector<coordinate, size>& rhs) const noexcept
    {
        Vector<coordinate, size> result(*this);

        for (unsigned int i = 0; i < size; ++i)
        {
            result._coords[i] += rhs._coords[i];
        }

        return result;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size> Vector<coordinate, size>::operator-(const Vector<coordinate, size>& rhs) const noexcept
    {
        Vector<coordinate, size> result(*this);

        for (unsigned int i = 0; i < size; ++i)
        {
            result._coords[i] -= rhs._coords[i];
        }

        return result;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::operator*(const Vector<coordinate, size>& rhs) const noexcept
    {
        coordinate product = 0;

        for (unsigned int i = 0; i < _coords.size(); ++i)
        {
            product += _coords[i] * rhs._coords[i];
        }

        return product;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size> Vector<coordinate, size>::operator^(const Vector<coordinate, size>& rhs) const noexcept requires(size == 3)
    {
        return { static_cast<coordinate>(_coords[1] * rhs._coords[2] - _coords[2] * rhs._coords[1]),
                 static_cast<coordinate>(_coords[2] * rhs._coords[0] - _coords[0] * rhs._coords[2]),
                 static_cast<coordinate>(_coords[0] * rhs._coords[1] - _coords[1] * rhs._coords[0]) };
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size> Vector<coordinate, size>::operator*(auto scalar) const noexcept
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        Vector<coordinate, size> result(*this);

        for (auto& coord : result._coords)
        {
            coord *= scalar;
        }

        return result;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size> Vector<coordinate, size>::operator/(auto scalar) const
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        if (scalar == 0.0)
        {
            throw std::invalid_argument("Can't divide by 0");
        }

        Vector<coordinate, size> result(*this);

        for (auto& coord : result._coords)
        {
            coord /= scalar;
        }

        return result;
    }

    template <Coordinate coordinate, unsigned int size>
    Vector<coordinate, size>& Vector<coordinate, size>::operator+=(const Vector<coordinate, size>& rhs) noexcept
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            _coords[i] += rhs._coords[i];
        }

        return *this;
    }

    template <Coordinate coordinate, unsigned int size>
    Vector<coordinate, size>& Vector<coordinate, size>::operator-=(const Vector<coordinate, size>& rhs) noexcept
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            _coords[i] -= rhs._coords[i];
        }

        return *this;
    }

    template <Coordinate coordinate, unsigned int size>
    Vector<coordinate, size>& Vector<coordinate, size>::operator*=(auto scalar) noexcept
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        for (auto& coord : _coords)
        {
            coord *= scalar;
        }

        return *this;
    }

    template <Coordinate coordinate, unsigned int size>
    Vector<coordinate, size>& Vector<coordinate, size>::operator/=(auto scalar)
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        if (scalar == 0.0)
        {
            throw std::invalid_argument("Can't divide by 0");
        }

        for (auto& coord : _coords)
        {
            coord /= scalar;
        }

        return *this;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::x() const noexcept
    {
        return _coords[0];
    }

    template <Coordinate coordinate, unsigned int size>
    coordinate& Vector<coordinate, size>::x() noexcept
    {
        return _coords[0];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::y() const noexcept requires(size > 1)
    {
        return _coords[1];
    }

    template <Coordinate coordinate, unsigned int size>
    coordinate& Vector<coordinate, size>::y() noexcept requires(size > 1)
    {
        return _coords[1];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::z() const noexcept requires(size > 2)
    {
        return _coords[2];
    }

    template <Coordinate coordinate, unsigned int size>
    coordinate& Vector<coordinate, size>::z() noexcept requires(size > 2)
    {
        return _coords[2];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::w() const noexcept requires(size > 3)
    {
        return _coords[3];
    }

    template <Coordinate coordinate, unsigned int size>
    coordinate& Vector<coordinate, size>::w() noexcept requires(size > 3)
    {
        return _coords[3];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr double Vector<coordinate, size>::sqrLength() const noexcept
    {
        double length_square = 0.0;

        for (const auto coord : _coords)
        {
            length_square += coord * coord;
        }

        return length_square;
    }

    template <Coordinate coordinate, unsigned int size>
    double Vector<coordinate, size>::length() const
    {
        return std::sqrt(sqrLength());
    }

    template <Coordinate coordinate, unsigned int size>
    void Vector<coordinate, size>::normalize() requires(std::is_floating_point_v<coordinate>)
    {
        const auto len = length();

        if (len != 0.0)
        {
            for (auto& coord : _coords)
            {
                coord /= len;
            }
        }
    }

    template <Coordinate coordinate, unsigned int size>
    Vector<coordinate, size> Vector<coordinate, size>::normalized() const requires(std::is_floating_point_v<coordinate>)
    {
        Vector<coordinate, size> result(*this);

        result.normalize();

        return result;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr bool Vector<coordinate, size>::isNull() const noexcept
    {
        for (const auto& coord : _coords)
        {
            if (coord != static_cast<coordinate>(0))
            {
                return false;
            }
        }

        return true;
    }
}  // namespace LCNS::Algebra

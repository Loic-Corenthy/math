#pragma once

#include "algebra/Internal.hpp"

#include <cmath>
#include <array>
#include <stdexcept>

namespace LCNS::Algebra
{
    /*!
     *  \brief This class is the template class for quaternions
     */
    template <Coordinate coordinate>
    class Quaternion
    {
    public:
        /*!
         * \brief Default constructor
         */
        constexpr Quaternion() = default;

        /*!
         * \brief Specific constructor for quaternions
         * @param x is the coordinate of unit vector i
         * @param y is the coordinate of unit vector j
         * @param z is the coordinate of unit vector k
         * @param w is the scalar coordinate
         */
        constexpr Quaternion(auto x, auto y, auto z, auto w);

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
        coordinate& operator[](unsigned int index);

        /*!
         * \brief Comparision operator
         * @param rhs is the quaternion to compare coordinates with
         * @return true if all coordinates of this quaternion and rhs are equal, false otherwise
         */
        constexpr bool operator==(const Quaternion<coordinate>& rhs) const;

        /*!
         * \brief Spaceship operator
         * @param rhs is the quaternion to compare with
         * @return true if the length of this quaternion is <, <=, >, >= than the length of rhs, false otherwise
         */
        constexpr auto operator<=>(const Quaternion<coordinate>& rhs) const;

        /*!
         * \brief Addition operator. Do not modify this object.
         * @param rhs is the quaternion to add to this one
         * @return a quaternion corresponding to this quaternion plus rhs
         */
        constexpr Quaternion<coordinate> operator+(const Quaternion<coordinate>& rhs) const noexcept;

        /*!
         * \brief Substraction operator. Do not modify this object.
         * @param rhs is the quaternion to substract from this one
         * @return a quaternion corresponding to this quaternion minus rhs
         */
        constexpr Quaternion<coordinate> operator-(const Quaternion<coordinate>& rhs) const noexcept;

        /*!
         * \brief Hamilton product. Does not modify this object.
         * @param rhs is the right hand side of the operation
         * @return a quaternion
         */
        constexpr Quaternion<coordinate> operator*(const Quaternion<coordinate>& rhs) const noexcept;

        /*!
         * \brief Multiplication by a scalar operator. Do not modify this object.
         * @param scalar is the value that will multiply each coordinate of this object
         * @return a quaternion
         */
        constexpr Quaternion<coordinate> operator*(auto scalar) const noexcept;

        /*!
         * \brief Division by a scalar operator. Do not modify this object.
         * @param scalar is the value that will divide each coordinate of this object
         * @return a quaternion
         */
        constexpr Quaternion<coordinate> operator/(auto scalar) const;

        /*!
         * @brief Addition operator. Modify this object
         * @param rhs is the quaternion to add to this
         * @return a reference on this object after the operation
         */
        Quaternion<coordinate>& operator+=(const Quaternion<coordinate>& rhs) noexcept;

        /*!
         * @brief Addition operator. Modify this object
         * @param rhs is the quaternion to substract to this
         * @return a reference on this object after the operation
         */
        Quaternion<coordinate>& operator-=(const Quaternion<coordinate>& rhs) noexcept;

        /*!
         * @brief Multiplication by a scalar operator. Modify this object
         * @param rhs is the scalar that the coordinates of this will be multiplied by.
         * @return a reference on this object after the operation
         */
        Quaternion<coordinate>& operator*=(auto rhs) noexcept;

        /*!
         * @brief Division by a scalar operator. Modify this object
         * @param rhs is the scalar that the coordinates of this will be divided by.
         * @return a reference on this object after the operation
         */
        Quaternion<coordinate>& operator/=(auto rhs);

        /*!
         * \brief Get the coordinate of unit vector i (read only)
         * @return the value of the first coordinate
         */
        constexpr coordinate x() const noexcept;

        /*!
         * \brief Get the coordinate of unit vector i (read/write)
         * @return the value of the first coordinate
         */
        coordinate& x() noexcept;

        /*!
         * \brief Get the coordinate of unit vector j (read only)
         * @return the value of the second coordinate
         */
        constexpr coordinate y() const noexcept;

        /*!
         * \brief Get the coordinate of unit vector j (read/write)
         * @return the value of the second coordinate
         */
        coordinate& y() noexcept;

        /*!
         * \brief Get the coordinate of unit vector k (read only)
         * @return the value of the third coordinate
         */
        constexpr coordinate z() const noexcept;

        /*!
         * \brief Get the coordinate of unit vector k (read/write)
         * @return the value of the third coordinate
         */
        coordinate& z() noexcept;

        /*!
         * \brief Get the scalar coordinate (read only)
         * @return the value of the fourth coordinate
         */
        constexpr coordinate w() const noexcept;

        /*!
         * \brief Get the fourth coordinate (read/write)
         * @return the value of the fourth coordinate
         */
        coordinate& w() noexcept;

        /*!
         * \brief Compute the square length of the quaternion
         * @return the length of the quaternion squared
         */
        constexpr double sqrLength() const noexcept;

        /*!
         * \brief Compute the length of the quaternion
         * @return the length of the quaternion
         */
        double length() const;

        /*!
         * \brief Normalize this quaternion
         */
        void normalize() requires(std::is_floating_point_v<coordinate>);

        /*!
         * \brief Create a new quaternion which corresponds to the normalized version of this quaternion.
         *        Does not modify this object.
         * @return a quaternion of length 1 with the same direction
         */
        Quaternion<coordinate> normalized() const requires(std::is_floating_point_v<coordinate>);

        /*!
         * @brief Check if this quaternion is the null quaternion
         * @return true if all the coordinates are 0, false otherwise
         */
        [[nodiscard]] constexpr bool isNull() const noexcept;

        /*!
         * \brief Conjugate this quaternion, i.e. multiply the imaginary coefficient by -1
         */
        void conjugate() noexcept;

        /*!
         * \brief Create a new quaternion which corresponds its conjugate
         *        Do not modify this object.
         * @return a copy of the conjugate of this quaternion
         */
        constexpr Quaternion<coordinate> conjugated() const noexcept;

    private:
        std::array<coordinate, 4> _coords = {};
    };  // class Quaternion

    template <Coordinate coordinate>
    constexpr Quaternion<coordinate>::Quaternion(auto x, auto y, auto z, auto w)
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

    template <Coordinate coordinate>
    constexpr coordinate Quaternion<coordinate>::operator[](unsigned int index) const
    {
        return _coords[index];
    }

    template <Coordinate coordinate>
    coordinate& Quaternion<coordinate>::operator[](unsigned int index)
    {
        return _coords[index];
    }

    template <Coordinate coordinate>
    constexpr bool Quaternion<coordinate>::operator==(const Quaternion<coordinate>& rhs) const
    {
        return _coords == rhs._coords;
    }

    template <Coordinate coordinate>
    constexpr auto Quaternion<coordinate>::operator<=>(const Quaternion<coordinate>& rhs) const
    {
        return sqrLength() <=> rhs.sqrLength();
    }

    template <Coordinate coordinate>
    constexpr Quaternion<coordinate> Quaternion<coordinate>::operator+(const Quaternion<coordinate>& rhs) const noexcept
    {
        const coordinate x = _coords[0] + rhs._coords[0];
        const coordinate y = _coords[1] + rhs._coords[1];
        const coordinate z = _coords[2] + rhs._coords[2];
        const coordinate w = _coords[3] + rhs._coords[3];

        return { x, y, z, w };
    }

    template <Coordinate coordinate>
    constexpr Quaternion<coordinate> Quaternion<coordinate>::operator-(const Quaternion<coordinate>& rhs) const noexcept
    {
        const coordinate x = _coords[0] - rhs._coords[0];
        const coordinate y = _coords[1] - rhs._coords[1];
        const coordinate z = _coords[2] - rhs._coords[2];
        const coordinate w = _coords[3] - rhs._coords[3];

        return { x, y, z, w };
    }

    template <Coordinate coordinate>
    constexpr Quaternion<coordinate> Quaternion<coordinate>::operator*(const Quaternion<coordinate>& rhs) const noexcept
    {
        const coordinate x = _coords[3] * rhs._coords[0] + _coords[0] * rhs._coords[3] + _coords[1] * rhs._coords[2] - _coords[2] * rhs._coords[1];
        const coordinate y = _coords[3] * rhs._coords[1] - _coords[0] * rhs._coords[2] + _coords[1] * rhs._coords[3] + _coords[2] * rhs._coords[0];
        const coordinate z = _coords[3] * rhs._coords[2] + _coords[0] * rhs._coords[1] - _coords[1] * rhs._coords[0] + _coords[2] * rhs._coords[3];
        const coordinate w = _coords[3] * rhs._coords[3] - _coords[0] * rhs._coords[0] - _coords[1] * rhs._coords[1] - _coords[2] * rhs._coords[2];

        return { x, y, z, w };
    }

    template <Coordinate coordinate>
    constexpr Quaternion<coordinate> Quaternion<coordinate>::operator*(auto scalar) const noexcept
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        const coordinate x = _coords[0] * scalar;
        const coordinate y = _coords[1] * scalar;
        const coordinate z = _coords[2] * scalar;
        const coordinate w = _coords[3] * scalar;

        return { x, y, z, w };
    }

    template <Coordinate coordinate>
    constexpr Quaternion<coordinate> Quaternion<coordinate>::operator/(auto scalar) const
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        if (scalar == 0.0)
        {
            throw std::invalid_argument("Can't divide by 0");
        }

        const coordinate x = _coords[0] / scalar;
        const coordinate y = _coords[1] / scalar;
        const coordinate z = _coords[2] / scalar;
        const coordinate w = _coords[3] / scalar;

        return { x, y, z, w };
    }

    template <Coordinate coordinate>
    Quaternion<coordinate>& Quaternion<coordinate>::operator+=(const Quaternion<coordinate>& rhs) noexcept
    {
        _coords[0] += rhs._coords[0];
        _coords[1] += rhs._coords[1];
        _coords[2] += rhs._coords[2];
        _coords[3] += rhs._coords[3];

        return *this;
    }

    template <Coordinate coordinate>
    Quaternion<coordinate>& Quaternion<coordinate>::operator-=(const Quaternion<coordinate>& rhs) noexcept
    {
        _coords[0] -= rhs._coords[0];
        _coords[1] -= rhs._coords[1];
        _coords[2] -= rhs._coords[2];
        _coords[3] -= rhs._coords[3];

        return *this;
    }

    template <Coordinate coordinate>
    Quaternion<coordinate>& Quaternion<coordinate>::operator*=(auto scalar) noexcept
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        _coords[0] *= scalar;
        _coords[1] *= scalar;
        _coords[2] *= scalar;
        _coords[3] *= scalar;

        return *this;
    }

    template <Coordinate coordinate>
    Quaternion<coordinate>& Quaternion<coordinate>::operator/=(auto scalar)
    {
        static_assert(std::is_same_v<decltype(scalar), coordinate>);

        if (scalar == 0.0)
        {
            throw std::invalid_argument("Can't divide by 0");
        }

        _coords[0] /= scalar;
        _coords[1] /= scalar;
        _coords[2] /= scalar;
        _coords[3] /= scalar;

        return *this;
    }

    template <Coordinate coordinate>
    constexpr coordinate Quaternion<coordinate>::x() const noexcept
    {
        return _coords[0];
    }

    template <Coordinate coordinate>
    coordinate& Quaternion<coordinate>::x() noexcept
    {
        return _coords[0];
    }

    template <Coordinate coordinate>
    constexpr coordinate Quaternion<coordinate>::y() const noexcept
    {
        return _coords[1];
    }

    template <Coordinate coordinate>
    coordinate& Quaternion<coordinate>::y() noexcept
    {
        return _coords[1];
    }

    template <Coordinate coordinate>
    constexpr coordinate Quaternion<coordinate>::z() const noexcept
    {
        return _coords[2];
    }

    template <Coordinate coordinate>
    coordinate& Quaternion<coordinate>::z() noexcept
    {
        return _coords[2];
    }

    template <Coordinate coordinate>
    constexpr coordinate Quaternion<coordinate>::w() const noexcept
    {
        return _coords[3];
    }

    template <Coordinate coordinate>
    coordinate& Quaternion<coordinate>::w() noexcept
    {
        return _coords[3];
    }

    template <Coordinate coordinate>
    constexpr double Quaternion<coordinate>::sqrLength() const noexcept
    {
        double length_square = 0.0;

        for (const auto coord : _coords)
        {
            length_square += coord * coord;
        }

        return length_square;
    }

    template <Coordinate coordinate>
    double Quaternion<coordinate>::length() const
    {
        return std::sqrt(sqrLength());
    }

    template <Coordinate coordinate>
    void Quaternion<coordinate>::normalize() requires(std::is_floating_point_v<coordinate>)
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

    template <Coordinate coordinate>
    Quaternion<coordinate> Quaternion<coordinate>::normalized() const requires(std::is_floating_point_v<coordinate>)
    {
        Quaternion<coordinate> result(*this);

        result.normalize();

        return result;
    }

    template <Coordinate coordinate>
    constexpr bool Quaternion<coordinate>::isNull() const noexcept
    {
        for (const auto& c : _coords)
        {
            if (c != static_cast<coordinate>(0))
            {
                return false;
            }
        }

        return true;
    }

    template <Coordinate coordinate>
    void Quaternion<coordinate>::conjugate() noexcept
    {
        _coords[0] = -_coords[0];
        _coords[1] = -_coords[1];
        _coords[2] = -_coords[2];
    }

    template <Coordinate coordinate>
    constexpr Quaternion<coordinate> Quaternion<coordinate>::conjugated() const noexcept
    {
        constexpr coordinate minusOne = -1;

        // clang-format off
        // The cast is necessary because negating changes the type in some cases, e.g. short int -> int
        return { static_cast<coordinate>(-_coords[0]),
                 static_cast<coordinate>(-_coords[1]),
                 static_cast<coordinate>(-_coords[2]),
                 _coords[3]};
        // clang-format on
    }

}  // namespace LCNS::Algebra

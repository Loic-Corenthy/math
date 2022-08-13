#pragma once

#include "algebra/Internal.hpp"

#include <cmath>
#include <array>

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
         * \brief Constructor with a list of values for the coordinates
         * @param coordinates is a list of coefficients that will be used to set the coordinates of the vector.
         *        There must be as many coefficients as SIZE
         */
        constexpr Vector(const std::initializer_list<coordinate>& coordinates);

        /*!
         * \brief Accessor (read/write)
         * @param index is the index of the coordinate to access
         * @return a reference to the corresponding coordinate
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
         * @param rhs is the vector to compare coefficients from
         * @return true if all coordinates of this vector and rhs are equal, false otherwise
         */
        constexpr bool operator==(const Vector<coordinate, size>& rhs) const;

        /*!
         * \brief Spaceship operator
         * @param rhs is the vector to compare from
         * @return true if the length of this vector is <, <=, >, >= than the length of rhs, false otherwise
         */
        constexpr bool operator<=>(const Vector<coordinate, size>& rhs) const;

        /*!
         * \brief Get the first coefficient (read only)
         * @return the value of the first coefficient
         */
        constexpr coordinate  x() const noexcept;
        constexpr coordinate& x() noexcept;

        constexpr coordinate  y() const noexcept requires(size > 1);
        constexpr coordinate& y() noexcept requires(size > 1);

        constexpr coordinate  z() const noexcept requires(size > 2);
        constexpr coordinate& z() noexcept requires(size > 2);

        constexpr coordinate  w() const noexcept requires(size > 3);
        constexpr coordinate& w() noexcept requires(size > 3);

        constexpr double sqrLength() const noexcept;
        double           length() const;

        constexpr coordinate dot(const Vector<coordinate, size>& rhs) const noexcept;

        constexpr Vector<coordinate, size> cross(const Vector<coordinate, size>& rhs) const noexcept requires(size == 3);

        void                     normalize();
        Vector<coordinate, size> normalized() const;

    private:
        std::array<coordinate, size> _coords = {};
    };  // class Vector

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x) requires(size == 1)
    : _coords({ x })
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x, auto y) requires(size == 2)
    : _coords({ x, y })
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);
        static_assert(std::is_same_v<decltype(y), coordinate>);
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x, auto y, auto z) requires(size == 3)
    : _coords({ x, y, z })
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);
        static_assert(std::is_same_v<decltype(y), coordinate>);
        static_assert(std::is_same_v<decltype(z), coordinate>);
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(auto x, auto y, auto z, auto w) requires(size == 4)
    : _coords({ x, y, z, w })
    {
        static_assert(std::is_same_v<decltype(x), coordinate>);
        static_assert(std::is_same_v<decltype(y), coordinate>);
        static_assert(std::is_same_v<decltype(z), coordinate>);
        static_assert(std::is_same_v<decltype(w), coordinate>);
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size>::Vector(const std::initializer_list<coordinate>& coordinates)
    : _coords(coordinates)
    {
        static_assert(coordinates.size() == size);
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
    constexpr bool Vector<coordinate, size>::operator<=>(const Vector<coordinate, size>& rhs) const
    {
        return sqrLength() <=> rhs.sqrLength();
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::x() const noexcept
    {
        return _coords[0];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate& Vector<coordinate, size>::x() noexcept
    {
        return _coords[0];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::y() const noexcept requires(size > 1)
    {
        return _coords[1];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate& Vector<coordinate, size>::y() noexcept requires(size > 1)
    {
        return _coords[1];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::z() const noexcept requires(size > 2)
    {
        return _coords[2];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate& Vector<coordinate, size>::z() noexcept requires(size > 2)
    {
        return _coords[2];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate Vector<coordinate, size>::w() const noexcept requires(size > 3)
    {
        return _coords[3];
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr coordinate& Vector<coordinate, size>::w() noexcept requires(size > 3)
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
    constexpr coordinate Vector<coordinate, size>::dot(const Vector<coordinate, size>& rhs) const noexcept
    {
        coordinate product = 0;

        for (unsigned int i = 0; i < _coords.size(); ++i)
        {
            product += _coords[i] * rhs._coords[i];
        }

        return product;
    }

    template <Coordinate coordinate, unsigned int size>
    constexpr Vector<coordinate, size> Vector<coordinate, size>::cross(const Vector<coordinate, size>& rhs) const noexcept requires(size == 3)
    {
        return { _coords[1] * rhs._coords[2] - _coords[2] * rhs._coords[1],
                 _coords[2] * rhs._coords[0] - _coords[0] * rhs._coords[2],
                 _coords[0] * rhs._coords[1] - _coords[1] * rhs._coords[0] };
    }

    template <Coordinate coordinate, unsigned int size>
    void Vector<coordinate, size>::normalize()
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
    Vector<coordinate, size> Vector<coordinate, size>::normalized() const
    {
        Vector<coordinate, size> result(*this);

        result.normalize();

        return result;
    }
}  // namespace LCNS::Algebra

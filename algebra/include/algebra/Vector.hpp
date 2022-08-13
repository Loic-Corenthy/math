#pragma once

#include "algebra/Internal.hpp"

#include <array>

namespace LCNS
{
    template <Coordinate number, unsigned int size>
    class Vector
    {
    public:
        constexpr Vector() = default;

        constexpr explicit Vector(auto x) requires(size == 1);
        constexpr explicit Vector(auto x, auto y) requires(size == 2);
        constexpr explicit Vector(auto x, auto y, auto z) requires(size == 3);
        constexpr explicit Vector(auto x, auto y, auto z, auto w) requires(size == 4);

        constexpr number  operator[](unsigned int index) const;
        constexpr number& operator[](unsigned int index);

        constexpr bool operator<=>(const Vector<number, size>& rhs) const;

        constexpr number  x() const noexcept;
        constexpr number& x() noexcept;

        constexpr number  y() const noexcept requires(size > 1);
        constexpr number& y() noexcept requires(size > 1);

        constexpr number  z() const noexcept requires(size > 2);
        constexpr number& z() noexcept requires(size > 2);

        constexpr number  w() const noexcept requires(size > 3);
        constexpr number& w() noexcept requires(size > 3);

        constexpr double length() const noexcept;

        constexpr number dot(const Vector<number, size>& rhs) const noexcept;

        constexpr Vector<number, size> cross(const Vector<number, size>& rhs) const requires(size == 2 || size == 3);

        constexpr void                 normalize() noexcept;
        constexpr Vector<number, size> normalized() const noexcept;

    private:
        std::array<number, size> _coords = {};
    };

    template <Coordinate number, unsigned int size>
    constexpr Vector<number, size>::Vector(auto x) requires(size == 1)
    {
        static_assert(std::is_same_v<decltype(x), number>);
        _coords[0] = x;
    }

    template <Coordinate number, unsigned int size>
    constexpr Vector<number, size>::Vector(auto x, auto y) requires(size == 2)
    {
        static_assert(std::is_same_v<decltype(x), number>);
        static_assert(std::is_same_v<decltype(y), number>);

        _coords[0] = x;
        _coords[1] = y;
    }

    template <Coordinate number, unsigned int size>
    constexpr Vector<number, size>::Vector(auto x, auto y, auto z) requires(size == 3)
    {
        _coords[0] = x;
        _coords[1] = y;
        _coords[2] = z;
    }

    template <Coordinate number, unsigned int size>
    constexpr Vector<number, size>::Vector(auto x, auto y, auto z, auto w) requires(size == 4)
    {
        _coords[0] = x;
        _coords[1] = y;
        _coords[2] = z;
        _coords[3] = w;
    }

    template <Coordinate number, unsigned int size>
    constexpr number Vector<number, size>::operator[](unsigned int index) const
    {
        return _coords[index];
    }

    template <Coordinate number, unsigned int size>
    constexpr number& Vector<number, size>::operator[](unsigned int index)
    {
        return _coords[index];
    }

    template <Coordinate number, unsigned int size>
    constexpr number Vector<number, size>::x() const noexcept
    {
        return _coords[0];
    }

    template <Coordinate number, unsigned int size>
    constexpr number& Vector<number, size>::x() noexcept
    {
        return _coords[0];
    }
    // constexpr Vector() = default;

    // constexpr Vector(number x) requires (size == 1);
    // constexpr Vector(number x, number y) requires (size == 2);
    // constexpr Vector(number x, number y, number z) requires (size == 3);
    // constexpr Vector(number x, number y, number w) requires (size == 4);

    // constexpr number operator[](unsigned int index) const;
    // constexpr number& operator[](unsigned int index);

    // constexpr bool operator<=>(const Vector<number, size>& rhs) const;

    // constexpr number x() const noexcept;
    // constexpr number& x() noexcept;

    // constexpr number y() const noexcept requires (size > 1);
    // constexpr number& y() noexcept requires (size > 1);

    // constexpr number z() const noexcept requires (size > 2);
    // constexpr number& z() noexcept requires (size > 2);

    // constexpr number w() const noexcept requires (size > 3);
    // constexpr number& w() noexcept requires (size > 3);

    // constexpr double length() const noexcept;

    // constexpr number dot(const Vector<number, size>& rhs) const noexcept;

    // constexpr Vector<number, size> cross(const Vector<number, size>& rhs) const requires (size == 2 || size == 3);

    // constexpr void normalize() noexcept;
    // constexpr Vector<number, size> normalized() const noexcept;
}
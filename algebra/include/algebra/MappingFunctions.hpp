#pragma once

#include "algebra/Vector.hpp"
#include "algebra/Matrix.hpp"
#include "algebra/Quaternion.hpp"

#include <tuple>
#include <cmath>
#include <numbers>

using std::numbers::pi;

namespace LCNS::Algebra
{
    template <Coordinate coordinate>
    std::tuple<double, double, double> EulerAnglesFromRotationMatrix(const Matrix<coordinate, 3, 3>& mat)
    requires std::is_floating_point_v<coordinate>
    {
        constexpr coordinate one = 1.0;
        if (std::abs(mat(2, 0)) != one)
        {
            const double theta     = -asin(mat(2, 0));
            const double cos_theta = cos(theta);
            const double psi       = atan2(mat(2, 1) / cos_theta, mat(2, 2) / cos_theta);
            const double phi       = atan2(mat(1, 0) / cos_theta, mat(0, 0) / cos_theta);

            return { psi, theta, phi };
        }

        // In this case, phi can be set to zero
        if (mat(2, 0) == -1.0)
        {
            constexpr double theta = pi / 2.0;
            const double     psi   = atan2(mat(0, 1), mat(0, 2));

            return { psi, theta, 0.0 };
        }

        constexpr double theta = -pi / 2.0;
        const double     psi   = atan2(-mat(0, 1), -mat(0, 2));

        return { psi, theta, 0.0 };
    }

    template <Coordinate coordinate>
    Quaternion<coordinate> RotationMatrixAsQuaternion(const Matrix<coordinate, 3, 3>& mat) requires std::is_floating_point_v<coordinate>
    {
        if (mat.isNull())
        {
            return {};
        }

        const auto [psi, theta, phi] = EulerAnglesFromRotationMatrix(mat);

        const double cos_psi   = cos(psi * 0.5);
        const double sin_psi   = sin(psi * 0.5);
        const double cos_theta = cos(theta * 0.5);
        const double sin_theta = sin(theta * 0.5);
        const double cos_phi   = cos(phi * 0.5);
        const double sin_phi   = sin(phi * 0.5);

        return { static_cast<coordinate>(sin_psi * cos_theta * cos_phi - cos_psi * sin_theta * sin_phi),
                 static_cast<coordinate>(cos_psi * sin_theta * cos_phi + sin_psi * cos_theta * sin_phi),
                 static_cast<coordinate>(cos_psi * cos_theta * sin_phi - sin_psi * sin_theta * cos_phi),
                 static_cast<coordinate>(cos_psi * cos_theta * cos_phi + sin_psi * sin_theta * sin_phi) };
    }

    template <Coordinate coordinate>
    Matrix<coordinate, 3, 3> QuaternionAsRotationMatrix(const Quaternion<coordinate>& quat) requires std::is_floating_point_v<coordinate>
    {
        const auto impl = [](const Quaternion<coordinate>& qtn)
        {
            // NOLINTBEGIN(readability-identifier-length)
            const coordinate xs = qtn.x() * qtn.x();
            const coordinate ys = qtn.y() * qtn.y();
            const coordinate zs = qtn.z() * qtn.z();
            const coordinate ws = qtn.w() * qtn.w();

            const coordinate xy = qtn.x() * qtn.y();
            const coordinate xz = qtn.x() * qtn.z();
            const coordinate yz = qtn.y() * qtn.z();
            const coordinate wx = qtn.w() * qtn.x();
            const coordinate wy = qtn.w() * qtn.y();
            const coordinate wz = qtn.w() * qtn.z();
            // NOLINTEND(readability-identifier-length)

            const coordinate two = 2.0;

            // clang-format off
            return Matrix<coordinate, 3, 3>({ws + xs - ys - zs,     two*(xy - wz),     two*(wy + xz),
                                                 two*(xy + wz), ws - xs + ys - zs,     two*(yz - wx),
                                                 two*(xz - wy),     two*(wx + yz), ws - xs - ys + zs});
            //clang-format on
        };

        if (quat.length() == 1.0)
        {
            return impl(quat);
        }

        auto copy = quat;
        copy.normalize();

        return impl(copy);
    }
}

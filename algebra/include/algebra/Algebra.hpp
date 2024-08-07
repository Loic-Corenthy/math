#pragma once

#include "algebra/Vector.hpp"
#include "algebra/Matrix.hpp"
#include "algebra/Quaternion.hpp"
#include "algebra/MappingFunctions.hpp"

using vec1i = LCNS::Algebra::Vector<int, 1>;
using vec1u = LCNS::Algebra::Vector<unsigned int, 1>;
using vec1f = LCNS::Algebra::Vector<float, 1>;
using vec1d = LCNS::Algebra::Vector<double, 1>;

using vec2i = LCNS::Algebra::Vector<int, 2>;
using vec2u = LCNS::Algebra::Vector<unsigned int, 2>;
using vec2f = LCNS::Algebra::Vector<float, 2>;
using vec2d = LCNS::Algebra::Vector<double, 2>;

using vec3i = LCNS::Algebra::Vector<int, 3>;
using vec3u = LCNS::Algebra::Vector<unsigned int, 3>;
using vec3f = LCNS::Algebra::Vector<float, 3>;
using vec3d = LCNS::Algebra::Vector<double, 3>;

using vec4i = LCNS::Algebra::Vector<int, 4>;
using vec4u = LCNS::Algebra::Vector<unsigned int, 4>;
using vec4f = LCNS::Algebra::Vector<float, 4>;
using vec4d = LCNS::Algebra::Vector<double, 4>;

using quati = LCNS::Algebra::Quaternion<int>;
using quatf = LCNS::Algebra::Quaternion<float>;
using quatd = LCNS::Algebra::Quaternion<double>;

using mat2i = LCNS::Algebra::Matrix<int, 2, 2>;
using mat2u = LCNS::Algebra::Matrix<unsigned int, 2, 2>;
using mat2f = LCNS::Algebra::Matrix<float, 2, 2>;
using mat2d = LCNS::Algebra::Matrix<double, 2, 2>;

using mat3i = LCNS::Algebra::Matrix<int, 3, 3>;
using mat3u = LCNS::Algebra::Matrix<unsigned int, 3, 3>;
using mat3f = LCNS::Algebra::Matrix<float, 3, 3>;
using mat3d = LCNS::Algebra::Matrix<double, 3, 3>;

using mat4i = LCNS::Algebra::Matrix<int, 4, 4>;
using mat4u = LCNS::Algebra::Matrix<unsigned int, 4, 4>;
using mat4f = LCNS::Algebra::Matrix<float, 4, 4>;
using mat4d = LCNS::Algebra::Matrix<double, 4, 4>;

#pragma once

#include "large/Matrix.hpp"

namespace LCNS::Large
{
    Matrix multiply_classic(const Matrix& lhs, const Matrix& rhs);
    Matrix multiply_simd(const Matrix& lhs, const Matrix& rhs);
}  // namespace LCNS::Large

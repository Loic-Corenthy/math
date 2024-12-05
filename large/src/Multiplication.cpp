#include "large/Multiplication.hpp"

#include <immintrin.h>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <array>

using LCNS::Large::Matrix;

using std::runtime_error;

Matrix LCNS::Large::multiply_classic(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.col_count() != rhs.row_count())
    {
        throw runtime_error("Invalid matrix dimensions for multiplication");
    }

    Matrix result(lhs.row_count(), rhs.col_count());
    for (unsigned int i = 0; i < lhs.row_count(); ++i)
    {
        for (unsigned int j = 0; j < rhs.col_count(); ++j)
        {
            for (unsigned int k = 0; k < lhs.col_count(); ++k)
            {
                result(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }

    return result;
}


Matrix LCNS::Large::multiply_simd(const Matrix& lhs, const Matrix& rhs)
{
    if (!__builtin_cpu_supports("avx"))
    {
        throw runtime_error("AVX is not supported on this processor.\n");
    }

    const Matrix rhs_transposed = rhs.transpose();
    const auto   division       = std::div(lhs.col_count(), 8);

    Matrix result(lhs.row_count(), rhs.col_count());
    for (unsigned int i = 0; i < lhs.row_count(); ++i)
    {
        for (unsigned int j = 0; j < rhs.col_count(); ++j)
        {
            float dot_product = 0.0f;
            for (int k = 0; k < division.quot; ++k)
            {
                __m256 lhs_chunk = _mm256_loadu_ps(lhs.data() + i * lhs.col_count() + 8 * k);
                __m256 rhs_chunk = _mm256_loadu_ps(rhs_transposed.data() + j * rhs_transposed.col_count() + 8 * k);

                __m256 multiplications = _mm256_mul_ps(lhs_chunk, rhs_chunk);
                float* tmp             = reinterpret_cast<float*>(&multiplications);
                dot_product += (tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7]);
            }

            if (division.rem != 0)
            {
                __m256 lhs_chunk = _mm256_loadu_ps(lhs.data() + i * lhs.col_count() + 8 * division.quot );
                __m256 rhs_chunk = _mm256_loadu_ps(rhs_transposed.data() + j * rhs_transposed.col_count() + 8 * division.quot);

                __m256 multiplications = _mm256_mul_ps(lhs_chunk, rhs_chunk);
                float* tmp             = reinterpret_cast<float*>(&multiplications);

                for (int k = 0; k < division.rem; ++k)
                {
                    dot_product += tmp[k];
                }
            }

            result(i, j) = dot_product;
        }
    }

    return result;
}

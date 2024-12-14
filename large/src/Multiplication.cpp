#include "large/Multiplication.hpp"

#include <immintrin.h>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <array>
#include <thread>
#include <vector>
#include <span>

using LCNS::Large::Matrix;

using std::dynamic_extent;
using std::ref;
using std::runtime_error;
using std::size_t;
using std::span;
using std::thread;
using std::vector;

namespace
{
    float dot_product(span<const float, dynamic_extent> row, span<const float, dynamic_extent> col)
    {
        float result = 0.0f;

        auto row_begin = row.begin();
        auto col_begin = col.begin();

        while (row_begin != row.end())
        {
            result += (*row_begin) * (*col_begin);
            row_begin++;
            col_begin++;
        }

        return result;
    }

    void process_rows(size_t thread_index, int count, const Matrix& lhs, const Matrix& rhs_transposed, Matrix& result)
    {
        const auto row_end = thread_index + count;
        for (size_t i = thread_index; i < row_end; ++i)
        {
            for (size_t j = 0; j < rhs_transposed.row_count(); j++)
            {
                result(i, j) = dot_product(
                span(lhs.data() + i * lhs.col_count(), lhs.data() + (i + 1) * lhs.col_count()),
                span(rhs_transposed.data() + j * rhs_transposed.col_count(), rhs_transposed.data() + (j + 1) * rhs_transposed.col_count()));
            }
        }
    }
}  // namespace


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
                __m256 lhs_chunk = _mm256_loadu_ps(lhs.data() + i * lhs.col_count() + 8 * division.quot);
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

Matrix LCNS::Large::multiply_concurrently([[maybe_unused]] const Matrix& lhs, [[maybe_unused]] const Matrix& rhs)
{
    const Matrix rhs_transposed = rhs.transpose();
    const auto   thread_count   = std::thread::hardware_concurrency();
    const auto   repartition    = std::div(static_cast<int>(lhs.row_count()), static_cast<int>(thread_count));

    const size_t real_thread_count    = lhs.row_count() < thread_count ? lhs.row_count() : thread_count;
    const auto   row_per_thread_count = repartition.quot == 0 ? 1u : static_cast<size_t>(repartition.quot);

    vector<thread> row_threads;
    row_threads.reserve(real_thread_count);
    Matrix result(lhs.row_count(), rhs.col_count());

    for (size_t i = 0; i < real_thread_count; ++i)
    {
        row_threads.emplace_back(
        process_rows, i * row_per_thread_count, row_per_thread_count, ref(lhs), ref(rhs_transposed), ref(result));
    }

    if (real_thread_count == thread_count && repartition.quot != 0)
    {
        for (size_t i = 0; i < static_cast<size_t>(repartition.rem); ++i)
        {
            row_threads.emplace_back(process_rows, row_per_thread_count * real_thread_count + i, 1, ref(lhs), ref(rhs_transposed), ref(result));
        }
    }

    for (auto& thread : row_threads)
    {
        thread.join();
    }

    return result;
}

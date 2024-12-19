#pragma once

#include "algebra/Matrix.hpp"

#ifdef AVX_ENABLED_ON_CPU
#include <immintrin.h>
#include <numeric>
#endif

#include <cstdlib>
#include <span>
#include <thread>
#include <vector>
#include <stdexcept>

namespace LCNS::Algebra
{
    namespace impl_details
    {
        template <Coordinate coordinate>
        float dot_product_concurrently(std::span<const coordinate, std::dynamic_extent> row, std::span<const coordinate, std::dynamic_extent> col)
        {
            float result = 0.0f;

            auto row_it = row.begin();
            auto col_it = col.begin();

            while (row_it != row.end())
            {
                result += (*row_it) * (*col_it);
                row_it++;
                col_it++;
            }

            return result;
        }

        template <Coordinate coordinate, unsigned int lhs_rows, unsigned int lhs_cols, unsigned int rhs_rows, unsigned int rhs_cols>
        void process_rows(size_t                                        thread_index,
                          int                                           count,
                          const Matrix<coordinate, lhs_rows, lhs_cols>& lhs,
                          const Matrix<coordinate, rhs_cols, rhs_rows>& rhs_transposed,
                          Matrix<coordinate, lhs_rows, rhs_cols>&       result)
        {
            const auto row_end = thread_index + count;
            for (size_t i = thread_index; i < row_end; ++i)
            {
                // Note, because rhs is transposed, rhs_cols is "rhs_transposed row count"
                // and rhs_rows is "rhs_transposed col count"
                for (size_t j = 0; j < rhs_cols; j++)
                {
                    result(i, j)
                    = dot_product_concurrently(std::span(lhs.data() + i * lhs_cols, lhs.data() + (i + 1) * lhs_cols),
                                               std::span(rhs_transposed.data() + j * rhs_rows, rhs_transposed.data() + (j + 1) * rhs_rows));
                }
            }
        }

#ifdef AVX_ENABLED_ON_CPU
        template <Coordinate coordinate>
        consteval int data_points_per_instruction()
        {
#if defined(AVX512_ENABLED)
            return 512 / (sizeof(coordinate) * 8);
#elif defined(AVX2_ENABLED)
            return 256 / (sizeof(coordinate) * 8);
#endif
        }

        template <Coordinate coordinate, unsigned int lhs_rows, unsigned int lhs_cols, unsigned int rhs_tr_rows, unsigned int rhs_tr_cols>
        coordinate dot_product_simd(const Matrix<coordinate, lhs_rows, lhs_cols>&       lhs,
                                    const Matrix<coordinate, rhs_tr_rows, rhs_tr_cols>& rhs_transposed,
                                    std::div_t                                          division,
                                    int                                                 dppi,
                                    unsigned int                                        i,
                                    unsigned int                                        j)
        {
            coordinate dot_product{};

            for (int k = 0; k < division.quot; ++k)
            {
                if constexpr (std::is_same_v<coordinate, double>)
                {
#if defined(AVX512_ENABLED)
                    __m512d lhs_chunk       = _mm512_loadu_pd(lhs.data() + i * lhs_cols + dppi * k);
                    __m512d rhs_chunk       = _mm512_loadu_pd(rhs_transposed.data() + j * rhs_tr_cols + dppi * k);
                    __m512d multiplications = _mm512_mul_pd(lhs_chunk, rhs_chunk);
#elif defined(AVX2_ENABLED)
                    __m256d lhs_chunk       = _mm256_loadu_pd(lhs.data() + i * lhs_cols + dppi * k);
                    __m256d rhs_chunk       = _mm256_loadu_pd(rhs_transposed.data() + j * rhs_tr_cols + dppi * k);
                    __m256d multiplications = _mm256_mul_pd(lhs_chunk, rhs_chunk);
#endif
                    auto* tmp = reinterpret_cast<double*>(&multiplications);
                    dot_product += std::accumulate(tmp, tmp + dppi, 0.0);
                }
                else if constexpr (std::is_same_v<coordinate, float>)
                {
#if defined(AVX512_ENABLED)
                    __m512 lhs_chunk       = _mm512_loadu_ps(lhs.data() + i * lhs_cols + dppi * k);
                    __m512 rhs_chunk       = _mm512_loadu_ps(rhs_transposed.data() + j * rhs_tr_cols + dppi * k);
                    __m512 multiplications = _mm512_mul_ps(lhs_chunk, rhs_chunk);
#elif defined(AVX2_ENABLED)
                    __m256 lhs_chunk       = _mm256_loadu_ps(lhs.data() + i * lhs_cols + dppi * k);
                    __m256 rhs_chunk       = _mm256_loadu_ps(rhs_transposed.data() + j * rhs_tr_cols + dppi * k);
                    __m256 multiplications = _mm256_mul_ps(lhs_chunk, rhs_chunk);
#endif
                    auto* tmp = reinterpret_cast<float*>(&multiplications);
                    dot_product += std::accumulate(tmp, tmp + dppi, 0.0f);
                }
                else
                {
                    static_assert(false && "unsupported type for simd operations");
                }
            }

            return dot_product;
        }


        template <Coordinate coordinate, unsigned int lhs_rows, unsigned int lhs_cols, unsigned int rhs_tr_rows, unsigned int rhs_tr_cols>
        coordinate dot_product_simd_last_chunk(const Matrix<coordinate, lhs_rows, lhs_cols>&       lhs,
                                               const Matrix<coordinate, rhs_tr_rows, rhs_tr_cols>& rhs_transposed,
                                               std::div_t                                          division,
                                               int                                                 dppi,
                                               unsigned int                                        i,
                                               unsigned int                                        j)
        {
            if constexpr (std::is_same_v<coordinate, double>)
            {
#if defined(AVX512_ENABLED)
                __m512d lhs_chunk       = _mm512_loadu_pd(lhs.data() + i * lhs_cols + dppi * division.quot);
                __m512d rhs_chunk       = _mm512_loadu_pd(rhs_transposed.data() + j * rhs_tr_cols + dppi * division.quot);
                __m512d multiplications = _mm512_mul_pd(lhs_chunk, rhs_chunk);
#elif defined(AVX2_ENABLED)
                __m256d lhs_chunk       = _mm256_loadu_pd(lhs.data() + i * lhs_cols + dppi * division.quot);
                __m256d rhs_chunk       = _mm256_loadu_pd(rhs_transposed.data() + j * rhs_tr_cols + dppi * division.quot);
                __m256d multiplications = _mm256_mul_pd(lhs_chunk, rhs_chunk);
#endif
                auto* tmp = reinterpret_cast<double*>(&multiplications);
                return std::accumulate(tmp, tmp + division.rem, 0.0);
            }
            else if constexpr (std::is_same_v<coordinate, float>)
            {
#if defined(AVX512_ENABLED)
                __m512 lhs_chunk       = _mm512_loadu_ps(lhs.data() + i * lhs_cols + dppi * division.quot);
                __m512 rhs_chunk       = _mm512_loadu_ps(rhs_transposed.data() + j * rhs_tr_cols + dppi * division.quot);
                __m512 multiplications = _mm512_mul_ps(lhs_chunk, rhs_chunk);
#elif defined(AVX2_ENABLED)
                __m256 lhs_chunk       = _mm256_loadu_ps(lhs.data() + i * lhs_cols + dppi * division.quot);
                __m256 rhs_chunk       = _mm256_loadu_ps(rhs_transposed.data() + j * rhs_tr_cols + dppi * division.quot);
                __m256 multiplications = _mm256_mul_ps(lhs_chunk, rhs_chunk);
#endif
                auto* tmp = reinterpret_cast<float*>(&multiplications);
                return std::accumulate(tmp, tmp + division.rem, 0.0f);
            }
            else
            {
                static_assert(false && "unsupported type for simd operations");
            }
        }
#endif
    }  // namespace impl_details

#ifdef AVX_ENABLED_ON_CPU
    template <Coordinate coordinate, unsigned int lhs_rows, unsigned int lhs_cols, unsigned int rhs_rows, unsigned int rhs_cols>
    Matrix<coordinate, lhs_rows, rhs_cols> multiply_simd(const Matrix<coordinate, lhs_rows, lhs_cols>& lhs,
                                                         const Matrix<coordinate, rhs_rows, rhs_cols>& rhs) requires std::is_floating_point_v<coordinate>
    {
        const auto rhs_transposed = rhs.transposed();

        const auto dppi     = impl_details::data_points_per_instruction<coordinate>();
        const auto division = std::div(lhs_cols, dppi);

        Matrix<coordinate, lhs_rows, rhs_cols> result;
        for (unsigned int i = 0; i < lhs_rows; ++i)
        {
            for (unsigned int j = 0; j < rhs_cols; ++j)
            {
                coordinate dot_product = impl_details::dot_product_simd(lhs, rhs_transposed, division, dppi, i, j);

                if (division.rem != 0)
                {
                    dot_product += impl_details::dot_product_simd_last_chunk(lhs, rhs_transposed, division, dppi, i, j);
                }

                result(i, j) = dot_product;
            }
        }

        return result;
    }
#endif

    template <Coordinate coordinate, unsigned int lhs_rows, unsigned int lhs_cols, unsigned int rhs_rows, unsigned int rhs_cols>
    Matrix<coordinate, lhs_rows, rhs_cols> multiply_concurrently(const Matrix<coordinate, lhs_rows, lhs_cols>& lhs,
                                                                 const Matrix<coordinate, rhs_rows, rhs_cols>& rhs)
    {
        const auto rhs_transposed = rhs.transposed();
        const auto thread_count   = std::thread::hardware_concurrency();
        const auto repartition    = std::div(static_cast<int>(lhs_rows), static_cast<int>(thread_count));

        const size_t real_thread_count    = lhs_rows < thread_count ? lhs_rows : thread_count;
        const auto   row_per_thread_count = repartition.quot == 0 ? 1u : static_cast<size_t>(repartition.quot);

        std::vector<std::thread> row_threads;
        row_threads.reserve(real_thread_count);
        Matrix<coordinate, lhs_rows, rhs_cols> result;

        for (size_t i = 0; i < real_thread_count; ++i)
        {
            row_threads.emplace_back(impl_details::process_rows<coordinate, lhs_rows, lhs_cols, rhs_rows, rhs_cols>,
                                     i * row_per_thread_count,
                                     row_per_thread_count,
                                     std::ref(lhs),
                                     std::ref(rhs_transposed),
                                     std::ref(result));
        }

        if (real_thread_count == thread_count && repartition.quot != 0)
        {
            for (size_t i = 0; i < static_cast<size_t>(repartition.rem); ++i)
            {
                row_threads.emplace_back(impl_details::process_rows<coordinate, lhs_rows, lhs_cols, rhs_rows, rhs_cols>,
                                         row_per_thread_count * real_thread_count + i,
                                         1,
                                         std::ref(lhs),
                                         std::ref(rhs_transposed),
                                         std::ref(result));
            }
        }

        for (auto& thread : row_threads)
        {
            thread.join();
        }

        return result;
    }
}  // namespace LCNS::Large

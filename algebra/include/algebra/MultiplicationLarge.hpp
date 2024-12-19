#pragma once

#include "algebra/Matrix.hpp"

#include <cstdlib>
#include <span>
#include <thread>
#include <vector>

namespace LCNS::Algebra
{
    // template <Coordinate coordinate, unsigned int rows_lhs, unsigned int cols_lhs, unsigned int rows_rhs, unsigned int cols_rhs>
    // Matrix multiply_simd(const Matrix& lhs, const Matrix& rhs)
    // {
    //     return {};
    // }

    namespace impl_details
    {
        template <Coordinate coordinate>
        float dot_product(std::span<const coordinate, std::dynamic_extent> row, std::span<const coordinate, std::dynamic_extent> col)
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
                    result(i, j) = dot_product(std::span(lhs.data() + i * lhs_cols, lhs.data() + (i + 1) * lhs_cols),
                                               std::span(rhs_transposed.data() + j * rhs_rows, rhs_transposed.data() + (j + 1) * rhs_rows));
                }
            }
        }
    }  // namespace impl_details


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

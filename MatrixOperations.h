/**
* GLSL++
*
* Dan Israel Malta
**/
#pragma once
#include "common.h"
#include "VectorBase.h"
#include "MatrixBase.h"
#include <algorithm>
#include <functional>
#include <bitset>

namespace GLSLCPP {

    // ----------------------
    // --- "constructors" ---
    // ----------------------

    /**
    * \brief given a cubicmatrix - convert it to I.
    *
    * @param {MatrixBase, in|out} cubic matrix to be transformed to an 'I'
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr void MakeIdentity(T& xio_mat) noexcept {
        using _T = underlying_type_t<T>;
        
        xio_mat = _T{};
        for (std::size_t i{}; i < Rows_v<T>; ++i) {
            xio_mat(i, i) = static_cast<_T>(1);
        }
    }

    /**
    * \brief given two equally sized vectors, create a matrix from their outer product
    *
    * @param {VectorBase, in}  vector #1
    * @param {VectorBase, in}  vector #2
    * @param {MatrixBase, out} outer product of input vectors
    **/
    template<typename T, typename U, REQUIRE(Are_TwoVectorsSimilar_v<T, U> && (Length_v<T> == 2))>
    constexpr MatrixBase<typename std::common_type<underlying_type_t<T>, underlying_type_t<U>>::type, Length_v<T>, Length_v<T>> OuterProduct(const T& xi_x, const U& xi_y) noexcept {
        using _T = underlying_type_t<T>;
        using _U = underlying_type_t<U>;
        using TYPE = typename std::common_type<_T, _U>::type;
        constexpr std::size_t N{ Length_v<T> };

        return MatrixBase<TYPE, N, N>(xi_x[0] * xi_y[0], xi_x[0] * xi_y[1],
                                      xi_x[1] * xi_y[0], xi_x[1] * xi_y[1]);
    }
    
    template<typename T, typename U, REQUIRE(Are_TwoVectorsSimilar_v<T, U> && (Length_v<T> == 3))>
    constexpr MatrixBase<typename std::common_type<underlying_type_t<T>, underlying_type_t<U>>::type, Length_v<T>, Length_v<T>> OuterProduct(const T& xi_x, const U& xi_y) noexcept {
        using _T = underlying_type_t<T>;
        using _U = underlying_type_t<U>;
        using TYPE = typename std::common_type<_T, _U>::type;
        constexpr std::size_t N{ Length_v<T> };

        return MatrixBase<TYPE, N, N>(xi_x[0] * xi_y[0], xi_x[0] * xi_y[1], xi_x[0] * xi_y[2],
                                      xi_x[1] * xi_y[0], xi_x[1] * xi_y[1], xi_x[1] * xi_y[2],
                                      xi_x[2] * xi_y[0], xi_x[2] * xi_y[1], xi_x[2] * xi_y[2]);
    }

    template<typename T, typename U, REQUIRE(Are_TwoVectorsSimilar_v<T, U> && (Length_v<T> == 4))>
    constexpr MatrixBase<typename std::common_type<underlying_type_t<T>, underlying_type_t<U>>::type, Length_v<T>, Length_v<T>> OuterProduct(const T& xi_x, const U& xi_y) noexcept {
        using _T = underlying_type_t<T>;
        using _U = underlying_type_t<U>;
        using TYPE = typename std::common_type<_T, _U>::type;
        constexpr std::size_t N{ Length_v<T> };

        return MatrixBase<TYPE, N, N>(xi_x[0] * xi_y[0], xi_x[0] * xi_y[1], xi_x[0] * xi_y[2], xi_x[0] * xi_y[3],
                                      xi_x[1] * xi_y[0], xi_x[1] * xi_y[1], xi_x[1] * xi_y[2], xi_x[1] * xi_y[3],
                                      xi_x[2] * xi_y[0], xi_x[2] * xi_y[1], xi_x[2] * xi_y[2], xi_x[2] * xi_y[3],
                                      xi_x[3] * xi_y[0], xi_x[3] * xi_y[1], xi_x[3] * xi_y[2], xi_x[3] * xi_y[3]);
    }

    template<typename T, typename U, REQUIRE(Are_TwoVectorsSimilar_v<T, U> && (Length_v<T> > 4))>
    constexpr MatrixBase<typename std::common_type<underlying_type_t<T>, underlying_type_t<U>>::type, Length_v<T>, Length_v<T>> OuterProduct(const T& xi_x, const U& xi_y) noexcept {
        using _T = underlying_type_t<T>;
        using _U = underlying_type_t<U>;
        using TYPE = typename std::common_type<_T, _U>::type;
        constexpr std::size_t N{ Length_v<T> };

        MatrixBase<TYPE, N, N> xo_mat;

        for (std::size_t i{}; i < N; ++i) {
            for (std::size_t j{}; j < N; ++j) {
                xo_mat(i, j) = xi_x[i] * xi_y[j];
            }
        }

        return xo_mat;
    }

    /**
    * \brief construct a givens rotation matrix (rotation in the plane spanned by two coordinates axes)
    *
    * @param {T,          in}  cosine of rotation angle
    * @param {T,          in}  sine of rotation angle
    * @param {T,          in}  column to start rotation
    * @param {MatrixBase, out} givens rotation matrix
    **/
    template<typename T, std::size_t N, REQUIRE(std::is_arithmetic_v<T> && (N > 1))>
    constexpr inline MatrixBase<T, N, N> GivensRotation(const T xi_cosine, const T xi_sine, const std::size_t xi_col) noexcept {
        assert(xi_col + 1 < N && " GivensRotation(..., column) - 'column' argument is out of bound.");
        MatrixBase<T, N, N> xo_givens;

        xo_givens(xi_col,     xi_col    ) =  xi_cosine;
        xo_givens(xi_col,     xi_col + 1) = -xi_sine;
        xo_givens(xi_col + 1, xi_col + 1) =  xi_cosine;
        xo_givens(xi_col + 1, xi_col    ) =  xi_sine;

        return xo_givens;
    }

    /**
    * \brief construct a householder matrix from vector 'xi_vec'
    *
    * @param {VectorBase, in}  vector
    * @param {MatrixBase, out} householder ,atrix
    **/
    template<typename T, REQUIRE(is_Vector_v<T> && (Length_v<T> == 2))>
    constexpr inline MatrixBase<underlying_type_t<T>, 2, 2> Householder(const T& xi_vec) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T one{ static_cast<_T>(1) },
                     two{ static_cast<_T>(-2) };
        return MatrixBase<_T, 2, 2>(one + two * xi_vec[0] * xi_vec[0],       two * xi_vec[0] * xi_vec[1],
                                          two * xi_vec[1] * xi_vec[0], one + two * xi_vec[1] * xi_vec[1]);
    }

    template<typename T, REQUIRE(is_Vector_v<T> && (Length_v<T> == 3))>
    constexpr inline MatrixBase<underlying_type_t<T>, 3, 3> Householder(const T & xi_vec) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T one{ static_cast<_T>(1) },
                     two{ static_cast<_T>(-2) };
        return MatrixBase<_T, 3, 3>(one + two * xi_vec[0] * xi_vec[0],       two * xi_vec[0] * xi_vec[1],       two * xi_vec[0] * xi_vec[2],
                                          two * xi_vec[1] * xi_vec[0], one + two * xi_vec[1] * xi_vec[1],       two * xi_vec[1] * xi_vec[2],
                                          two * xi_vec[2] * xi_vec[0],       two * xi_vec[2] * xi_vec[1], one + two * xi_vec[2] * xi_vec[2]);
    }

    template<typename T, REQUIRE(is_Vector_v<T> && (Length_v<T> == 4))>
    constexpr inline MatrixBase<underlying_type_t<T>, 3, 3> Householder(const T & xi_vec) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T one{ static_cast<_T>(1) },
                     two{ static_cast<_T>(-2) };
        return MatrixBase<_T, 3, 3>(one + two * xi_vec[0] * xi_vec[0],       two * xi_vec[0] * xi_vec[1],       two * xi_vec[0] * xi_vec[2],       two * xi_vec[0] * xi_vec[3],
                                          two * xi_vec[1] * xi_vec[0], one + two * xi_vec[1] * xi_vec[1],       two * xi_vec[1] * xi_vec[2],       two * xi_vec[1] * xi_vec[3],
                                          two * xi_vec[2] * xi_vec[0],       two * xi_vec[2] * xi_vec[1], one + two * xi_vec[2] * xi_vec[2],       two * xi_vec[2] * xi_vec[3],
                                          two * xi_vec[3] * xi_vec[0],       two * xi_vec[3] * xi_vec[1],       two * xi_vec[3] * xi_vec[2], one + two * xi_vec[3] * xi_vec[3]);
    }

    template<typename T, REQUIRE(is_Vector_v<T> && (Length_v<T> > 4))>
    constexpr inline MatrixBase<underlying_type_t<T>, Length_v<T>, Length_v<T>> Householder(const T& xi_vec) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ Length_v<T> };

        MatrixBase<_T, N, N> reflect(OuterProduct(xi_vec, xi_vec)),
                             xo_mat;
        reflect *= static_cast<_T>(2);
        xo_mat  -= reflect;

        return xo_mat;
    }

    /**
    * \brief construct a van-der-monde matrix
    *
    * @param {VectorBase, in}  vector
    * @param {MatrixBase, out} van-der-monde matrix
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr MatrixBase<underlying_type_t<T>, Length_v<T>, Length_v<T>> VanDerMonde(const T& xi_vec) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ Length_v<T> };

        MatrixBase<_T, N, N> xo_mat; 

        for (std::size_t i{}; i < N; ++i) {
            for (std::size_t j{}; j < N; ++j) {
                const _T power{ static_cast<_T>(N - j - 1) };
                xo_mat(i, j) = static_cast<_T>(std::pow(xi_vec[i], power));
            }
        }

        return xo_mat;
    }

    /**
    * \brief construct a Toeplitz matrix
    *
    * @param {VectorBase, in}  vector
    * @param {MatrixBase, out} Toeplitz matrix
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr MatrixBase<underlying_type_t<T>, Length_v<T>, Length_v<T>> Toeplitz(const T& xi_vec) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ Length_v<T> };

        MatrixBase<_T, N, N> xo_mat;

        for (std::size_t i{}; i < N; ++i) {
            for (std::size_t j{}; j < N; ++j) {
                xo_mat(j, i) = (j >= i) ? xi_vec[j - i] : xi_vec[i - j];
            }
        }

        return xo_mat;
    }

    /**
    * \brief construct a rotation matrix (3x3) from a normalized axis and an angle (given by its trigonometric components
    *
    * @param {VectorBase, in}  normalized axis
    * @param {T,          in}  rotation angle sine
    * @param {T,          in}  rotation angle cosine
    * @param {MatrixBase, out} rotation matrix matrix (3x3)
    **/
    template<typename T, REQUIRE(Is_VectorOfLength_v<T, 3>)>
    constexpr MatrixBase<underlying_type_t<T>, 3, 3> FromAxisAngle(const T& xi_axis, const underlying_type_t<T> xi_sine, const underlying_type_t<T> xi_cosine) noexcept {
        using _T = underlying_type_t<T>;
        assert(IsNormalized(xi_axis) && " FromAxisAngle(axis, ...) - axis is not normalized.");
        assert(std::abs(xi_sine)   <= static_cast<_T>(1) && " FromAxisAngle(..., sine, ...) - rotation angle sine must be in the region [-1, 1].");
        assert(std::abs(xi_cosine) <= static_cast<_T>(1) && " FromAxisAngle(..., ..., cosine) - rotation angle cosine must be in the region [-1, 1].");

        // locals
        const _T oneMinusCosine{ static_cast<_T>(1) - xi_cosine },
                 xx{ xi_axis[0] * xi_axis[0] },
                 xy{ xi_axis[0] * xi_axis[1] },
                 xz{ xi_axis[0] * xi_axis[2] },
                 yy{ xi_axis[1] * xi_axis[1] },
                 yz{ xi_axis[1] * xi_axis[2] },
                 zz{ xi_axis[2] * xi_axis[2] },
                 xyOne{ xy * oneMinusCosine },
                 xzOne{ xz * oneMinusCosine },
                 yzOne{ yz * oneMinusCosine },
                 axisSine0{ xi_axis[0] * xi_sine },
                 axisSine1{ xi_axis[1] * xi_sine },
                 axisSine2{ xi_axis[2] * xi_sine };

        // output
        return MatrixBase<_T, 3, 3>(xi_cosine + xx * oneMinusCosine, xyOne - axisSine2,               xzOne + axisSine1,
                                    xyOne + axisSine2,               xi_cosine + yy * oneMinusCosine, yzOne - axisSine0,
                                    xzOne - axisSine1,               yzOne + axisSine0,               xi_cosine + zz * oneMinusCosine );
    }

    // -----------------
    // --- modifiers ---
    // -----------------

    /**
    * \brief swap two rows of a given matrix
    *
    * @param {MatrixBase, in}  matrix whose rows shall be swapped
    * @param {size_t,     in}  row #1
    * @param {size_t,     in}  row #2
    * @param {MatrixBase, out} input matrix with swapped rows
    **/
    template<typename T, std::size_t COL, std::size_t ROW>
    constexpr inline MatrixBase<T, COL, ROW> SwapRows(MatrixBase<T, COL, ROW>&& xi_matrix, const std::size_t a, const std::size_t b) {
        assert((a < ROW) && (b < ROW) && "MatrixBase::SwapRows - attempting to swap rows which are outside of matrix boundaries.");

        for (std::size_t i{}; i < COL; ++i) {
            std::swap(xi_matrix(i, a), xi_matrix(i, b));
        }

        return xi_matrix;
    }

    template<typename T, std::size_t COL, std::size_t ROW>
    constexpr inline MatrixBase<T, COL, ROW> SwapRows(const MatrixBase<T, COL, ROW>& xi_matrix, const std::size_t a, const std::size_t b) {
        assert((a < ROW) && (b < ROW) && "MatrixBase::SwapRows - attempting to swap rows which are outside of matrix boundaries.");
        auto mat = FWD(xi_matrix);

        for (std::size_t i{}; i < COL; ++i) {
            std::swap(mat(i, a), mat(i, b));
        }

        return FWD(mat);
    }

    /**
    * \brief swap two columns of a given matrix
    *
    * @param {MatrixBase, in}  matrix whose columns shall be swapped
    * @param {size_t,     in}  row #1
    * @param {size_t,     in}  row #2
    * @param {MatrixBase, out} input matrix with swapped columns
    **/
    template<typename T, std::size_t COL, std::size_t ROW>
    constexpr inline MatrixBase<T, COL, ROW> SwapColumns(MatrixBase<T, COL, ROW>&& xi_matrix, const std::size_t a, const std::size_t b) {
        assert((a < ROW) && (b < ROW) && "MatrixBase::SwapColumns - attempting to swap columns which are outside of matrix boundaries.");

        for (std::size_t i{}; i < ROW; ++i) {
            std::swap(xi_matrix(a, i), xi_matrix(b, i));
        }

        return xi_matrix;
    }

    template<typename T, std::size_t COL, std::size_t ROW>
    constexpr inline MatrixBase<T, COL, ROW> SwapColumns(const MatrixBase<T, COL, ROW>& xi_matrix, const std::size_t a, const std::size_t b) {
        assert((a < ROW) && (b < ROW) && "MatrixBase::SwapColumns - attempting to swap columns which are outside of matrix boundaries.");
        auto mat = FWD(xi_matrix);

        for (std::size_t i{}; i < ROW; ++i) {
            std::swap(mat(a, i), mat(b, i));
        }

        return FWD(mat);
    }

    /**
    * \brief set the row of a given matrix
    *
    * @param {MatrixBase, in|out} matrix whose row shall be set
    * @param {size_t,     in}     row index
    * @param {VectorBase, in}     new row
    **/
    template<typename T, typename U, std::size_t COL, std::size_t ROW>
    constexpr inline void SetRow(MatrixBase<T, COL, ROW>& xio_matrix, const std::size_t xi_index, VectorBase<U, COL>&& xi_row) {
        assert(xi_index < ROW && "MatrixBase::SetRow - attempting to set a row which doesn't exist.");

        for_each(xi_row, [&, i = 0](const auto & elm) mutable {
            xio_matrix(i, xi_index) = static_cast<T>(elm);
            ++i;
        });
    }

    template<typename T, typename U, std::size_t COL, std::size_t ROW>
    constexpr inline void SetRow(MatrixBase<T, COL, ROW>& xio_matrix, const std::size_t xi_index, const VectorBase<U, COL>& xi_row) {
        assert(xi_index < ROW && "MatrixBase::SetRow - attempting to set a row which doesn't exist.");
        auto row = FWD(xi_row);

        for_each(row, [&, i = 0](const auto & elm) mutable {
            xio_matrix(i, xi_index) = static_cast<T>(elm);
            ++i;
        });
    }

    /**
    * \brief set the diagonal of a cubic matrix
    *
    * @param {MatrixBase, in|out} matrix whose diagonal shall be set
    * @param {VectorBase/T, in}   new diagonal
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr inline void SetDiagonal(T& xio_matrix, const VectorBase<underlying_type_t<T>, Columns_v<T>>& xi_diagonal) {
        for (std::size_t i{}; i < Columns_v<T>; ++i) {
            xio_matrix(i, i) = xi_diagonal[i];
        }
    }

    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr inline void SetDiagonal(T& xio_matrix, VectorBase<underlying_type_t<T>, Columns_v<T>>&& xi_diagonal) {
        for (std::size_t i{}; i < Columns_v<T>; ++i) {
            xio_matrix(i, i) = std::move(xi_diagonal[i]);
        }
    }

    /**
    * \brief return the transpose of a given matrix
    *
    * @param {MatrixBase, in}  matrix whose row shall be to be transposed
    * @param {MatrixBase, out} transposed matrix
    **/
    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW == 2))>
    constexpr inline MatrixBase<T, COL, ROW> Transpose(MatrixBase<T, COL, ROW>&& xi_mat) noexcept {
        return MatrixBase<T, 2, 2>(xi_mat(0, 0), xi_mat(1, 0),
                                   xi_mat(0, 1), xi_mat(1, 1));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW == 3))>
    constexpr inline MatrixBase<T, COL, ROW> Transpose(MatrixBase<T, COL, ROW>&& xi_mat) noexcept {
        return MatrixBase<T, 3, 3>(xi_mat(0, 0), xi_mat(1, 0), xi_mat(2, 0),
                                   xi_mat(0, 1), xi_mat(1, 1), xi_mat(2, 1),
                                   xi_mat(0, 2), xi_mat(1, 2), xi_mat(2, 2));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW == 4))>
    constexpr inline MatrixBase<T, COL, ROW> Transpose(MatrixBase<T, COL, ROW>&& xi_mat) noexcept {
        return MatrixBase<T, 4, 4>(xi_mat(0, 0), xi_mat(1, 0), xi_mat(2, 0), xi_mat(3, 0),
                                   xi_mat(0, 1), xi_mat(1, 1), xi_mat(2, 1), xi_mat(3, 1),
                                   xi_mat(0, 2), xi_mat(1, 2), xi_mat(2, 2), xi_mat(3, 2),
                                   xi_mat(0, 3), xi_mat(1, 3), xi_mat(2, 3), xi_mat(3, 3));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW > 4))>
    constexpr inline MatrixBase<T, COL, ROW> Transpose(MatrixBase<T, COL, ROW>&& xi_mat) noexcept {
        constexpr std::size_t last{ ROW * COL },
                              size{ last - 1 },
                              n{ last / COL };

        // housekeeping
        std::bitset<last> visited;

        // transposing
        std::size_t cycle{};
        while (++cycle != last) {
            // visited this element?
            if (visited[cycle]) continue;

            // cycle along elements
            std::size_t a{ cycle };
            do {
                a = (a == size) ? (size) : ((n * a) % size);
                std::swap(xi_mat.m_data[a], xi_mat.m_data[cycle]);
                visited[a] = true;
            } while (a != cycle);
        }

        return xi_mat;
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW == 2))>
    constexpr inline MatrixBase<T, COL, ROW> Transpose(const MatrixBase<T, COL, ROW>& xi_mat) noexcept {
        return MatrixBase<T, 2, 2>(xi_mat(0, 0), xi_mat(0, 1),
                                   xi_mat(1, 0), xi_mat(1, 1));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW == 3))>
    constexpr inline MatrixBase<T, COL, ROW> Transpose(const MatrixBase<T, COL, ROW>& xi_mat) noexcept {
        return MatrixBase<T, 3, 3>(xi_mat(0, 0), xi_mat(1, 0), xi_mat(2, 0),
                                   xi_mat(0, 1), xi_mat(1, 1), xi_mat(2, 1),
                                   xi_mat(0, 2), xi_mat(1, 2), xi_mat(2, 2));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW == 4))>
    constexpr inline MatrixBase<T, COL, ROW> Transpose(const MatrixBase<T, COL, ROW>& xi_mat) noexcept {
        return MatrixBase<T, 4, 4>(xi_mat(0, 0), xi_mat(1, 0), xi_mat(2, 0), xi_mat(3, 0),
                                   xi_mat(0, 1), xi_mat(1, 1), xi_mat(2, 1), xi_mat(3, 1),
                                   xi_mat(0, 2), xi_mat(1, 2), xi_mat(2, 2), xi_mat(3, 2),
                                   xi_mat(0, 3), xi_mat(1, 3), xi_mat(2, 3), xi_mat(3, 3));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (ROW > 4))>
    constexpr inline MatrixBase<T, ROW, COL> Transpose(const MatrixBase<T, COL, ROW>& xi_mat) noexcept {
        constexpr std::size_t last{ ROW * COL },
                              size{ last - 1 },
                              n{ last / COL };

        // housekeeping
        auto mat = FWD(xi_mat);
        std::bitset<last> visited;

        // transposing
        std::size_t cycle{};
        while (++cycle != last) {
            // visited this element?
            if (visited[cycle]) continue;

            // cycle along elements
            std::size_t a{ cycle };
            do {
                a = (a == size) ? (size) : ((n * a) % size);
                std::swap(mat.m_data[a], mat.m_data[cycle]);
                visited[a] = true;
            } while (a != cycle);
        }

        return FWD(mat);
    }

    /**
    * \brief perform element-wise multiplication between two matrix
    *
    * @param {MatrixBase, in}  matrix #1
    * @param {MatrixBase, in}  matrix #2
    * @param {MatrixBase, out} element wise multiplication of input matrix
    **/
    template<typename T, typename U, REQUIRE(is_MatrixBase_v<T> && is_MatrixBase_v<U> && 
                                             (Columns_v<T> == Columns_v<U>) && (Rows_v<T> == Rows_v<U>))>
    constexpr inline MatrixBase<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>, Columns_v<T>, Rows_v<T>>
    matrixMatrixMul(const T& xi_a, const U& xi_b) noexcept {
        MatrixBase<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>, Columns_v<T>, Rows_v<T>> xo_mat(xi_a);
        xo_mat.m_data *= xi_b.m_data;
        return xo_mat;
    }

    // ---------------
    // --- getters ---
    // ---------------

    /**
    * \brief return a given row of a given matrix
    *
    * @param {MatrixBase, in}  matrix
    * @param {size_t,     in}  row index
    * @param {VectorBase, out} row
    **/
    template<typename T, REQUIRE(is_MatrixBase_v<T>)>
    constexpr inline VectorBase<underlying_type_t<T>, Columns_v<T>> GetRow(const T& xi_matrix, const std::size_t xi_index) {
        assert(xi_index < Rows_v<T> && "MatrixBase::GetRow - attempting to get a row which doesn't exist.");
        constexpr std::size_t COL{ Columns_v<T> };
        VectorBase<underlying_type_t<T>, COL> xo_row;

        for (std::size_t i{}; i < COL; ++i) {
            xo_row[i] = xi_matrix(i, xi_index);
        }

        return xo_row;
    }

    /**
    * \brief return the diagonal of a cubic matrix
    *
    * @param {MatrixBase, in}  cubic matrix
    * @param {VectorBase, out} diagonal
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 2))>
    constexpr inline VectorBase<underlying_type_t<T>, Rows_v<T>> GetDiagonal(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ Rows_v<T> };
        return VectorBase<_T, N>(xi_matrix(0,0), xi_matrix(1,1));
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 3))>
    constexpr inline VectorBase<underlying_type_t<T>, Rows_v<T>> GetDiagonal(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ Rows_v<T> };
        return VectorBase<_T, N>(xi_matrix(0, 0), xi_matrix(1, 1), xi_matrix(2, 2));
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 4))>
    constexpr inline VectorBase<underlying_type_t<T>, Rows_v<T>> GetDiagonal(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ Rows_v<T> };
        return VectorBase<_T, N>(xi_matrix(0, 0), xi_matrix(1, 1), xi_matrix(2, 2), xi_matrix(3, 3));
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> > 4))>
    constexpr inline VectorBase<underlying_type_t<T>, Rows_v<T>> GetDiagonal(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ Rows_v<T> };

        VectorBase<_T, N> xo_diag;
        for (std::size_t i{}; i < N; ++i) {
            xo_diag[i] = xi_matrix(i, i);
        }
        return xo_diag;
    }
    /**
    * \brief return the lower triangular part of a cubic matrix
    *
    * @param {MatrixBase, in}  cubic matrix
    * @param {MatrixBase, out} lower triangular part
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr inline T GetLowerTriangular(const T& xi_matrix) noexcept {
        constexpr std::size_t N{ Rows_v<T> };
        T xo_mat(0);
        for (std::size_t i{}; i < N; ++i) {
            for (std::size_t j{ i }; j < N; ++j) {
                xo_mat(i, j) = xi_matrix(i, j);
            }
        }
        return xo_mat;
    }

    /**
    * \brief return the upper triangular part of a cubic matrix
    *
    * @param {MatrixBase, in}  cubic matrix
    * @param {MatrixBase, out} upper triangular part
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr inline T GetUpperTriangular(const T& xi_matrix) noexcept {
        T xo_mat(0);
        for (std::size_t i{}; i < Rows_v<T>; ++i) {
            for (std::size_t j{}; j <= i; ++j) {
                xo_mat(i, j) = xi_matrix(i, j);
            }
        }
        return xo_mat;
    }

    /**
    * \brief return a block of a given matrix, where the bloc size is known at compile time
    *
    * @param {MatrixBase,  in}  matrix whos block will be extracted
    * @param {std::size_t, in}  column start
    * @param {std::size_t, in}  column end
    * @param {std::size_t, in}  row start
    * @param {std::size_t, in}  row end
    * @param {MatrixBase,  out} block
    **/
    template<std::size_t COL_MIN, std::size_t COL_MAX, 
             std::size_t ROW_MIN, std::size_t ROW_MAX,
             typename T, std::size_t COL, std::size_t ROW,
             REQUIRE((ROW_MIN < ROW_MAX) && (COL_MIN < COL_MAX) && (ROW_MAX <= ROW) && (COL_MAX <= COL))>
    constexpr inline MatrixBase<T, COL_MAX - COL_MIN + 1, ROW_MAX - ROW_MIN + 1> GetBlock(const MatrixBase<T, COL, ROW>& xi_matrix) noexcept {
        MatrixBase<T, COL_MAX - COL_MIN + 1, ROW_MAX - ROW_MIN + 1> xo_block(T{});

        for (std::size_t j{ COL_MIN }; j <= COL_MAX; ++j) {
            for (std::size_t i{ ROW_MIN }; i <= ROW_MAX; ++i) {
                 xo_block(j - COL_MIN, i - ROW_MIN) = xi_matrix(j, i);
            }
        }

        return xo_block;
    }

    // ---------------------------------
    // --- general matrix operations ---
    // ---------------------------------

    /** \brief return the trace (sum of diagonal elements) of a matrix (cubic)
    *
    * @param {matrix,  in} matrix
    * @param {T,      out} matrix trace
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 2))>
    constexpr inline underlying_type_t<T> Trace(const T& xi_matrix) noexcept {
        return (xi_matrix(0, 0) + xi_matrix(1, 1));
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 3))>
    constexpr inline underlying_type_t<T> Trace(const T& xi_matrix) noexcept {
        return (xi_matrix(0, 0) + xi_matrix(1, 1) + xi_matrix(2, 2));
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 4))>
    constexpr inline underlying_type_t<T> Trace(const T& xi_matrix) noexcept {
        return (xi_matrix(0, 0) + xi_matrix(1, 1) + xi_matrix(2, 2) + xi_matrix(3, 3) );
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> > 4))>
    constexpr inline underlying_type_t<T> Trace(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        _T xo_trace{};
        for (std::size_t i{}; i < COL; ++i) {
            xo_trace += xi_matrix(i, i);
        }

        return xo_trace;
    }

    /** \brief return the determinant of a given matrix (cubic)
    *
    * @param {matrix,  in} matrix
    * @param {T,      out} matrix determinant
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 2))>
    constexpr inline underlying_type_t<T> Determinant(const T& xi_matrix) noexcept {
        return (xi_matrix(0, 0) * xi_matrix(1, 1) - xi_matrix(0, 1) * xi_matrix(1, 0));
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 3))>
    constexpr inline underlying_type_t<T> Determinant(const T& xi_matrix) noexcept {
        return (xi_matrix(0, 0) * (xi_matrix(1, 1) * xi_matrix(2, 2) - xi_matrix(2, 1) * xi_matrix(1, 2)) -
                xi_matrix(0, 1) * (xi_matrix(1, 0) * xi_matrix(2, 2) - xi_matrix(2, 0) * xi_matrix(1, 2)) +
                xi_matrix(0, 2) * (xi_matrix(1, 0) * xi_matrix(2, 1) - xi_matrix(2, 0) * xi_matrix(1, 1)));
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 4))>
    constexpr inline underlying_type_t<T> Determinant(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;

        // minor 0
        MatrixBase<_T, 3, 3> minor( xi_matrix(1, 1), xi_matrix(1, 2), xi_matrix(1, 3),
                                    xi_matrix(2, 1), xi_matrix(2, 2), xi_matrix(2, 3), 
                                    xi_matrix(3, 1), xi_matrix(3, 2), xi_matrix(3, 3) );
        const _T det0{ Determinant(minor) };

        // minor 1
        minor = MatrixBase<_T, 3, 3>( xi_matrix(1, 0), xi_matrix(1, 2), xi_matrix(1, 3),
                                      xi_matrix(2, 0), xi_matrix(2, 2), xi_matrix(2, 3), 
                                      xi_matrix(3, 0), xi_matrix(3, 2), xi_matrix(3, 3) );
        const _T det1{ Determinant(minor) };

        // minor 2
        minor = MatrixBase<_T, 3, 3>( xi_matrix(1, 0), xi_matrix(1, 1), xi_matrix(1, 3),
                                      xi_matrix(2, 0), xi_matrix(2, 1), xi_matrix(2, 3), 
                                      xi_matrix(3, 0), xi_matrix(3, 1), xi_matrix(3, 3) );
        const _T det2{ Determinant(minor) };

        // minor 3
        minor = MatrixBase<_T, 3, 3>( xi_matrix(1, 0), xi_matrix(1, 1), xi_matrix(1, 2),
                                      xi_matrix(2, 0), xi_matrix(2, 1), xi_matrix(2, 2), 
                                      xi_matrix(3, 0), xi_matrix(3, 1), xi_matrix(3, 2) );
        const _T det3{ Determinant(minor) };

        // output
        return (xi_matrix(0, 0) * det0 - xi_matrix(0, 1) * det1 + 
                xi_matrix(0, 2) * det2 - xi_matrix(0, 3) * det3);
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> > 4))>
    constexpr inline underlying_type_t<T> Determinant(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        // get matrix upper triangular decomposition (dolittle style)
        T lu;
        std::int32_t sign{};
        VectorBase<std::size_t, COL> pivot;
        LU(xi_matrix, lu, pivot, sign);

        // determinant calculation
        _T xo_det{ static_cast<_T>(sign) };
        for (std::size_t i{}; i < COL; ++i) {
            xo_det *= lu(i, i);
        }

        return xo_det;
    }

    /** \brief return the inverse of a given matrix (cubic).
    *          notice that assertion is the only way to test if matrix is singular (invertible).
    *
    * @param {matrix,  in}  matrix
    * @param {matrix,  out} matrix inverse
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 2))>
    constexpr inline T Inv(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;

        const _T det{ Determinant(xi_matrix) };
        assert(std::abs(det) > std::numeric_limits<_T>::epsilon() && " attempting to inverse a not invertiable matrix.");

        const _T detInv{ _T{ 1 } / det };
        return MatrixBase<_T, 2, 2>( xi_matrix(1, 1) * detInv, -xi_matrix(0, 1) * detInv,
                                    -xi_matrix(1, 0) * detInv,  xi_matrix(0, 0) * detInv );
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 3))>
    constexpr inline T Inv(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;

        const _T det{ Determinant(xi_matrix) };
        assert(std::abs(det) > std::numeric_limits<_T>::epsilon() && " attempting to inverse a not invertiable matrix.");

        const _T detInv{ _T{ 1 } / det };
        return MatrixBase<_T, 3, 3>( (xi_matrix(1, 1) * xi_matrix(2, 2) - xi_matrix(2, 1) * xi_matrix(1, 2)) * detInv,
                                     (xi_matrix(0, 2) * xi_matrix(2, 1) - xi_matrix(2, 2) * xi_matrix(0, 1)) * detInv,
                                     (xi_matrix(0, 1) * xi_matrix(1, 2) - xi_matrix(1, 1) * xi_matrix(0, 2)) * detInv,
                                     (xi_matrix(1, 2) * xi_matrix(2, 0) - xi_matrix(2, 2) * xi_matrix(1, 0)) * detInv,
                                     (xi_matrix(0, 0) * xi_matrix(2, 2) - xi_matrix(2, 0) * xi_matrix(0, 2)) * detInv,
                                     (xi_matrix(0, 2) * xi_matrix(1, 0) - xi_matrix(1, 2) * xi_matrix(0, 0)) * detInv,
                                     (xi_matrix(1, 0) * xi_matrix(2, 1) - xi_matrix(2, 0) * xi_matrix(1, 1)) * detInv,
                                     (xi_matrix(0, 1) * xi_matrix(2, 0) - xi_matrix(2, 1) * xi_matrix(0, 0)) * detInv,
                                     (xi_matrix(0, 0) * xi_matrix(1, 1) - xi_matrix(1, 0) * xi_matrix(0, 1)) * detInv );
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 4))>
    constexpr inline T Inv(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;

        MatrixBase<_T, 4, 4> xo_inv( xi_matrix.m_data[5] * xi_matrix.m_data[10] * xi_matrix.m_data[15] - xi_matrix.m_data[5] * xi_matrix.m_data[11] * xi_matrix.m_data[14] - xi_matrix.m_data[9] * xi_matrix.m_data[6] * xi_matrix.m_data[15] + xi_matrix.m_data[9] * xi_matrix.m_data[7] * xi_matrix.m_data[14] + xi_matrix.m_data[13] * xi_matrix.m_data[6] * xi_matrix.m_data[11] - xi_matrix.m_data[13] * xi_matrix.m_data[7] * xi_matrix.m_data[10],
                                    -xi_matrix.m_data[1] * xi_matrix.m_data[10] * xi_matrix.m_data[15] + xi_matrix.m_data[1] * xi_matrix.m_data[11] * xi_matrix.m_data[14] + xi_matrix.m_data[9] * xi_matrix.m_data[2] * xi_matrix.m_data[15] - xi_matrix.m_data[9] * xi_matrix.m_data[3] * xi_matrix.m_data[14] - xi_matrix.m_data[13] * xi_matrix.m_data[2] * xi_matrix.m_data[11] + xi_matrix.m_data[13] * xi_matrix.m_data[3] * xi_matrix.m_data[10],
                                     xi_matrix.m_data[1] * xi_matrix.m_data[6]  * xi_matrix.m_data[15] - xi_matrix.m_data[1] * xi_matrix.m_data[7]  * xi_matrix.m_data[14] - xi_matrix.m_data[5] * xi_matrix.m_data[2] * xi_matrix.m_data[15] + xi_matrix.m_data[5] * xi_matrix.m_data[3] * xi_matrix.m_data[14] + xi_matrix.m_data[13] * xi_matrix.m_data[2] * xi_matrix.m_data[7]  - xi_matrix.m_data[13] * xi_matrix.m_data[3] * xi_matrix.m_data[6],
                                    -xi_matrix.m_data[1] * xi_matrix.m_data[6]  * xi_matrix.m_data[11] + xi_matrix.m_data[1] * xi_matrix.m_data[7]  * xi_matrix.m_data[10] + xi_matrix.m_data[5] * xi_matrix.m_data[2] * xi_matrix.m_data[11] - xi_matrix.m_data[5] * xi_matrix.m_data[3] * xi_matrix.m_data[10] - xi_matrix.m_data[9]  * xi_matrix.m_data[2] * xi_matrix.m_data[7]  + xi_matrix.m_data[9]  * xi_matrix.m_data[3] * xi_matrix.m_data[6],
                                    -xi_matrix.m_data[4] * xi_matrix.m_data[10] * xi_matrix.m_data[15] + xi_matrix.m_data[4] * xi_matrix.m_data[11] * xi_matrix.m_data[14] + xi_matrix.m_data[8] * xi_matrix.m_data[6] * xi_matrix.m_data[15] - xi_matrix.m_data[8] * xi_matrix.m_data[7] * xi_matrix.m_data[14] - xi_matrix.m_data[12] * xi_matrix.m_data[6] * xi_matrix.m_data[11] + xi_matrix.m_data[12] * xi_matrix.m_data[7] * xi_matrix.m_data[10],
                                     xi_matrix.m_data[0] * xi_matrix.m_data[10] * xi_matrix.m_data[15] - xi_matrix.m_data[0] * xi_matrix.m_data[11] * xi_matrix.m_data[14] - xi_matrix.m_data[8] * xi_matrix.m_data[2] * xi_matrix.m_data[15] + xi_matrix.m_data[8] * xi_matrix.m_data[3] * xi_matrix.m_data[14] + xi_matrix.m_data[12] * xi_matrix.m_data[2] * xi_matrix.m_data[11] - xi_matrix.m_data[12] * xi_matrix.m_data[3] * xi_matrix.m_data[10],
                                    -xi_matrix.m_data[0] * xi_matrix.m_data[6]  * xi_matrix.m_data[15] + xi_matrix.m_data[0] * xi_matrix.m_data[7]  * xi_matrix.m_data[14] + xi_matrix.m_data[4] * xi_matrix.m_data[2] * xi_matrix.m_data[15] - xi_matrix.m_data[4] * xi_matrix.m_data[3] * xi_matrix.m_data[14] - xi_matrix.m_data[12] * xi_matrix.m_data[2] * xi_matrix.m_data[7]  + xi_matrix.m_data[12] * xi_matrix.m_data[3] * xi_matrix.m_data[6],
                                     xi_matrix.m_data[0] * xi_matrix.m_data[6]  * xi_matrix.m_data[11] - xi_matrix.m_data[0] * xi_matrix.m_data[7]  * xi_matrix.m_data[10] - xi_matrix.m_data[4] * xi_matrix.m_data[2] * xi_matrix.m_data[11] + xi_matrix.m_data[4] * xi_matrix.m_data[3] * xi_matrix.m_data[10] + xi_matrix.m_data[8]  * xi_matrix.m_data[2] * xi_matrix.m_data[7]  - xi_matrix.m_data[8]  * xi_matrix.m_data[3] * xi_matrix.m_data[6],
                                     xi_matrix.m_data[4] * xi_matrix.m_data[9]  * xi_matrix.m_data[15] - xi_matrix.m_data[4] * xi_matrix.m_data[11] * xi_matrix.m_data[13] - xi_matrix.m_data[8] * xi_matrix.m_data[5] * xi_matrix.m_data[15] + xi_matrix.m_data[8] * xi_matrix.m_data[7] * xi_matrix.m_data[13] + xi_matrix.m_data[12] * xi_matrix.m_data[5] * xi_matrix.m_data[11] - xi_matrix.m_data[12] * xi_matrix.m_data[7] * xi_matrix.m_data[9],
                                    -xi_matrix.m_data[0] * xi_matrix.m_data[9]  * xi_matrix.m_data[15] + xi_matrix.m_data[0] * xi_matrix.m_data[11] * xi_matrix.m_data[13] + xi_matrix.m_data[8] * xi_matrix.m_data[1] * xi_matrix.m_data[15] - xi_matrix.m_data[8] * xi_matrix.m_data[3] * xi_matrix.m_data[13] - xi_matrix.m_data[12] * xi_matrix.m_data[1] * xi_matrix.m_data[11] + xi_matrix.m_data[12] * xi_matrix.m_data[3] * xi_matrix.m_data[9],
                                     xi_matrix.m_data[0] * xi_matrix.m_data[5]  * xi_matrix.m_data[15] - xi_matrix.m_data[0] * xi_matrix.m_data[7]  * xi_matrix.m_data[13] - xi_matrix.m_data[4] * xi_matrix.m_data[1] * xi_matrix.m_data[15] + xi_matrix.m_data[4] * xi_matrix.m_data[3] * xi_matrix.m_data[13] + xi_matrix.m_data[12] * xi_matrix.m_data[1] * xi_matrix.m_data[7]  - xi_matrix.m_data[12] * xi_matrix.m_data[3] * xi_matrix.m_data[5],
                                    -xi_matrix.m_data[0] * xi_matrix.m_data[5]  * xi_matrix.m_data[11] + xi_matrix.m_data[0] * xi_matrix.m_data[7]  * xi_matrix.m_data[9]  + xi_matrix.m_data[4] * xi_matrix.m_data[1] * xi_matrix.m_data[11] - xi_matrix.m_data[4] * xi_matrix.m_data[3] * xi_matrix.m_data[9]  - xi_matrix.m_data[8]  * xi_matrix.m_data[1] * xi_matrix.m_data[7]  + xi_matrix.m_data[8]  * xi_matrix.m_data[3] * xi_matrix.m_data[5],
                                    -xi_matrix.m_data[4] * xi_matrix.m_data[9]  * xi_matrix.m_data[14] + xi_matrix.m_data[4] * xi_matrix.m_data[10] * xi_matrix.m_data[13] + xi_matrix.m_data[8] * xi_matrix.m_data[5] * xi_matrix.m_data[14] - xi_matrix.m_data[8] * xi_matrix.m_data[6] * xi_matrix.m_data[13] - xi_matrix.m_data[12] * xi_matrix.m_data[5] * xi_matrix.m_data[10] + xi_matrix.m_data[12] * xi_matrix.m_data[6] * xi_matrix.m_data[9],
                                     xi_matrix.m_data[0] * xi_matrix.m_data[9]  * xi_matrix.m_data[14] - xi_matrix.m_data[0] * xi_matrix.m_data[10] * xi_matrix.m_data[13] - xi_matrix.m_data[8] * xi_matrix.m_data[1] * xi_matrix.m_data[14] + xi_matrix.m_data[8] * xi_matrix.m_data[2] * xi_matrix.m_data[13] + xi_matrix.m_data[12] * xi_matrix.m_data[1] * xi_matrix.m_data[10] - xi_matrix.m_data[12] * xi_matrix.m_data[2] * xi_matrix.m_data[9],
                                    -xi_matrix.m_data[0] * xi_matrix.m_data[5]  * xi_matrix.m_data[14] + xi_matrix.m_data[0] * xi_matrix.m_data[6]  * xi_matrix.m_data[13] + xi_matrix.m_data[4] * xi_matrix.m_data[1] * xi_matrix.m_data[14] - xi_matrix.m_data[4] * xi_matrix.m_data[2] * xi_matrix.m_data[13] - xi_matrix.m_data[12] * xi_matrix.m_data[1] * xi_matrix.m_data[6]  + xi_matrix.m_data[12] * xi_matrix.m_data[2] * xi_matrix.m_data[5],
                                     xi_matrix.m_data[0] * xi_matrix.m_data[5]  * xi_matrix.m_data[10] - xi_matrix.m_data[0] * xi_matrix.m_data[6]  * xi_matrix.m_data[9]  - xi_matrix.m_data[4] * xi_matrix.m_data[1] * xi_matrix.m_data[10] + xi_matrix.m_data[4] * xi_matrix.m_data[2] * xi_matrix.m_data[9]  + xi_matrix.m_data[8]  * xi_matrix.m_data[1] * xi_matrix.m_data[6]  - xi_matrix.m_data[8]  * xi_matrix.m_data[2] * xi_matrix.m_data[5]);

        _T det{ xi_matrix.m_data[0] * xo_inv.m_data[0] + xi_matrix.m_data[1] * xo_inv.m_data[4] + 
                xi_matrix.m_data[2] * xo_inv.m_data[8] + xi_matrix.m_data[3] * xo_inv.m_data[12] };
        assert(std::abs(det) > std::numeric_limits<_T>::epsilon() && " attempting to inverse a not invertiable matrix.");
        det = static_cast<_T>(1) / det;

        xo_inv *= det;
        return xo_inv;
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> > 4))>
    constexpr inline T Inv(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        // LU decompose
        T lu, xo_inv( _T{} );
        VectorBase<std::size_t, COL> P;
        std::int32_t sign{};
        LU(xi_matrix, lu, P, sign);

        // iverted matrix
        for (std::size_t j{}; j < COL; ++j) {
            // columns
            for (std::size_t i{}; i < COL; ++i) {
                xo_inv(j, i) = (P[i] == j) * static_cast<_T>(1);

                for (std::size_t k{}; k < i; ++k) {
                    xo_inv(j, i) -= lu(k, i) * xo_inv(j, k);
                }
            }

            // rows
            for (std::int32_t i{ static_cast<std::int32_t>(COL) - 1 }; i >= 0; i--) {
                for (std::int32_t k{ i + 1 }; k < static_cast<std::int32_t>(COL); ++k) {
                    xo_inv(j, i) -= lu(k, i) * xo_inv(j, k);
                }

                xo_inv(j, i) /= lu(i, i);
            }
        }

        return xo_inv;
    }

    /**
    * \brief orthonormalize a given matrix (make it columns orthogonal and normalized)
    *        using modified gram-schmidt process.
    *
    * @param {matrixBase, in}  matrix to be orthonormalized
    * @param {matrixBase, out} orthonormalized matrix
    **/
    template<typename T, REQUIRE(is_MatrixBase_v<T>)>
    constexpr T Orthonormalize(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        // gram-schmidt
        T xo_mat;
        for (std::size_t i{}; i < COL; ++i) {
            xo_mat[i] = xi_matrix[i];

            for (std::size_t j{}; j < i; ++j) {
                xo_mat[i] -= ProjectOn(xo_mat[i], xo_mat[j]);
            }

            xo_mat[i] = Normalize(std::move(xo_mat[i]));
        }

        return xo_mat;
    }

    // ----------------------
    // --- Decompositions ---
    // ----------------------

    /**
    * \brief perform LU decomposition of a cubic matrix (using Doolittle algorithm),
    *        i.e. - given matrix A, decompose it to L*P*U, where L is lower traingular with unit diagonal,
    *               U is an upper triangular and P is a diagonal pivot matrix (given as a vector holding its diagonal)
    *
    * @param {matrixBase, in}  cubic matrix to be decomposed
    * @param {matrixBase, out} decomposed matrix, such that its upper triangular portion
    *                          is the 'U' portion, and its lower triangulat portion is the 'L' portion.
    *                          lower triangular matrix should have its diagonal as '1'.
    * @param {VectorBase, out} decomposition pivot vector (row vector, i.e - VectorN<std::size_t, COL>)
    * @param {INT32_T,    out} pivot sign
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr void LU(const T& xi_matrix, T& xo_lu, VectorBase<std::size_t, Columns_v<T>>& xo_pivot, std::int32_t& xo_sign) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        xo_lu = xi_matrix;
        xo_pivot = [](const std::size_t i) { return i; };
        xo_sign = 1;

        for (std::size_t c{}; c < COL; ++c) {
            // find pivot
            std::size_t pivot{ c };
            for (std::size_t r{ c + 1 }; r < COL; ++r) {
                if (std::abs(xo_lu(c, r)) > std::abs(xo_lu(c, pivot))) {
                    pivot = r;
                }
            }
            // exchange pivot
            if (pivot != c) {
                for (std::size_t cc{}; cc < COL; ++cc) {
                    std::swap(xo_lu(cc, pivot), xo_lu(cc, c));
                }
                std::swap(xo_pivot[pivot], xo_pivot[c]);
                xo_sign = -xo_sign;
            }

            // calculate multipliers and eliminate c-th column.
            if (xo_lu(c, c) != _T{}) {
                for (std::size_t r{ c + 1 }; r < COL; ++r) {
                    xo_lu(c, r) /= xo_lu(c, c);

                    for (std::size_t cc{ c + 1 }; cc < COL; ++cc) {
                        xo_lu(cc, r) -= xo_lu(c, r) * xo_lu(cc, c);
                    }
                }
            }
        }
    }

    /**
    * \brief perform QR decomposition of a cubic using gram-schmidt process.
    *
    * @param {matrixBase, in}  cubic matrix to be decomposed (whose number of rows is either equal or larger then the number of columns)
    * @param {matrixBase, out} Q matrix (orthogonal matrix with orthogonal columns, i.e. - Q*Q^T = I; COLxROW)
    * @param {matrixBase, out} R matrix (upper triangular matrix; COLxCOL)
    **/
    template<typename T, REQUIRE(is_MatrixBase_v<T> && (Rows_v<T> >= Columns_v<T>))>
    constexpr void QRgramSchmidt(const T& xi_matrix, 
                      MatrixBase<underlying_type_t<T>, Columns_v<T>, Rows_v<T>>& xo_Q,
                      MatrixBase<underlying_type_t<T>, Columns_v<T>, Columns_v<T>>& xo_R) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };
        
        // Q
        xo_Q = Orthonormalize(xi_matrix);

        // R
        xo_R = _T{};
        for (std::size_t i{}; i < COL; ++i) {
            for (std::size_t j{ i }; j < COL; ++j) {
                xo_R(j, i) = dot(xi_matrix[j], xo_Q[i]);
            }
        }
    }

    /**
    * \brief perform QR decomposition using "Givens rotations".
    *
    * @param {matrixBase, in}  matrix to be decomposed (whose number of rows is either equal or larger then the number of columns)
    * @param {matrixBase, out} Q matrix (orthogonal matrix with orthogonal columns, i.e. - Q*Q^T = I; COLxROW)
    * @param {matrixBase, out} R matrix (upper triangular matrix; COLxCOL)
    **/
    template<typename T, REQUIRE(is_MatrixBase_v<T> && (Rows_v<T> >= Columns_v<T>))>
    void QRgivensRotations(const T& xi_matrix, T& xo_Q, 
                           MatrixBase<underlying_type_t<T>, Columns_v<T>, Columns_v<T>>& xo_R) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> },
                              ROW{ Rows_v<T> };

        /**
        * "givens rotation" (return in order of {cosine, sine, radius})
        **/
        auto GivensRotationInternal = [](const _T& a, const _T& b) {
            constexpr _T one{ static_cast<_T>(1) },
                         TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };
            // a == 0
            if (std::abs(a) <= TOL) {
                return VectorBase<_T, 3>(_T{}, std::copysign(one, b), std::abs(b));
            } // b == 0
            else if (std::abs(b) <= TOL) {
                return VectorBase<_T, 3>(std::copysign(one, a), _T{}, std::abs(a));
            } // a > b
            else if (std::abs(a) > std::abs(b)) {
                const _T t{ b / a },
                         u{ std::copysign(one, a) * std::sqrt(one + t * t) },
                         c{ one / u};
                return VectorBase<_T, 3>(c, t * c, a * u);
            } // a <= b
            else {
                const _T t{ a / b },
                         u{std::copysign(one, b) * std::sqrt(one + t * t)},
                         s{ one / u};
                return VectorBase<_T, 3>(t * s, s, b * u);
            }
        };

        MatrixBase<_T, COL, ROW> R(xi_matrix);
        MatrixBase<_T, ROW, ROW> Q;

        for (std::size_t j{}; j < COL; ++j) {
            for (std::size_t i{ ROW - 1 }; i >= j + 1; --i) {
                VectorBase<_T, 3> CSR( GivensRotationInternal(R(j, i - 1), R(j, i)) );

                // R' = G * R
                for (std::size_t x{}; x < COL; ++x) {
                    const _T temp1{ R(x, i - 1) },
                             temp2{ R(x, i) };
                    R(x, i - 1) =  temp1 * CSR[0] + temp2 * CSR[1];
                    R(x, i)     = -temp1 * CSR[1] + temp2 * CSR[0];
                }
                R(j, i - 1) = CSR[2];
                R(j, i)     = _T{};

                // Q' = Q * G^
                for (std::size_t x{}; x < ROW; ++x) {
                    const _T temp1{ Q(i - 1, x) },
                             temp2{ Q(i,     x) };
                    Q(i - 1, x) =  temp1 * CSR[0] + temp2 * CSR[1];
                    Q(i,     x) = -temp1 * CSR[1] + temp2 * CSR[0];
                }
            }
        }

        // adjust Q
        if constexpr (ROW != COL) {
            Q = Transpose(std::move(Q));
        }
        xo_Q = GetBlock<0, COL - 1, 0, ROW - 1>(Q);

        // adjust R
        xo_R = GetBlock<0, COL-1, 0, COL-1>(R);
    }

    /**
    * \brief perform singular value decomposition on a given matrix, i.e. - given A, return A = U * W * V^T
    *        where U & V columns are orthonormal (U^T*U = U*U^T = V^T*V = V*V^T = I).
    *
    *        important remarks:
    *        1) to avoid arithmetic complexity which is not needed for most SVD related operations:
    *           a) instead of U, U*W is returned.
    *              i.e - for a 3x3 matrix:
    *              {U(0, 0) * sqrt(W[0]), U(0, 1) * sqrt(W[1]), U(0, 2) * sqrt(W[2]);
    *               U(1, 0) * sqrt(W[0]), U(1, 1) * sqrt(W[1]), U(1, 2) * sqrt(W[2]);
    *               U(2, 0) * sqrt(W[0]), U(2, 1) * sqrt(W[1]), U(2, 2) * sqrt(W[2])}
    *           b) W holds the SQUARE of singular values (i.e. - "eigenvalues").
    *           C) V is not transposed.
    *        2) SVD values are numerically correct, but their SIGN MIGHT BE WRONG. For further reading on this subject, see:
    *           SANDIA REPORT, SAND2007-6422, "Resolving the Sign Ambiguity in the Singular Value Decomposition", R. Bra, E. Acar, T. Kolda.
    *
    * @param {matrixBase, in}  matrix to be decomposed
    * @param {matrixBase, out} U*W [COLxROW]
    * @param {vectorBase, out} Vector holding SQUARE of singular values [col]
    * @param {matrixBase, out} V (not V transposed!) [COLxCOL]
    * @param {bool,       out} true if SVD rutine converged, false otherwise
    **/
    template<typename T, REQUIRE(is_MatrixBase_v<T> && (Rows_v<T> >= Columns_v<T>))>
    bool SVDfast(const T& xi_mat, T& xo_UW, 
             VectorBase<underlying_type_t<T>, Columns_v<T>>& xo_W2, 
             MatrixBase<underlying_type_t<T>, Columns_v<T>, Columns_v<T>>& xo_V) noexcept {

        // housekeeping
        using _T = underlying_type_t<T>;
        constexpr std::size_t ROW{ Rows_v<T> },
                              COL{ Columns_v<T> },
                              sweepLimit{ (COL < 120) ? 30 : (COL / 4) };

        constexpr _T eps{ std::numeric_limits<_T>::epsilon() },
                     e2{ static_cast<_T>(10.0) * ROW * eps * eps },
                     tol{ static_cast<_T>(0.1) * eps },               // algorithm convergence tolerance
                     tolSqr{ tol * tol };

        // locals
        std::size_t estimatedColumnRank{ COL },
                    rotationCount{ ROW },
                    sweepCount{};

        // fill A
        MatrixBase<_T, COL, ROW + COL> A(_T{});
        for (std::size_t c{}; c < COL; ++c) {
            for (std::size_t r{}; r < ROW; ++r) {
                A(c, r) = xi_mat(c, r);
            }
        }
        for (std::size_t i{}; i < COL; ++i) {
            A(i, ROW + i) = static_cast<_T>(1.0);
        }

        while ((rotationCount != 0) && (sweepCount++ <= sweepLimit)) {
            rotationCount = estimatedColumnRank * (estimatedColumnRank - 1) / 2;

            // Jacobi sweep
            for (std::size_t j{}; j < estimatedColumnRank - 1; ++j) {
                for (std::size_t k{ j + 1 }; k < estimatedColumnRank; ++k) {
                    _T p{}, q{}, r{};

                    for (std::size_t i{}; i < ROW; ++i) {
                        const _T x0{ A(j, i) },
                                 y0{ A(k, i) };
                        p += x0 * y0;
                        q += x0 * x0;
                        r += y0 * y0;
                    }
                    xo_W2[j] = q;
                    xo_W2[k] = r;

                    // are columns ordered?
                    if (q >= r) {
                        if ((q <= e2 * xo_W2[0]) ||           // are columns 'norm' so small that rotation makes no sense?
                            (std::abs(p) <= tol * q)) {       // is the inner product is small with respect to the larger of the columns?
                                                              // then rotation angle is very small and we can skip it
                            --rotationCount;
                        } // givens rotation
                        else {
                            const _T qInv{ static_cast<_T>(1.0) / q };
                            p *= qInv;
                            r = static_cast<_T>(1.0) - r * qInv;
                            const _T vt{ std::sqrt(static_cast<_T>(4.0) * p * p + r * r) },
                                     c0{ std::sqrt(static_cast<_T>(0.5) * (static_cast<_T>(1.0) + r / vt)) },
                                     s0{ p / (vt * c0) };

                            for (std::size_t i{}; i < ROW + COL; ++i) {
                                const _T d1{ A(j, i) },
                                         d2{ A(k, i) };
                                A(j, i) =  d1 * c0 + d2 * s0;
                                A(k, i) = -d1 * s0 + d2 * c0;
                            }
                        }
                    } // givens rotation
                    else {
                        const _T rInv{ static_cast<_T>(1.0) / r };
                        p *= rInv;
                        q = q * rInv - static_cast<_T>(1.0);

                        const _T vt{ std::sqrt(static_cast<_T>(4.0) * p * p + q * q) };

                        _T s0{ std::sqrt(static_cast<_T>(0.5) * (static_cast<_T>(1.0) - q / vt)) };
                        if (p < _T{}) {
                            s0 = -s0;
                        }

                        const _T c0{ p / (vt * s0) };

                        for (std::size_t i{}; i < ROW + COL; ++i) {
                            const _T d1{ A(j, i) },
                                     d2{ A(k, i) };
                            A(j, i) =  d1 * c0 + d2 * s0;
                            A(k, i) = -d1 * s0 + d2 * c0;
                        }
                    }
                }
            }

            const _T bound{ xo_W2[0] * tol + tolSqr };
            while ((estimatedColumnRank > 2) && (xo_W2[estimatedColumnRank - 1] <= bound)) {
                estimatedColumnRank--;
            }
        }

        // reached maximal number of sweeps
        if (sweepCount > sweepLimit) {
            return false;
        }

        // extract V
        xo_V = GetBlock<0, COL - 1, ROW, ROW + COL - 1>(A);

        // extract U*W
        xo_UW = GetBlock<0, COL - 1, 0, ROW - 1>(A);

        return true;
    }

    /**
    * \brief perform singular value decomposition on a given matrix, i.e. - given A, return A = U * W * V^T
    *        where U & V columns are orthonormal (U^T*U = U*U^T = V^T*V = V*V^T = I).
    *
    *        important remarks:
    *        1) SVD values are numerically correct, but their SIGN MIGHT BE WRONG. For further reading on this subject, see:
    *           SANDIA REPORT, SAND2007-6422, "Resolving the Sign Ambiguity in the Singular Value Decomposition", R. Bra, E. Acar, T. Kolda.
    *        2) singular values (W) are ordererd from big to small.
    *
    * @param {matrixBase, in}  matrix to be decomposed
    * @param {matrixBase, out} U [COLxROW]
    * @param {vectorBase, out} Vector holding singular values [col]
    * @param {matrixBase, out} V transposed [COLxCOL]
    * @param {bool,       out} true if SVD rutine converged, false otherwise
    **/
    template<typename T, REQUIRE(is_MatrixBase_v<T> && (Rows_v<T> >= Columns_v<T>))>
    bool SVD(const T& xi_mat, T& xo_U, VectorBase<underlying_type_t<T>, Columns_v<T>>& xo_W,
             MatrixBase<underlying_type_t<T>, Columns_v<T>, Columns_v<T>>& xo_V) noexcept {

        // housekeeping
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        // fast SVD
        const bool xo_flag{ SVDfast(xi_mat, xo_U, xo_W, xo_V) };
        if (!xo_flag) return false;

        // adjust singular values
        xo_W = sqrt(std::move(xo_W));

        // adjust U
        for (std::size_t i{}; i < COL; ++i) {
            xo_U[i] /= xo_W[i];
        }

        // adjust V
        xo_V = Transpose(std::move(xo_V));

        // output
        return true;
     }

    /**
    * \brief given cubic and positive definite matrix A, 
    *        constructs a lower triangular matrix L such that L*L' = A.
    *        (it's roughly TWICE as efficient as the LU decomposition)
    *
    * @param {matrixBase, in}  'A' (must be symmetric)
    * @param {matrixBase, out} lower decomposition
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr T Cholesky(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        T xo_lower(_T{});

        for (std::size_t j{}; j < COL; ++j) {
            _T d{};

            for (std::size_t k{}; k < j; ++k) {
                _T s{};

                for (std::size_t i{}; i < k; ++i) {
                    s += xo_lower(i, k) * xo_lower(i, j);
                }

                xo_lower(k, j) = s = (xi_matrix(k, j) - s) / xo_lower(k, k);
                d += s * s;
            }

            d = xi_matrix(j, j) - d;

            xo_lower(j, j) = (d > _T{}) ? (std::sqrt(d)) : (_T{});
        }

        return xo_lower;
    }

    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr T Cholesky(T&& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        T xo_lower(_T{});

        for (std::size_t j{}; j < COL; ++j) {
            _T d{};

            for (std::size_t k{}; k < j; ++k) {
                _T s{};

                for (std::size_t i{}; i < k; ++i) {
                    s += xo_lower(i, k) * xo_lower(i, j);
                }

                xo_lower(k, j) = s = (xi_matrix(k, j) - s) / xo_lower(k, k);
                d += s * s;
            }

            d = xi_matrix(j, j) - d;

            xo_lower(j, j) = (d > _T{}) ? (std::sqrt(d)) : (_T{});
        }

        return xo_lower;
    }

    // --------------------------------------
    // --- linear equations system solver ---
    // --------------------------------------

    /**
    * \brief solve linear system A*x=b (A must be CUBIC).
    *        (notice, performs LU decomposition internally)
    *
    * @param {matrixBase, in}  A (CUBIC)
    * @param {vectorBase, in}  b (column vector)
    * @param {vectorBase, out} x (column vector)
    **/
    template<typename T, typename U, REQUIRE(is_Cubic<T>::value && is_Vector<U>::value && (Length_v<U> == Columns_v<T>) &&
                                             std::is_same_v<underlying_type_t<T>, underlying_type_t<U>>)>
    constexpr U SolveSquareLU(const T& xi_A, const U& xi_b) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };
        
        // LU decomposition
        T lowerUpper;
        std::int32_t sign{};
        VectorBase<std::size_t, COL> piv;
        LU(xi_A, lowerUpper, piv, sign);

        // x is the permuted copy of xi_b as xi_pivot
        U xo_x;
        for (std::size_t i{}; i < COL; ++i) {
            xo_x[i] = xi_b[piv[i]];
        }

        // Solve L*Y = B(pivoted)
        for (std::size_t k{}; k < COL; ++k) {
            for (std::size_t i{ k + 1 }; i < COL; ++i) {
                xo_x[i] -= xo_x[k] * lowerUpper(k, i);
            }
        }

        // Solve U*X = Y
        for (int64_t k{ COL - 1 }; k >= 0; k--) {
            const std::size_t _k{ static_cast<std::size_t>(k) };
            xo_x[_k] /= lowerUpper(_k, _k);

            for (std::size_t i{}; i < _k; ++i) {
                xo_x[i] -= xo_x[_k] * lowerUpper(_k, i);
            }
        }

        // output
        return xo_x;
    }

    /**
    * \brief solve linear system A*x=b using Cholesky decomposition.
    *        'A' must be CUBIC and positive definite.
    *        (only the CUBIC requirement is enforced)
    *
    * @param {matrixBase, in}  A (CUBIC and positive definite)
    * @param {vectorBase, in}  b (column vector)
    * @param {vectorBase, out} x (column vector)
    **/
    template<typename T, typename U, REQUIRE(is_Cubic<T>::value&& is_Vector<U>::value&&
                                             std::is_same_v<underlying_type_t<T>, underlying_type_t<U>> && (Length_v<U> == Columns_v<T>))>
        constexpr U SolveCubicCholesky(const T& xi_A, const U& xi_b) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> };

        // Cholesky decomposition
        const T L(Cholesky(xi_A));

        U xo_x(xi_b);

        // Solve L*y = b;
        for (std::size_t k{}; k < COL; ++k) {
            for (std::size_t i{}; i < k; ++i) {
                xo_x[k] -= xo_x[i] * L(i, k);
            }

            xo_x[k] /= L(k, k);
        }

        // Solve L'*X = Y;
        for (int64_t k{ COL - 1 }; k >= 0; --k) {
            const std::size_t ks{ static_cast<std::size_t>(k) };

            for (std::size_t i{ ks + 1 }; i < COL; ++i) {
                xo_x[ks] -= xo_x[i] * L(ks, i);
            }

            xo_x[ks] /= L(ks, ks);
        }

        // output
        return xo_x;
    }

    /**
    * \brief solve linear system A*x=b (using internally both QR & LU decomposition)
    *
    *        Notice that QR decomposition is used and not:
    *        > pseudo-inverse - to avoid increasing the output matrix condition number (happens when multiplying the matrix by its transpose),
    *        > SVD - high running time complexity.
    *
    * @param {matrixBase, in}  A (ROWxCOL, ROW >= COL)
    * @param {vectorBase, in}  B (column vector, ROWx1)
    * @param {vectorBase, out} X (column vector, COL, 1)
    **/
    template<typename T, REQUIRE(is_MatrixBase_v<T> && (Rows_v<T> >= Columns_v<T>))>
    constexpr VectorBase<underlying_type_t<T>, Columns_v<T>> 
    SolveQR(const T& xi_A, const VectorBase<underlying_type_t<T>, Rows_v<T>>& xi_B) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t COL{ Columns_v<T> },
                              ROW{ Rows_v<T> };

        // QR decomposition
        MatrixBase<_T, COL, ROW> Q(_T{});
        MatrixBase<_T, COL, COL> R(_T{});
        QRgivensRotations(xi_A, Q, R);

        // C = Q * B
        const auto C(xi_B * Q);

        // R*x = C
        MatrixBase<_T, COL, COL> Rlu;
        VectorBase<std::size_t, COL> piv;
        int32_t sign;
        LU(R, Rlu, piv, sign);

        return SolveSquareLU(Rlu, C);
    }


    // ---------------
    // --- Queries ---
    // ---------------
    

    /**
    * \brief check if a CUBIC matrix is symmetric (around its diagonal; A = A^T)
    *
    * @param {MatrixBase, in}  matrix
    * @param {bool,       out} true if matrix is symmetric (around its diagonal)
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 2))>
    constexpr bool IsSymmetric(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };
        return (std::abs(xi_matrix(0, 1) - xi_matrix(1, 0)) <= TOL);
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 3))>
    constexpr bool IsSymmetric(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };

        bool xo_symmetric{ std::abs(xi_matrix(0, 1) - xi_matrix(1, 0)) <= TOL };
        xo_symmetric &= std::abs(xi_matrix(0, 2) - xi_matrix(2, 0)) <= TOL;
        xo_symmetric &= std::abs(xi_matrix(1, 2) - xi_matrix(2, 1)) <= TOL;
        return xo_symmetric;
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> > 3))>
    constexpr bool IsSymmetric(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t ROW{ Rows_v<T> };
        constexpr _T TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };

        bool xo_symmetric{ true };
        for (std::size_t j{}; (j < ROW) && xo_symmetric; ++j) {
            for (std::size_t i{}; (i < ROW) && xo_symmetric; ++i) {
                if (i == j) continue;
                xo_symmetric = std::abs(xi_matrix(i, j) - xi_matrix(j, i)) <= TOL;
            }
        }

        return xo_symmetric;
    }

    /**
    * \brief check if a CUBIC matrix is skew-symmetric (around its diagonal; -A = A^T)
    *
    * @param {MatrixBase, in}  matrix
    * @param {bool,       out} true if matrix is symmetric (around its diagonal)
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 2))>
    constexpr bool IsSkewSymmetric(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };
        return (std::abs(xi_matrix(0, 1) + xi_matrix(1, 0)) <= TOL);
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> == 3))>
    constexpr bool IsSkewSymmetric(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };

        bool xo_symmetric{ std::abs(xi_matrix(0, 1) + xi_matrix(1, 0)) <= TOL };
        xo_symmetric &= std::abs(xi_matrix(0, 2) + xi_matrix(2, 0)) <= TOL;
        xo_symmetric &= std::abs(xi_matrix(1, 2) + xi_matrix(2, 1)) <= TOL;
        return xo_symmetric;
    }

    template<typename T, REQUIRE(is_Cubic<T>::value && (Rows_v<T> > 3))>
    constexpr bool IsSkewSymmetric(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t ROW{ Rows_v<T> };
        constexpr _T TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };

        bool xo_symmetric{ true };
        for (std::size_t j{}; (j < ROW) && xo_symmetric; ++j) {
            for (std::size_t i{}; (i < ROW) && xo_symmetric; ++i) {
                if (i == j) continue;
                xo_symmetric = std::abs(xi_matrix(i, j) + xi_matrix(j, i)) <= TOL;
            }
        }

        return xo_symmetric;
    }

    /**
    * \brief check if a CUBIC matrix is upper triangular
    *
    * @param {MatrixBase, in}  matrix
    * @param {bool,       out} true if matrix is upper triangular
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr bool IsUpperTriangular(const T& xi_matrix) noexcept {
        constexpr std::size_t ROW{ Rows_v<T> };
        constexpr underlying_type_t<T> TOL{ static_cast<underlying_type_t<T>>(2) * std::numeric_limits<underlying_type_t<T>>::epsilon() };

        bool xo_triangular{ true };

        for (std::size_t i{}; (i < ROW) && xo_triangular; ++i) {
            for (std::size_t j{ i + 1 }; (j < ROW) && xo_triangular; ++j) {
                auto t = xi_matrix(i, j);
                xo_triangular = std::abs(xi_matrix(i, j)) <= TOL;
            }
        }
        
        return xo_triangular;
    }

    /**
    * \brief check if a CUBIC matrix is lower triangular
    *
    * @param {MatrixBase, in}  matrix
    * @param {bool,       out} true if matrix is lower triangular
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr bool IsLowerTriangular(const T& xi_matrix) noexcept {
        constexpr std::size_t ROW{ Rows_v<T> };
        constexpr underlying_type_t<T> TOL{ static_cast<underlying_type_t<T>>(2) * std::numeric_limits<underlying_type_t<T>>::epsilon() };

        bool xo_triangular{ true };

        for (std::size_t i{}; (i < ROW) && xo_triangular; ++i) {
            for (std::size_t j{}; (j < i) && xo_triangular; ++j) {
                xo_triangular = std::abs(xi_matrix(i, j)) <= TOL;
            }
        }

        return xo_triangular;
    }

    /**
    * \brief check if a CUBIC matrix is diagonal
    *
    * @param {MatrixBase, in}  matrix
    * @param {bool,       out} true if matrix is diagonal
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr bool IsDiagonal(const T& xi_matrix) noexcept {
        constexpr std::size_t ROW{ Rows_v<T> };
        constexpr underlying_type_t<T> TOL{ static_cast<underlying_type_t<T>>(2) * std::numeric_limits<underlying_type_t<T>>::epsilon() };

        // a diagonal matrix must also be triangular
        bool xo_diagonal{ IsUpperTriangular(xi_matrix) };
        if (!xo_diagonal) return false;
        xo_diagonal = IsLowerTriangular(xi_matrix);
        if (!xo_diagonal) return false;

        // diagonal
        xo_diagonal = true;
        for (std::size_t i{}; (i < ROW) && xo_diagonal; ++i) {
            xo_diagonal = std::abs(xi_matrix(i, i)) > TOL;
        }

        return xo_diagonal;
    }

    /**
    * \brief check if a CUBIC matrix is permutation matrix (there is only one '1' in every column and row)
    *
    * @param {MatrixBase, in}  matrix
    * @param {bool,       out} true if matrix is a permutation matrix
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr bool IsPermutation(const T& xi_matrix) noexcept {
        using _T = underlying_type_t<T>;
        constexpr std::size_t ROW{ Rows_v<T> };
        constexpr _T row{ static_cast<_T>(ROW) },
                     one{ static_cast<_T>(1) },
                     eps{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() },
                     TOL{ one + row * eps };
        
        bool xo_permutation{ true };
        VectorBase<_T, ROW> temp;
        for (std::size_t i{}; (i < ROW) && xo_permutation; ++i) {
            temp = GetRow(xi_matrix, i);
            xo_permutation = sum(temp) <= TOL;
            if (!xo_permutation) return xo_permutation;

            temp = xi_matrix[i];
            xo_permutation &= sum(temp) <= TOL;
        }
        
        return xo_permutation;
    }

    // ---------------------------------------------
    // --- Specialized Operations for 2x2 matrix ---
    // ---------------------------------------------

    /**
    * \brief return the angle which rotates a 2x2 matrix into diagonal form,
    *        i.e - elements (1, 0) = (0,1) = 0, and elements (0, 0) > (1, 1) are the eigenvalues
    *
    * @param {matrixBase, in}  matrix
    * @param {T,          out} angle [rad]
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Length_v<T> == 4))> 
    constexpr inline underlying_type_t<T> Diagonalizer(const T& xi_mat) noexcept {
        using _T = underlying_type_t<T>;
        const _T diff{ xi_mat(1, 1) - xi_mat(0, 0) };
        return std::atan2(diff + std::sqrt(diff * diff + static_cast<T>(4) * xi_mat(0, 1) * xi_mat(1, 0)), static_cast<T>(2) * xi_mat(1, 0));
    }

    /**
    * \brief return 2x2 matrix eigenvalues
    *
    * @param {matrixBase, in}  matrix
    * @param {T,          out} eigenvalue
    * @param {T,          out} eigenvalue
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Length_v<T> == 4))>
    constexpr inline void EigenValues2x2(const T& xi_mat, underlying_type_t<T>& xo_eigen1, underlying_type_t<T>& xo_eigen2) noexcept {
        using _T = underlying_type_t<T>;

        const _T diff{ xi_mat(0, 0) - xi_mat(1, 1) },
                 center{ xi_mat(0, 0) + xi_mat(1, 1) },
                 delta{ std::sqrt(diff * diff + static_cast<_T>(4) * xi_mat(1, 0) * xi_mat(0, 1)) };

        xo_eigen1 = static_cast<_T>(0.5) * (center + delta);
        xo_eigen2 = static_cast<_T>(0.5) * (center - delta);
    }

    /**
    * \brief return 2x2 matrix eigenvalues and eigenvectors
    *
    * @param {matrixBase, in}  matrix
    * @param {T,          out} eigenvalue #1
    * @param {T,          out} eigenvalue #2
    * @param {vectorBase, out} eigenvector #1 (belongs to eigen value #1)
    * @param {vectorBase, out} eigenvector #2 (belongs to eigen value #2)
    **/
    template<typename T, typename U, REQUIRE(is_Cubic<T>::value && (Length_v<T> == 4) &&
                                             is_Vector<U>::value && (Length_v<U> == 2))> 
    constexpr inline void EigenSolver2x2(const T& xi_mat, underlying_type_t<T>& xo_eigenvalue0, underlying_type_t<T>& xo_eigenvalue1,
                                         U& xo_eigenvector0, U& xo_eigenvector1) noexcept {
        using _T = underlying_type_t<T>;

        EigenValues2x2(xi_mat, xo_eigenvalue0, xo_eigenvalue1);

        xo_eigenvector0 = { static_cast<_T>(-xi_mat(0, 1)), static_cast<_T>(xi_mat(0, 0) - xo_eigenvalue0) };
        xo_eigenvector1 = { static_cast<_T>(-xi_mat(0, 1)), static_cast<_T>(xi_mat(0, 0) - xo_eigenvalue1) };

        xo_eigenvector0 = Normalize(std::move(xo_eigenvector0));
        xo_eigenvector1 = Normalize(std::move(xo_eigenvector1));
    }

    /**
    * \brief perform SVD decomposition of a SYMMETRIC 2x2 matrix, i.e.:
    *           A      =      U    *     W     *   U^T
    *        [ A  B ]  =  [ c  -s ] [ r1   0  ] [  c  s ]
    *        [ B  C ]     [ s   c ] [  0   r2 ] [ -s  c ]
    *
    *        notice that as with any SVD decomposition which does not incorporate sign ambiguity logic,
    *        this method will output the correct values, but not necessarily the correct signs.
    *
    * @param {matrixBase, in}  SYMMETRIC matrix to be decomposed
    * @param {matrixBase, out} U
    * @param {vectorBase, out} W (as a vector)
    **/
    template<typename T, typename U, REQUIRE(is_Cubic<T>::value && (Length_v<T> == 4) && 
                                             is_Vector<U>::value && (Length_v<U> == 2))> 
    constexpr inline void SVDsymmetric2x2(const T& xi_mat, T& xo_U, U& xo_W) noexcept {
        using _T = underlying_type_t<T>;
        constexpr _T TOL{ static_cast<_T>(2) * std::numeric_limits<_T>::epsilon() };
        assert(std::abs(xi_mat(0, 1) - xi_mat(1, 0)) <= TOL && " SVDsymmetric2x2 input matrix is not symmetric.");

        const _T A{ xi_mat(0, 0) },
                 B{ xi_mat(0, 1) },
                 C{ xi_mat(1, 1) },
                 traceSum{ A + C },
                 traceDiff{ A - C },
                 rt{ std::sqrt(traceDiff * traceDiff + static_cast<_T>(4) * B * B) };
        _T r1, r2, c, s, t;

        // eigenvalues
        if (traceSum > _T{}) {
            r1 = static_cast<_T>(0.5) * (traceSum + rt);
            t = static_cast<_T>(1) / (r1);
            r2 = (A * t) * C - (B * t) * B;
        }
        else if (traceSum < _T{}) {
            r2 = static_cast<_T>(0.5) * (traceSum - rt);
            t = static_cast<_T>(1) / (r2);
            r1 = (A * t) * C - (B * t) * B;
        }
        else {
            r1 =  static_cast<_T>(0.5) * rt;
            r2 = -static_cast<_T>(0.5) * rt;
        }
        xo_W[0] = static_cast<_T>(r1);
        xo_W[1] = static_cast<_T>(r2);

        // eigenvectors
        c = (traceDiff > _T{}) ? (traceDiff + rt) : (traceDiff - rt);

        if (std::abs(c) > static_cast<_T>(2) * std::abs(B)) {
            t = -static_cast<_T>(2) * B / c;
            s = static_cast<_T>(1) / std::sqrt(static_cast<_T>(1) + t * t);
            c = t * s;
        }
        else if (std::abs(B) <= TOL) {
            c = static_cast<_T>(1);
            s = _T{};
        }
        else {
            t = -static_cast<_T>(0.5) * c / B;
            c = static_cast<_T>(1) / std::sqrt(static_cast<_T>(1) + t * t);
            s = t * c;
        }

        if (traceDiff > _T{}) {
            t =  c;
            c = -s;
            s =  t;
        }

        xo_U = { c, s,
                -s, c };
    }

    /**
    * \brief perform polar decomposition (PD) on a given matrix, i.e. A = R * S,
    *        where R is a rotation matrix in Givens form, S is symmetric describing deformations.
    *        (a granted negative sign on the small magnitude singular value)
    *
    * @param {matrixBase, in}  A
    * @param {matrixBase, out} R
    * @param {matrixBase, out} S
    **/
    template<typename T, REQUIRE(is_Cubic<T>::value && (Length_v<T> == 4))>
    constexpr inline void PolarDecomposition2x2(const T& xi_A, T& xo_R, T& xo_S) noexcept {
        using _T = underlying_type_t<T>;

        const _T x0{ xi_A(0, 0) + xi_A(1, 1) },
                 x1{ xi_A(0, 1) - xi_A(1, 0) };
        _T den{ std::sqrt(x0 * x0 + x1 * x1) },
           c{ static_cast<_T>(1) },
           s{};

        // R
        if (std::abs(den) > _T{}) {
            den = static_cast<_T>(1) / den;
            c =  x0 * den;
            s = -x1 * den;
        }
        xo_R = { c, s,
                -s, c };

        // S
        xo_S = xi_A;
        static_for<0, 2>([&](std::size_t j) {
            const _T tau1{ xo_S(j, 0) },
                     tau2{ xo_S(j, 1) };
            xo_S(j, 0) = c * tau1 - s * tau2;
            xo_S(j, 1) = s * tau1 + c * tau2;
        });
    }

}; // namespace GLSLCPP

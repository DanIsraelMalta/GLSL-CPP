/**
* Fixed size rectangular (i.e. ROW x COL) numerical matrix.
*
* This object follows the GLSL specification, therfore:
* > Matrix storage layout is column major.
* > Matrix element access is in the following manner: (column, row)
* > vector-matrix multiplication convention:
*   a right vector operand is treated as a column vector, while a left vector
*   operand is treated as a row vector.
*
* Dan Israel Malta
**/
#pragma once
#include "Common.h"
#include "VectorBase.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <assert.h>
#include <type_traits>
#include <utility>
#include <limits>

namespace GLSLCPP {
    /**
    * \brief fixed size numerical matrix
    *
    * @param {T,      in} underlying type
    * @param {COL,    in} number of columns
    * @param {ROW,    in} number of rows
    **/
    template<typename T, std::size_t COL, std::size_t ROW> class MatrixBase {
        static_assert(std::is_arithmetic<T>::value, "MatrixBase<T,COL, ROW> - T must be of numerical type.");
        static_assert(ROW != 0, "MatrixBase<T,COL, ROW> - ROW/COL parameters must be positive.");
        static_assert(COL != 0, "MatrixBase<T,COL, ROW> - ROW/COL parameters must be positive.");

        // properties
        public:
            VectorBase<T, ROW * COL> m_data;

        // internal helpers
        private:

            // given its column and row indices's, return the appropriate linear index
            constexpr static std::size_t Index(const std::size_t xi_row, const std::size_t xi_col) {
                return (xi_col * ROW + xi_row);
            }

        // constructors
        public:

        // empty constructor for a cubic matrix only (I matrix)
        template<std::size_t c = COL, std::size_t r = ROW, REQUIRE(r == c)> explicit constexpr MatrixBase() : m_data(T{}) {
            for (std::size_t i{}; i < ROW; ++i) {
                m_data[Index(i, i)] = static_cast<T>(1);
            }
        }

        // construct using a single value
        template<typename U> explicit constexpr MatrixBase(const U xi_value = U{}, REQUIRE(is_ArithmeticConvertible_v<U, T>)) : m_data(xi_value) {}

        // construct from VectorBase with ROW*COL elements
        template<typename U> explicit constexpr MatrixBase(const U& xi_vec, REQUIRE(Is_VectorOfLength_v<U, ROW * COL>)) : m_data(xi_vec) {}
        template<typename U> explicit constexpr MatrixBase(U&& xi_vec, REQUIRE(Is_VectorOfLength_v<U, ROW* COL>))       : m_data(std::move(xi_vec)) {}

        // construct using ROW*COL individual values (of same type)
        template<typename ...Us, REQUIRE((sizeof...(Us) == ROW * COL) && Are_ArithmeticConvertible<Us...>::value)>
        explicit constexpr MatrixBase(Us... xi_values) : m_data(xi_values...) {}

        // construct from a smaller matrix (the rest of the matrix shall be an 'I')
        template<typename U, std::size_t _col, std::size_t _row>
        explicit constexpr MatrixBase(const MatrixBase<U, _col, _row> & xi_mat,
            REQUIRE((_col < COL) || (_row < ROW))) : m_data(T{}) {
            // make it an 'I' matrix in case the input matrix size is smaller
            if constexpr (COL == ROW) {
                for (std::size_t i{}; i < ROW; ++i) {
                    m_data[Index(i, i)] = static_cast<T>(1);
                }
            }

            // copy input matrix
            for (std::size_t i{}; i < _col; ++i) {
                for (std::size_t j{}; j < _row; ++j) {
                    m_data[Index(j, i)] = static_cast<T>(xi_mat(i, j));
                }
            }
        }

        template<typename U, std::size_t _col, std::size_t _row>
        explicit constexpr MatrixBase(MatrixBase<U, _col, _row> && xi_mat,
            REQUIRE((_col < COL) || (_row < ROW))) : m_data(T{}) {
            // make it an 'I' matrix in case the input matrix size is smaller
            if constexpr (COL == ROW) {
                for (std::size_t i{}; i < ROW; ++i) {
                    m_data[Index(i, i)] = static_cast<T>(1);
                }
            }

            // copy input matrix
            for (std::size_t i{}; i < _col; ++i) {
                for (std::size_t j{}; j < _row; ++j) {
                    m_data[Index(j, i)] = static_cast<T>(std::move(xi_mat(i, j)));
                }
            }
        }

        // construct with columns
        template<typename ...Us, REQUIRE(sizeof...(Us) == COL)>
        explicit constexpr MatrixBase(const Us & ... xi_columns) {
            static_assert(Are_VectorsSimilar<T, ROW, Us...>::value,
                "When attempting to construct a MatrixBase by its columns, make sure that they are all of length 'ROW' and with identical underlying type.");
            const std::array<VectorBase<T, ROW>, COL> columns{ xi_columns... };

            for (std::size_t i{}; i < COL; ++i) {
                const VectorBase<T, ROW> col(columns[i]);
                for (std::size_t j{}; j < ROW; ++j) {
                    m_data[i * ROW + j] = static_cast<T>(col[j]);
                }
            }

        }

        // copy semantics
        MatrixBase(const MatrixBase&)            = default;
        MatrixBase& operator=(const MatrixBase&) = default;

        // move semantics
        MatrixBase(MatrixBase&&)            noexcept = default;
        MatrixBase& operator=(MatrixBase&&) noexcept = default;

        // assignment operator
    public:

        // assign an element
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)> constexpr MatrixBase& operator=(const U xi_value) noexcept {
            m_data = xi_value;
            return *this;
        }

        // assign a vector
        template<typename U, REQUIRE(Is_VectorOfLength_v<U, ROW * COL>)> constexpr MatrixBase& operator=(const U& xi_vec) noexcept {
            m_data = FWD(xi_vec);
            return *this;
        }

        // query operations
    public:

        // extract vector size
        constexpr std::size_t length() const noexcept { return (ROW * COL); }

        // extract row #i
        constexpr VectorBase<T, COL> getRow(const std::size_t index) {
            assert(index < ROW && "MatrixBase::getRow(index) - trying to access a non existent row.");
            VectorBase<T, COL> xo_row;

            for (std::size_t i{}; i < COL; ++i) {
                xo_row[i] = m_data[Index(index, i)];
            }

            return xo_row;
        }

        // set/get operations
    public:

        // '[]' column access (return column #i)
        constexpr auto& operator[](const std::size_t i) {
            assert(i < COL && " trying to access a non existent column.");
            return *(VectorBase<T, ROW>*)(&m_data[Index(0, i)]);
        }
        constexpr auto operator[](const std::size_t i) const {
            assert(i < COL && " trying to access a non existent column.");
            VectorBase<T, ROW> xo_col;

            for (std::size_t j{}; j < ROW; ++j) {
                xo_col[j] = m_data[Index(j, i)];
            }

            return xo_col;
        }

        // '(col, row)' element access
        constexpr T operator()(const std::size_t col, const std::size_t row) const {
            assert((col < COL) && (row < ROW) && " trying to access a non existent element.");
            return m_data[Index(row, col)];
        }
        constexpr T& operator()(const std::size_t col, const std::size_t row) {
            assert((col < COL) && (row < ROW) && " trying to access a non existent element.");
            return m_data[Index(row, col)];
        }

        // compound operator overloading
    public:

        // (element wise) operations with scalars
#define M_OPERATOR(OP)                                                      \
       template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)>      \
       constexpr MatrixBase& operator OP (const U xi_value) {               \
           m_data OP xi_value;                                              \
           return *this;                                                    \
       }

        M_OPERATOR(+= );
        M_OPERATOR(-= );
        M_OPERATOR(*= );
        M_OPERATOR(/= );
        M_OPERATOR(&= );
        M_OPERATOR(|= );
        M_OPERATOR(^= );
        M_OPERATOR(>>= );
        M_OPERATOR(<<= );

#undef M_OPERATOR

        // (element wise) operations with equally size matrix
#define M_OPERATOR(OP)                                                              \
       constexpr MatrixBase& operator OP (const MatrixBase<T, COL, ROW>& xi_mat) {  \
           m_data OP xi_mat.m_data;                                                 \
           return *this;                                                            \
       }

        M_OPERATOR(+= );
        M_OPERATOR(-= );
        M_OPERATOR(/= );
        M_OPERATOR(&= );
        M_OPERATOR(|= );
        M_OPERATOR(^= );
        M_OPERATOR(>>= );
        M_OPERATOR(<<= );

#undef M_OPERATOR

        // cubic matrix compound multiplication
        constexpr MatrixBase& operator *= (const MatrixBase<T, COL, ROW>& xi_mat) {
            static_assert(ROW == COL, " MatrixBase: compound multiplication (*=) can only be performed between cubic matrix's of equal dimensions.");

            if constexpr (COL == 2) {
                *this = { m_data[0] * xi_mat(0, 0) + m_data[2] * xi_mat(0, 1),
                          m_data[1] * xi_mat(0, 0) + m_data[3] * xi_mat(0, 1),
                          m_data[0] * xi_mat(1, 0) + m_data[2] * xi_mat(1, 1),
                          m_data[1] * xi_mat(1, 0) + m_data[3] * xi_mat(1, 1) };
            }
            else if constexpr (COL == 3) {
                *this = { m_data[0] * xi_mat(0, 0) + m_data[3] * xi_mat(0, 1) + m_data[6] * xi_mat(0, 2),
                          m_data[1] * xi_mat(0, 0) + m_data[4] * xi_mat(0, 1) + m_data[7] * xi_mat(0, 2),
                          m_data[2] * xi_mat(0, 0) + m_data[5] * xi_mat(0, 1) + m_data[8] * xi_mat(0, 2),
                          m_data[0] * xi_mat(1, 0) + m_data[3] * xi_mat(1, 1) + m_data[6] * xi_mat(1, 2),
                          m_data[1] * xi_mat(1, 0) + m_data[4] * xi_mat(1, 1) + m_data[7] * xi_mat(1, 2),
                          m_data[2] * xi_mat(1, 0) + m_data[5] * xi_mat(1, 1) + m_data[8] * xi_mat(1, 2),
                          m_data[0] * xi_mat(2, 0) + m_data[3] * xi_mat(2, 1) + m_data[6] * xi_mat(2, 2),
                          m_data[1] * xi_mat(2, 0) + m_data[4] * xi_mat(2, 1) + m_data[7] * xi_mat(2, 2),
                          m_data[2] * xi_mat(2, 0) + m_data[5] * xi_mat(2, 1) + m_data[8] * xi_mat(2, 2) };
            }
            else {
                for (std::size_t i{}; i < ROW; ++i) {
                    const VectorBase<T, COL> _row(getRow(i));

                    for (std::size_t j{}; j < COL; ++j) {
                        VectorBase<T, ROW> _col(xi_mat[j]);
                        this->operator()(j, i) = dot(_row, _col);
                    }
                }
            }
            return *this;
        }

        constexpr MatrixBase& operator *= (MatrixBase<T, COL, ROW>&& xi_mat) {
            static_assert(ROW == COL, " MatrixBase: compound multiplication (*=) can only be performed between cubic matrix's of equal dimensions.");

            if constexpr (COL == 2) {
                *this = { m_data[0] * xi_mat(0, 0) + m_data[2] * xi_mat(0, 1),
                          m_data[1] * xi_mat(0, 0) + m_data[3] * xi_mat(0, 1),
                          m_data[0] * xi_mat(1, 0) + m_data[2] * xi_mat(1, 1),
                          m_data[1] * xi_mat(1, 0) + m_data[3] * xi_mat(1, 1) };
            }
            else if constexpr (COL == 3) {
                *this = { m_data[0] * xi_mat(0, 0) + m_data[3] * xi_mat(0, 1) + m_data[6] * xi_mat(0, 2),
                          m_data[1] * xi_mat(0, 0) + m_data[4] * xi_mat(0, 1) + m_data[7] * xi_mat(0, 2),
                          m_data[2] * xi_mat(0, 0) + m_data[5] * xi_mat(0, 1) + m_data[8] * xi_mat(0, 2),
                          m_data[0] * xi_mat(1, 0) + m_data[3] * xi_mat(1, 1) + m_data[6] * xi_mat(1, 2),
                          m_data[1] * xi_mat(1, 0) + m_data[4] * xi_mat(1, 1) + m_data[7] * xi_mat(1, 2),
                          m_data[2] * xi_mat(1, 0) + m_data[5] * xi_mat(1, 1) + m_data[8] * xi_mat(1, 2),
                          m_data[0] * xi_mat(2, 0) + m_data[3] * xi_mat(2, 1) + m_data[6] * xi_mat(2, 2),
                          m_data[1] * xi_mat(2, 0) + m_data[4] * xi_mat(2, 1) + m_data[7] * xi_mat(2, 2),
                          m_data[2] * xi_mat(2, 0) + m_data[5] * xi_mat(2, 1) + m_data[8] * xi_mat(2, 2) };
            }
            else {
                for (std::size_t i{}; i < ROW; ++i) {
                    const VectorBase<T, COL> _row(getRow(i));

                    for (std::size_t j{}; j < COL; ++j) {
                        VectorBase<T, ROW> _col(xi_mat[j]);
                        this->operator()(j, i) = dot(_row, _col);
                    }
                }
            }
            return *this;
        }

        // stream operator overloading
    public:

        // output matrix elements to a stream
        friend std::ostream& operator<<(std::ostream& xio_stream, const MatrixBase& xi_mat) {
            xio_stream << "\n{\n";

            for (std::size_t i{}; i < ROW; ++i) {
                xio_stream << "{";
                for (std::size_t j{}; j < COL - 1; ++j) {
                    xio_stream << xi_mat(j, i) << ", ";
                }
                xio_stream << xi_mat(COL - 1, i) << "}\n";
            }

            return xio_stream << "\n}\n";
        }

        // element wise iterators
    public:

        auto begin()   noexcept -> decltype(m_data.begin()) { return m_data.m_data.begin(); }
        auto rbegin()  noexcept -> decltype(m_data.rbegin()) { return m_data.m_data.rbegin(); }
        auto cbegin()  noexcept -> decltype(m_data.cbegin()) { return m_data.m_data.cbegin(); }
        auto crbegin() noexcept -> decltype(m_data.crbegin()) { return m_data.m_data.crbegin(); }

        auto end()   noexcept -> decltype(m_data.end()) { return m_data.m_data.end(); }
        auto rend()  noexcept -> decltype(m_data.rend()) { return m_data.m_data.rend(); }
        auto cend()  noexcept -> decltype(m_data.cend()) { return m_data.m_data.cend(); }
        auto crend() noexcept -> decltype(m_data.crend()) { return m_data.m_data.crend(); }
    };

    /**
    * numerical operator overload
    **/

    // binary operations without multiplication
#define M_BINARY_OP_NO_LHS_SCALAR(OP, AOP)                                                                                                    \
    template<typename T, typename U, std::size_t COL, std::size_t ROW, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                             \
    constexpr inline MatrixBase<T, COL, ROW> operator OP (MatrixBase<T, COL, ROW>&& xi_mat, const U xi_value) {                               \
        xi_mat AOP xi_value;                                                                                                                  \
        return xi_mat;                                                                                                                        \
    }                                                                                                                                         \
    template<typename T, typename U, std::size_t COL, std::size_t ROW, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                             \
    constexpr inline MatrixBase<T, COL, ROW> operator OP (const MatrixBase<T, COL, ROW>& xi_mat, const U xi_value) {                          \
        auto xo_mat = FWD(xi_mat);                                                                                                            \
        xo_mat AOP xi_value;                                                                                                                  \
        return FWD(xo_mat);                                                                                                                   \
    }                                                                                                                                         \
    template<typename T, std::size_t COL, std::size_t ROW>                                                                                    \
    constexpr inline MatrixBase<T, COL, ROW> operator OP (const MatrixBase<T, COL, ROW>& xi_mat1, const MatrixBase<T, COL, ROW>& xi_mat2) {   \
        auto mat1 = FWD(xi_mat1);                                                                                                             \
        auto mat2 = FWD(xi_mat2);                                                                                                             \
        mat1 AOP mat2;                                                                                                                        \
        return FWD(mat1);                                                                                                                     \
    }

    M_BINARY_OP_NO_LHS_SCALAR(+, +=);
    M_BINARY_OP_NO_LHS_SCALAR(-, -=);
    M_BINARY_OP_NO_LHS_SCALAR(/ , /=);
    M_BINARY_OP_NO_LHS_SCALAR(&, &=);
    M_BINARY_OP_NO_LHS_SCALAR(| , |=);
    M_BINARY_OP_NO_LHS_SCALAR(^, ^=);
    M_BINARY_OP_NO_LHS_SCALAR(>> , >>=);
    M_BINARY_OP_NO_LHS_SCALAR(<< , <<=);

#undef M_BINARY_OP_NO_LHS_SCALAR

    // binary operations with left hand side scalar
#define M_BINARY_OP_WITH_LHS_SCALAR(OP, AOP)                                                                                       \
    template<typename T, typename U, std::size_t COL, std::size_t ROW, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                  \
    constexpr inline MatrixBase<T, COL, ROW> operator OP (MatrixBase<T, COL, ROW>&& xi_mat, const U xi_value) {                    \
        xi_mat AOP xi_value;                                                                                                       \
        return xi_mat;                                                                                                             \
    }                                                                                                                              \
    template<typename T, typename U, std::size_t COL, std::size_t ROW, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                  \
    constexpr inline MatrixBase<T, COL, ROW> operator OP (const MatrixBase<T, COL, ROW>& xi_mat, const U xi_value) {               \
        auto xo_mat = FWD(xi_mat);                                                                                                 \
        xo_mat AOP xi_value;                                                                                                       \
        return FWD(xo_mat);                                                                                                        \
    }                                                                                                                              \
    template<typename T, typename U, std::size_t COL, std::size_t ROW, REQUIRE(is_ArithmeticConvertible_v<U, T>::value)>           \
    constexpr inline MatrixBase<T, COL, ROW> operator OP (const U xi_value, MatrixBase<T, COL, ROW>&& xi_mat) {                    \
        xi_mat AOP xi_value;                                                                                                       \
        return xi_mat;                                                                                                             \
    }                                                                                                                              \
    template<typename T, typename U, std::size_t COL, std::size_t ROW, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                  \
    constexpr inline MatrixBase<T, COL, ROW> operator OP (const U xi_value, const MatrixBase<T, COL, ROW>& xi_mat) {               \
        auto xo_mat = FWD(xi_mat);                                                                                                 \
        xo_mat AOP xi_value;                                                                                                       \
        return FWD(xo_mat);                                                                                                        \
    }

    M_BINARY_OP_WITH_LHS_SCALAR(*, *=);

#undef M_BINARY_OP_WITH_LHS_SCALAR

    // cubic matrix multiplication
    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr inline T operator * (const T& xi_lhs, const T& xi_rhs) {
        auto lhs = FWD(xi_lhs);
        lhs *= xi_rhs;
        return FWD(lhs);
    }

    template<typename T, REQUIRE(is_Cubic<T>::value)>
    constexpr inline T operator * (T&& xi_lhs, const T& xi_rhs) {
        xi_lhs *= xi_rhs;
        return xi_lhs;
    }

    // matrix * vector (i.e - right multiply a matrix by a vector; vector is treated as column vector)
    // (row X 1) = (row X col) * (1 X col)
    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (COL == 2))>
    constexpr inline VectorBase<T, ROW> operator * (const MatrixBase<T, COL, ROW>& xi_mat, const VectorBase<T, COL>& xi_vec) {
        return VectorBase<T, 2>(xi_mat(0, 0) * xi_vec[0] + xi_mat(1, 0) * xi_vec[1],
                                xi_mat(0, 1) * xi_vec[0] + xi_mat(1, 1) * xi_vec[1]);
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (COL == 3))>
    constexpr inline VectorBase<T, ROW> operator * (const MatrixBase<T, COL, ROW>& xi_mat, const VectorBase<T, COL>& xi_vec) {
        return VectorBase<T, 3>(xi_mat(0, 0) * xi_vec[0] + xi_mat(1, 0) * xi_vec[1] + xi_mat(2, 0) * xi_vec[2],
                                xi_mat(0, 1) * xi_vec[0] + xi_mat(1, 1) * xi_vec[1] + xi_mat(2, 1) * xi_vec[2],
                                xi_mat(0, 2) * xi_vec[0] + xi_mat(1, 2) * xi_vec[1] + xi_mat(2, 2) * xi_vec[2]);
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (COL == 4))>
    constexpr inline VectorBase<T, ROW> operator * (const MatrixBase<T, COL, ROW>& xi_mat, const VectorBase<T, COL>& xi_vec) {
        return VectorBase<T, 4>(xi_mat(0, 0) * xi_vec[0] + xi_mat(1, 0) * xi_vec[1] + xi_mat(2, 0) * xi_vec[2] + xi_mat(3, 0) * xi_vec[3],
                                xi_mat(0, 1) * xi_vec[0] + xi_mat(1, 1) * xi_vec[1] + xi_mat(2, 1) * xi_vec[2] + xi_mat(3, 1) * xi_vec[3],
                                xi_mat(0, 2) * xi_vec[0] + xi_mat(1, 2) * xi_vec[1] + xi_mat(2, 2) * xi_vec[2] + xi_mat(3, 2) * xi_vec[3],
                                xi_mat(0, 3) * xi_vec[0] + xi_mat(1, 3) * xi_vec[1] + xi_mat(2, 3) * xi_vec[2] + xi_mat(3, 3) * xi_vec[3]);
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL != ROW) || ((COL == ROW) && (COL > 4)))>
    constexpr VectorBase<T, ROW> operator * (const MatrixBase<T, COL, ROW>& xi_mat, const VectorBase<T, COL>& xi_vec) {
        VectorBase<T, ROW> xo_vec;

        for (std::size_t i{}; i < ROW; ++i) {
            T _sum{}; 

            for (std::size_t j{}; j < COL; ++j) {
                _sum += xi_mat(j, i) * xi_vec[j];
            }

            xo_vec[i] = _sum;
        }

        return xo_vec;
    }

    // vector * matrix (i.e - left multiply a matrix by a vector; vector is treated as row vector)
    // (1 X col) = (1 X row) * (row X col)
    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (COL == 2))>
    constexpr inline VectorBase<T, COL> operator * (const VectorBase<T, ROW>& xi_vec, const MatrixBase<T, COL, ROW>& xi_mat) {
        return VectorBase<T, 2>(xi_vec[0] * xi_mat(0, 0) + xi_vec[1] * xi_mat(0, 1),
                                xi_vec[0] * xi_mat(1, 0) + xi_vec[1] * xi_mat(1, 1));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (COL == 3))>
    constexpr inline VectorBase<T, COL> operator * (const VectorBase<T, ROW>& xi_vec, const MatrixBase<T, COL, ROW>& xi_mat) {
        return VectorBase<T, 3>(xi_vec[0] * xi_mat(0, 0) + xi_vec[1] * xi_mat(0, 1) + xi_vec[2] * xi_mat(0, 2),
                                xi_vec[0] * xi_mat(1, 0) + xi_vec[1] * xi_mat(1, 1) + xi_vec[2] * xi_mat(1, 2),
                                xi_vec[0] * xi_mat(2, 0) + xi_vec[1] * xi_mat(2, 1) + xi_vec[2] * xi_mat(2, 2));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL == ROW) && (COL == 4))>
    constexpr inline VectorBase<T, COL> operator * (const VectorBase<T, ROW>& xi_vec, const MatrixBase<T, COL, ROW>& xi_mat) {
        return VectorBase<T, 4>(xi_vec[0] * xi_mat(0, 0) + xi_vec[1] * xi_mat(0, 1) + xi_vec[2] * xi_mat(0, 2) + xi_vec[3] * xi_mat(0, 3),
                                xi_vec[0] * xi_mat(1, 0) + xi_vec[1] * xi_mat(1, 1) + xi_vec[2] * xi_mat(1, 2) + xi_vec[3] * xi_mat(1, 3),
                                xi_vec[0] * xi_mat(2, 0) + xi_vec[1] * xi_mat(2, 1) + xi_vec[2] * xi_mat(2, 2) + xi_vec[3] * xi_mat(2, 3),
                                xi_vec[0] * xi_mat(3, 0) + xi_vec[1] * xi_mat(3, 1) + xi_vec[2] * xi_mat(3, 2) + xi_vec[3] * xi_mat(3, 3));
    }

    template<typename T, std::size_t COL, std::size_t ROW, REQUIRE((COL != ROW) || ((COL == ROW) && (COL > 4)))>
    constexpr VectorBase<T, COL> operator * (const VectorBase<T, ROW>& xi_vec, const MatrixBase<T, COL, ROW>& xi_mat) {
        VectorBase<T, COL> xo_vec;

        for (std::size_t i{}; i < COL; ++i) {
            T _sum{};

            for (std::size_t j{}; j < ROW; ++j) {
                _sum += xi_mat(i, j) * xi_vec[j];
            }

            xo_vec[i] = _sum;
        }

        return xo_vec;
    }

    // rectangular matrix-matrix multiplication
    // (col x row) = (dim x row) * (col * dim)
    template<typename T, std::size_t COL, std::size_t ROW, std::size_t DIM, REQUIRE((DIM > 1) &&
                                                                                    (COL > 1) &&    
                                                                                    (ROW > 1) &&
                                                                                    (COL != ROW) && 
                                                                                    (COL != DIM) && 
                                                                                    (ROW != DIM) && 
                                                                                    std::is_arithmetic_v<T>)>
    constexpr MatrixBase<T, COL, ROW> operator * (const MatrixBase<T, DIM, ROW>& xi_lhs, const MatrixBase<T, COL, DIM>& xi_rhs) {
        MatrixBase<T, COL, ROW> xo_mat(0);

        for (std::size_t i{}; i < ROW; ++i) {
            for (std::size_t j{}; j < COL; ++j) {
                T _sum{};

                for (std::size_t d{}; d < DIM; ++d) {
                    _sum += xi_lhs(d, i) * xi_rhs(j, d);
                }

                xo_mat(j, i) = _sum;
            }
        }

        return xo_mat;
    }
}; // namespace GLSLCPP

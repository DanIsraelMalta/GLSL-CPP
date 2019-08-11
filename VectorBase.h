/**
* GLSL++
*
* Dan Israel Malta
**/
#pragma once
#include "common.h"
#include <array>
#include <algorithm>
#include <execution>
#include <assert.h>
#include <iostream>
#include <string>

namespace GLSLCPP {

    /**
    * \brief fixed size numerical vector
    *
    * @param {T, in} underlying type
    * @param {N, in} size
    **/
    template<typename T, std::size_t N> class VectorBase {
        static_assert(std::is_arithmetic<T>::value, "VectorBase<T,N> - T must be of numerical type.");

        // properties
    public:
        alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) std::array<T, N> m_data{};

        // constructors
    public:

        // default constructor
        VectorBase() : m_data() {}

        // construct using a single value
        template<typename U> explicit constexpr
        VectorBase(const U xi_value = U{}, REQUIRE(is_ArithmeticConvertible_v<U, T>)) {
            m_data.fill(static_cast<T>(xi_value));
        }

        // construct using N individual values (of same type)
        template<typename ...Us, REQUIRE((sizeof...(Us) == N) && Are_ArithmeticConvertible<T, Us...>::value)>
        explicit constexpr VectorBase(Us... xi_values) : m_data({ static_cast<T>(xi_values)... }) {}

        // construct from a swizzle
        template<typename U> explicit constexpr VectorBase(U&& s, REQUIRE(is_SwizzleOfLength_v<U, N>)) {
            s.Pack(std::forward<U>(m_data));
        }

        // construct from any Vector object (copied object size must be equal or larger to constructed one size)
        template<typename U> explicit constexpr VectorBase(const U& v, REQUIRE(Is_VectorOfLength_v<U, N>)) {
            for_each(m_data, [&, i = 0](auto & elm) mutable {
                elm = static_cast<T>(v[i]);
                ++i;
            });
        }
        template<typename U> explicit constexpr VectorBase(U& v, REQUIRE(Is_VectorOfLength_v<U, N>)) {
            for_each(m_data, [&, i = 0](auto & elm) mutable {
                elm = static_cast<T>(std::move(v[i]));
                ++i;
            });
        }

        // construct based upon a function whos input argument is element index
        constexpr explicit VectorBase(const std::function<T(std::size_t)>& xi_func) {
            for_each(m_data, [&, i = 0](auto & elm) mutable {
                elm = xi_func(i);
                ++i;
            });
        }
        constexpr explicit VectorBase(std::function<T(std::size_t)>&& xi_func) {
            for_each(m_data, [&, i = 0](auto & elm) mutable {
                elm = xi_func(i);
                ++i;
            });
        }

        // assign a function whos input argument is element index
        VectorBase& operator = (const std::function<T(std::size_t)>& xi_func) {
            for_each(m_data, [&, i = 0](auto & elm) mutable {
                elm = xi_func(i);
                ++i;
            });
            return *this;
        }
        VectorBase& operator = (std::function<T(std::size_t)>&& xi_func) {
            for_each(m_data, [&, i = 0](auto & elm) mutable {
                elm = xi_func(i);
                ++i;
            });
            return *this;
        }

        // copy semantics
        VectorBase(const VectorBase&) = default;
        VectorBase& operator=(const VectorBase&) = default;

        // move semantics
        VectorBase(VectorBase&&)            noexcept = default;
        VectorBase& operator=(VectorBase&&) noexcept = default;

        // operator overloading
    public:

        // '[]' element access
        constexpr T  operator[](const std::size_t i) const { assert(i < N && " attempting tp access an out-of-region index"); return m_data[i]; }
        constexpr T& operator[](const std::size_t i)       { assert(i < N && " attempting tp access an out-of-region index"); return m_data[i]; }

        // castings 
    public:

        // cast to Vector2
        template<typename U, std::size_t M = N, REQUIRE(M >= 2)> operator Vector2<U>() const {
            return Vector2<U>(m_data[0], m_data[1]);
        }

        // cast to Vector3
        template<typename U, std::size_t M = N, REQUIRE(M >= 3)> operator Vector3<U>() const {
            return Vector3<U>(m_data[0], m_data[1], m_data[2]);
        }

        // cast to Vector4
        template<typename U, std::size_t M = N, REQUIRE(M >= 4)> operator Vector4<U>() const {
            return Vector4<U>(m_data[0], m_data[1], m_data[2], m_data[3]);
        }

        // iterators
    public:

        auto begin()   noexcept -> decltype(m_data.begin()) { return m_data.begin(); }
        auto rbegin()  noexcept -> decltype(m_data.rbegin()) { return m_data.rbegin(); }
        auto cbegin()  noexcept -> decltype(m_data.cbegin()) { return m_data.cbegin(); }
        auto crbegin() noexcept -> decltype(m_data.crbegin()) { return m_data.crbegin(); }

        auto end()   noexcept -> decltype(m_data.end()) { return m_data.end(); }
        auto rend()  noexcept -> decltype(m_data.rend()) { return m_data.rend(); }
        auto cend()  noexcept -> decltype(m_data.cend()) { return m_data.cend(); }
        auto crend() noexcept -> decltype(m_data.crend()) { return m_data.crend(); }

        // assignment operations
    public:

        // assign an element
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)> constexpr VectorBase& operator=(const U xi_value) {
            for_each(m_data, [this, v = static_cast<T>(xi_value)](auto & elm) {
                elm = v;
            });
            return *this;
        }

        // assign a swizzle
        template<typename U, REQUIRE(is_SwizzleOfLength_v<U, N>)> constexpr VectorBase& operator=(U&& s) {
            VectorBase<T, N> temp(s);
            m_data = std::move(temp.m_data);
            return *this;
        }

        // query operations
    public:

        // extract vector size
        constexpr std::size_t length() const noexcept { return N; }

        // compound operators
    public:

#define M_OPERATOR(OP)                                                                                                            \
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                                                           \
        constexpr VectorBase& operator OP (const U xi_value) {                                                                    \
            for_each(m_data, [this, xi_value](auto& elm) {                                                                        \
                elm OP static_cast<T>(xi_value);                                                                                  \
            });                                                                                                                   \
            return *this;                                                                                                         \
        }                                                                                                                         \
        template<typename U> constexpr inline VectorBase& operator OP (const VectorBase<U, N>& xi_vector) {                       \
            for_each(m_data, [this, xi_vector, i = 0](auto& elm) mutable {                                                        \
                elm OP static_cast<T>(xi_vector[i]);                                                                              \
                ++i;                                                                                                              \
            });                                                                                                                   \
            return *this;                                                                                                         \
        }                                                                                                                         \
        template<typename U> constexpr inline VectorBase& operator OP (VectorBase<U, N>&& xi_vector) {                            \
            for_each(m_data, [this, xi_vector, i = 0](auto& elm) mutable {                                                        \
                elm OP std::move(static_cast<T>(xi_vector[i]));                                                                   \
                ++i;                                                                                                              \
            });                                                                                                                   \
            return *this;                                                                                                         \
        }                                                                                                                         \
        template<typename U, REQUIRE(is_SwizzleOfLength_v<U, N>)> constexpr VectorBase& operator OP (U s) {                       \
            VectorBase<T, N>&& temp(s);                                                                                           \
            for_each(m_data, [this, t = temp, i = 0](auto& elm) mutable {                                                         \
                elm OP t[i];                                                                                                      \
                ++i;                                                                                                              \
            });                                                                                                                   \
            return *this;                                                                                                         \
        }

        M_OPERATOR(-= );
        M_OPERATOR(+= );
        M_OPERATOR(*= );
        M_OPERATOR(/= );
        M_OPERATOR(&= );
        M_OPERATOR(|= );
        M_OPERATOR(^= );
        M_OPERATOR(>>= );
        M_OPERATOR(<<= );
#undef M_OPERATOR

        // stream operator overloading
    public:

        // output vector to stream
        friend std::ostream& operator<<(std::ostream& xio_stream, VectorBase& xi_vector) {
            xio_stream << "{";

            if (isVectorLalue(xi_vector)) {
                for (std::size_t i{}; i < N - 1; ++i) {
                    xio_stream << std::to_string(xi_vector[i]) << ", ";
                }
                xio_stream << xi_vector[N - 1] << "}";
            }
            else {
                for (std::size_t i{}; i < N - 1; ++i) {
                    xio_stream << std::to_string(std::move(xi_vector[i])) << ", ";
                }
                xio_stream << std::move(xi_vector[N - 1]) << "}";
            }
            return xio_stream;
        }

        // read the space-separated components of a vector from a stream
        friend std::istream& operator>>(std::istream & is, VectorBase & xi_vector) {
            if (isVectorLalue(xi_vector)) {
                for (std::size_t i{}; i < N; ++i) {
                    is >> xi_vector[i];
                }
            }
            else {
                for (std::size_t i{}; i < N; ++i) {
                    is >> std::move(xi_vector[i]);
                }
            }

            return is;
        }
    };

#define M_OPERATOR(OP, AOP)                                                                                              \
    template<typename T, typename U, std::size_t N, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                           \
    constexpr inline VectorBase<T, N> operator OP (VectorBase<T, N> xi_lhs, const U xi_rhs) {                            \
        xi_lhs AOP xi_rhs;                                                                                               \
        return xi_lhs;                                                                                                   \
    }                                                                                                                    \
    template<typename T, typename U, std::size_t N, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                           \
    constexpr inline VectorBase<T, N> operator OP (const U xi_lhs, VectorBase<T, N> xi_rhs) {                            \
        xi_rhs AOP xi_lhs;                                                                                               \
        return xi_rhs;                                                                                                   \
    }                                                                                                                    \
    template<typename T, std::size_t N>                                                                                  \
    constexpr inline VectorBase<T, N> operator OP (VectorBase<T, N> xi_lhs, const VectorBase<T, N>& xi_rhs) {            \
        xi_lhs AOP xi_rhs;                                                                                               \
        return xi_lhs;                                                                                                   \
    }                                                                                                                    \
    template<typename T, std::size_t N>                                                                                  \
    constexpr inline VectorBase<T, N> operator OP (const VectorBase<T, N>& xi_lhs, VectorBase<T, N>&& xi_rhs) {          \
        xi_rhs AOP xi_lhs;                                                                                               \
        return xi_rhs;                                                                                                   \
    }                                                                                                                    \
    template<typename T, typename U, std::size_t N, REQUIRE(is_Swizzle_v<U>)>                                            \
    constexpr inline VectorBase<T, N> operator OP (VectorBase<T, N> xi_lhs, U& xi_rhs) {                                 \
        xi_lhs AOP xi_rhs;                                                                                               \
        return xi_lhs;                                                                                                   \
    }                                                                                                                    \
    template<typename T, typename U, std::size_t N, REQUIRE(is_Swizzle_v<U>)>                                            \
    constexpr inline VectorBase<T, N> operator OP (U& xi_lhs, VectorBase<T, N> xi_rhs) {                                 \
        xi_rhs AOP xi_lhs;                                                                                               \
        return xi_rhs;                                                                                                   \
    }

    M_OPERATOR(+, +=);
    M_OPERATOR(-, -=);
    M_OPERATOR(*, *=);
    M_OPERATOR(/ , /=);
    M_OPERATOR(&, &=);
    M_OPERATOR(| , |=);
    M_OPERATOR(^, ^=);
    M_OPERATOR(>> , >>=);
    M_OPERATOR(<< , <<=);

#undef M_OPERATOR
};  // namespace GLSLCPP
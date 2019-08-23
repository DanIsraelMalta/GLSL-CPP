/**
* GLSL++
*
* Dan Israel Malta
**/
#pragma once
#include "common.h"
#include "VectorBase.h"
#include "Swizzle.h"
#include <string>

// notice using anonymous structs is supported in c11 (so MSVC should only throw a warning)
// and is supported via extension in GCC/CLANG
#pragma warning(disable : 4201)

namespace GLSLCPP {

    /**
    * \brief 2 elements numerical vector
    *
    * @param {T, in} underlying type
    **/
    template<typename T> union Vector2 {

        // data structure
    public:
        union {
            VectorBase<T, 2> m_data{};

            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T x, y; };
            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T r, g; };
            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T s, t; };

            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> xx;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 1> xy;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 0> yx;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> yy;

            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> rr;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 1> rg;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 0> gr;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> gg;

            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> ss;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 1> st;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 0> ts;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> tt;
        };

        // query operations
    public:

        // extract vector size
        constexpr std::size_t length() const noexcept { return 2; }

        // constructors
    public:

        // default constructor
        Vector2() : m_data() {}

        // construct using 1 value
        template<typename U> explicit constexpr Vector2(const U xi_value = U{}, REQUIRE(is_ArithmeticConvertible_v<U, T>)) : m_data(xi_value) {}

        // construct using 2 values (of same type)
        template<typename ...Us, REQUIRE((sizeof...(Us) == 2) && Are_ArithmeticConvertible<T, Us...>::value)> explicit constexpr Vector2(Us... xi_values) : m_data(xi_values...) {}

        // construct using 2 values (of different type)
        template<typename U, typename V> explicit constexpr Vector2(const U u, const V v, REQUIRE(Are_ArithmeticConvertible<T, U, V>::value)) :
            m_data(static_cast<T>(u), static_cast<T>(v)) {}

        // construct from a swizzle
        template<typename U> explicit constexpr Vector2(U&& s, REQUIRE(is_SwizzleOfLength_v<U, 2>)) : m_data(std::forward<U>(s)) {}

        // construct from a different type vector
        template<typename U> explicit constexpr Vector2(const U& v, REQUIRE(Is_VectorOfLength_v<U, 2>)) {
            static_for<0, 2>([&](std::size_t i) {
                m_data[i] = static_cast<T>(v[i]);
            });
        }
        template<typename U> explicit constexpr Vector2(U&& v, REQUIRE(Is_VectorOfLength_v<U, 2>)) noexcept {
            static_for<0, 2>([&](std::size_t i) {
                m_data[i] = static_cast<T>(std::move(v[i]));
            });
        }

        // copy semantics
        Vector2(const Vector2&)            = default;
        Vector2& operator=(const Vector2&) = default;

        // move semantics
        Vector2(Vector2&&)            noexcept = default;
        Vector2& operator=(Vector2&&) noexcept = default;

        // cast as VectorBase
        template<typename U> operator VectorBase<U, 2>() const {
            return VectorBase<U, 2>(static_cast<U>(x), static_cast<U>(y));
        }

        // access operator overloading
    public:

        // '[]' element access
        constexpr T  operator[](const std::size_t i) const { assert(i < 2); return m_data[i]; }
        constexpr T& operator[](const std::size_t i)       { assert(i < 2); return m_data[i]; }

        // get pointer to vector internal storage
        constexpr       T* data()       { return m_data; }
        constexpr const T* data() const { return m_data; } 

        // iterators
    public:

        auto begin()   noexcept -> decltype(m_data.begin())   { return m_data.begin();   }
        auto rbegin()  noexcept -> decltype(m_data.rbegin())  { return m_data.rbegin();  }
        auto cbegin()  noexcept -> decltype(m_data.cbegin())  { return m_data.cbegin();  }
        auto crbegin() noexcept -> decltype(m_data.crbegin()) { return m_data.crbegin(); }

        auto end()   noexcept -> decltype(m_data.end())   { return m_data.end();   }
        auto rend()  noexcept -> decltype(m_data.rend())  { return m_data.rend();  }
        auto cend()  noexcept -> decltype(m_data.cend())  { return m_data.cend();  }
        auto crend() noexcept -> decltype(m_data.crend()) { return m_data.crend(); }

        // stream operator overloading
    public:

        // output vector to stream
        friend std::ostream& operator<<(std::ostream& xio_stream, Vector2& xi_vector) {
            return xio_stream << xi_vector.m_data;
        }

        // read the space-separated components of a vector from a stream
        friend std::istream& operator>>(std::istream& is, Vector2& xi_vector) {
            if (isVectorLalue(xi_vector)) {
                for (std::size_t i{}; i < 2; ++i) {
                    is >> xi_vector[i];
                }
            }
            else {
                for (std::size_t i{}; i < 2; ++i) {
                    is >> std::move(xi_vector[i]);
                }
            }

            return is;
        }

        // compound operator overloading
    public:

#define M_OPERATOR(OP)                                                                                  \
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                                 \
        constexpr Vector2& operator OP (const U xi_value) {                                             \
            m_data OP xi_value;                                                                         \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector2& operator OP (const Vector2<U>& xi_vector) {             \
            m_data OP xi_vector.m_data;                                                                 \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector2& operator OP (Vector2<U>&& xi_vector) {                  \
            m_data OP std::move(xi_vector.m_data);                                                      \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector2& operator OP (const VectorBase<U, 2>& xi_vector) {       \
            m_data OP xi_vector;                                                                        \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector2& operator OP (VectorBase<U, 2>&& xi_vector) {            \
            m_data OP std::move(xi_vector);                                                             \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U, REQUIRE(is_SwizzleOfLength_v<U, 2>)>                                       \
        constexpr Vector2& operator OP (U& s) {                                                         \
            m_data OP s;                                                                                \
            return *this;                                                                               \
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
    };

    // unary minus
    template<typename T> constexpr inline Vector2<T> operator - (const Vector2<T>& xi_vec) {
        auto v = FWD(xi_vec);
        v *= static_cast<T>(-1.0);
        return std::forward<Vector2<T>>(v);
    }

    template<typename T> constexpr inline Vector2<T> operator - (const VectorBase<T, 2> & xi_vec) {
        auto v = FWD(xi_vec);
        v *= static_cast<T>(-1.0);
        return Vector2<T>(v);
    }

    template<typename T, typename U, REQUIRE(is_SwizzleOfLength_v<U, 2>)>
    constexpr inline Vector2<T> operator - (U & s) {
        Vector2<T> xo_vec(s);
        xo_vec = -xo_vec;
        return xo_vec;
    }

}; // namespace GLSLCPP

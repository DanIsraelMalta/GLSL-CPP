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
    * \brief 3 elements numerical vector
    *
    * @param {T, in} underlying type
    **/
    template<typename T> union Vector3 {

        // data structure
    public:
        union {
            VectorBase<T, 3> m_data{};

            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T x, y, z; };
            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T r, g, b; };
            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T s, t, p; };

            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> xx;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 1> xy;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 2> xz;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 0> yx;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> yy;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 2> yz;
            Swizzle<VectorBase<T, 2>, T, 2, true, 2, 0> zx;
            Swizzle<VectorBase<T, 2>, T, 2, true, 2, 1> zy;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 2> zz;

            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> rr;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 1> rg;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 2> rb;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 0> gr;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> gg;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 2> gb;
            Swizzle<VectorBase<T, 2>, T, 2, true, 2, 0> br;
            Swizzle<VectorBase<T, 2>, T, 2, true, 2, 1> bg;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 2> bb;

            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> ss;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 1> st;
            Swizzle<VectorBase<T, 2>, T, 2, true, 0, 2> sp;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 0> ts;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> tt;
            Swizzle<VectorBase<T, 2>, T, 2, true, 1, 2> tp;
            Swizzle<VectorBase<T, 2>, T, 2, true, 2, 0> ps;
            Swizzle<VectorBase<T, 2>, T, 2, true, 2, 1> pt;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 2> pp;

            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 0> xxx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 1> xxy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 2> xxz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 0> xyx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 1> xyy;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 2> xyz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 0> xzx;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 1> xzy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 2> xzz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 0> yxx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 1> yxy;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 2> yxz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 0> yyx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 1> yyy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 2> yyz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 0> yzx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 1> yzy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 2> yzz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 0> zxx;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 1> zxy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 2> zxz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 0> zyx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 1> zyy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 2> zyz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 0> zzx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 1> zzy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 2> zzz;

            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 0> rrr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 1> rrg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 2> rrb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 0> rgr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 1> rgg;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 2> rgb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 0> rbr;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 1> rbg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 2> rbb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 0> grr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 1> grg;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 2> grb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 0> ggr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 1> ggg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 2> ggb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 0> gbr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 1> gbg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 2> gbb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 0> brr;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 1> brg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 2> brb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 0> bgr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 1> bgg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 2> bgb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 0> bbr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 1> bbg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 2> bbb;

            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 0> sss;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 1> sst;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 2> ssp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 0> sts;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 1> stt;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 2> stp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 0> sps;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 1> spt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 2> spp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 0> tss;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 1> tst;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 2> tsp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 0> tts;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 1> ttt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 2> ttp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 0> tps;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 1> tpt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 2> tpp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 0> pss;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 1> pst;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 2> psp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 0> pts;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 1> ptt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 2> ptp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 0> pps;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 1> ppt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 2> ppp;
        };

        // query operations
    public:

        // extract vector size
        constexpr std::size_t length() const noexcept { return 3; }

        // constructors
    public:

        // default constructor
        Vector3() : m_data() {}

        // construct using 1 value
        template<typename U> explicit constexpr Vector3(const U xi_value = U{}, REQUIRE(is_ArithmeticConvertible_v<U, T>)) : m_data(xi_value) {}

        // construct using 3 values (of same type)
        template<typename ...Us, REQUIRE((sizeof...(Us) == 3) && Are_ArithmeticConvertible<T, Us...>::value)> explicit constexpr Vector3(Us... xi_values) : m_data(xi_values...) {}

        // construct using 3 values (of different type)
        template<typename U, typename V, typename W> explicit constexpr Vector3(const U u, const V v, const W w, REQUIRE(Are_ArithmeticConvertible<T, U, V, W>::value)) :
            m_data(static_cast<T>(u), static_cast<T>(v), static_cast<T>(w)) {}

        // construct using a VectorBase<U,2> child and a scalar
        template<typename U, typename V> explicit constexpr Vector3(U&& vec, const V s, REQUIRE(is_ArithmeticConvertible_v<V, T> && Is_VectorOfLength_v<U,2>)) :
            m_data(static_cast<T>(vec[0]), static_cast<T>(vec[1]), static_cast<T>(s)) {}

        template<typename U, typename V> explicit constexpr Vector3(const V s, U&& vec, REQUIRE(is_ArithmeticConvertible_v<V, T>&& Is_VectorOfLength_v<U, 2>)) :
            m_data(static_cast<T>(s), static_cast<T>(vec[0]), static_cast<T>(vec[1])) {}

        // construct using a swizzle and a scalar
        template<typename U, typename V> explicit constexpr Vector3(U& swiz, const V scalar, REQUIRE(is_ArithmeticConvertible_v<V, T>)) :
            Vector3<T>(VectorBase<T, 2>(swiz), scalar) {}

        template<typename U, typename V> explicit constexpr Vector3(const V scalar, U& swiz,
            REQUIRE(is_ArithmeticConvertible_v<V, T> && is_SwizzleOfLength_v<U, 2>)) :
            Vector3<T>(scalar, VectorBase<T, 2>(swiz)) {}

        // construct from a swizzle
        template<typename U> explicit constexpr Vector3(U& s, REQUIRE(is_Swizzle_v<U> && (Length_v<U> == 3))) : m_data(s) {}

        // construct from a different type vector
        template<typename U> explicit constexpr Vector3(const U& v, REQUIRE(Is_VectorOfLength_v<U, 3>)) {
            static_for<0, 3>([&](std::size_t i) {
                m_data[i] = static_cast<T>(v[i]);
            });
        }
        template<typename U> explicit constexpr Vector3(U&& v, REQUIRE(Is_VectorOfLength_v<U, 3>)) noexcept {
            static_for<0, 3>([&](std::size_t i) {
                m_data[i] = static_cast<T>(std::move(v[i]));
            });
        }

        // copy semantics
        Vector3(const Vector3&)            = default;
        Vector3& operator=(const Vector3&) = default;

        // move semantics
        Vector3(Vector3&&)            noexcept = default;
        Vector3& operator=(Vector3&&) noexcept = default;

        // casting
        template<typename U> operator VectorBase<U, 3>() const {
            return VectorBase<U, 3>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
        }

        // access operator overloading
    public:

        // '[]' element access
        constexpr T  operator[](const std::size_t i) const { assert(i < 3); return m_data[i]; }
        constexpr T& operator[](const std::size_t i)       { assert(i < 3); return m_data[i]; }

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
        friend std::ostream& operator<<(std::ostream& xio_stream, Vector3& xi_vector) {
            return xio_stream << xi_vector.m_data;
        }

        // read the space-separated components of a vector from a stream
        friend std::istream& operator>>(std::istream& is, Vector3& xi_vector) {
            if (isVectorLalue(xi_vector)) {
                for (std::size_t i{}; i < 3; ++i) {
                    is >> xi_vector[i];
                }
            }
            else {
                for (std::size_t i{}; i < 3; ++i) {
                    is >> std::move(xi_vector[i]);
                }
            }

            return is;
        }

        // compound operator overloading
    public:

#define M_OPERATOR(OP)                                                                                  \
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                                 \
        constexpr Vector3& operator OP (const U xi_value) {                                             \
            m_data OP xi_value;                                                                         \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector3& operator OP (const Vector3<U>& xi_vector) {             \
            m_data OP xi_vector.m_data;                                                                 \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector3& operator OP (Vector3<U>&& xi_vector) {                  \
            m_data OP std::move(xi_vector.m_data);                                                      \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector3& operator OP (const VectorBase<U, 3>& xi_vector) {       \
            m_data OP xi_vector;                                                                        \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector3& operator OP (VectorBase<U, 3>&& xi_vector) {            \
            m_data OP std::move(xi_vector);                                                             \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U, REQUIRE(is_SwizzleOfLength_v<U, 3>)>                                       \
        constexpr Vector3& operator OP (U& s) {                                                         \
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
    template<typename T> constexpr inline Vector3<T> operator - (const Vector3<T>& xi_vec) {
        auto v = FWD(xi_vec);
        v *= static_cast<T>(-1.0);
        return FWD(v);
    }

    template<typename T> constexpr inline Vector3<T> operator - (const VectorBase<T, 3> & xi_vec) {
        auto v = FWD(xi_vec);
        v *= static_cast<T>(-1.0);
        return Vector3<T>(v);
    }

    template<typename T, typename U, REQUIRE(is_SwizzleOfLength_v<U, 3>)>
    constexpr inline Vector3<T> operator - (U & s) {
        Vector3<T> xo_vec(s);
        xo_vec *= -xo_vec;
        return xo_vec;
    }
}; // namespace GLSLCPP

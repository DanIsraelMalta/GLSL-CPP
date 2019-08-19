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
    template<typename T> class Vector2 : public VectorBase<T, 2> {

        // data structure
    public:
        union {
            alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) std::array<T, 2> m_data{};

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

        // internal helper
    private:

        // get parent properties
        void CopyParentData() noexcept {
            std::copy(VectorBase<T, 2>::m_data.begin(), VectorBase<T, 2>::m_data.end(), Vector2::m_data.begin());
        }

        // fill Vector2 from VectorBase
        void FromVectorBase(VectorBase<T, 2>&& xi_base) noexcept {
            m_data = std::move(xi_base.m_data);
        }

        // query operations
    public:

        // extract vector size
        constexpr std::size_t length() const noexcept { return 2; }

        // constructors
    public:

        // default constructor
		Vector2() : m_data() {}
        
        // construct using 1 value
        template<typename U> explicit constexpr Vector2(const U xi_value = U{}, REQUIRE(is_ArithmeticConvertible_v<U, T>)) : VectorBase<T, 2>(xi_value) { CopyParentData(); }

        // construct using 2 values (of same type)
        template<typename ...Us, REQUIRE((sizeof...(Us) == 2) && Are_ArithmeticConvertible<T, Us...>::value)> explicit constexpr Vector2(Us... xi_values) : VectorBase<T, 2>(xi_values...) { CopyParentData(); }

        // construct using 2 values (of different type)
        template<typename U, typename V> explicit constexpr Vector2(const U u, const V v, REQUIRE(Are_ArithmeticConvertible<T, U, V>::value)) :
            VectorBase<T, 2>(static_cast<T>(u), static_cast<T>(v)) { CopyParentData(); }

        // construct from a swizzle
        template<typename U> explicit constexpr Vector2(U&& s, REQUIRE(is_SwizzleOfLength_v<U, 2>)) : VectorBase<T, 2>(std::forward<U>(s)) { CopyParentData(); }

        // cast as VectorBase
        operator VectorBase<T, 2>() const {
            return VectorBase<T, 2>(m_data);
        }

        // assignments
    public:

        template<typename U, std::size_t M, REQUIRE(M >= 2)> constexpr Vector2& operator=(VectorBase<U, M>&& v) noexcept {
            for_each(m_data, [this, i = 0, temp = FWD(v)](auto & elm) mutable {
                elm = temp[i];
                ++i;
            });

            return *this;
        }

        // access operator overloading
    public:

        // '[]' element access
        constexpr T  operator[](const std::size_t i) const { assert(i < 2); return m_data[i]; }
        constexpr T& operator[](const std::size_t i) { assert(i < 2); return m_data[i]; }

        // get pointer to vector internal storage
        constexpr       T* data() { return m_data; }
        constexpr const T* data() const { return m_data; }

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
        // compound operator overloading
    public:

#define M_OPERATOR(OP)                                                                                  \
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                                 \
        constexpr Vector2& operator OP (const U xi_value) {                                             \
            FromVectorBase(std::move(VectorBase<T,2>(*this) OP xi_value));                              \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector2& operator OP (Vector2<U>&& xi_vector) {                  \
            FromVectorBase(std::move(VectorBase<T,2>(*this) OP std::move(xi_vector)));                  \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector2& operator OP (const VectorBase<U, 2>& xi_vector) {       \
            auto _vec = FWD(static_cast<VectorBase<U, 2>>(xi_vector));                                  \
            FromVectorBase(std::move(VectorBase<T,2>(*this) OP _vec));                                  \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U, REQUIRE(is_SwizzleOfLength_v<U, 2>)>                                       \
        constexpr Vector2& operator OP (U& s) {                                                         \
            FromVectorBase(std::move(VectorBase<T,2>(*this) OP s));                                     \
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

/**
* GLSL++
* 
* Dan Israel Malta
**/
#pragma once
#include "common.h"
#include <array>

namespace GLSLCPP {

    /**
    * \brief 'swizzling' class
    *
    * @param {VECTOR,     in}  swizzled element, must be of type 'VectorBase'
    * @param {T,          in}  swizzled element type, i.e. - VectorBase<T,..>
    * @param {size_t,     in}  swizzled element length, i.e. - VectorBase<..,N>
    * @param {bool,       in}  true - all indices's are unique, false - there is a duplicate index
    * @param {Indexes..., in}  elements to swizzle, given as indices's in array
    *                          their length should be equal to the underlying VectorBase, i.e.:
    *                          length(Indexes...) = N in VectroBase<T,N>
    *                          and their value must be smaller then N.
    **/
    template<class VECTOR, typename T, std::size_t N, bool Unique, std::size_t... Indexes> class Swizzle {
        static_assert(std::is_arithmetic<T>::value, "Swizzle must operate on arithmetic types.");
        static_assert(is_VectorBase_v<VECTOR>, "Swizzle must operate on objects of type VectorBase.");
        static_assert(N == sizeof...(Indexes), "Swizzle must operate on objects of type VectorBase.");

        // properties
    private:
        alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) std::array<T, N> m_pack{};

        // constructor
    public:

        // default construction from other swizzle (checked that compiler generate reasonable constructors)
        Swizzle(const Swizzle&)            = default;
        Swizzle& operator=(const Swizzle&) = default;
        Swizzle(Swizzle&&)            noexcept = default;
        Swizzle& operator=(Swizzle&&) noexcept = default;

        // no copy semantics or move assignments from vectors
        template<typename U> Swizzle(const VectorBase<U, N>&)                = delete;
        template<typename U> Swizzle& operator=(const VectorBase<U, N>&)     = delete;
        template<typename U> Swizzle& operator=(VectorBase<U, N>&&) noexcept = delete;

        // only move constructor vectors
        template<typename U> explicit constexpr Swizzle(VectorBase<U, N>&& xi_rhs) noexcept {
            constexpr std::size_t indexes[] = { Indexes... };
            auto rhs = FWD(xi_rhs);

            static_for<0, N>([&](std::size_t i) {
                const std::size_t index{ indexes[i] };
                assert(index < N && " Swizzle indices's are defined such that they point to non existent members, i.e. - they are larger then N.");
                m_pack[index] = static_cast<T>(rhs[i]);
            });
        }

        // methods
    public:

        // get ordered pack
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)> void Pack(U xo_pack[N]) {
            // unpack parameters
            constexpr std::size_t indexes[N] = { Indexes... };

            // fill internal data structure
            static_for<0, N>([&](std::size_t i) {
                xo_pack[i] = static_cast<U>(m_pack[indexes[i]]);
            });
        }

        // swizzle size
        constexpr std::size_t length() const { return N; }

        // return true if indices's are unique
        constexpr bool isUnique() const { return Unique; }

        // conversion operations
    public:

#define M_CAST_GLSL_VECTOR(NAME)              \
        operator NAME() const {               \
            return NAME(m_pack[Indexes]...);  \
        }

        M_CAST_GLSL_VECTOR(VECTOR);
        M_CAST_GLSL_VECTOR(Vector2<T>);
        M_CAST_GLSL_VECTOR(Vector3<T>);
        M_CAST_GLSL_VECTOR(Vector4<T>);

#undef M_CAST_GLSL_VECTOR

        // assignment operation overload
    public:

        // extract as a VECTOR (only when assigned swizzle indices's are unique)
        template<bool unq = Unique, REQUIRE(unq == true)>
        VECTOR& operator=(VECTOR&& xi_rhs) noexcept {
            constexpr std::size_t indexes[] = { Indexes... };

            static_for<0, N>([&](std::size_t i) {
                m_pack[indexes[i]] = xi_rhs[i];
            });

            return *reinterpret_cast<VECTOR*>(this);
        }
        template<bool unq = Unique, REQUIRE(unq == true)>
        VECTOR& operator=(const VECTOR& xi_rhs) {
            constexpr std::size_t indexes[] = { Indexes... };

            static_for<0, N>([&](std::size_t i) {
                m_pack[indexes[i]] = xi_rhs[i];
                });

            return *reinterpret_cast<VECTOR*>(this);
        }

        // compound operator overload
    public:

#define M_COMPOUND(OP)                                                                                                      \
        template<typename U, bool unq = Unique, REQUIRE((unq == true) && is_ArithmeticConvertible_v<U, T>)>                 \
        Swizzle& operator OP (const U rhs) {                                                                                \
            constexpr std::size_t indexes[] = { Indexes... };                                                               \
            static_for<0, N>([&](std::size_t i) {                                                                           \
                m_pack[indexes[i]] OP static_cast<T>(rhs);                                                                  \
            });                                                                                                             \
            return *this;                                                                                                   \
        }                                                                                                                   \
        template<bool unq = Unique, REQUIRE(unq == true)>                                                                   \
        Swizzle& operator OP (VECTOR&& rhs) {                                                                               \
            constexpr std::size_t indexes[] = { Indexes... };                                                               \
            static_for<0, N>([&](std::size_t i) {                                                                           \
                m_pack[indexes[i]] OP static_cast<T>(rhs[i]);                                                               \
            });                                                                                                             \
            return *this;                                                                                                   \
        }                                                                                                                   \
        template<typename U, bool unq = Unique, REQUIRE(unq == true)>                                                       \
        Swizzle& operator OP (const VectorBase<U, N>& xi_rhs) {                                                             \
            constexpr std::size_t indexes[] = { Indexes... };                                                               \
            auto rhs = FWD(static_cast<VectorBase<U, N>>(xi_rhs));                                                          \
            static_for<0, N>([&](std::size_t i) {                                                                           \
                m_pack[indexes[i]] OP static_cast<T>(rhs[i]);                                                               \
            });                                                                                                             \
            return *this;                                                                                                   \
        }                                                                                                                   \
        template<bool un = Unique, class VECTOR, typename U, bool unq, std::size_t ... indexes, REQUIRE(un == true)>        \
        Swizzle& operator OP (Swizzle<VECTOR, U, N, unq, indexes...>& xi_rhs) {                                             \
            T pack[N];                                                                                                      \
            xi_rhs.Pack(pack);                                                                                              \
            static_for<0, N>([&](std::size_t i) {                                                                           \
                m_pack[i] OP std::move(pack[i]);                                                                            \
            });                                                                                                             \
            return *this;                                                                                                   \
        }

        M_COMPOUND(-= );
        M_COMPOUND(+= );
        M_COMPOUND(*= );
        M_COMPOUND(/= );
        M_COMPOUND(&= );
        M_COMPOUND(|= );
        M_COMPOUND(^= );
        M_COMPOUND(>>= );
        M_COMPOUND(<<= );

#undef M_COMPOUND
    };

    /**
    * numerical operator overload
    **/

#define M_NUMERICAL_OPERATOR(OP, AOP)                                                                                                     \
    template<class VECTOR, typename T, std::size_t N, bool Unique, std::size_t ... Indexes, bool Unique2, std::size_t ... Indexes2>       \
    constexpr inline Swizzle<VECTOR, T, N, Unique, Indexes...> operator OP (const Swizzle<VECTOR, T, N, Unique, Indexes...>& xi_lhs,      \
                                                                            const Swizzle<VECTOR, T, N, Unique2, Indexes2...>& xi_rhs) {  \
        VectorBase<T, N>&& lhs(xi_lhs),                                                                                                   \
                           rhs(xi_rhs);                                                                                                   \
        lhs AOP rhs;                                                                                                                      \
        return Swizzle<VECTOR, T, N, Unique, Indexes...>(std::move(lhs));                                                                 \
    }                                                                                                                                     \
    template<class VECTOR, typename T, std::size_t N, bool Unique, std::size_t ... Indexes, bool Unique2, std::size_t ... Indexes2>       \
    constexpr inline Swizzle<VECTOR, T, N, Unique, Indexes...> operator OP (Swizzle<VECTOR, T, N, Unique, Indexes...>&& xi_lhs,           \
                                                                            const Swizzle<VECTOR, T, N, Unique2, Indexes2...>& xi_rhs) {  \
        VectorBase<T, N>&& lhs(std::move(xi_lhs)),                                                                                        \
                           rhs(xi_rhs);                                                                                                   \
        lhs AOP rhs;                                                                                                                      \
        return Swizzle<VECTOR, T, N, Unique, Indexes...>(std::move(lhs));                                                                 \
    }                                                                                                                                     \
    template<class VECTOR, typename T, std::size_t N, bool Unique, std::size_t ... Indexes, bool Unique2, std::size_t ... Indexes2>       \
    constexpr inline Swizzle<VECTOR, T, N, Unique, Indexes...> operator OP (const Swizzle<VECTOR, T, N, Unique, Indexes...>& xi_lhs,      \
                                                                            Swizzle<VECTOR, T, N, Unique2, Indexes2...>&& xi_rhs) {       \
        VectorBase<T, N>&& lhs(xi_lhs),                                                                                                   \
                           rhs(std::move(xi_rhs));                                                                                        \
        lhs AOP rhs;                                                                                                                      \
        return Swizzle<VECTOR, T, N, Unique, Indexes...>(std::move(lhs));                                                                 \
    }                                                                                                                                     \
    template<class VECTOR, typename T, std::size_t N, bool Unique, std::size_t ... Indexes, bool Unique2, std::size_t ... Indexes2>       \
    constexpr inline Swizzle<VECTOR, T, N, Unique, Indexes...> operator OP (Swizzle<VECTOR, T, N, Unique, Indexes...>&& xi_lhs,           \
                                                                            Swizzle<VECTOR, T, N, Unique2, Indexes2...>&& xi_rhs) {       \
        VectorBase<T, N>&& lhs(std::move(xi_lhs)),                                                                                        \
                           rhs(std::move(xi_rhs));                                                                                        \
        lhs AOP rhs;                                                                                                                      \
        return Swizzle<VECTOR, T, N, Unique, Indexes...>(std::move(lhs));                                                                 \
    }

    M_NUMERICAL_OPERATOR(+, +=);
    M_NUMERICAL_OPERATOR(-, -=);
    M_NUMERICAL_OPERATOR(*, *=);
    M_NUMERICAL_OPERATOR(/ , /=);

#undef M_NUMERICAL_OPERATOR

}; // namespace GLSLCPP
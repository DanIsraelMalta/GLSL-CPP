/**
* GLSL++
*
* Dan Israel Malta
**/
#pragma once
#include "common.h"
#include "VectorBase.h"
#include "MatrixBase.h"
#include<cmath>

namespace GLSLCPP {

    // -----------------------------------
    // --- numerical operator overload ---
    // -----------------------------------

    // unary minus
    template<typename T, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline T operator - (const T& xi_col) {
        auto v = FWD(xi_col);
        v *= static_cast<underlying_type_t<T>>(-1.0);
        return FWD(v);
    }

    // ------------------------------------
    // --- relational operator overload ---
    // ------------------------------------
    
#define M_OPERATOR(OP)                                                                                              \
    template<typename T, typename U, REQUIRE(is_Vector_v<U> && is_Vector_v<T> && (Length_v<U> == Length_v<T>))>     \
    constexpr inline bool operator OP (const T& xi_lhs, const U& xi_rhs) {                                          \
        bool xo_rational{ true };                                                                                   \
        for (std::size_t i{}; (i < Length_v<U>) && xo_rational; ++i) {                                              \
            xo_rational = xi_lhs[i] OP xi_rhs[i];                                                                   \
        }                                                                                                           \
        return xo_rational;                                                                                         \
    }                                                                                                               \
    template<typename T, typename U, REQUIRE(std::is_arithmetic_v<T> && is_Vector_v<U>)>                            \
    constexpr inline bool operator OP (const T xi_lhs, const U& xi_rhs) {                                           \
        bool xo_rational{ true };                                                                                   \
        for (std::size_t i{}; (i < Length_v<U>) && xo_rational; ++i) {                                              \
            xo_rational = xi_lhs OP xi_rhs[i];                                                                      \
        }                                                                                                           \
        return xo_rational;                                                                                         \
    }                                                                                                               \
    template<typename T, typename U, REQUIRE(std::is_arithmetic_v<T> && is_Vector_v<U>)>                            \
    constexpr inline bool operator OP (const U& xi_lhs, const T xi_rhs) {                                           \
        bool xo_rational{ true };                                                                                   \
        for (std::size_t i{}; (i < Length_v<U>) && xo_rational; ++i) {                                              \
            xo_rational = xi_lhs[i] OP xi_rhs;                                                                      \
        }                                                                                                           \
        return xo_rational;                                                                                         \
    }

    M_OPERATOR(== );
    M_OPERATOR(!= );
    M_OPERATOR(>= );
    M_OPERATOR(> );
    M_OPERATOR(<= );
    M_OPERATOR(< );

#undef M_OPERATOR


#define M_OPERATOR(OP)                                                                                                  \
    template<typename T, std::size_t COL, std::size_t ROW>                                                              \
    constexpr inline bool operator OP (const MatrixBase<T, COL, ROW>& xi_lhs, const MatrixBase<T, COL, ROW>& xi_rhs) {  \
        return xi_lhs.m_data OP xi_rhs.m_data;                                                                          \
    }                                                                                                                   \
    template<typename T, std::size_t COL, std::size_t ROW>                                                              \
    constexpr inline bool operator OP (const T xi_lhs, const MatrixBase<T, COL, ROW>& xi_rhs) {                         \
        return xi_lhs OP xi_rhs.m_data;                                                                                 \
    }                                                                                                                   \
    template<typename T, std::size_t COL, std::size_t ROW>                                                              \
    constexpr inline bool operator OP (const MatrixBase<T, COL, ROW>& xi_lhs, const T xi_rhs) {                         \
        return xi_lhs.m_data OP xi_rhs;                                                                                 \
    }

    M_OPERATOR(== );
    M_OPERATOR(!= );
    M_OPERATOR(>= );
    M_OPERATOR(> );
    M_OPERATOR(<= );
    M_OPERATOR(< );

#undef M_OPERATOR

    // ----------------------------
    // --- relational functions ---
    // ----------------------------

    /**
    * \brief return true if vector/matrix holds a NaN
    *
    * @param {VectorBase, in}  vector/matrix
    * @param {bool,       out} true if vector/matrix holds a NaN, false otherwise
    **/
    template<typename T, REQUIRE(is_iterate_able_v<T>&& std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isnan(T&& xi_col) noexcept {
        return any(FWD(xi_col), [&](const underlying_type_t<T> & v) { return std::isnan(v); });
    }
    template<typename T, REQUIRE(is_iterate_able_v<T> && !std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isnan(T&& xi_col) noexcept {
        return any(FWD(xi_col), [&](const underlying_type_t<T>& v) { return std::isnan(static_cast<double>(v)); });
    }

    template<typename T, REQUIRE(is_iterate_able_v<T> && std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isnan(const T& xi_col) noexcept {
        return any(xi_col, [&](const underlying_type_t<T>& v) { return std::isnan(v); });
    }
    template<typename T, REQUIRE(is_iterate_able_v<T> && !std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isnan(const T& xi_col) noexcept {
        return any(xi_col, [&](const underlying_type_t<T> & v) { return std::isnan(static_cast<double>(v)); });
    }

    /**
    * \brief return true if vector/matrix holds an Inf
    *
    * @param {VectorBase, in}  vector/matrix
    * @param {bool,       out} true if vector/matrix holds an Inf, false otherwise
    **/
    template<typename T, REQUIRE(is_iterate_able_v<T> && std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isinf(T&& xi_vec) noexcept {
        return any(FWD(xi_vec), [&](const underlying_type_t<T>& v) { return std::isinf(v); });
    }
    template<typename T, REQUIRE(is_iterate_able_v<T> && !std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isinf(T&& xi_vec) noexcept {
        return any(FWD(xi_vec), [&](const underlying_type_t<T> & v) { return std::isinf(static_cast<double>(v)); });
    }

    template<typename T, REQUIRE(is_iterate_able_v<T> && std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isinf(const T& xi_vec) noexcept {
        return any(xi_vec, [&](const underlying_type_t<T>& v) { return std::isinf(v); });
    }
    template<typename T, REQUIRE(is_iterate_able<T>::value && !std::is_floating_point_v<underlying_type_t<T>>)>
    constexpr inline bool isinf(const T& xi_vec) noexcept {
        return any(xi_vec, [&](const underlying_type_t<T> & v) { return std::isinf(static_cast<double>(v)); });
    }

    /**
    * \brief return a reversed vector
    *
    * @param {VectorBase, in}  vector
    * @param {VectorBase, out} reversed vector
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline auto reverse(T&& xi_vector) noexcept {
        constexpr std::size_t N{ Length_v<T> },
                              halfN{ N / 2 };
        for (std::size_t i{}; i < halfN; ++i) {
            std::swap(xi_vector[i], xi_vector[N - i - 1]);
        }

        return xi_vector;
    }

    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline auto reverse(const T& xi_vector) noexcept {
        constexpr std::size_t N{ Length_v<T> },
                              halfN{ N / 2 };
        auto _vec = FWD(xi_vector);

        for (std::size_t i{}; i < halfN; ++i) {
            std::swap(_vec[i], _vec[N - i - 1]);
        }

        return FWD(_vec);
    }

    // -------------------------------------------------------------------------
    // --- "STL compliance" unary functions (element wise) for vector/matrix ---
    // -------------------------------------------------------------------------

#define M_UNARY_FUNCTION(NAME, FUNC)                                                                            \
    template<typename T, REQUIRE(is_IterableRvalue<T>::value)> constexpr inline auto NAME(T&& xi_value) {       \
        for_each(xi_value, [&, i = 0](auto& elm) mutable {                                                      \
            elm = FUNC(xi_value[i]);                                                                            \
            ++i;                                                                                                \
        });                                                                                                     \
        return xi_value;                                                                                        \
    }                                                                                                           \
    template<typename T, REQUIRE(is_IterableLvalue<T>::value)> constexpr inline auto NAME(T&& xi_value) {       \
        auto _col = FWD(xi_value);                                                                              \
        for_each(_col, [&, i = 0](auto& elm) mutable {                                                          \
            elm = FUNC(_col[i]);                                                                                \
            ++i;                                                                                                \
        });                                                                                                     \
        return FWD(_col);                                                                                       \
    }                                                                                                           \
    template<typename T, REQUIRE(is_iterate_able_v<T>)> constexpr inline auto NAME(const T& xi_value) {         \
        auto _col = FWD(xi_value);                                                                              \
        for_each(_col, [&, i = 0](auto& elm) mutable {                                                          \
            elm = FUNC(_col[i]);                                                                                \
            ++i;                                                                                                \
        });                                                                                                     \
        return FWD(_col);                                                                                       \
    }

    M_UNARY_FUNCTION(abs,   std::abs);
    M_UNARY_FUNCTION(floor, std::floor);
    M_UNARY_FUNCTION(ceil,  std::ceil);
    M_UNARY_FUNCTION(trunc, std::trunc);
    M_UNARY_FUNCTION(round, std::round);
    M_UNARY_FUNCTION(exp,   std::exp);
    M_UNARY_FUNCTION(exp2,  std::exp2);
    M_UNARY_FUNCTION(log,   std::log);
    M_UNARY_FUNCTION(log2,  std::log2);
    M_UNARY_FUNCTION(sqrt,  std::sqrt);
    M_UNARY_FUNCTION(sin,   std::sin);
    M_UNARY_FUNCTION(cos,   std::cos);
    M_UNARY_FUNCTION(tan,   std::tan);
    M_UNARY_FUNCTION(asin,  std::asin);
    M_UNARY_FUNCTION(acos,  std::acos);
    M_UNARY_FUNCTION(atan,  std::atan);
    M_UNARY_FUNCTION(sinh,  std::sinh);
    M_UNARY_FUNCTION(cosh,  std::cosh);
    M_UNARY_FUNCTION(tanh,  std::tanh);
    M_UNARY_FUNCTION(asinh, std::asinh);
    M_UNARY_FUNCTION(acosh, std::acosh);
    M_UNARY_FUNCTION(atanh, std::atanh);

#undef M_UNARY_FUNCTION

    // ----------------------------------------------------------------
    // --- general unary functions (element wise) for vector/matrix ---
    // ----------------------------------------------------------------

#define M_UNARY_FUNCTION(NAME, FUNC1, FUNC2)                                                                    \
    template<typename T, REQUIRE(is_IterableRvalue<T>::value)> constexpr inline auto NAME(T&& xi_value) {       \
        for_each(xi_value, [&, i = 0](auto& elm) mutable {                                                      \
            elm = FUNC1;                                                                                        \
            ++i;                                                                                                \
        });                                                                                                     \
        return xi_value;                                                                                        \
    }                                                                                                           \
    template<typename T, REQUIRE(is_IterableLvalue<T>::value)> constexpr inline auto NAME(T&& xi_value) {       \
        auto _col = FWD(xi_value);                                                                              \
        for_each(_col, [&, i = 0](auto& elm) mutable {                                                          \
            elm = FUNC2;                                                                                        \
            ++i;                                                                                                \
        });                                                                                                     \
        return FWD(_col);                                                                                       \
    }                                                                                                           \
    template<typename T, REQUIRE(is_iterate_able_v<T>)> constexpr inline auto NAME(const T& xi_value) {         \
        auto _col = FWD(xi_value);                                                                              \
        for_each(_col, [&, i = 0](auto& elm) mutable {                                                          \
            elm = FUNC2;                                                                                        \
            ++i;                                                                                                \
        });                                                                                                     \
        return FWD(_col);                                                                                       \
    }

    M_UNARY_FUNCTION(radians, [&]() { return xi_value[i] * static_cast<underlying_type_t<T>>(3.1415926535897932384626433832795) / static_cast<underlying_type_t<T>>(180.0); }(),
                              [&]() { return _col[i] * static_cast<underlying_type_t<T>>(3.1415926535897932384626433832795) / static_cast<underlying_type_t<T>>(180.0); }());
    M_UNARY_FUNCTION(degrees, [&]() { return xi_value[i] * static_cast<underlying_type_t<T>>(180.0) / static_cast<underlying_type_t<T>>(3.1415926535897932384626433832795); }(),
                              [&]() { return _col[i] * static_cast<underlying_type_t<T>>(180.0) / static_cast<underlying_type_t<T>>(3.1415926535897932384626433832795); }());
    M_UNARY_FUNCTION(inversesqrt, [&]() { return (static_cast<underlying_type_t<T>>(1.0) / std::sqrt(xi_value[i])); }(),
                                  [&]() { return (static_cast<underlying_type_t<T>>(1.0) / std::sqrt(_col[i])); }());
    M_UNARY_FUNCTION(sign, [&]() { return (xi_value[i] > static_cast<underlying_type_t<T>>(0)) ? static_cast<underlying_type_t<T>>(1.0) : (xi_value[i] < static_cast<underlying_type_t<T>>(0)) ? static_cast<underlying_type_t<T>>(-1.0) : static_cast<underlying_type_t<T>>(0); }(),
                           [&]() { return (_col[i] > static_cast<underlying_type_t<T>>(0)) ? static_cast<underlying_type_t<T>>(1.0) : (_col[i] < static_cast<underlying_type_t<T>>(0)) ? static_cast<underlying_type_t<T>>(-1.0) : static_cast<underlying_type_t<T>>(0); }());
#undef M_UNARY_FUNCTION

    /**
    * \brief given a vector/matrix, change each of its elements equal to the nearest even integer.
    *        The fractional part of 0.5 will round toward the nearest even integer. i.e. - both 3.5 and 4.5 will round to 4.0.
    *
    * @param {VectorBase, in}  vector/matrix to be rounded
    * @param {VectorBase, out} rounded vector/matrix
    **/
    template<typename T, REQUIRE(is_iterate_able_v<T>)> constexpr inline auto roundEven(T&& xi_value) {
        constexpr underlying_type_t<T> one{ static_cast<underlying_type_t<T>>(1.0) },
                                       half{ static_cast<underlying_type_t<T>>(0.5) },
                                       zero{ static_cast<underlying_type_t<T>>(0) };
        for_each(xi_value, [&, i = 0](auto & elm) mutable {
            const std::int32_t castedInt{ static_cast<int>(elm) };
            underlying_type_t<T> IntegerPart,
                                 FractionalPart{ std::modf(elm, &IntegerPart) };
            elm = ((FractionalPart > half) || (FractionalPart < half)) ? std::round(elm)     :
                  (castedInt % 2 == 0)                                 ? IntegerPart         :
                  (elm <= zero)                                        ? (IntegerPart - one) :
                                                                         (IntegerPart + one);
            ++i;
        });
        return xi_value;
    }
    template<typename T, REQUIRE(is_iterate_able_v<T>)> constexpr inline auto roundEven(const T& xi_value) {
        constexpr underlying_type_t<T> one{ static_cast<underlying_type_t<T>>(1.0) },
                                       half{ static_cast<underlying_type_t<T>>(0.5) },
                                       zero{ static_cast<underlying_type_t<T>>(0) };
        auto _value = FWD(xi_value);
        for_each(_value, [&, i = 0](auto & elm) mutable {
            const std::int32_t castedInt{ static_cast<int>(elm) };
            underlying_type_t<T> IntegerPart,
                                 FractionalPart{ std::modf(elm, &IntegerPart) };
            elm = ((FractionalPart > half) || (FractionalPart < half)) ? std::round(elm)     :
                  (castedInt % 2 == 0)                                 ? IntegerPart         :
                  (elm <= zero)                                        ? (IntegerPart - one) :
                                                                         (IntegerPart + one);
            ++i;
        });
        return FWD(_value);
    }

    // --------------------------------------------------------------------------
    // --- "STL compliance" binary functions (element wise) for vector/matrix ---
    // --------------------------------------------------------------------------

#define M_BINARY_FUNCTION(NAME, FUNC)                                                                                                       \
    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && is_ArithmeticConvertible_v<U, underlying_type_t<T>>)>                  \
    constexpr inline auto NAME(T&& xi_lhs, const U xi_rhs) {                                                                                \
        for_each(xi_lhs, [&, i = 0](auto& elm) mutable {                                                                                    \
            elm = FUNC(elm, static_cast<underlying_type_t<T>>(xi_rhs));                                                                     \
            ++i;                                                                                                                            \
        });                                                                                                                                 \
        return xi_lhs;                                                                                                                      \
    }                                                                                                                                       \
    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && is_ArithmeticConvertible_v<U, underlying_type_t<T>>)>                  \
    constexpr inline auto NAME(const T& xi_lhs, const U xi_rhs) {                                                                           \
        auto lhs = FWD(xi_lhs);                                                                                                             \
        for_each(lhs, [&, i = 0](auto& elm) mutable {                                                                                       \
            elm = FUNC(elm, static_cast<underlying_type_t<T>>(xi_rhs));                                                                     \
            ++i;                                                                                                                            \
        });                                                                                                                                 \
        return FWD(lhs);                                                                                                                    \
    }                                                                                                                                       \
    template<typename T, REQUIRE(is_iterate_able_v<T>)> constexpr inline auto NAME(T&& xi_lhs, T&& xi_rhs) {                                \
        for_each(xi_lhs, [&, i = 0](auto& elm) mutable {                                                                                    \
            elm = FUNC(elm, xi_rhs[i]);                                                                                                     \
            ++i;                                                                                                                            \
        });                                                                                                                                 \
        return xi_lhs;                                                                                                                      \
    }                                                                                                                                       \
    template<typename T, REQUIRE(is_iterate_able_v<T>)> constexpr inline auto NAME(const T& xi_lhs, const T& xi_rhs) {                      \
        auto lhs = FWD(xi_lhs);                                                                                                             \
        for_each(lhs, [&, i = 0](auto& elm) mutable {                                                                                       \
            elm = FUNC(elm, xi_rhs[i]);                                                                                                     \
            ++i;                                                                                                                            \
        });                                                                                                                                 \
        return FWD(lhs);                                                                                                                    \
    }

    M_BINARY_FUNCTION(pow,   std::pow);
    M_BINARY_FUNCTION(atan2, std::atan2);
    M_BINARY_FUNCTION(modf,  std::fmod);

#undef M_BINARY_FUNCTION

    // -----------------------------------------------
    // --- general binary functions (element wise) ---
    // -----------------------------------------------

    /**
    * \brief return the internal ("dot") product between a variadic number of collections.
    *        collections must have identical underlying type and be with the same length
    *
    * @param {Collection, in}  collections...
    * @param {T,          out} dot(collection #1, ...)
    **/
    template<typename T, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline underlying_type_t<T> dot(const T& xi_tail) {
        using _T = underlying_type_t<T>;

        // return squared magnitude
        auto l = FWD(xi_tail);
        return reduce(_T{}, l, [&](const _T init, const _T elm) -> _T { return (init + elm * elm); });
    }

    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline underlying_type_t<T> dot(T&& xi_tail) {
        using _T = underlying_type_t<T>;
        // return vector squred magnitude
        return reduce(_T{}, xi_tail, [&](const _T init, const _T elm) -> _T { return (init + elm * elm); });
    }

    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline underlying_type_t<T> dot(const T& xi_tail, const T& xi_head) {
        using _T = underlying_type_t<T>;

        // standard dot ("scalar") product
        auto _l = FWD(xi_tail);
        auto _r = FWD(xi_head);
        return transform_reduce(_l, _r, _T{},
                               [&](const _T l, const _T r) -> _T { return (l + r); },
                               [&](const _T l, const _T r) -> _T { return l * r; });
    }

    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline underlying_type_t<T> dot(T&& xi_tail, const T& xi_head) {
        using _T = underlying_type_t<T>;

        // standard dot ("scalar") product
        auto _r = FWD(xi_head);
        return transform_reduce(xi_tail, _r, _T{},
                                [&](const _T l, const _T r) -> _T { return (l + r); },
                                [&](const _T l, const _T r) -> _T { return l * r; });
    }

    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T> &&
                                                   Are_IterAbleEqualSize_v<Length_v<T>, Args...> &&
                                                   (sizeof...(Args) > 1))>
        constexpr inline underlying_type_t<T> dot(const T& xi_tail, const Args& ...args) {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ sizeof...(Args) };

        // dot product of several vectors
        const std::array<T, N + 1> _args{ xi_tail, args... };
        _T xo_dot{};

        for (std::size_t i{}; i < N + 1; ++i) {
            _T temp{ static_cast<_T>(1) };

            for (std::size_t j{}; j < N + 1; ++j) {
                temp *= _args[j][i];
            }

            xo_dot += temp;
        }

        return xo_dot;
    }

    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T> &&
                                                   Are_IterAbleEqualSize_v<Length_v<T>, Args...> &&
                                                   (sizeof...(Args) > 1))>
    constexpr inline underlying_type_t<T> dot(T&& xi_tail, const Args& ...args) {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ sizeof...(Args) };

        // dot product of several vectors
        const std::array<T, N + 1> _args{ xi_tail, args... };
        _T xo_dot{};

        for (std::size_t i{}; i < N + 1; ++i) {
            _T temp{ static_cast<_T>(1) };

            for (std::size_t j{}; j < N + 1; ++j) {
                temp *= _args[j][i];
            }

            xo_dot += temp;
        }

        return xo_dot;
    }

    /**
    * \brief return the internal ("dot") product between two vectors, in a specific range of indices.
    *        vectors must have identical underlying type and be with the same length.
    *
    * @param {VectorBase, in}  vector 1
    * @param {VectorBase, in}  vector 2
    * @param {size_t,     in}  dot product initial element, given by its index
    * @param {size_t,     in}  dot product last element, given by its index
    * @param {T,          out} left looking dot product between given vectors and witin given range
    **/
    template<typename T, REQUIRE(is_VectorBase_v<T> && (Length_v<T> > 0))>
    constexpr inline underlying_type_t<T> leftLookingDot(const T& xi_a, const T& xi_b, const std::size_t xi_start, const std::size_t xi_end) {
        using _T = underlying_type_t<T>;
        assert(xi_start <= xi_end && " leftLookingDot(..., xi_start, xi_end) - xi_start must be smaller then xi_end.");
        assert(xi_end <= Length_v<T> && " leftLookingDot(..., xi_end) - it appears that xi_end is larger than vector length.");

        _T xo_dot{};

        for (std::size_t i{ xi_start }; i < xi_end; ++i) {
            xo_dot += xi_a[i] * xi_b[i];
        }

        return xo_dot;
    }

    template<typename T, REQUIRE(is_VectorBase_v<T> && (Length_v<T> > 0))>
    constexpr inline underlying_type_t<T> leftLookingDot(T&& xi_a, T&& xi_b, const std::size_t xi_start, const std::size_t xi_end) {
        using _T = underlying_type_t<T>;
        assert(xi_start <= xi_end && " leftLookingDot(..., xi_start, xi_end) - xi_start must be smaller then xi_end.");
        assert(xi_end <= Length_v<T> && " leftLookingDot(..., xi_end) - it appears that xi_end is larger than vector length.");

        _T xo_dot{};

        for (std::size_t i{ xi_start }; i < xi_end; ++i) {
            xo_dot += xi_a[i] * xi_b[i];
        }

        return xo_dot;
    }

    /**
    * \brief return the minimal scalar value from a variadic number of collections.
    *        vectors must have identical underlying type and be with the same length.
    *
    * @param {Collection, in}  collections...
    * @param {common,     out} minimal value amongst given collections
    **/
    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T> && Are_IterAbleEqualSize_v<Length_v<T>, Args...>)>
    constexpr inline underlying_type_t<T> min(const T& xi_tail, const Args& ...args) {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ sizeof...(Args) };

        auto v = FWD(xi_tail);
        _T xo_min{ reduce(v[0], v, [&](const _T init, const _T elm) -> _T { return std::min(init, elm); }) };
 
        if constexpr (N > 0) {
            static_for<0, N>([&](auto i) {
                auto _a = FWD(getArgument<i>(args...));
                const _T _min{ reduce(_a[0], _a, [&](const _T init, const _T elm) -> _T { return std::min(init, elm); }) };
                xo_min = std::min(xo_min, _min);
            });
        }

        return xo_min;
    }

    /**
    * \brief return the maximal scalar value from a variadic number of collections.
    *        vectors must have identical underlying type and be with the same length.
    *
    * @param {Collection, in}  collections...
    * @param {common,     out} maximal value amongst given collections
    **/
    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T> && Are_IterAbleEqualSize_v<Length_v<T>, Args...>)>
    constexpr inline underlying_type_t<T> max(const T& xi_tail, const Args& ...args) {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ sizeof...(Args) };

        auto v = FWD(xi_tail);
        _T xo_max{ reduce(v[0], v, [&](const _T init, const _T elm) -> _T { return std::max(init, elm); }) };

        if constexpr (N > 0) {
            static_for<0, N>([&](auto i) {
                auto _a = FWD(getArgument<i>(args...));
                const _T _max{ reduce(_a[0], _a, [&](const _T init, const _T elm) -> _T { return std::max(init, elm); }) };
                xo_max = std::max(xo_max, _max);
            });
        }

        return xo_max;
    }

    /**
    * \brief return the sum of a number variadic number of collections.
    *        vectors must have identical underlying type and be with the same length.
    *
    * @param {Collection, in}  collections...
    * @param {T,             out} sum of all vectors collections
    **/
    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T> && Are_IterAbleEqualSize_v<Length_v<T>, Args...>)>
    constexpr inline underlying_type_t<T> sum(const T& xi_tail, const Args& ...args) {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ sizeof...(Args) };

        auto tail = FWD(xi_tail);
        _T xo_sum{ reduce(_T{}, tail, [&](const _T init, const _T elm) -> _T { return (init + elm); }) };

        if constexpr (N > 0) {
            static_for<0, N>([&](auto i) {
                auto _a = FWD(getArgument<i>(args...));
                const _T _sum{ reduce(_T{}, _a, [&](const _T init, const _T elm) -> _T { return (init + elm); }) };
                xo_sum += _sum;
            });
        }

        return xo_sum;
    }

    /**
    * \brief return the product of a number variadic number of collections.
    *        vectors must have identical underlying type and be with the same length.
    *
    * @param {Collection, in}  collections...
    * @param {T,             out} product of all collections elements
    **/
    template<typename T, typename... Args, REQUIRE(is_iterate_able_v<T> && Are_IterAbleEqualSize_v<Length_v<T>, Args...>)>
    constexpr inline underlying_type_t<T> prod(const T& xi_tail, const Args& ...args) {
        using _T = underlying_type_t<T>;
        constexpr std::size_t N{ sizeof...(Args) };

        auto tail = FWD(xi_tail);
        _T xo_prod{ reduce(static_cast<_T>(1), tail, [&](const _T init, const _T elm) -> _T { return (init * elm); }) };

        if constexpr (N > 0) {
            static_for<0, N>([&](auto i) {
                auto _a = FWD(getArgument<i>(args...));
                const _T _prod{ reduce(static_cast<_T>(1), _a, [&](const _T init, const _T elm) -> _T { return (init * elm); }) };
                xo_prod *= _prod;
            });
        }

        return xo_prod;
    }

    /**
    * \brief clamp collections elements to a given region
    *
    * @param {Collection, in}  a collections
    * @param {U,          in}  minimal or maximal value
    * @param {U,          in}  maximal or maximal value
    * @param {Collection, out} clamped collections
    **/
    template<typename T, typename U, typename W, REQUIRE(is_iterate_able_v<T> && Are_ArithmeticConvertible<underlying_type_t<T>, U, W>::value)>
    constexpr T clamp(T&& xi_col, const U xi_boundary1, const W xi_boundary2) {
        using _T = underlying_type_t<T>;

        _T _min{ static_cast<_T>(xi_boundary1) },
           _max{ static_cast<_T>(xi_boundary2) };
        if (_min > _max) std::swap(_min, _max);

        for_each(xi_col, [&](auto & elm) {
            elm = std::clamp(elm, _min, _max);
        });

        return xi_col;
    }

    template<typename T, typename U, typename W, REQUIRE(is_iterate_able_v<T> && Are_ArithmeticConvertible<underlying_type_t<T>, U, W>::value)>
    constexpr T clamp(const T& xi_col, const U xi_boundary1, const W xi_boundary2) {
        using _T = underlying_type_t<T>;
        auto vec = FWD(xi_col);

        _T _min{ static_cast<_T>(xi_boundary1) },
           _max{ static_cast<_T>(xi_boundary2) };
        if (_min > _max) std::swap(_min, _max);

        for_each(vec, [&](auto & elm) {
            elm = std::clamp(elm, _min, _max);
        });

        return FWD(vec);
    }

    /**
    * \brief clamp collections elements to a given region
    *
    * @param {Collection, in}  a collections
    * @param {Collection, in}  minimal or maximal value
    * @param {Collection, in}  maximal or maximal value
    * @param {Collection, out} clamped collections
    **/
    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && is_IterAbleOfSize<Length_v<T>, U>::value)>
    constexpr inline T clamp(const T& xi_col, const U& xi_boundary1, const U& xi_boundary2) {
        using _T = underlying_type_t<T>;
        auto vec = FWD(xi_col);

        for_each(vec, [&, i = 0](auto& elm) mutable {
            _T _min{ static_cast<_T>(xi_boundary1[i]) },
               _max{ static_cast<_T>(xi_boundary2[i]) };
            if (_min > _max) std::swap(_min, _max);

            elm = std::clamp(elm, _min, _max);
        });

        return FWD(vec);
    }

    /**
    * \brief return the linear blend between two (equally sized) collections
    *
    * @param {Collection, in}  collection #1 (v1)
    * @param {Collection, in}  collection #2 (v2)
    * @param {U,          in}  blend parameter (a), should be in the region [0, 1]
    * @param {Collection, out} v1 * (1-a) + v2 * a
    **/
    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && is_ArithmeticConvertible_v<U, underlying_type_t<T>>)>
    constexpr T mix(const T& xi_col1, const T& xi_col2, const U xi_mix) {
        using _T = underlying_type_t<T>;
        assert(((static_cast<_T>(xi_mix) > _T{})                || 
                (static_cast<_T>(xi_mix) < static_cast<_T>(1))) && 
               "mix(collection, collection, a) - a should be in the region [0, 1].");

        auto col1 = FWD(xi_col1);
        auto col2 = FWD(xi_col2);

        const _T a{ static_cast<_T>(xi_mix) },
                 oneMinusA{ static_cast<_T>(1) - a };

        for_each(col1, [&, i = 0](auto & elm) mutable {
            elm = oneMinusA * elm + a * col2[i];
            ++i;
        });

        return FWD(col1);
    }

    /**
    * \brief given a collection, on each of its elements: return 0 if element is smaller then a value, otherwise - return 1.
    *
    * @param {Collection, in}  collection
    * @param {U,          in}  edge
    * @param {Collection, out} collection
    **/
    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && is_ArithmeticConvertible_v<U, underlying_type_t<T>>)>
    constexpr T step(T&& xi_col, const U xi_edge) {
        using _T = underlying_type_t<T>;

        const _T edge{ static_cast<_T>(xi_edge) },
                 one{ static_cast<_T>(1) };
        for_each(xi_col, [&](auto & elm) {
            elm = (elm < edge) ? _T{} : one;
        });

        return xi_col;
    }

    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && is_ArithmeticConvertible_v<U, underlying_type_t<T>>)>
    constexpr T step(const T& xi_col, const U xi_edge) {
        using _T = underlying_type_t<T>;
        auto _vec = FWD(xi_col);

        const _T edge{ static_cast<_T>(xi_edge) },
                 one{ static_cast<_T>(1) };
        for_each(_vec, [&](auto & elm) {
            elm = (elm < edge) ? _T{} : one;
        });

        return FWD(_vec);
    }

    /**
    * \brief given a collection, for each of its elements:
    *        return 0 if smaller then edg0, return 1 if larger then edg1, perform Hermite interpolation
    *        between 0 and 1 when element is in region [edge0, edge1]
    *
    * @param {Collection,  in}  collection
    * @param {U,           in}  edge0
    * @param {U,           in}  edge1
    * @param {Collection,  out} collection
    **/
    template<typename T, typename U, typename W, REQUIRE(is_iterate_able_v<T> && Are_ArithmeticConvertible<underlying_type_t<T>, U, W>::value)>
    constexpr T smoothstep(T&& xi_col, const U xi_edge0, const W xi_edge1) {
        using _T = underlying_type_t<T>;

        const _T edge0{ static_cast<_T>(xi_edge0) },
                 edge1{ static_cast<_T>(xi_edge1) };
        assert(static_cast<_T>(xi_edge0) < static_cast<_T>(xi_edge1) && " smoothstep(COLLECTION, a, b) - 'a' can not be smaller then 'b'.");

        // scalar normalized clamping
        auto clamp = [&](_T && _value, const _T _min, const _T _max) -> _T {
            return std::clamp((_value - _min) / (_max - _min), _T{}, static_cast<_T>(1));
        };

        // scalar Hermite interpolation
        auto hermite = [&](_T && _value) -> _T {
            return (_value * _value * (static_cast<_T>(3) - static_cast<_T>(2) * _value));
        };

        for_each(xi_col, [&](auto & elm) {
            elm = hermite(clamp(std::move(elm), edge0, edge1));
        });

        return xi_col;
    }

    template<typename T, typename U, typename W, REQUIRE(is_iterate_able_v<T> && Are_ArithmeticConvertible<underlying_type_t<T>, U, W>::value)>
    constexpr T smoothstep(const T& xi_col, const U xi_edge0, const W xi_edge1) {
        using _T = underlying_type_t<T>;

        const _T edge0{ static_cast<_T>(xi_edge0) },
                 edge1{ static_cast<_T>(xi_edge1) };
        assert(static_cast<_T>(xi_edge0) < static_cast<_T>(xi_edge1) && " smoothstep(COLLECTION, a, b) - 'a' can not be smaller then 'b'.");

        // scalar normalized clamping
        auto clamp = [&](_T && _value, const _T _min, const _T _max) -> _T {
            return std::clamp((_value - _min) / (_max - _min), _T{}, static_cast<_T>(1));
        };

        // scalar Hermite interpolation
        auto hermite = [&](_T && _value) -> _T {
            return (_value * _value * (static_cast<_T>(3) - static_cast<_T>(2) * _value));
        };

        auto col = FWD(xi_col);

        for_each(col, [&](auto & elm) {
            elm = hermite(clamp(std::move(elm), edge0, edge1));
        });

        return FWD(col);
    }

    /**
    * \brief given a collection, for each of its elements:
    *        return 0 if smaller then edg0[i], return 1 if larger then edg1[i], perform Hermite interpolation
    *        between 0 and 1 when element is in region [edge0, edge1]
    *
    * @param {Collection, in}  Collection
    * @param {Collection, in}  edge 0
    * @param {Collection, in}  edge 1
    * @param {Collection, out} Collection
    **/
    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && Are_IterAbleEqualSize_v<Length_v<T>, U>)>
    constexpr T smoothstep(T&& xi_col, const U& xi_edge0, const U& xi_edge1) {
        using _T = underlying_type_t<T>;

        // scalar normalized clamping
        auto clamp = [&](_T && _value, const _T _min, const _T _max) -> _T {
            return std::clamp((_value - _min) / (_max - _min), _T{}, static_cast<_T>(1));
        };

        // scalar Hermite interpolation
        auto hermite = [&](_T && _value) -> _T {
            return (_value * _value * (static_cast<_T>(3) - static_cast<_T>(2) * _value));
        };

        for_each(xi_col, [&, i = 0](auto & elm) mutable {
            const _T edge0{ static_cast<_T>(xi_edge0[0]) },
                     edge1{ static_cast<_T>(xi_edge1[1]) };
            assert(edge0 < edge1 && " smoothstep(collection, a, b) - 'a' can not be smaller then 'b'.");

            elm = hermite(clamp(std::move(elm), edge0, edge1));
            ++i;
        });

        return xi_col;
    }

    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && Are_IterAbleEqualSize_v<Length_v<T>, U>)>
    constexpr T smoothstep(const T& xi_col, const U& xi_edge0, const U& xi_edge1) {
        using _T = underlying_type_t<T>;

        // scalar normalized clamping
        auto clamp = [&](_T && _value, const _T _min, const _T _max) -> _T {
            return std::clamp((_value - _min) / (_max - _min), _T{}, static_cast<_T>(1));
        };

        // scalar Hermite interpolation
        auto hermite = [&](_T && _value) -> _T {
            return (_value * _value * (static_cast<_T>(3) - static_cast<_T>(2) * _value));
        };

        auto _col = FWD(xi_col);

        for_each(_col, [&, i = 0](auto & elm) mutable {
            const _T edge0{ static_cast<_T>(xi_edge0[0]) },
                     edge1{ static_cast<_T>(xi_edge1[1]) };
            assert(edge0 < edge1 && " smoothstep(collection, a, b) - 'a' can not be smaller then 'b'.");

            elm = hermite(clamp(std::move(elm), edge0, edge1));
            ++i;
        });

        return FWD(_col);
    }

    /**
    * \brief given a collection, for each of its elements perform a "smoother' smoothestep,
    *        i.e. - a smoothstep whose first and second derivative at the edges are zero.
    *
    * @param {Collection,  in}  collection
    * @param {U,           in}  edge0
    * @param {U,           in}  edge1
    * @param {Collection,  out} collection
    **/
    template<typename T, typename U, typename W, REQUIRE(is_iterate_able_v<T> && Are_ArithmeticConvertible<underlying_type_t<T>, U, W>::value)>
    constexpr T smootherstep(T&& xi_col, const U xi_edge0, const W xi_edge1) {
        using _T = underlying_type_t<T>;

        const _T edge0{ static_cast<_T>(xi_edge0) },
                 edge1{ static_cast<_T>(xi_edge1) };
        assert(static_cast<_T>(xi_edge0) < static_cast<_T>(xi_edge1) && " smoothstep(COLLECTION, a, b) - 'a' can not be smaller then 'b'.");

        // scalar normalized clamping
        auto clamp = [&](_T && _value, const _T _min, const _T _max) -> _T {
            return std::clamp((_value - _min) / (_max - _min), _T{}, static_cast<_T>(1));
        };

        // scalar Hermite interpolation
        auto hermite = [&](_T && _value) -> _T {
            return (_value * _value * _value * (_value * (_value * static_cast<_T>(6) - static_cast<_T>(15)) + static_cast<_T>(10)));
        };

        for_each(xi_col, [&](auto & elm) {
            elm = hermite(clamp(std::move(elm), edge0, edge1));
        });

        return xi_col;
    }

    template<typename T, typename U, typename W, REQUIRE(is_iterate_able_v<T> && Are_ArithmeticConvertible<underlying_type_t<T>, U, W>::value)>
    constexpr T smootherstep(const T& xi_col, const U xi_edge0, const W xi_edge1) {
        using _T = underlying_type_t<T>;

        const _T edge0{ static_cast<_T>(xi_edge0) },
                 edge1{ static_cast<_T>(xi_edge1) };
        assert(static_cast<_T>(xi_edge0) < static_cast<_T>(xi_edge1) && " smoothstep(collection, a, b) - 'a' can not be smaller then 'b'.");

        // scalar normalized clamping
        auto clamp = [&](_T && _value, const _T _min, const _T _max) -> _T {
            return std::clamp((_value - _min) / (_max - _min), _T{}, static_cast<_T>(1));
        };

        // scalar Hermite interpolation
        auto hermite = [&](_T && _value) -> _T {
            return (_value * _value * _value * (_value * (_value * static_cast<_T>(6) - static_cast<_T>(15)) + static_cast<_T>(10)));
        };

        auto col = FWD(xi_col);

        for_each(col, [&](auto & elm) {
            elm = hermite(clamp(std::move(elm), edge0, edge1));
        });

        return FWD(col);
    }

    /**
    * \brief given three collections: a, b, c - return 'a*b+c'
    *
    * @param {Collection, in}  a
    * @param {Collection, in}  b
    * @param {Collection, in}  c
    * @param {Collection, out} a*b+c
    **/
    template<typename T, typename U, REQUIRE(is_iterate_able_v<T> && Are_IterAbleEqualSize_v<Length_v<T>, U>)>
    constexpr T fma(const T& a, const U& b, const U& c) {
        using _T = underlying_type_t<T>;

        auto _a = FWD(a);

        for_each(_a, [&, i = 0](auto & elm) mutable {
            elm = std::fma(elm, static_cast<_T>(b[i]), static_cast<_T>(c[i]));
            ++i;
        });

        return FWD(_a);
    }

    /**
    * \brief return the length/magnitude (L2 norm) of an iterable, i.e. - sqrt(x[0]^2 + x[1]^2 + ...)
    *
    * @param {Iterab;e, in}  iterab;e
    * @param {T,        out} length
    **/
    template<typename T, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline underlying_type_t<T> length(T&& xi_vec) {
        return std::sqrt(dot(xi_vec));
    }
    template<typename T, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline underlying_type_t<T> length(const T& xi_vec) {
        return std::sqrt(dot(xi_vec));
    }

    /**
    * \brief return the distance between two vectors
    *
    * @param {VectorBase, in}  vector
    * @param {VectorBase, in}  vector
    * @param {T,          out} distance
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline underlying_type_t<T> distance(const T& xi_p0, const T& xi_p1) {
        return length(xi_p0 - xi_p1);
    }

    /**
    * \brief return the cross produce between two 1x3 vectors
    *
    * @param {VectorBase, in}  a
    * @param {VectorBase, in}  b
    * @param {VectorBase, out} axb
    **/
    template<typename T, REQUIRE(is_Vector_v<T> && (Length_v<T> == 3))> constexpr inline T cross(const T& x, const T& y) noexcept {
        return VectorBase<underlying_type_t<T>, 3>(x[1] * y[2] - y[1] * x[2],
                                                   x[2] * y[0] - y[2] * x[0],
                                                   x[0] * y[1] - y[0] * x[1]);
    }

    /**
    * \brief return the tangent of angle between two 1x3 vectors
    *
    * @param {VectorBase, in}  vector
    * @param {VectorBase, in}  vector
    * @param {T,          out} tan(angle between input vectors)
    **/
    template<typename T, REQUIRE(is_Vector_v<T> && (Length_v<T> == 2))>
    constexpr inline underlying_type_t<T> tangent(const T& a, const T& b) noexcept {
        return ((a.x * b.y - a.y * b.x) / (a.x * b.x + a.y * b.y));
    }

    template<typename T, REQUIRE(is_Vector_v<T> && (Length_v<T> == 3))>
    constexpr inline underlying_type_t<T> tangent(const T& a, const T& b) noexcept {
        return (length(cross(a, b)) / dot(a, b));
    }

    /**
    * \brief given a vector, return a vector in the same direction but with unit magnitude
    *
    * @param {VectorBase, in}  vector
    * @param {VectorBase, out} vector normalized
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline T Normalize(const T& xi_vec) {
        return (xi_vec / length(xi_vec));
    }
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline T Normalize(T&& xi_vec) {
        return (xi_vec / length(xi_vec));
    }

    /**
    * \brief given three vectors N, I, Nref: if Nref and I face in the same direction - return N, otherwise - return -N.
    *
    * @param {VectorBase, in}  N (vector to orient)
    * @param {VectorBase, in}  I (incident vector)
    * @param {VectorBase, in}  Nref (reference vector)
    * @param {VectorBase, out} dot(Nref, I) < 0 -> N, otherwise -> -N
    **/
    template<typename T, REQUIRE(is_Vector_v<T> && ((Length_v<T> == 2) || (Length_v<T> == 3)))>
    constexpr inline underlying_type_t<T> faceforward(const T& xi_N, const T& xi_I, const T& xi_Nref) {
        return (dot(xi_Nref, xi_I) < T{}) ? xi_N : (-xi_N);
    }

    /**
    * \brief given in incident vector I and surface orientation N (normalized vector), return the reflection direction: I - 2 * dot(N, I) * N
    *        notice that N must be normalized.
    *
    * @param {VectorBase, in}  I (incident vector)
    * @param {VectorBase, in}  N (normal vector)
    * @param {VectorBase, out} reflection direction
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline T reflect(const T& xi_I, const T& xi_N) {
        return (xi_I - static_cast<underlying_type_t<T>>(2) * dot(xi_I, xi_N) * xi_N);
    }

    /**
    * \brief given in incident vector I, surface orientation N (normalized vector), and ratio of indices of refractions, return the refraction vector.
    *
    * @param {VectorBase, in}  I (incident vector)
    * @param {VectorBase, in}  N (normal vector)
    * @param {U,          in}  eta (ratio of indices's of refraction)
    * @param {VectorBase, out} refraction direction
    **/
    template<typename T, typename U, REQUIRE(is_Vector_v<T>&& is_ArithmeticConvertible_v<U, underlying_type_t<T>>)>
    constexpr inline T refract(const T& xi_I, const T& xi_N, const U eta) {
        using _T = underlying_type_t<T>;

        const _T _eta{ static_cast<_T>(eta) },
                 _dot{ dot(xi_N, xi_I) },
                 k{ static_cast<_T>(1) - _eta * _eta * (static_cast<_T>(1) - _dot * _dot) };

        return (k > _T{}) ? (_eta * xi_I - (_eta * _dot + std::sqrt(k)) * xi_N) : T();
    }

    /**
    * \brief project one vector on the other
    *
    * @param {VectorBase, in}  vector to project
    * @param {VectorBase, in}  vector on which we project
    * @param {VectorBase, out} projected vector
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline T ProjectOn(const T& xi_to, const T& xi_on) {
        return (xi_on * (dot(xi_to, xi_on) / dot(xi_on)));
    }

    /**
    * \brief tests whether a vector is normalized.
    *
    * @param {VectorBase, in}  vector to test
    * @param {T,          in}  tolerance for normalization test (default is 2 * epsilon)
    * @param {bool,       out} true if squared length indicate a normalized algebraic structure.
    **/
    template<typename T, REQUIRE(is_Vector_v<T>)>
    constexpr inline bool IsNormalized(const T& xi_vec, 
                                       const underlying_type_t<T> xi_tol = static_cast<underlying_type_t<T>>(2) * std::numeric_limits<underlying_type_t<T>>::epsilon()) {
        return (std::abs(length(xi_vec) - static_cast<underlying_type_t<T>>(1)) < xi_tol);
    }

    /**
    * \brief return a unit orthogonal vector to a given vector
    *
    * @param {VectorBase, in}  vector
    * @param {VectorBase, out} unit orthogonal vector
    **/
    template<typename T, typename U, REQUIRE(is_Vector_v<T> && (Length_v<T> == 3))>
    constexpr T orthogonal(const T& xi_vec) noexcept {
        using _T = underlying_type_t<T>;

        // xi_vec minimal (or maximal) value
        const _T minValue = [&]() {
            _T _min{ min(xi_vec) };

            // avoid cases in which the input vector has a zero component
            if (std::abs(_min) < std::numeric_limits<_T>::epsilon()) {
                _min = max(xi_vec);
            }

            return _min;
        }();

        // unit vector composed of xi_vec minimal (or maximal) value
        T&& e(minValue);
        Normalize(e);

        // orthogonal vector
        return cross(xi_vec, e);
    }
}; // namespace GLSLCPP

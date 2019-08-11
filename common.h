/**
* common utiLties for GLSLS++
*
* Dan Israel Malta
**/
#pragma once
#include<type_traits>
#include<inttypes.h>
#include<cinttypes>
#include<iterator>
#include<algorithm>
#include<utility>
#include<functional>
#include<tuple>

namespace GLSLCPP {

    /**
    * forward declaration
    **/

    // base objects
    template<typename T, std::size_t N> class VectorBase;                                                   // general N elements vector
    template<typename T, std::size_t COL, std::size_t ROW> class MatrixBase;                                // general ROWxCOL matrix
    template<class VECTOR, typename T, std::size_t N, bool Unique, std::size_t ... Indexes> class Swizzle;  // general swizzling ("index changer") object

    // first generation objects
    template<typename T> class Vector2;   // general 2 elements vector
    template<typename T> class Vector3;   // general 3 elements vector
    template<typename T> class Vector4;   // general 4 elements vector

    // common type definitions (vectors)
    using ivec2 = Vector2<std::int32_t>;   // specialized 2 elements vector
    using uvec2 = Vector2<std::uint32_t>;  // specialized 2 elements vector
    using bvec2 = Vector2<bool>;           // specialized 2 elements vector
    using dvec2 = Vector2<double>;         // specialized 2 elements vector
    using vec2  = Vector2<float>;          // specialized 2 elements vector

    using ivec3 = Vector3<std::int32_t>;   // specialized 3 elements vector
    using uvec3 = Vector3<std::uint32_t>;  // specialized 3 elements vector
    using bvec3 = Vector3<bool>;           // specialized 3 elements vector
    using dvec3 = Vector3<double>;         // specialized 3 elements vector
    using vec3  = Vector3<float>;          // specialized 3 elements vector

    using ivec4 = Vector4<std::int32_t>;   // specialized 4 elements vector
    using uvec4 = Vector4<std::uint32_t>;  // specialized 4 elements vector
    using bvec4 = Vector4<bool>;           // specialized 4 elements vector
    using dvec4 = Vector4<double>;         // specialized 4 elements vector
    using vec4  = Vector4<float>;          // specialized 4 elements vector

    // common type definitions (matrix)
    using mat2  = MatrixBase<float, 2, 2>;  // specialized 2x2 matrix (column major)
    using dmat2 = MatrixBase<double, 2, 2>; // specialized 2x2 matrix (column major)

    using mat3 = MatrixBase<float, 3, 3>;   // specialized 3x3 matrix (column major)
    using dmat3 = MatrixBase<double, 3, 3>; // specialized 3x3 matrix (column major)

    using mat4 = MatrixBase<float, 4, 4>;   // specialized 4x2 matrix (column major)
    using dmat4 = MatrixBase<double, 4, 4>; // specialized 4x2 matrix (column major)

    using mat23  = MatrixBase<float, 2, 3>; // |
    using dmat23 = MatrixBase<double, 2, 3>;    //  \ 2 columns, 3 rows (two 1x3 columns)

    using mat24  = MatrixBase<float, 2, 4>; // |
    using dmat24 = MatrixBase<double, 2, 4>;    //  \ 2 columns, 4 rows (two 1x4 columns)

    using mat32  = MatrixBase<float, 3, 2>; // |
    using dmat32 = MatrixBase<double, 3, 2>;    //  \ 3 columns, 2 rows (three 1x2 columns)

    using mat34  = MatrixBase<float, 3, 4>; // |
    using dmat34 = MatrixBase<double, 3, 4>;    //  \ 3 columns, 4 rows (three 1x4 columns)

    using mat42  = MatrixBase<float, 4, 2>; // |
    using dmat42 = MatrixBase<double, 4, 2>;    //  \ 4 columns, 2 rows (four 1x2 columns)

    using mat43  = MatrixBase<float, 4, 3>; // |
    using dmat43 = MatrixBase<double, 4, 3>;    //  \ 4 columns, 3 rows (four 1x3 columns)

    // syntactic sugar for a more "modern" usage of SFINAE concept in template/function signatures (use with care)
#define REQUIRE(...) typename std::enable_if<__VA_ARGS__>::type* = nullptr

    // a helper to write less code
#define FWD(...) std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

    /**
    * type traits
    **/

    // type trait to test if an object is of type VectorBase
    template<typename>                  struct is_VectorBase : public std::false_type {};
    template<typename T, std::size_t N> struct is_VectorBase<VectorBase<T, N>> : public std::true_type {};
    template<typename T> inline constexpr bool is_VectorBase_v = is_VectorBase<T>::value;
    template<typename U> constexpr bool isVectorBase(const U&) { return is_VectorBase<U>::value; }

    // type trait to test if an object is a swizzle
    template<typename>                                                                    struct is_Swizzle : public std::false_type {};
    template<class TYPE, typename T, std::size_t N, bool Unique, std::size_t ... Indexes> struct is_Swizzle<Swizzle<TYPE, T, N, Unique, Indexes...>> : public std::true_type {};
    template<typename T> inline constexpr bool is_Swizzle_v = is_Swizzle<T>::value;

    // type trait to test if an object is of type MatrixBase
    template<typename>                                     struct is_MatrixBase : public std::false_type {};
    template<typename T, std::size_t COL, std::size_t ROW> struct is_MatrixBase<MatrixBase<T, COL, ROW>> : public std::true_type {};
    template<typename T> inline constexpr bool is_MatrixBase_v = is_MatrixBase<T>::value;
    template<typename U> constexpr bool isMatrixBase(const U&) { return is_MatrixBase<U>::value; }

    // type trait to test if an object is of type Vector2
    template<typename>   struct is_Vector2 : public std::false_type {};
    template<typename T> struct is_Vector2<Vector2<T>> : public std::true_type {};
    template<typename U> constexpr bool isVector2(const U&) { return is_Vector2<U>::value; }

    // type trait to test if an object is of type Vector3
    template<typename>   struct is_Vector3 : public std::false_type {};
    template<typename T> struct is_Vector3<Vector3<T>> : public std::true_type {};
    template<typename U> constexpr bool isVector3(const U&) { return is_Vector3<U>::value; }

    // type trait to test if an object is of type Vector4
    template<typename>   struct is_Vector4 : public std::false_type {};
    template<typename T> struct is_Vector4<Vector4<T>> : public std::true_type {};
    template<typename U> constexpr bool isVector4(const U&) { return is_Vector4<U>::value; }

    // type trait to test if an object if of type VectorBase/Vector2/Vector3/Vector4
    template<typename>                  struct is_Vector : public std::false_type {};
    template<typename T>                struct is_Vector<Vector2<T>> : public std::true_type {};
    template<typename T>                struct is_Vector<Vector3<T>> : public std::true_type {};
    template<typename T>                struct is_Vector<Vector4<T>> : public std::true_type {};
    template<typename T, std::size_t N> struct is_Vector<VectorBase<T, N>> : public std::true_type {};
    template<typename T> inline constexpr bool is_Vector_v = is_Vector<T>::value;
    template<typename U> constexpr bool isVector(const U&) { return is_Vector<U>::value; }

    // return the underlying type of any collection which has begin() iterator
    template<typename T> using underlying_type_t = std::remove_reference_t<decltype(*std::begin(std::declval<T&>()))>;

    // test if an object is a rvalue vector
    template<typename T> struct is_VectorRvalue {
        static constexpr bool value{ is_Vector_v<T> && std::is_rvalue_reference<T>::value };
    };
    template<typename U> constexpr bool isVectorRalue(const U&) { return is_VectorRvalue<U>::value; }

    // test if an object is a lvalue vector
    template<typename T> struct is_VectorLvalue {
        static constexpr bool value{ is_Vector_v<T> && std::is_lvalue_reference<T>::value };
    };
    template<typename U> constexpr bool isVectorLalue(const U&) { return is_VectorLvalue<U>::value; }

    // type trait to test if a pack of object are of types Vector
    template<typename ...Ts> struct Are_VectorBases {
        static constexpr bool value{ (is_Vector_v<Ts> && ...) };
    };

    // type trait to test if a POD 'T' is both arithmetic and convertible to 'U'
    template<typename T, typename U> struct is_ArithmeticConvertible {
        static constexpr bool value{ std::is_arithmetic<T>::value && std::is_convertible<T, U>::value };
    };
    template<typename T, typename U> inline constexpr bool is_ArithmeticConvertible_v = is_ArithmeticConvertible<T, U>::value;

    // type trait to test if a pack of POD's 'Ts' are both arithmetic and convertible to 'U'
    // notice the reversal in parameter order as apposed to 'is_ArithmeticConvertible'.
    template<typename U, typename ...Ts> struct Are_ArithmeticConvertible {
        static constexpr bool value{ (std::is_arithmetic_v<Ts> && ...) && (std::is_convertible_v<Ts, U> && ...) };
    };

    // get the number of elements in an object (if object is not defined in this header - his size is 0)
    template<typename>                                                                    struct Length { static constexpr std::size_t value{ 0 }; };
    template<typename T, std::size_t N>                                                   struct Length<VectorBase<T, N>> { static constexpr std::size_t value{ N }; };
    template<typename T, std::size_t COL, std::size_t ROW>                                struct Length<MatrixBase<T, COL, ROW>> { static constexpr std::size_t value{ ROW * COL }; };
    template<class TYPE, typename T, std::size_t N, bool Unique, std::size_t ... Indexes> struct Length<Swizzle<TYPE, T, N, Unique, Indexes...>> { static constexpr std::size_t value{ N }; };
    template<typename T>                                                                  struct Length<Vector2<T>> { static constexpr std::size_t value{ 2 }; };
    template<typename T>                                                                  struct Length<Vector3<T>> { static constexpr std::size_t value{ 3 }; };
    template<typename T>                                                                  struct Length<Vector4<T>> { static constexpr std::size_t value{ 4 }; };
    template<typename T> inline constexpr std::size_t Length_v = Length<T>::value;

    // type trait to test if a 'T' is a vector of length 'LEN'
    template<typename T, std::size_t LEN> struct Is_VectorOfLength {
        static constexpr bool value{ is_Vector_v<T> && (Length_v<T> == LEN) };
    };
    template<typename T, std::size_t LEN> inline constexpr bool Is_VectorOfLength_v = Is_VectorOfLength<T, LEN>::value;

    // type trait to test if two objects are vectors with the same length
    template<typename T, typename U> struct Are_TwoVectorsSimilar {
        static constexpr bool value{ is_Vector_v<T> && is_Vector_v<U> && (Length_v<T> == Length_v<U>) };
    };
    template<typename T, typename U> inline constexpr bool Are_TwoVectorsSimilar_v = Are_TwoVectorsSimilar<T, U>::value;

    // type trait to test if a pack of objects are of types Vector and have the same length (N)
    template<typename T, std::size_t N, typename ...Ts> struct Are_VectorsSimilar {
        static constexpr bool value{ (is_Vector_v<Ts> && ...) &&
                                     (std::is_same<std::remove_reference_t<decltype(*std::begin(std::declval<Ts&>()))>,T>::value && ...) &&
                                     ((Length_v<Ts> == N) && ...) };
    };

    // test if a swizzle indices's are unique
    template<typename>                                                       struct is_SwizzleUnique : public std::false_type {};
    template<class TYPE, typename T, std::size_t N, std::size_t ... Indexes> struct is_SwizzleUnique<Swizzle<TYPE, T, N, false, Indexes...>> : public std::false_type {};
    template<class TYPE, typename T, std::size_t N, std::size_t ... Indexes> struct is_SwizzleUnique<Swizzle<TYPE, T, N, true, Indexes...>> : public std::true_type {};
    template<typename U> constexpr bool isSwizzleUnique(const U&) { return is_SwizzleUnique<U>::value; }

    // test if an object is a swizzle of a given length
    template<class U, std::size_t N> struct is_SwizzleOfLength {
        static constexpr bool value{ is_Swizzle_v<U> && (Length_v<U> == N) };
    };
    template<typename T, std::size_t N> inline constexpr bool is_SwizzleOfLength_v = is_SwizzleOfLength<T, N>::value;


    // get MatrixBase number of rows
    template<typename>                                     struct Rows { static constexpr std::size_t value{ 0 }; };
    template<typename T, std::size_t COL, std::size_t ROW> struct Rows<MatrixBase<T, COL, ROW>> { static constexpr std::size_t value{ ROW }; };
    template<typename T> inline constexpr std::size_t Rows_v = Rows<T>::value;

    // get MatrixBase number of columns
    template<typename>                                     struct Columns { static constexpr std::size_t value{ 0 }; };
    template<typename T, std::size_t COL, std::size_t ROW> struct Columns<MatrixBase<T, COL, ROW>> { static constexpr std::size_t value{ COL }; };
    template<typename T> inline constexpr std::size_t Columns_v = Columns<T>::value;

    // test if a matrix is cubic
    template<typename T> struct is_Cubic {
        static constexpr bool value{ is_MatrixBase_v<T> && (Rows_v<T> == Columns_v<T>) };
    };

    // test if an object is iterate-able
    template<typename T, typename = void>                  struct is_iterate_able : public std::false_type {};
    template<typename T>                                   struct is_iterate_able<T, std::void_t<decltype(std::begin(std::declval<T>())),
                                                                                                 decltype(std::end(std::declval<T>()))>> : public std::true_type  {};
    template<typename T>                                   struct is_iterate_able<Vector2<T>> : public std::true_type {};
    template<typename T>                                   struct is_iterate_able<Vector3<T>> : public std::true_type {};
    template<typename T>                                   struct is_iterate_able<Vector4<T>> : public std::true_type {};
    template<typename T, std::size_t N>                    struct is_iterate_able<VectorBase<T, N>> : public std::true_type {};
    template<typename T, std::size_t COL, std::size_t ROW> struct is_iterate_able<MatrixBase<T, COL, ROW>> : public std::true_type {};
    template<typename T> inline constexpr bool is_iterate_able_v = is_iterate_able<T>::value;

    // test if an object underlying type is 'bool'
    template<typename>                         struct is_UnderlyingBool : public std::false_type {};
    template<>                                 struct is_UnderlyingBool<Vector2<bool>> : public std::true_type {};
    template<>                                 struct is_UnderlyingBool<Vector3<bool>> : public std::true_type {};
    template<>                                 struct is_UnderlyingBool<Vector4<bool>> : public std::true_type {};
    template<std::size_t N>                    struct is_UnderlyingBool<VectorBase<bool, N>> : public std::true_type {};
    template<std::size_t COL, std::size_t ROW> struct is_UnderlyingBool<MatrixBase<bool, COL, ROW>> : public std::true_type {};
    template<typename T> inline constexpr bool is_UnderlyingBool_v = is_UnderlyingBool<T>::value;
    template<typename U> constexpr bool isUnderlyingBool(const U&) { return is_UnderlyingBool<U>::value; }

    // test if an object is iterate-able and of length 'N'
    template<std::size_t N, typename T> struct is_IterAbleOfSize {
        static constexpr bool value{ is_iterate_able_v<T> && (Length_v<T> == N) };
    };

    // test if a pack of objects are iter-able
    template<typename ...Ts> struct Are_IterAble {
        static constexpr bool value{ (is_iterate_able_v<Ts> && ...) };
    };

    // test if a pack of objects are iter-able anf have 'N' elements
    template<std::size_t N, typename ...Ts> struct Are_IterAbleEqualSize {
        static constexpr bool value{ (is_iterate_able_v<Ts> && ...) &&
                                     ((Length_v<Ts> == N) && ...) };
    };
    template<std::size_t N, typename ...Ts> inline constexpr bool Are_IterAbleEqualSize_v = Are_IterAbleEqualSize<N, Ts...>::value;

    // test if an object is a rvalue iterable
    template<typename T> struct is_IterableRvalue {
        static constexpr bool value{ is_iterate_able_v<T> && std::is_rvalue_reference<T>::value };
    };
    template<typename U> constexpr bool isIterableRalue(const U&) { return is_IterableRvalue<U>::value; }

    // test if an object is a lvalue iterable
    template<typename T> struct is_IterableLvalue {
        static constexpr bool value{ is_iterate_able_v<T> && std::is_lvalue_reference<T>::value };
    };
    template<typename U> constexpr bool isIterableLalue(const U&) { return is_IterableLvalue<U>::value; }

    // return the N'th argument in a parameter pack (N is required at compile time)
    template<std::size_t N, typename... Args> constexpr decltype(auto) getArgument(Args&& ... as) noexcept {
        return std::get<N>(std::forward_as_tuple(FWD(as)...));
    }

    /**
    * \brief a simple syntactic sugar for std::any_of on a given collection.
    *        if collection underlying type is boolean - then return true if any
    *        of the elements is 'true'.
    *
    * @param {collection, in} reference to collection on which std::any_of shall operate
    * @param {function,   in} std::any_of predicate
    **/
    template<class T, class Fn, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline bool any(T&& xi_collection, Fn&& xi_function) {
        return std::any_of(xi_collection.begin(), xi_collection.end(), FWD(xi_function));
    }
    template<class T, class Fn, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline bool any(const T& xi_collection, Fn&& xi_function) {
        auto collection = FWD(xi_collection);
        return std::any_of(collection.begin(), collection.end(), FWD(xi_function));
    }

    template<class T, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline bool any(T&& xi_collection) {
        return any(xi_collection, [](auto & elm) { return elm; });
    }
    template<class T, REQUIRE(is_iterate_able_v<T>)>
    constexpr inline bool any(const T& xi_collection) {
        auto collection = FWD(xi_collection);
        return any(collection, [](auto & elm) { return elm; });
    }

    /**
    * \brief a simple syntactic sugar for std::all_of on a given collection.
    *        if collection underlying type is boolean - then return true if all
    *        the elements are 'true'.
    *
    * @param {collection, in} reference to collection on which std::any_of shall operate
    * @param {function,   in} std::any_of predicate
    **/
    template<class T, class Fn, REQUIRE(is_iterate_able_v<T>)>
    inline bool all(T&& xi_collection, Fn&& xi_function) {
        return std::all_of(xi_collection.begin(), xi_collection.end(), FWD(xi_function));
    }
    template<class T, class Fn, REQUIRE(is_iterate_able_v<T>)>
    inline bool all(const T& xi_collection, Fn&& xi_function) {
        auto collection = FWD(xi_collection);
        return std::all_of(collection.begin(), collection.end(), FWD(xi_function));
    }

    template<class T, REQUIRE(is_iterate_able_v<T>)>
    inline bool all(T&& xi_collection) {
        return all(xi_collection, [](auto & elm) { return elm; });
    }
    template<class T, REQUIRE(is_iterate_able_v<T>)>
    inline bool all(const T& xi_collection) {
        auto collection = FWD(xi_collection);
        return all(collection, [](auto & elm) { return elm; });
    }

    /**
    * \brief return component wise logical complement of a boolean iterable collection
    *
    * @param {collection, in}  reference to collection whos underlying type is boolean
    * @param {collection, out} component wise logical complement of input vector
    **/
    template<class T, REQUIRE(is_UnderlyingBool_v<T>)>
    inline T Not(T&& xi_collection) {
        auto _collection = FWD(xi_collection);
        for_each(_collection, [&](auto & elm) {
            elm = !elm;
        });
        return FWD(_collection);
    }
    template<class T, REQUIRE(is_UnderlyingBool_v<T>)>
    inline T Not(const T& xi_collection) {
        static_assert(is_UnderlyingBool_v<T>, "");
        auto _collection = FWD(xi_collection);
        for_each(_collection, [&](auto & elm) {
            elm = !elm;
        });
        return FWD(_collection);
    }

    /**
    * \brief a simple syntactic sugar for per-element iteration and transformation, in a non sequentially manner, on a given collection
    *
    * @param {collection, in} reference to iterated and transformed collection
    * @param {function,   in} function to be applied on collection elements
    **/
    template<class T, class Fn, REQUIRE(is_iterate_able<T>::value)>
    inline void for_each(T&& xi_collection, Fn&& xi_function) {
        std::for_each(/*std::execution::unseq,*/ xi_collection.begin(), xi_collection.end(), FWD(xi_function));
    }

    /**
    * \brief a simple wrapper for std::reduce, which is performed in non sequential manner.
    *
    * @param {output,     in}  output initial value
    * @param {collection, in}  reference to iterated collection
    * @param {function,   in}  binary function to be applied
    * @param {output,     out} arithmetic value changed by operation
    **/
    template<typename T, class V, class Fn, REQUIRE(std::is_arithmetic<T>::value&& is_iterate_able_v<V>)>
    constexpr inline T reduce(T xi_init, V&& xi_collection, Fn&& xi_function) {
        return std::reduce(/*std::execution::unseq,*/ xi_collection.cbegin(), xi_collection.cend(), xi_init, FWD(xi_function));
    }

    /**
    * \brief a simple wrapper for std::transform_reduce, which is performed in non sequential manner on two vectors
    *
    * @param {value,      in}  reduction function initial value
    * @param {collection, in}  reference to first collection
    * @param {collection, in}  reference to second collection
    * @param {function,   in}  reduction function to be applied (binary function)
    * @param {function,   in}  transformation function to be applied (on pair of elements from both collections)
    * @param {output,     out} arithmetic value changed by operation
    **/
    template<typename T, class V1, class V2, class BFn1, class BFn2, REQUIRE(is_iterate_able_v<V1> && is_iterate_able_v<V2> && std::is_arithmetic_v<T>)>
    constexpr inline T transform_reduce(V1&& xi_collection1, V2&& xi_collection2, T xi_init, BFn1&& xi_function1, BFn2&& xi_function2) {
        return std::transform_reduce(/*std::execution::unseq,*/ xi_collection1.cbegin(), xi_collection1.cend(), xi_collection2.cbegin(),
                                     xi_init, FWD(xi_function1), FWD(xi_function2));
    }

    /**
    * compile time for loop (a modification of an implementation I saw somewhere on the Internet)
    **/
    namespace static_for_detail {
        template<std::size_t lower, std::size_t... Is, class F> constexpr void static_for_impl(F&& f, std::index_sequence<Is...>) {
            ((void)f(std::integral_constant<std::size_t, Is + lower>{}), ...);
        }
    }
    template<std::size_t Lower, std::size_t Upper, class F> constexpr void static_for(F&& f) {
        static_for_detail::static_for_impl<Lower>(FWD(f), std::make_index_sequence<Upper - Lower>{});
    }

}; // namespace GLSLCPP
# GLSL++

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/60dee26081f547baa293ccf2dc7b7002)](https://www.codacy.com/app/DanIsraelMalta/GLSL-CPP?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DanIsraelMalta/GLSL-CPP&amp;utm_campaign=Badge_Grade)

A generic, modern and extensible numerical toolkit following the syntax and functionality of the GLSL shading language as defined in its [specification.](https://www.khronos.org/registry/OpenGL/specs/gl/)

Although the library is aimed mainly at 3D software developers as it's meant to ease the c++ shader bridge by providing common syntax, it can be used for any application requiring generic, portable and efficient numerical operations. 
This library is not limited to GLSL features alone, as it include numerous mathematical constructs and functionalities spanning a wide range of numerical realms.

###### Documentation

* [FAQ](#FAQ)
* [Vector Constructs](#Numerical-Constructs)
* [Swizzling](#Swizzling)
* [Matrix Constructs](#Matrix-Constructs)
* [Numerical Operators](#Numerical-Operators)
* [Bitwise Operators](#Bitwise-Operators)
* [Relational Operators](#Relational-Operators)
* [Functions](#Functions)
* [Quaternion](#Quaternion)
* [Interval](#Interval)
* [Scalar Functions](#Scalar Functions)

## FAQ

### How to use? Which compiler is required?

GLSL++ requires a compiler which supports c++17.
So far it was only tested and compiled with MSVC X86.
Just include 'GLSL+++.h' in your project and add an include path to its resident directory.

### Why another linear algebra library?

I wanted a numerical toolkit which is...
* Encompassing in its functionality, but doesn't slow down compile times and complicate inclusions into projects.
* Allow me to write with the exact syntax of the GLSL language, but is not restricted by its specific functionality.
* Is small enough, can be easily dropped into a project, and imposes no restrictions on software design (either architecturally or legally).
* Is efficient without sacrificing readability and extensibility.

... since I haven't found one, I wrote one.

### Why are there no explicit SIMD intrinsics inside the code?

If your main focus is on high performance code, then explicit SIMD intrinsics is the way to go.
But, it has several downsides to it, most notoriously:
* it is not portable (for instance, at current time, WebAssembly doesn't support SIMD) and uses different instructions on different hardware architectures.
* It requires a lot of compiler directives to make sure you use the correct intrinsic, and the user has to manually update it every time a new intrinsic ships out.
* It is not readable, nor hackable.
* It hides the underlying algorithm, and it also make it harder to argue if a given algorithm was implemented in a correct manner.

On the other hand:
* compilers have come a long way in automatically vectorizing code, and they get better with every new release.
* why not focus on things which are on the developer side (API, memory access, correct usage and implementation of algorithms) and let the compiler take care of vectorization.
* c++20 will ship with SIMD wrapper as part of the STL (and when its is out, I will integrate it)...

### OK, so there is no usage of explicit SIMD intrinsics, I guess expression templates are used, right?

Expression templates are great for lazy evaluation and loop fusion, but anyone who has implemented them in the past knows that they have a few problems here and there (aliasing, cache trashing, in certain situations they actually create more operations the required - see matrix * matrix * vector expression).
The only way to solve it is either using some sort of smart expression template system (difficult to debug and design correctly with scalability in mind) or hand over the control to the user (whether with compiler directives which enable/disable the expression template mechanism, or using the notorious 'eval' method).
Another problem with expression templates is extending them to variadic operations, i.e. - it is easy to embeed the operation 'min(vector1, vector2)' in expression graph, but it is harder to support 'min(vector1, ...)'.
Trying to avoid this sort of complexities means that there wont be any expression template mechanism in here.
So, how hard will it impact performance? if we are using small fixed size constructs - not to much.

### WTF!@#! no SIMD and no expression template? can I use this library in CPU hungry operations?

Although GLSL++ was designed with readability and scalability in mind, performance was not overlooked.
And as always, if in dought, measure!

## Vector Constructs

### 'VectorBase<T, N>'

'VectorBase<T, N>' represents a fixed size numerical vector containing 'N' elements of type 'T'.

available construction options:

* 'VectorBase<T, N>(U value)'                   - constructs a vector such that all its elements have the value of 'value' converted to type 'T'.
* 'VectorBase<T, N>(U value1, U value2, ...)'   - constructs a vector from exactly 'N' elements of type 'U' converted to type 'T'.
* 'VectorBase<T, N>(swizzle)'                   - constructs a vector from a [swizzle](#Swizzling) of size 'N'.
* 'VectorBase<T, N>(VectorBase<U, N> value)'    - constructs a vector from another vector with exactly 'N' elements of type 'U' converted to type 'T'.
* 'VectorBase<T, N>(std::function<T(size_t)>)'  - constructs a vector using a builder function. The function accepts element index and return a value.

available assignment options:

* 'VectorBase<T, N> = U value'                   - assigns a 'value' given as 'U' type to all vectors elements (converted to type 'T').
* 'VectorBase<T, N> = {U value1, U value2, ...}' - assigns exactly 'N' elements of type 'U' (converted to type 'T').
* 'VectorBase<T, N> = swizzle'                   - assigns a [swizzle](#Swizzling) of length 'N' to vector elements.
* 'VectorBase<T, N> = VectorBase<T, N>'          - assigns the elements from right-hand-side vector.
* 'VectorBase<T, N> = std::function<T(size_t)>'  - constructs a vector using a builder function. The function accepts element index and return a value.

element accessors:

* 'operator []' allow to access an element by its index.

available utilities:

* 'begin', 'rbegin', 'cbegin', 'crbegin', 'end', 'rend', 'cend', 'crend' allow element wise iteration.
* 'length' method returns number of elements in vector.

Although it is obvious, I should write it anyway - all the above utilities are available in all the specialized vectors.

### 2 elemens vector (replicate a GLSL builtin)

the following 2 elements vectors are available:
* Vector2<T> - a general 2 elements vector.
* bvec2      - a 2 elements vector whose elements are of type boolean.
* ivec2      - a 2 elements vector whose elements are of type integer (32 bit).
* uvec2      - a 2 elements vector whose elements are of type unsigned integer (32 bit).
* vec2       - a 2 elements vector whose elements are of type float.
* dvec2      - a 2 elements vector whose elements are of type double.

available construction options:

* 'Vector2<T>(U value)'            - all elements have the value of 'value' converted to type 'T'.
* 'Vector2<T>(U value0, W value1)' - first element is 'value0' converted to 'T', second element is 'value1' converted to 'T'.
* 'Vector2<T>(VectorBase<U, N>)'   - construct from a 'VectorBase' (or its descendant) whose length is equal or larger then 2.
* 'Vector2<T>(swizzle)'            - construct from a [swizzle](#Swizzling) whose length is equal or larger then 2.

available assignment options:

* 'Vector2<T> = swizzle'          - assigns a [swizzle](#Swizzling) of length 2 to vector elements.
* 'Vector2<T> = VectorBase<U, N>' - assigns the elements from right-hand-side vector, whose length is equal or larger then 2.

### 3 elemens vector (replicate a GLSL builtin)

the following 3 elements vectors are available:
* Vector3<T> - a general 3 elements vector.
* bvec3      - a 3 elements vector whose elements are of type boolean.
* ivec3      - a 3 elements vector whose elements are of type integer (32 bit).
* uvec3      - a 3 elements vector whose elements are of type unsigned integer (32 bit).
* vec3       - a 3 elements vector whose elements are of type float.
* dvec3      - a 3 elements vector whose elements are of type double.

available construction options:

* 'Vector3<T>(U value)'                      - all elements have the value of 'value' converted to type 'T'.
* 'Vector3<T>(U value0, W value1, V value2)' - first element is 'value0' converted to 'T', second element is 'value1' converted to 'T', third element is 'value2' converted to 'T'.
* 'Vector3<T>(VectorBase<U, N>)'             - construct from a 'VectorBase' (or its descendant) whose length is equal or larger then 3.
* 'Vector3<T>(swizzle)'                      - construct from a [swizzle](#Swizzling) whose length is equal or larger then 3.
* 'Vector3<T>(Vector2<U> vector, W value)'   - constructs the first two elements from 'vector', and the third element from 'value'.
* 'Vector3<T>(W value, Vector2<U> vector)'   - constructs the first element from 'value', and the last two elements from 'vector'.
* 'Vector3<T>(Swizzle, W value)'             - constructs the first two elements from 2 elements [swizzle](#Swizzling), and the third element from 'value'.
* 'Vector3<T>(W value, Swizzle)'             - constructs the first element from 'value', and the last two elements from 2 elements [swizzle](#Swizzling).

available assignment options:

* 'Vector3<T> = swizzle'          - assigns a [swizzle](#Swizzling) of length 3 to vector elements.
* 'Vector3<T> = VectorBase<U, N>' - assigns the elements from right-hand-side vector, whose length is equal or larger then 3.

### 4 elemens vector (replicate a GLSL builtin)

the following 4 elements vectors are available:
* Vector4<T> - a general 4 elements vector.
* bvec4      - a 4 elements vector whose elements are of type boolean.
* ivec4      - a 4 elements vector whose elements are of type integer (32 bit).
* uvec4      - a 4 elements vector whose elements are of type unsigned integer (32 bit).
* vec4       - a 4 elements vector whose elements are of type float.
* dvec4      - a 4 elements vector whose elements are of type double.

available construction options:

* 'Vector4<T>(U value)'                                - all elements have the value of 'value' converted to type 'T'.
* 'Vector4<T>(U value0, W value1, V value2, R value3)' - first element is 'value0' converted to 'T', second element is 'value1' converted to 'T', third element is 'value2' converted to 'T', fourth element is 'value3' converted to 'T'.
* 'Vector4<T>(VectorBase<U, N>)'                       - construct from a 'VectorBase' (or its descendant) whose length is equal or larger then 4.
* 'Vector4<T>(swizzle)'                                - construct from a [swizzle](#Swizzling) whose length is equal or larger then 4.
* 'Vector4<T>(Vector2<U> vector, Vector2<W> vector1)'  - first and second elements are taken from 'vector', third and fourth elements are taken from 'vector1'.
* 'Vector4<T>(Vector2<U> vector, W value1, R value2)'  - first and second elements are taken from 'vector', third element from 'value1', fourth element from 'value2'.
* 'Vector4<T>(W value1, Vector2<U> vector, R value2)'  - first element from 'value1', second and third elements from 'vector',  fourth element from 'value2'.
* 'Vector4<T>(W value1, R value2, Vector2<U> vector)'  - first element from 'value1', second element from 'value2', third and fourth elements from 'vector'.
* 'Vector4<T>(Swizzle1, Swizzle2)'                     - first and second elements are taken from 2 elements [swizzle](#Swizzling), third and fourth elements are taken from 2 elements [swizzle](#Swizzling).
* 'Vector4<T>(Swizzle, W value1, R value2)'            - first and second elements are taken from 2 elements [swizzle](#Swizzling), third element from 'value1', fourth element from 'value2'.
* 'Vector4<T>(W value1, Swizzle, R value2)'            - first element from 'value1', second and third elements from 2 elements [swizzle](#Swizzling),  fourth element from 'value2'.
* 'Vector4<T>(W value1, R value2, Swizzle)'            - first element from 'value1', second element from 'value2', third and fourth elements from 2 elements [swizzle](#Swizzling).
* 'Vector4<T>(Vector3<U> vector, W value)'             - constructs the first three elements from 'vector', and the third element from 'value'.
* 'Vector4<T>(W value, Vector3<U> vector)'             - constructs the first element from 'value', and the last three elements from 'vector'.
* 'Vector4<T>(Swizzle, W value)'                       - constructs the first two elements from 3 elements [swizzle](#Swizzling), and the third element from 'value'.
* 'Vector4<T>(W value, Swizzle)'                       - constructs the first element from 'value', and the last two elements from 3 elements [swizzle](#Swizzling).

available assignment options:

* 'Vector4<T> = swizzle'          - assigns a [swizzle](#Swizzling) of length 4 to vector elements.
* 'Vector4<T> = VectorBase<U, N>' - assigns the elements from right-hand-side vector, whose length is equal or larger then 4.

### Swizzling

Although any vector can be accessed by the '[]' operator, they often have a name or an interpretation given as a single letter.
As a notational convenience, several letters are associated with each component based on common usage of position, color or texture coordinate vectors.
The individual components can be selected by following the variable name with a period (.) and then the component name.
Supported component names:

```c

|--------------|--------------------------------------------------------------------|
| {x, y, z, w} | Useful when accessing vectors that represent points or directions. |
| {r, g, b, a} | Useful when accessing vectors that represent colors.               |
| {s, t, p, q} | Useful when accessing vectors that represent texture coordinates.  |

```

The component selection syntax allow multiple components to be selected by appending their names (from the same set) after the period (.), example:

```c

vec4 v4;
v4.rgba; // is a vec4 and the same as just using v4
v4.rgb;  // is a vec3
v4.b;    // is a float
v4.xy;   // is a vec2
v4.xgba; // is illegal - the component names do not come from the same set.
```

The order of the components can be different to swizzle them, or replicated:

```c
vec4 pos  = vec4(1.0, 2.0, 3.0, 4.0);
vec4 swiz = pos.wzyx; // swiz = (4.0, 3.0, 2.0, 1.0)
vec4 dup  = pos.xxyy; // dup = (1.0, 1.0, 2.0, 2.0)
float f   = 1.2;
vec4 dup  = f.xxxx;   // dup = (1.2, 1.2, 1.2, 1.2)
```

The component group notation can occur on the left hand side of an expression:

```c
vec4 pos = vec4(1.0, 2.0, 3.0, 4.0);
pos.xw = vec2(5.0, 6.0);      // pos = (5.0, 2.0, 3.0, 6.0)
pos.wx = vec2(7.0, 8.0);      // pos = (8.0, 2.0, 3.0, 7.0)
pos.xx = vec2(3.0, 4.0);      // illegal - 'x' used twice
pos.xy = vec3(1.0, 2.0, 3.0); // illegal - mismatch between vec2 and vec3
```

To form a "l-value", swizzling must be applied to a "l-value" of vector or scalar type, contain no duplicate
components, and it results in a "l-value" of scalar or vector type, depending on number of components
specified.


## Matrix Constructs

### MatrixBase<T, COL, ROW> 

'MatrixBase<T, COL, ROW>' represents a fixed size matrix composed of elements of type 'T'. It has 'ROW' rows and 'COL' columns. Matrix underlying layout is column major.
The following demonstrates matrix layout:

```c

// a = {1, 3,
//      2, 4 } <- matrix is filled in column by column
MatrixBase<std::int32_t, 2, 2> a(1, 2, 3, 4);

// a = {1, 4,
//      2, 5, 
/       3, 6 } <- matrix is filled in column-first order
MatrixBase<std::int32_t, 2, 3> a(1, 2, 3, 4, 5, 6);

```

available construction options:

* 'MatrixBase<T, COL, ROW>()'                                 - availabe only for cubic matrix. constructs an identity matrix ('I'; all '0' except the diagnoal which is '1').
* 'MatrixBase<T, COL, ROW>(U value)'                          - constructs a matrix such that all its elements have the value of 'value' converted to type 'T'.
* 'MatrixBase<T, COL, ROW>(U value1, U value2, ...)'          - constructs a matrix from exactly 'COL'*'ROW' elements of type 'U' converted to type 'T'.
* 'MatrixBase<T, COL, ROW>(VectorBase<U, N> value)'           - constructs a matrix from A with exactly 'COL'*'ROW' elements of type 'U' converted to type 'T'.
* 'MatrixBase<T, COL, ROW>(MatrixBase<U, COL, ROW> value)'    - constructs a matrix from another matrix with with identical size and layout, with elements of type 'U' converted to type 'T'.
* 'MatrixBase<T, COL, ROW>(MatrixBase<U, COL1, ROW1> value)'  - constructs a matrix from another smaller matrix. The constructed matrix would be exatly like the argument matrix on the same elements, and the rest of its elements will either be an 'I' matrix if it is cubic, or null otherwise.
* 'MatrixBase<T, COL, ROW>(VectorBase<T, ROW> col0, VectorBase<T, ROW> col1, ...)' - constrcut a matrix by its columns. The user supplies 'COL' vectors of type 'T' and length 'ROW' from which the matrix columns are built.

available assignment options:

* 'MatrixBase<T, COL, ROW> = U value'                   - assigns a 'value' given as 'U' type to all matrix elements (converted to type 'T').
* 'MatrixBase<T, COL, ROW> = {U value1, U value2, ...}' - assigns exactly 'ROW'*'COL' elements of type 'U' (converted to type 'T').
* 'MatrixBase<T, COL, ROW> = VectorBase<ROW*COL, N>'    - assigns the elements from right-hand-side vector.
* 'MatrixBase<T, COL, ROW> = MatrixBase<Tu, COL, ROW>'  - assigns a mstrix of indetical size and layout.

element accessors:

* 'operator (col, row)' allow to access element by specifying the pair (column, row).
* 'operator [i]' allow to access to column #i. example:

```c

// a = {1, 4,
//      2, 5,
//      3, 6}
MatrixBase<int, 2, 3> a(1, 2, 3, 4, 5, 6);

// column0 = {1, 2, 3}
ivec3 column0 = av[0];

// a = {1, 5,
//      2, 4,
//      3, 8}
av[1] = ivec3(5, 4, 8);

```

available utilities:

* 'begin', 'rbegin', 'cbegin', 'crbegin', 'end', 'rend', 'cend', 'crend' allow element wise iteration.
* 'length' method returns number of elements in vector.

Although it is obvious, I should write in anyway - all the above utilities are available in all MatrixrBase children.

### 2x2 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 2x2 matrix are available:
* mat2  - a column major 2x2 matrix whose elements are of type float.
* dmat2 - a column major 2x2 matrix whose elements are of type double.

### 2x3 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 2x3 matrix are available:
* mat23  - a column major 2x3 matrix whose elements are of type float.
* dmat23 - a column major 2x3 matrix whose elements are of type double.

### 2x4 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 2x4 matrix are available:
* mat24  - a column major 2x4 matrix whose elements are of type float.
* dmat24 - a column major 2x4 matrix whose elements are of type double.

## 3x2 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 3x3 matrix are available:
* mat32  - a column major 3x2 matrix whose elements are of type float.
* dmat32 - a column major 3x2 matrix whose elements are of type double.

### 3x3 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 3x3 matrix are available:
* mat3  - a column major 3x3 matrix whose elements are of type float.
* dmat3 - a column major 3x3 matrix whose elements are of type double.

### 3x4 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 2x4 matrix are available:
* mat34  - a column major 3x4 matrix whose elements are of type float.
* dmat34 - a column major 3x4 matrix whose elements are of type double.

## 4x2 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 3x3 matrix are available:
* mat42  - a column major 4x2 matrix whose elements are of type float.
* dmat42 - a column major 4x2 matrix whose elements are of type double.

### 4x3 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 3x3 matrix are available:
* mat43  - a column major 4x3 matrix whose elements are of type float.
* dmat43 - a column major 4x3 matrix whose elements are of type double.

### 4x4 matrix (replicate a GLSL builtin; inherits from 'MatrixBase')

the following 2x4 matrix are available:
* mat4  - a column major 4x4 matrix whose elements are of type float.
* dmat4 - a column major 4x4 matrix whose elements are of type double.

## Numerical Operators

### Compound Operators

The following compound operators are available between vectors and scalars:

* 'Vector<T> Vector += U Scalar' - applies the binary operator '+' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* 'Vector<T> Vector -= U Scalar' - applies the binary operator '-' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* 'Vector<T> Vector *= U Scalar' - applies the binary operator '*' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* 'Vector<T> Vector /= U Scalar' - applies the binary operator '/' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').

The following compound operators are available between vectors and vectors:

* 'Vector<T, N> LHS += Vector<U, N> RHS' - applies the binary operator '+' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* 'Vector<T, N> LHS -= Vector<U, N> RHS' - applies the binary operator '-' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* 'Vector<T, N> LHS *= Vector<U, N> RHS' - applies the binary operator '*' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* 'Vector<T, N> LHS /= Vector<U, N> RHS' - applies the binary operator '/' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').

The following compound operators are available between matrix and scalars:

* 'Matrix<T> Matrix += U Scalar' - applies the binary operator '+' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* 'Matrix<T> Matrix -= U Scalar' - applies the binary operator '-' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* 'Matrix<T> Matrix *= U Scalar' - applies the binary operator '*' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* 'Matrix<T> Matrix /= U Scalar' - applies the binary operator '/' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').

The following compound operators are available between matrix and matrix:

* 'Matrix<T,COL,ROW> LHS += Matrix<U,COL,ROW> RHS' - applies the binary operator '+' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* 'Matrix<T,COL,ROW> LHS -= Matrix<U,COL,ROW> RHS' - applies the binary operator '-' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* 'Matrix<T,COL,ROW> LHS /= Matrix<U,COL,ROW> RHS' - applies the binary operator '/' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').

The following compound operator is available only between two squared matrix:
* 'Matrix<T, N, N> LHS *= Matrix<U, N, N> RHS' - return the matrix product between `LHS` and `RHS` (converted to 'T').

### Standard Operators

The following standard operators are available between vectors and scalars:

* '(Vector<T> Vector) + (U Scalar)', '(U Scalar) + (Vector<T> Vector)' - applies the binary operator '+' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* '(Vector<T> Vector) - (U Scalar)', '(U Scalar) - (Vector<T> Vector)' - applies the binary operator '-' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* '(Vector<T> Vector) * (U Scalar)', '(U Scalar) * (Vector<T> Vector)' - applies the binary operator '*' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* '(Vector<T> Vector) / (U Scalar)'                                    - applies the binary operator '/' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').

The following standard operators are available between vectors and vectors:

* '(Vector<T, N> LHS) + (Vector<U, N> RHS)' - applies the binary operator '+' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Vector<T, N> LHS) - (Vector<U, N> RHS)' - applies the binary operator '-' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Vector<T, N> LHS) * (Vector<U, N> RHS)' - applies the binary operator '*' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Vector<T, N> LHS) / (Vector<U, N> RHS)' - applies the binary operator '/' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').

The following standard operators are available between matrix and scalars:

* '(Matrix<T,COL,ROW> Matrix) + (U Scalar)', '(U Scalar) + (Matrix<T,COL,ROW> Matrix)' - applies the binary operator '+' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* '(Matrix<T,COL,ROW> Matrix) - (U Scalar)', '(U Scalar) - (Matrix<T,COL,ROW> Matrix)' - applies the binary operator '-' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* '(Matrix<T,COL,ROW> Matrix) * (U Scalar)', '(U Scalar) * (Matrix<T,COL,ROW> Matrix)' - applies the binary operator '*' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* '(Matrix<T,COL,ROW> Matrix) / (U Scalar)'                                            - applies the binary operator '/' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').

The following standard operators are available between matrix and matrix:

* '(Matrix<T,COL,ROW> LHS) + (Matrix<T,COL,ROW> RHS)' - applies the binary operator '+' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Matrix<T,COL,ROW> LHS) - (Matrix<T,COL,ROW> RHS)' - applies the binary operator '-' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Matrix<T,COL,ROW> LHS) / (Matrix<T,COL,ROW> RHS)' - applies the binary operator '/' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
 
The following implements matrix-matrix, matrix-vector and vector-matrix product:
* 'Matrix<T, COL, ROW> = Matrix<T, DIM, ROW> * Matrix<T, COL, DIM>' - returns the outcome of matrix-matrix multiplications.
* 'Vector<COL> = Vector<ROW> * Matrix<COL, ROW>' - returns the outcome of left multplication of a vector (treated as row vector) with a matrix.
* 'Vector<ROW> = Matrix<COL, ROW> * Vector<COL>' - returns the outcome of RIGHT multplication of a vector (treated as COLUMN vector) with a matrix.

The following unary operator is available:

* '-Vector<T> vector' - applies the unary operator '-' to each element of 'vector'.
* '-Matrix<T, COL, RO> matrix' - applies the unary operator '-' to each element of 'matrix'.

## Bitwise Operators

### Compound Operators

The following compound operators are available between vectors and scalars:

* 'Vector<T> Vector &= U Scalar'  - applies the bitwise operator '&' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* 'Vector<T> Vector |= U Scalar'  - applies the bitwise operator '|' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* 'Vector<T> Vector ^= U Scalar'  - applies the bitwise operator '^' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* 'Vector<T> Vector >>= U Scalar' - applies the bitwise operator '>>' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* 'Vector<T> Vector <<= U Scalar' - applies the bitwise operator '<<' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').

The following compound operators are available between vectors and vectors:

* 'Vector<T> LHS &= Vector<U, N> RHS'  - applies the bitwise operator '&' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Vector<T> LHS |= Vector<U, N> RHS'  - applies the bitwise operator '|' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Vector<T> LHS ^= Vector<U, N> RHS'  - applies the bitwise operator '^' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Vector<T> LHS >>= Vector<U, N> RHS' - applies the bitwise operator '>>' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Vector<T> LHS <<= Matrix<U, N> RHS' - applies the bitwise operator '<<' between each element at 'LHS' and the value of 'RHS' (converted to 'T').

The following compound operators are available between matrix and scalars:

* 'Matrix<T> Matrix &= U Scalar'  - applies the bitwise operator '&' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* 'Matrix<T> Matrix |= U Scalar'  - applies the bitwise operator '|' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* 'Matrix<T> Matrix ^= U Scalar'  - applies the bitwise operator '^' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* 'Matrix<T> Matrix >>= U Scalar' - applies the bitwise operator '>>' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').
* 'Matrix<T> Matrix <<= U Scalar' - applies the bitwise operator '<<' between each element at 'Matrix' and the value of 'Scalar' (converted to 'T').

The following compound operators are available between matrix and vectors:

* 'Matrix<T,COL,ROW> LHS &= Matrix<U,COL,ROW> RHS'  - applies the bitwise operator '&' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Matrix<T,COL,ROW> LHS |= Matrix<U,COL,ROW> RHS'  - applies the bitwise operator '|' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Matrix<T,COL,ROW> LHS ^= Matrix<U,COL,ROW> RHS'  - applies the bitwise operator '^' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Matrix<T,COL,ROW> LHS >>= Matrix<U,COL,ROW> RHS' - applies the bitwise operator '>>' between each element at 'LHS' and the value of 'RHS' (converted to 'T').
* 'Matrix<T,COL,ROW> LHS <<= Matrix<U,COL,ROW> RHS' - applies the bitwise operator '<<' between each element at 'LHS' and the value of 'RHS' (converted to 'T').

### Standard Operators

The following standard operators are available between vectors and scalars:

* '(Vector<T> Vector) & (U Scalar)'  - applies the bitwise operator '&' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* '(Vector<T> Vector) | (U Scalar)'  - applies the bitwise operator '|' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* '(Vector<T> Vector) ^ (U Scalar)'  - applies the bitwise operator '^' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* '(Vector<T> Vector) >> (U Scalar)' - applies the bitwise operator '>>' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').
* '(Vector<T> Vector) << (U Scalar)' - applies the bitwise operator '<<' between each element at 'Vector' and the value of 'Scalar' (converted to 'T').

The following standard operators are available between vectors and vectors:

* '(Vector<T, N> LHS) & (Vector<U, N> RHS)'  - applies the binary operator '&' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Vector<T, N> LHS) | (Vector<U, N> RHS)'  - applies the binary operator '|' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Vector<T, N> LHS) ^ (Vector<U, N> RHS)'  - applies the binary operator '^' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Vector<T, N> LHS) >> (Vector<U, N> RHS)' - applies the binary operator '>>' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').
* '(Vector<T, N> LHS) << (Vector<U, N> RHS)' - applies the binary operator '<<' to component-wise pairs of elements from `LHS` and `RHS` (converted to 'T').

## Relational Operators

The following relational Operators are available between vectors and scalars:

* 'Vector<T, N> vector == T scalar', 'T vector == Vector<T, N> scalar' - applies the relational operator '==' between each element at 'vector' and the value 'scalar', outcome is boolean.
* 'Vector<T, N> vector != T scalar', 'T vector != Vector<T, N> scalar' - applies the relational operator '!=' between each element at 'vector' and the value 'scalar', outcome is boolean.
* 'Vector<T, N> vector >= T scalar', 'T vector >= Vector<T, N> scalar' - applies the relational operator '>=' between each element at 'vector' and the value 'scalar', outcome is boolean.
* 'Vector<T, N> vector <= T scalar', 'T vector <= Vector<T, N> scalar' - applies the relational operator '<=' between each element at 'vector' and the value 'scalar', outcome is boolean.
* 'Vector<T, N> vector > T scalar', 'T vector > Vector<T, N> scalar'   - applies the relational operator '>' between each element at 'vector' and the value 'scalar', outcome is boolean.
* 'Vector<T, N> vector < T scalar', 'T vector < Vector<T, N> scalar'   - applies the relational operator '<' between each element at 'vector' and the value 'scalar', outcome is boolean.

The following relational Operators are available between vectors and vectors:

* 'Vector<T, N> LHS == T RHS' - applies the relational operator '==' to component-wise pairs of elements from `LHS` and `RHS`.
* 'Vector<T, N> LHS != T RHS' - applies the relational operator '!=' to component-wise pairs of elements from `LHS` and `RHS`.
* 'Vector<T, N> LHS >= T RHS' - applies the relational operator '>=' to component-wise pairs of elements from `LHS` and `RHS`.
* 'Vector<T, N> LHS <= T RHS' - applies the relational operator '<=' to component-wise pairs of elements from `LHS` and `RHS`.
* 'Vector<T, N> LHS > T RHS'  - applies the relational operator '>' to component-wise pairs of elements from `LHS` and `RHS`.
* 'Vector<T, N> LHS < T RHS'  - applies the relational operator '<' to component-wise pairs of elements from `LHS` and `RHS`.

## Functions

### Reduction Functions

The following reduction functions are available for both vectors and matrix types (generaly refered to as 'Collection'):

* 'bool = any(Collection<T>, Predicate)'           - return true if any component in 'Collection' upholds a given 'Predicate'.
* 'bool = any(Collection<bool>)'                   - return true if any component in 'Collection' is 'true'.
* 'bool = all(Collection<T>, Predicate)'           - return true if all component in 'Collection' upholds a given 'Predicate'.
* 'bool = all(Collection<bool>)'                   - return true if all component in 'Collection' are 'true'.
* 'Collection<bool, N> = Not(Collection<bool, N>)' - return component wise logical complement of 'Collection'
* 'bool = isnan(Collection<T>)'                    - return true if any component in 'Collection' is a 'NaN'.
* 'bool = isinf(Collection<T>)'                    - return true if any component in 'Collection' is an 'Infinity'.
* 'bool = IsNormalized(Collection<T>, U tol)'      - return true if vector is normalized to a given tolerance 'tol'.
* 'T = min(Collection<T, N>, ...)'                 - return the minimal scalar value from a variadic number of collections.
* 'T = max(Collection<T, N>, ...)'                 - return the maximal scalar value from a variadic number of collections.
* 'T = sum(Collection<T, N>, ...)'                 - return the sum of all elements from a variadic number of collections.
* 'T = prod(Collection<T, N>, ...)'                - return the product of all elements from a variadic number of collections.

### Ternary Functions:

The following ternary functions are available for both vectors and matrix types (generaly refered to as 'Collection'):

* 'Collection = clamp(Collection, U a, W b)                   - return 'Collection' after his elements were clamped to the region [min(a, b), max(a, b)].
* 'Collection = clamp(Collection, Collection a, Collection b) - return 'Collection' after his elements at index i was clamped to the region [min(a[i], b[i]), max(a[i], b[i])], for every i.

### Numerical Unary Functions:

The following unary functions are available for both vectors and matrix types (generaly refered to as 'Collection'):

* 'Collection = abs(Collection)'   - applies 'std::abs' to each element, and return the result.
* 'Collection = floor(Collection)' - applies 'std::floor' to each element, and return the result.
* 'Collection = ceil(Collection)'  - applies 'std::ceil' to each element, and return the result.
* 'Collection = trunc(Collection)' - applies 'std::trunc' to each element, and return the result.
* 'Collection = round(Collection)' - applies 'std::round' to each element, and return the result.
* 'Collection = exp(Collection)'   - applies 'std::exp' to each element, and return the result.
* 'Collection = exp2(Collection)'  - applies 'std::exp2' to each element, and return the result.
* 'Collection = log(Collection)'   - applies 'std::log' to each element, and return the result.
* 'Collection = log2(Collection)'  - applies 'std::log2' to each element, and return the result.
* 'Collection = sqrt(Collection)'  - applies 'std::sqrt' to each element, and return the result.
* 'Collection = sin(Collection)'   - applies 'std::sin' to each element, and return the result.
* 'Collection = cos(Collection)'   - applies 'std::cos' to each element, and return the result.
* 'Collection = tan(Collection)'   - applies 'std::tan' to each element, and return the result.
* 'Collection = asin(Collection)'  - applies 'std::asin' to each element, and return the result.
* 'Collection = acos(Collection)'  - applies 'std::acos' to each element, and return the result.
* 'Collection = atan(Collection)'  - applies 'std::atan' to each element, and return the result.
* 'Collection = sinh(Collection)'  - applies 'std::sinh' to each element, and return the result.
* 'Collection = cosh(Collection)'  - applies 'std::cosh' to each element, and return the result.
* 'Collection = tanh(Collection)'  - applies 'std::tanh' to each element, and return the result.
* 'Collection = asinh(Collection)' - applies 'std::asinh' to each element, and return the result.
* 'Collection = acosh(Collection)' - applies 'std::acosh' to each element, and return the result.
* 'Collection = atanh(Collection)' - applies 'std::atanh' to each element, and return the result.
* 'Collection = radians(Collection)'     - transform all elements from degrees to radians (i.e. - multiply by PI/180), and return the result.
* 'Collection = degrees(Collection)'     - transform all elements from radians to degrees(i.e. - multiply by 180/PI), and return the result.
* 'Collection = inversesqrt(Collection)' - applies '1/std::sqrt' to each element, and return the result.
* 'Collection = sign(Collection)'        - return a vector holding the sign of each element ('1' for positive value, '-1' for negative value, '0' otherwise).
* 'Collection = roundEven(Collection)'   - return a vector such that each of its elements are equal to the nearest even integer.

### Numerical Binary Functions:

The following binary functions are available for both vectors and matrix types (generaly refered to as 'Collection'):

* 'Collection = pow(Collection C, U scalar)'                   - applies 'std::pow(, scalar)' to each element of 'C', and return the result.
* 'Collection = pow(Collection vector1, Collection vector2)'   - applies 'std::pow()' to component-wise pairs of elements from `vector1` and `vector2`, and return the result.
* 'Collection = atan2(Collection C, U scalar)'                 - applies 'std::atan2(, scalar)' to each element of 'C', and return the result.
* 'Collection = atan2(Collection vector1, Collection vector2)' - applies 'std::atan2()' to component-wise pairs of elements from `vector1` and `vector2`, and return the result.
* 'Collection = modf(Collection C, U scalar)'                  - applies 'std::modf(, scalar)' to each element of 'C', and return the result.
* 'Collection = modf(Collection vector1, Collection vector2)'  - applies 'std::modf()' to component-wise pairs of elements from `vector1` and `vector2`, and return the result.

### General/Numerical Functions:

The following general numerical functions are available for both vectors and matrix (generaly refered to as 'Collection'):

* 'T = length(Collection)'                                                    - return the length/magnitude of a 'Collection'.
* 'T = distance(Collection, Collection)'                                      - return the distance between two collections of identical underlying type.
* 'T = dot(Collection, ...)'                                                  - return the internal ("dot") product between a variaidic number of collections. If input argument is composed of only one collection - the output is its squared magnitude.
* 'Collection = mix(Collection, Collection, U blend)'                         - return the linear blend between two vectors.
* 'Collection = step(Collection, U edge)'                                     - for each element: return '0' if element is smaller than 'edge', otherwise - return '1'.
* 'Collection = smoothstep(Collection, U edge0, W edge1)'                     - for each element: return '0' is smaller then 'edge0', return '1' if larger then 'edge1',
                                                                                otherwise - perform Hermite interpolation between '0' and '1'.
* 'Collection = smoothstep(Collection C, Collection edge0, Collection edge1)' - for each element: return '0' is smaller then 'edge0', return '1' if larger then 'edge1',
                                                                                otherwise - perform Hermite interpolation between '0' and '1'.
* 'Collection = smootherstep(Collection C, U edge0, W edge1)                  - for each element: return '0' is smaller then 'edge0', return '1' if larger then 'edge1',
                                                                                otherwise - perform Hermite interpolation between '0' and '1', but with the first and second derivative at the edges are '0'.
* 'Collection = fma(Collection a, Collection b, Collection c)'                - return an element wise fused multiply add operation between three collections, i.e. - return 'a*b+c'.

The following functions are availabe for vector types:

* 'Vector<T> = normalize(Vector<T>)'                         - return a vector in the same direction but with unit magnitude.
* 'Vector<T, N> = ProjectOn(Vector<T, N> a, Vector<T, N> b)' - return the projection of vector 'a' on 'b'.
* 'T = leftLookingDot(vector 1, vector 2, start, end)'       - return the internal ("dot") product between two vectors, but only between elements in the index range ['start', 'end'].

The following specialized numerical functions are available for 3 elements vectors:

* 'Vector<T, 3> = cross(Vector<T, 3> a, Vector<T, 3> b)'                          - return the cross product between two vectors.
* 'Vector<T, 3> = orthogonal(Vector<T, 3>)'                                       - given a vector, return a normalized vector which is orthogonal to it. 
* 'T = tangent(Vector<T, 3>, Vector<T, 3>)'                                       - return the tangent of angle between two vectors.
* 'Vector<T, 3> = faceforward(Vector<T, 3> N, Vector<T, 3> I, Vector<T, 3> Nref)' - if 'Nref' and 'I' face in the same direction - return 'N', otherwise return '-N'.
* 'Vector<T, 3> = reflect(Vector<T, 3> I, Vector<T, 3> N')                        - given incident vector 'I' and surface orientation 'N' (normalized vector), return the reflection direction.
* 'Vector<T, 3> = refract(Vector<T, 3> I, Vector<T, 3> N, U eta)                  - given incident vector 'I', surface orientation 'N' (normalized vector) and ratio of indices's's of refractions, return the refraction vector.

The following specialized numerical functions are available for 2 elements vectors:

* 'T = tangent(Vector<T, 2>, Vector<T, 2>)'                                       - return the tangent of angle between two vectors.
* 'Vector<T, 2> = faceforward(Vector<T, 2> N, Vector<T, 2> I, Vector<T, 2> Nref)' - if 'Nref' and 'I' face in the same direction - return 'N', otherwise return '-N'.
* 'Vector<T, 2> = reflect(Vector<T, 2> I, Vector<T, 2> N)'                        - given incident vector 'I' and orientation 'N' (normalized vector), return the reflection direction.
* 'Vector<T, 2> = refract(Vector<T, 2> I, Vector<T, 2> N, U eta)                  - given incident vector 'I', orientation 'N' (normalized vector) and ratio of indices's of refractions, return the refraction vector.

The following functions are availabe for matrix types:

"named" constructors:
* 'MakeIdentity(MatrixBase xio_mat)'                                      - transform 'xio_mat' to the identity matrix, i.e. - 'I'.
* 'MatrixBase OuterProduct(Vector xi_x, Vector xi_y)'                     - return a matrix which is the outer product of vectors 'xi_x' and 'xi_y'.
* 'MatrixBase VanDerMonde(Vector xi_vec)'                                 - return a Van-Der-Monde matrix from vector 'xi_vec'.
* 'MatrixBase Toeplitz(Vector xi_vec)'                                    - return a Toeplitz matrix from vector 'xi_vec'.
* 'MatrixBase GivensRotation(T xi_cosine, T xi_sine, std::size_t xi_col)' - return givens rotation matrix with rotation angle given by its components ('xi_cosine', 'xi_sine') and the row/column 'xi_col' on which it operates.
* 'MatrixBase Householder(const T& xi_vec)'                               - return the householder transformation of vector 'xi_vec' (I - 2 * OuterProduct(xi_vec, xi_vec)).

matrix modifiers:
* 'MatrixBase SwapRows(MatrixBase xi_matrix, i, j)'              - returns 'xi_matrix' after its 'i'th and 'j'th rows were swapped.
* 'MatrixBase SwapColumns(MatrixBase xi_matrix, i, j)'           - returns 'xi_matrix' after its 'i'th and 'j'th columns were swapped.
* 'SetRow(MatrixBase xio_matrix, i, VectorBase row)'             - set 'xio_matrix' 'i'th row to be 'row'.
* 'SetDiagonal(MatrixBase xio_matrix, i, T diagonal)'            - set cubic 'xio_matrix' diagonal elements to 'diagonal'.
* 'T Trace(MatrixBase xi_matrix)'                                - return the trace (sum of diagonal elements) of cubic matrix 'xi_matrix'.
* 'T Determinant(MatrixBase xi_matrix)'                          - return the determinant of cubic matrix 'xi_matrix'.
* 'MatrixBase Transpose(MatrixBase xi_mat)'                      - return the transpose of matrix 'xi_mat'.
* 'MatrixBase Inv(MatrixBase xi_mat)'                            - return the inverse of cubic matrix 'xi_mat'.
* 'MatrixBase Orthonormalize(MatrixBase xi_matrix)'              - orthonormalize (make the columns normalized and orthogonal to each other) 'xi_matrix'.
* 'MatrixBase matrixMatrixMul(MatrixBase xi_a, MatrixBase xi_b)' - return the element wise multiplication between two identical size matrix 'xi_a' & 'xi_b'.

functions to get a given portion of a matrix:
* 'VectorBase GetRow(xi_matrix, i)'                                               - return the 'xi_matrix' 'i'th row.
* 'VectorBase GetDiagonal(xi_matrix)'                                             - return the diagonal of a cubic matrix 'xi_matrix'.
* 'MatrixBase GetLowerTriangular(xi_matrix)'                                      - return the lower traingular portion of a cubic matrix 'xi_matrix'.
* 'MatrixBase GetUpperTriangular(xi_matrix)'                                      - return the upper traingular portion of a cubic matrix 'xi_matrix'.
* 'MatrixBase GetBlock<COL_MIN, COL_MAX, ROW_MIN, ROW_MAX>(MatrixBase xi_matrix)' - return 'xi_matrix' block according to given column and row ranges.

functions to test if matrix has a special characteristic:
* 'bool IsSymmetric(xi_matrix)'       - return true if 'xi_matrix' is symmetric arround its diagonal.
* 'bool IsSkewSymmetric(xi_matrix)'   - return true if 'xi_matrix' is skew-symmetric arround its diagonal.
* 'bool IsUpperTriangular(xi_matrix)' - return true if 'xi_matrix' is upper triangular arround its diagonal.
* 'bool IsLowerTriangular(xi_matrix)' - return true if 'xi_matrix' is lower triangular arround its diagonal.
* 'bool IsDiagonal(xi_matrix)'        - return true if 'xi_matrix' is diagonal.
* 'bool IsPermutation(xi_matrix)'     - return true if 'xi_matrix' is permutation matrix (there is only one '1' in every column and row).

matrix decompositions:
* 'LU(xi_matrix, xo_lowerUpper, VectorBase<size_t, COL> xo_pivot, int32_t xo_sign)' - return the lower-upper (Lower * Pivot * Upper) decomposition of cubic matrix 'xi_matrix' in one matrix 'xo_lowerUpper' along with pivot matrix (givne as a vector holding the diagonal 'xo_pivot') and pivot sign "xo_sign". The decomposition is performed such that the lower triangular matrix has a diagonal filled with '1'.
* 'QRgramSchmidt(xi_matrix, Q, R)'                                                  - given rectangular matrix 'xi_matrix' (COL * ROW, ROW >= COL), perform QR decomposition (using gram-schmidt process) and return 'Q' (COL * ROW orthogonal matrix) and 'R' (COL * COL upper triangular matrix).
* 'QRgivensRotations(xi_matrix, Q, R)'                                              - given rectangular matrix 'xi_matrix' (COL * ROW, ROW >= COL), perform QR decomposition (using givens rotatin) and return 'Q' (COL * ROW orthogonal matrix) and 'R' (COL * COL upper triangular matrix).
* 'L = Cholesky(xi_matrix)'                                                         - given cubic and positive definite matrix 'xi_matrix', return a lower triangular matrix 'L' such that L * L' = xi_matrix. This is called Cholesky decomposition.
* 'SVDfast(xi_mat, xo_UW, xo_W2, xo_V)'                                             - perform singular value decomposition of matrix 'xi_mat', but it returns a different output then the standard operation, see extra information at function definition.
* 'SVD(xi_mat, xo_U, xo_W, xo_V)'                                                   - perform singular value decomposition of matrix 'xi_mat', and return 'xi_U * xi_W * xi_V^T', where 'xi_U' & 'xi_V' columns are orthonormal and 'xi_W' holds the singular values.

linear equation system solvers:
* 'b = SolveSquareLU(A, b)'      - given cubic matrix 'A' and column matrix 'b', solve the linear equations system A * x = b, and return 'x'. This method uses LU decomposition internaly.
* 'b = SolveCubicCholesky(A, b)' - given cubic and positive definite matrix 'A' and column matrix 'b', solve the linear equations system A * x = b, and return 'x'. This method uses Cholesky decomposition internaly.
* 'b = SolveQR(A, b)'            - given rectangular (rows >= columns) matrix 'A', solve the linear equation system A * x = b, and return x. This method uses both LU and QR decompositins. 

The following specialized functions are availabe for 2x2 matrix:

* 'EigenValues2x2(matrix, xo_eigen1, xo_eigen2)'                                     - given a cubic 2x2 matrix 'matrix', return its eigenvalues 'xo_eigen1' & 'xi_eigen2'.
* 'EigenSolver2x2(matrix, xo_eigen1, xo_eigen2, xo_eigen_vector1, xo_eigen_vector2)' - given a cubic 2x2 matrix 'matrix', return its eigenvalues 'xo_eigen1' & 'xi_eigen2' and its approrpiate eigenvectors ('xo_eigen_vector1', 'xo_eigen_vector2'').
* 'SVDsymmetric2x2(matrix, matrix U, vector W)'                                      - given a cubic symmetric 2x2 matrix 'matrix', perform singular value decomposition and return 'U' and 'W' which are: matrix = U * W * U^T (where W is a diagonal matrix returned as a vector holding the diagonal elements)
* 'PolarDecomposition2x2(matrix, matrix r, matrix S)'                                - given a vubic 2x2 matrix 'matrix', perform polar decomposition and return 'R' and 'S' (matrix = R * S), where 'R' is rotatin matrix and 'S' is symmetric describing deformations.


The following specialized functions are availabe for 3x3 matrix:

* 'MatrixBase FromAxisAngle(Vector xi_axis, T xi_sine, T xi_cosine)'   - return a rotation matrix (3x3) from a normalized axis 'xi_axis', and an angle (given by its trigonometric components - 'xi_sine' & 'xi_cosine').
* 'EigenValues3x3(matrix, xo_eig)'                                     - given a cubic 3x3 matrix 'matrix', return its eigenvalues as elements in vector 'xo_eig'.
* 'EigenSolverSymmetric3x3(matrix, xo_eigen_values, xo_eigen_vectors)' - given a cubis symmetric 3x3 matrix 'matrix', return its eigenvalues (as 3 element vector) 'xo_eigen_values', and corresponding eigen vectors (as column ins a 3x3 matrix) 'xo_eigen_vectors'.

The following specialized functions are availabe for 4x4 matrix:

* 

### General Functions:

The following general functions are available for vectors:

* 'Vector<T, N> = reverse(Vector<T, N>)' - reverse vector elements.

### Higher Order Functions

The following higher order functions are available for both vectors and matrix types (generaly refered to as 'Collection'):

* 'for_each(Collection, Function)'                                                                      - apply a given 'Function' on supplied 'Collection'.
* 'T reduce(init_value, Collection, Function)'                                                          - return the outcome of applying a reduction function 'Function' with initial value 'init' on supplied 'Collection'. Operation is performed in a non-sequential form.
* 'T transform_reduce(Collection #1, Collection #2, init, reduction_function, transformation_function)' - return the outcome of a map-reduce operation on two collections ('Collection #1', 'Collection #2') by supplying reduction function ('reduction_function') with initial value ('init') and transformation function 'transformation_function'. Operation is performed in a non-sequential form.


### Type Traits

the following compile time type traits are available (this is a short list of the most usefull ones):

* 'is_VectorBase<T>::value'                - return 'true' if 'T' is 'VectorBase'.
* 'is_Vector2<T>::value'                   - return 'true' if 'T' is 'Vector2' (i.e. - 'bvec2', 'ivec2', 'uvec2', 'vec2', 'dvec2').
* 'is_Vector3<T>::value'                   - return 'true' if 'T' is 'Vector3' (i.e. - 'bvec3', 'ivec3', 'uvec3', 'vec3', 'dvec3').
* 'is_Vector4<T>::value'                   - return 'true' if 'T' is 'Vector4' (i.e. - 'bvec4', 'ivec4', 'uvec4', 'vec4', 'dvec4').
* 'is_Vector<T>::value'                    - return 'true' if 'T' is one of the following: 'VectorBase', 'Vector2', 'Vector3', 'Vector4'.
* 'Are_VectorBases<Ts...>::value'          - return 'true' if all packed variables in 'Ts' are of the following: 'VectorBase', 'Vector2', 'Vector3', 'Vector4'.
* 'Are_VectorsSimilar<T, N, TS...>::value' - return 'true' if all packed variables in 'Ts' are of the following: 'VectorBase', 'Vector2', 'Vector3', 'Vector4',
                                              and their underlying type is 'T', and their length is 'N'.
* 'Length<T>::value'                       - if 'T' is either a 'VectorBase' (or its descendent's) or a 'MatrixBase' - return its number of elements, otherwise return '0'.
* 'is_RowMajor<T>::value'                  - return 'true' if 'T' is of type 'MatrixBase' and its layout is row major.
* 'Rows<T>::value'                         - if 'T' is of type 'MatrixBase' then return its number of rows, otherwise - return '0
* 'Columns<T>::value'                      - if 'T' is of type 'MatrixBase' then return its number of columns, otherwise - return '0'.
* 'is_MatrixBase<T>::value'                - return 'true' if 'T' is 'MatrixBase'.
* 'is_VectorRvalue<T>::Value'              - return 'true' if 'T' is a rvalue 'Vector'.
* 'is_VectorLvalue<T>::Value'              - return 'true' if 'T' is a lvalue 'Vector'.
* 'is_IterableRvalue<T>::Value'            - return 'true' if 'T' is a rvalue vector/matrix.
* 'is_IterableRvalue<T>::Value'            - return 'true' if 'T' is a lvalue vector/matrix.
* 'is_UnderlyingBool_v<T>'                 - return 'true' if 'T' is a vector/matrix with underlying type boolean.
* 'underlying_type_t<T>'                   - return the underlying type of a vector/matrix.
* 'is_Cubic<T>::value'                     - return 'true' if 'T' is a cubic matrix


the following run time type traits are available (this is a short list of the most usefull ones):

* 'isVectorBase(T)'            - return 'true' if 'T' is 'VectorBase'.
* 'isVector2(T)'               - return 'true' if 'T' is 'Vector2' (i.e. - 'bvec2', 'ivec2', 'uvec2', 'vec2', 'dvec2').
* 'isVector3(T)'               - return 'true' if 'T' is 'Vector3' (i.e. - 'bvec3', 'ivec3', 'uvec3', 'vec3', 'dvec3').
* 'isVector4(T)'               - return 'true' if 'T' is 'Vector4' (i.e. - 'bvec4', 'ivec4', 'uvec4', 'vec4', 'dvec4').
* 'isVector(T)'                - return 'true' if 'T' is one of the following: 'VectorBase', 'Vector2', 'Vector3', 'Vector4'.
* 'isRowMajor(T)'              - return 'true' if 'T' is of type 'MatrixBase' and its layout is row major.
* 'isMatrixBase(T)'            - return 'true' if 'T' is 'MatrixBase'.
* 'isVectorRalue(T)'           - return 'true' if 'T' is a rvalue 'Vector'.
* 'isVectorLalue(T)'           - return 'true' if 'T' is a lvalue 'Vector'.
* 'isIterableRvalue<T>::Value' - return 'true' if 'T' is a rvalue vector/matrix.
* 'isIterableRvalue<T>::Value' - return 'true' if 'T' is a lvalue vector/matrix.
* 'isUnderlyingBool(T)'        - return 'true' if 'T' is a vector/matrix with underlying type boolean.

## Quaternion

## Interval

## Scalar Functions

The following general scalar functions are available:

* 'exist = SolveQuadratic(a, b, c, x1, x2)'                     - stable numeric solution of a quadratic equation (a*x^2 + b*x + c = 0), where 'x1' is the smaller root and 'x2' is larger root and 'exist' is true only if a solution exists.
* 'numOfRoots = SolveCubic(b, c, d, VectorBase<T, 6> xo_roots)' - stable numeric solution of a cubic equation (x^3 + b*x^2 + c*x + d = 0), where 'xo_roots' holds three paired solutions in the form (real solution #1, imag solution #1, ...) and 'numOfRoots' is the number of real roots (either 1 or 3)

## Todo
```C
[] check SVD decomposition for rectangular matrix
[] implement polar decomposition
[] implement a bunch of 2x2/3x3/4x4 matrix operations
[] implement quaternion object
[] implement interval object
[] allow VectorBase to become dyanmicly sized.
[] move from the standard inheritance model to static one (i.e. - CRTP).
[] move from SFINEA to c++20 concepts.
[] use c++20 SIMD operations.
```

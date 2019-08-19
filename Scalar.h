/**
* Scalar functions
*
* Dan Israel Malta
**/
#pragma once
#include "common.h"
#include <vector>

namespace GLSLCPP {

    /**
    * \brief stable numeric solution of a quadratic equation (a*x^2 + b*x + c = 0)
    *
    * @param {T,    in}  a
    * @param {T,    in}  b
    * @param {T,    in}  c
    * @param {T,    out} smaller root (x1)
    * @param {T,    out} larger root (x2)
    * @param {bool, out} true if a solution exists - false otherwise
    **/
    template<typename T, REQUIRE(std::is_arithmetic_v<T>)> 
    constexpr bool SolveQuadratic(const T xi_a, const T xi_b, const T xi_c, T& xo_x1, T& xo_x2) noexcept {

        constexpr T TOL{ static_cast<T>(2) * std::numeric_limits<T>::epsilon() };

        // trivial solution
        if ((std::abs(xi_a) <= TOL) && 
            (std::abs(xi_b) <= TOL)) {
            xo_x1 = xo_x2 = T{};
            return true;
        }

        const T discriminant{ xi_b * xi_b - static_cast<T>(4) * xi_a * xi_c };

        if (discriminant < T{}) {
            xo_x1 = T{};
            xo_x2 = T{};
            return false;
        }

        // solution
        const T sign{ xi_b < T{} ? static_cast<T>(-1) : static_cast<T>(1) },
                t{ static_cast<T>(-0.5) * (xi_b + sign * std::sqrt(discriminant)) };
        xo_x1 = t / xi_a;
        xo_x2 = xi_c / t;

        if (xo_x1 > xo_x2) std::swap(xo_x1, xo_x2);
        return true;
    }

    /**
    * \brief stable numeric solution of a cubic equation (x^3 + b*x^2 + c*x + d = 0)
    * 
    * @param {T,        in}  b
    * @param {T,        in}  c
    * @param {T,        in}  d
    * @param {uint32_t, out} number of real roots
    * @param {vector,   out} a 1x6 vector holding three paired solutions in the form (real solution #1, imag solution #1, ...)
    **/
    template<typename T, REQUIRE(std::is_arithmetic_v<T>)> 
    constexpr uint32_t SolveCubic(const T xi_b, const T xi_c, const T xi_d, VectorBase<T, 6>& xo_roots) noexcept {
        xo_roots = T{};

        // transform to: x^3 + p*x + q = 0
        const T ov3{ static_cast<T>(1) / static_cast<T>(3) },
                ov27{ static_cast<T>(1) / static_cast<T>(27) },
                ovsqrt27{ static_cast<T>(1) / std::sqrt(static_cast<T>(27)) },
                bSqr{ xi_b * xi_b },
                p{ (static_cast<T>(3) * xi_c - bSqr) * ov3 },
                q{ (static_cast<T>(9) * xi_b * xi_c - static_cast<T>(27) * xi_d - static_cast<T>(2) * bSqr * xi_b) * ov27 };

        // x = w - (p / (3 * w))
        // (w^3)^2 - q*(w^3) - (p^3)/27 = 0
        T h{ q * q * static_cast<T>(0.25) + p * p * p * ov27 };

        // one single real solution
        if (h > T{}) {
            h = std::sqrt(h);

            const T qHalf{ q * static_cast<T>(0.5) },
                    bThird{ xi_b * ov3 },
                    r{ qHalf + h },
                    t{ qHalf - h },
                    s{ std::cbrt(r) },
                    u{ std::cbrt(t) },
                    re{ -(s + u) * static_cast<T>(0.5) - bThird },
                    im{  (s - u) * static_cast<T>(std::sqrt(3)) * static_cast<T>(0.5) };

            // real root
            xo_roots[0] = (s + u) - bThird;

            // first complex root
            xo_roots[2] = re;
            xo_roots[3] = im;

            // second complex root
            xo_roots[4] = re;
            xo_roots[5] = -im;

            // one real solution
            return 1;
        }  // three real solutions
        else {            
            const T i{ p * std::sqrt(-p) * ovsqrt27 },     // p is negative (since h is positive)
                    j{ std::cbrt(i) },
                    k{ ov3 * std::acos((q / (static_cast<T>(2) * i))) },
                    m{ std::cos(k) },
                    n{ std::sin(k) * static_cast<T>(std::sqrt(3)) },
                    s{ -xi_b * ov3 };

            // roots
            xo_roots[0] = static_cast<T>(2) * j * m + s;
            xo_roots[2] = -j * (m + n) + s;
            xo_roots[4] = -j * (m - n) + s;

            // 3 real roots
            return 3;
        }
    }
};

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "GLSL++.h"
#include <iostream>
#include <assert.h>
#include "ExecutionTimer.h"

using namespace GLSLCPP;

// ------------------------------
// --- scalar operations test ---
// ------------------------------
void ScalarTest() {
    // second order equation
    float x1, x2;
    bool exist0{ SolveQuadratic(3.0f, 7.8f, 6.3f, x1, x2) };
    assert(exist0 == false);
    assert(x1 == 0.0f);
    assert(x2 == 0.0f);

    exist0 = SolveQuadratic(-3.0f, 7.8f, 6.3f, x1, x2);
    assert(exist0 == true);
    assert(x1 == -0.646792233f);
    assert(x2 == 3.24679255f);

    // third order equation
    VectorBase<float, 6> roots,
                         rootseq(-5.63887119f, 0.0f,
                                 0.819435477f, 0.754922748f,
                                 0.819435477f, -0.754922748f);
    uint32_t n{ SolveCubic(4.0f, -8.0f, 7.0f, roots) };
    assert(n == 1);
    assert(roots == rootseq);
}

// ------------------------------------
// --- VectorBase construction test ---
// ------------------------------------
void VectorBaseTest() {

    // --- construction test ---
    {
        VectorBase<bool, 2> a(true),
                            b(true, false),
                            c(b),
                            d = c;

        // this should fail:
        //VectorBase<bool, 2> a(true, true, false);

        assert(isVectorBase(a) && isVectorBase(b) && isVectorBase(c) && isVectorBase(d) && " one of the vectors is not of type VectorBase.");
        assert((a[0] == true) && (a[1] == true));
        assert((b[0] == true) && (b[1] == false));
        assert((c[0] == true) && (c[1] == false));
        assert((d[0] == true) && (d[1] == false));

        VectorBase<float, 3> e(0.0),
                             f(0, 1, 2),
                             g = f,
                             h = VectorBase<float, 3>(3, 2, 1);
        assert(isVectorBase(e) && isVectorBase(f) && isVectorBase(g) && isVectorBase(h) && " one of the vectors is not of type VectorBase.");
        assert((static_cast<int>(e[0]) == 0) && (static_cast<int>(e[1]) == 0) && (static_cast<int>(e[2]) == 0));
        assert((static_cast<int>(f[0]) == 0) && (static_cast<int>(f[1]) == 1) && (static_cast<int>(f[2]) == 2));
        assert((static_cast<int>(g[0]) == 0) && (static_cast<int>(g[1]) == 1) && (static_cast<int>(g[2]) == 2));
        assert((static_cast<int>(h[0]) == 3) && (static_cast<int>(h[1]) == 2) && (static_cast<int>(h[2]) == 1));
    }

    // --- numerical operator test ---
    {
        VectorBase<int, 3> ab(0),
                           bb(0, 1, 0);
        VectorBase<int, 3> ai(0.0),
                           bi(0, 1, 2);
        VectorBase<float, 3> af(0.0),
                             bf(0, 1, 2);
        VectorBase<float, 3> c(0);

        // element wise numerical+assignment operations with scalars
        c += 1;
        assert((static_cast<int>(c[0]) == 1) && (static_cast<int>(c[1]) == 1) && (static_cast<int>(c[2]) == 1));

        c -= 2;
        assert((static_cast<int>(c[0]) == -1) && (static_cast<int>(c[1]) == -1) && (static_cast<int>(c[2]) == -1));

        c *= -2.0f;
        assert((static_cast<int>(c[0]) == 2) && (static_cast<int>(c[1]) == 2) && (static_cast<int>(c[2]) == 2));

        c /= 2.0f;
        assert((static_cast<int>(c[0]) == 1) && (static_cast<int>(c[1]) == 1) && (static_cast<int>(c[2]) == 1));

        // element wise numerical+assignment operations with vectors
        c += bb;
        assert((static_cast<int>(c[0]) == 1) && (static_cast<int>(c[1]) == 2) && (static_cast<int>(c[2]) == 1));

        c -= bb;
        assert((static_cast<int>(c[0]) == 1) && (static_cast<int>(c[1]) == 1) && (static_cast<int>(c[2]) == 1));

        c *= bb;
        assert((static_cast<int>(c[0]) == 0) && (static_cast<int>(c[1]) == 1) && (static_cast<int>(c[2]) == 0));

        c /= VectorBase<float, 3>(1);
        assert((static_cast<int>(c[0]) == 0) && (static_cast<int>(c[1]) == 1) && (static_cast<int>(c[2]) == 0));

        c = VectorBase<float, 3>(1);

        c += bi;
        assert((static_cast<int>(c[0]) == 1) && (static_cast<int>(c[1]) == 2) && (static_cast<int>(c[2]) == 3));

        c -= bi;
        assert((static_cast<int>(c[0]) == 1) && (static_cast<int>(c[1]) == 1) && (static_cast<int>(c[2]) == 1));

        c *= bi;
        assert((static_cast<int>(c[0]) == 0) && (static_cast<int>(c[1]) == 1) && (static_cast<int>(c[2]) == 2));

        c = VectorBase<float, 3>(1);

        // numerical operators with vectors
        VectorBase<float, 3> d = c + bf;
        assert((static_cast<int>(d[0]) == 1) && (static_cast<int>(d[1]) == 2) && (static_cast<int>(d[2]) == 3));

        d = VectorBase<float, 3>(1) + bf;
        assert((static_cast<int>(d[0]) == 1) && (static_cast<int>(d[1]) == 2) && (static_cast<int>(d[2]) == 3));

        d = d * 2;
        assert((static_cast<int>(d[0]) == 2) && (static_cast<int>(d[1]) == 4) && (static_cast<int>(d[2]) == 6));

        auto cc = -c;
        assert((static_cast<int>(cc[0]) == -1) && (static_cast<int>(cc[1]) == -1) && (static_cast<int>(cc[2]) == -1));

        VectorBase<float, 6> _cc = -VectorBase<float, 6>(1);
        for_each(_cc, [](const auto& elm) {assert(elm == -1); });

        VectorBase<float, 6> _dd = -_cc;
        for_each(_dd, [](const auto& elm) {assert(elm == 1); });
    }

    // relational operators and functions
    {
        VectorBase<int, 4> i0(0, 1, 2, 3),
                           i1(1, 1, 1, 1),
                           i2(5, 5, 5, 5);
        bool a{ i0 > i1 },
             b(i1 < i2),
             c(i1 == 1),
             d(i1 == 3);
        assert(a == false);
        assert(b == true);
        assert(c == true);
        assert(d == false);

        VectorBase<bool, 3> f(0,0,0),
                            t(1,1,1);
        assert(any(f) == false);
        assert(any(VectorBase<bool, 3>(0,0,1)) == true);
        assert(any(t) == true);

        assert(all(f) == false);
        assert(all(t) == true);

        f = Not(f);
        assert(all(f) == true);

        f = Not(VectorBase<bool, 3>(0));
        assert(all(f) == true);

        const VectorBase<bool, 3> fc(0, 0, 0);
        f = Not(fc);
        assert(all(f) == true);
    }

    // swizzles
    {
        Vector2<int> _a(1, 2),
                     _a1(Vector2<int>(3,4));

        Vector3<int> __a(1, 2,3);
        Vector4<int> a(0, 1, 2, 3);
        VectorBase<int, 4> b(0);
        b = 2;
        assert((b[0] == 2) && (b[1] == 2) && (b[2] == 2) && (b[3] == 2));

        b = a.wzyx;
        assert((b[0] == 3) && (b[1] == 2) && (b[2] == 1) && (b[3] == 0));
    }

    // numerical functions
    {
        VectorBase<float, 3> a(-1.0f, 2.3f, -5.5f);
        
        // unary functions
        auto b = sign(a);
        assert((static_cast<int>(b[0]) == -1) && (static_cast<int>(b[1]) == 1) && (static_cast<int>(b[2]) == -1));

        a = abs(a);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1] * 10) == 23) && (static_cast<int>(a[2] * 10) == 55));

        // binary functions
        a = VectorBase<float, 3>(1, 2, 3);
        a = pow(a, VectorBase<float, 3>(2));
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4) && (static_cast<int>(a[2]) == 9));

        a = VectorBase<float, 3>(1, 2, 3);
        a = pow(a, 2.0f);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4) && (static_cast<int>(a[2]) == 9));

        a = VectorBase<float, 3>(-1.0f, 2.3f, 5.5f);
        a = clamp(std::move(a), 3, 2);
        assert((static_cast<int>(a[0]) == 2) && (static_cast<int>(10 * a[1]) == 23) && (static_cast<int>(a[2]) == 3));

        const VectorBase<float, 3> acc(-1.0f, 2.3f, 5.5f),
                                   amin(0.0f),
                                   amax(2.0f);
        a = clamp(acc, 3, 2);
        assert((static_cast<int>(a[0]) == 2) && (static_cast<int>(10 * a[1]) == 23) && (static_cast<int>(a[2]) == 3));

        a = clamp(acc, amin, amax);
        assert((static_cast<int>(a[0]) == 0) && (static_cast<int>(a[1]) == 2) && (static_cast<int>(a[2]) == 2));

        // dot product
        VectorBase<int, 3> c(1,2,3),
                           d(2,2,2),
                           g(3,2,1);
        VectorBase<int, 5> e(6, 7, 8, 9, 5),
                           f(-2, -3, -4, -5, -6);

        assert(dot(d) == 12);
        assert(dot(VectorBase<int, 3>(1,2,3)) == 14);
        assert(dot(c, d) == 12);
        assert(static_cast<int>(dot(c, VectorBase<int, 3>(5, 0, 0))) == 5);
        assert(static_cast<int>(dot(VectorBase<int, 3>(5, 0, 0), c)) == 5);
        assert(static_cast<int>(dot(VectorBase<int, 3>(5, 0, 0), VectorBase<int, 3>(1,2,3))) == 5);

        assert(static_cast<int>(dot(c, d, g)) == 20);

        // min element
        assert(min(c) == 1);
        assert(min(d) == 2);
        assert(min(VectorBase<int, 3>(2,3,1)) == 1);
        assert(min(VectorBase<int, 3>(2,2,2)) == 2);

        assert(min(c, d) == 1);
        assert(min(VectorBase<int, 3>(2,3,1), VectorBase<int, 3>(2,2,2)) == 1);
        assert(min(c, VectorBase<int, 3>(2,2,2)) == 1);
        assert(min(VectorBase<int, 3>(2,3,1), d) == 1);

        assert(min(e, f) == -6);
        assert(min(e, f, VectorBase<int, 5>(-8)) == -8);
        assert(min(VectorBase<int, 5>(-18), e, f, VectorBase<int, 5>(-8)) == -18);

        // max element
        assert(max(c) == 3);
        assert(max(d) == 2);
        assert(max(VectorBase<int, 3>(2, 3, 1)) == 3);
        assert(max(VectorBase<int, 3>(2, 2, 2)) == 2);

        assert(max(c, d) == 3);
        assert(max(VectorBase<int, 3>{2, 3, 1}, VectorBase<int, 3>(2, 2, 2)) == 3);
        assert(max(c, VectorBase<int, 3>(2, 2, 2)) == 3);
        assert(max(VectorBase<int, 3>(2, 3, 1), d) == 3);

        assert(max(e, f) == 9);
        assert(max(e, f, VectorBase<int, 5>(12)) == 12);
        assert(max(VectorBase<int, 5>(-18), e, f, VectorBase<int, 5>(18)) == 18);

        // sum elements
        assert(sum(c) == 6);
        assert(sum(e) == 35);
        assert(sum(VectorBase<int, 5>(6, 7, 8, 9, 5)) == 35);
        assert(sum(c, d) == 12);
        assert(sum(c, VectorBase<int, 3>(6, 7, 7)) == 26);
        assert(sum(VectorBase<int, 3>(6, 7, 7), c) == 26);
        assert(sum(VectorBase<int, 3>(1,2,3), VectorBase<int, 3>(6, 7, 7)) == 26);
        assert(sum(c, d, g) == 18);
        assert(sum(VectorBase<int, 3>(1,2,3), VectorBase<int, 3>(2,2,2), g) == 18);

        // product elements
        assert(prod(c) == 6);
        assert(prod(e) == 15'120);
        assert(prod(VectorBase<int, 5>(6, 7, 8, 9, 5)) == 15'120);
        assert(prod(c, d) == 48);
        assert(prod(c, VectorBase<int, 3>(6, 7, 7)) == 1'764);
        assert(prod(VectorBase<int, 3>(6, 7, 7), c) == 1'764);
        assert(prod(VectorBase<int, 3>(1,2,3), VectorBase<int, 3>(6, 7, 7)) == 1'764);
        assert(prod(c, d, g) == 288);
        assert(prod(VectorBase<int, 3>(1,2,3), VectorBase<int, 3>(2,2,2), g) == 288);

        // mix
        VectorBase<float, 3> af(mix(VectorBase<float, 3>(0.5, 0, 2), VectorBase<float, 3>(1, 1, 3), 0.5));
        assert((static_cast<int>(100.0f * af[0]) == 75) && (static_cast<int>(10.0f * af[1]) == 5) && (static_cast<int>(10.0f * af[2]) == 25));

        af = VectorBase<float, 3>(0.5, 0, 2);
        VectorBase<float, 3> af1(mix(af, VectorBase<float, 3>(1, 1, 3), 0.5));
        assert((static_cast<int>(100.0f * af1[0]) == 75) && (static_cast<int>(10.0f * af1[1]) == 5) && (static_cast<int>(10.0f * af1[2]) == 25));
        
        af1 = mix(VectorBase<float, 3>(1, 1, 3), af, 0.5);
        assert((static_cast<int>(100.0f * af1[0]) == 75) && (static_cast<int>(10.0f * af1[1]) == 5) && (static_cast<int>(10.0f * af1[2]) == 25));

        const VectorBase<float, 3> camix(1, 1, 3);
        af1 = mix(camix, af, 0.5);
        assert((static_cast<int>(100.0f* af1[0]) == 75) && (static_cast<int>(10.0f* af1[1]) == 5) && (static_cast<int>(10.0f* af1[2]) == 25));

        // step
        af = step(std::move(af), 1);
        assert((static_cast<int>(af[0]) == 0) && (static_cast<int>(af[1]) == 0) && (static_cast<int>(af[2]) == 1));

        af = step(VectorBase<float, 3>(0.5, 0, 2), 1);
        assert((static_cast<int>(af[0]) == 0) && (static_cast<int>(af[1]) == 0) && (static_cast<int>(af[2]) == 1));

        const VectorBase<float, 3> astep(0.5, 0, 2);
        af = step(astep, 1);
        assert((static_cast<int>(af[0]) == 0) && (static_cast<int>(af[1]) == 0) && (static_cast<int>(af[2]) == 1));

        // smoothstep
        auto s0 = smoothstep(VectorBase<float, 3>(0.5f), 0, 1);
        assert((static_cast<int>(10.0f * s0[0]) == 5) && (static_cast<int>(10.0f * s0[1]) == 5) && (static_cast<int>(10.0f * s0[2]) == 5));

        const VectorBase<float, 3> _sc0(0.5f);
        s0 = smoothstep(_sc0, 0, 1);
        assert((static_cast<int>(10.0f* s0[0]) == 5) && (static_cast<int>(10.0f* s0[1]) == 5) && (static_cast<int>(10.0f* s0[2]) == 5));

        auto s2 = smoothstep(VectorBase<float, 3>(0.5f), VectorBase<float, 3>(0), VectorBase<float, 3>(1));
        assert((static_cast<int>(10.0f * s2[0]) == 5) && (static_cast<int>(10.0f * s2[1]) == 5) && (static_cast<int>(10.0f * s2[2]) == 5));

        s2 = smoothstep(_sc0, VectorBase<float, 3>(0), VectorBase<float, 3>(1));
        assert((static_cast<int>(10.0f* s2[0]) == 5) && (static_cast<int>(10.0f* s2[1]) == 5) && (static_cast<int>(10.0f* s2[2]) == 5));

        // smootherstep
        auto s1 = smootherstep(VectorBase<float, 3>(0.5f), 0, 1);
        assert((static_cast<int>(10.0f * s1[0]) == 5) && (static_cast<int>(10.0f * s1[1]) == 5) && (static_cast<int>(10.0f * s1[2]) == 5));

        s1 = smootherstep(_sc0, 0, 1);
        assert((static_cast<int>(10.0f* s1[0]) == 5) && (static_cast<int>(10.0f* s1[1]) == 5) && (static_cast<int>(10.0f* s1[2]) == 5));

        // isnan/isinf
        bool temp = GLSLCPP::isnan(s0);
        assert(temp == false);

        temp = GLSLCPP::isinf(s0);
        assert(temp == false);

        const VectorBase<float, 8> ss(0);
        temp = GLSLCPP::isinf(ss);
        assert(temp == false);

        s0[0] = std::numeric_limits<float>::quiet_NaN();
        s0[1] = std::numeric_limits<float>::infinity();

        temp = GLSLCPP::isnan(s0);
        assert(temp == true);
        temp = GLSLCPP::isnan(VectorBase<float, 3>(0.5f));
        assert(temp == false);
        temp = GLSLCPP::isinf(s0);
        assert(temp == true);

        const VectorBase<int, 4> s4(2);
        temp = GLSLCPP::isnan(s4);
        assert(temp == false);

        temp = GLSLCPP::isinf(VectorBase<float, 3>(0, 2, std::numeric_limits<float>::infinity()));
        assert(temp == true);

        // fma
        s0[0] = 0.5f;
        s0[1] = 0.5f;
        auto s3 = fma(s0, VectorBase<float, 3>(1), VectorBase<float, 3>(0.5));
        assert((static_cast<int>(s3[0]) == 1) && (static_cast<int>(s3[1]) == 1) && (static_cast<int>(s3[2]) == 1));

        // length
        assert(std::abs(length(VectorBase<double, 3>(1, 2, 3)) - std::sqrt(14)) < 1e-3);

        const VectorBase<double, 3> cdot(1, 2, 3);
        assert(std::abs(length(cdot) - std::sqrt(14)) < 1e-3);

        // distance
        assert(std::abs(distance(s3, VectorBase<float, 3>(0)) - std::sqrt(3)) < 1e-3);

        // cross
        s3[1] = s3[2] = 0;
        auto crs = cross(s3, VectorBase<float, 3>(0,1,0));
        assert((static_cast<int>(crs[0]) == 0) && (static_cast<int>(crs[1]) == 0) && (static_cast<int>(crs[2]) == 1));

        // round even
        auto re = roundEven(VectorBase<float, 3>(2.5, 3.5, 4.5));
        assert((static_cast<int>(re[0]) == 2) && (static_cast<int>(re[1]) == 4) && (static_cast<int>(re[2]) == 4));

        const VectorBase<float, 3> cre(2.5, 3.5, 4.5);
        re = roundEven(cre);
        assert((static_cast<int>(re[0]) == 2) && (static_cast<int>(re[1]) == 4) && (static_cast<int>(re[2]) == 4));

        re = roundEven(std::move(re));
        assert((static_cast<int>(re[0]) == 2) && (static_cast<int>(re[1]) == 4) && (static_cast<int>(re[2]) == 4));

        // reverse a vector
        VectorBase<int, 5> rev(0, 1, 2, 3, 4);

        auto brev = reverse(rev);
        assert((brev[0] == 4) && (brev[1] == 3) && (brev[2] == 2) && (brev[3] == 1) && (brev[4] == 0));

        rev = reverse(std::move(rev));
        assert((rev[0] == 4) && (rev[1] == 3) && (rev[2] == 2) && (rev[3] == 1) && (rev[4] == 0));

        const VectorBase<int, 5> crev(0, 1, 2, 3, 4);
        rev = reverse(crev);
        assert((rev[0] == 4) && (rev[1] == 3) && (rev[2] == 2) && (rev[3] == 1) && (rev[4] == 0));
    }

    std::cout << "VectorBase test successfully finished." << std::endl;
}

void Vector2Test() {
    // --- construction test ---
    {
        Vector2<bool> bool1(true),
                      bool2(true, false),
                      bool3(VectorBase<bool, 2>(false, true)),
                      bool4(Vector2<bool>(false, false)),
                      bool5(bool3.yx),
                      bool6(1, 0),
                      bool7(bool3),
                      bool8(VectorBase<bool, 3>(true, false, true));

        assert(isVector2(bool1) && isVector2(bool2) && isVector2(bool3) && 
               isVector2(bool4) && isVector2(bool5) && isVector2(bool6) && isVector2(bool7) && isVector2(bool8) && " one of the vectors is not of type Vector2<bool>.");

        assert((bool1.x == true) && (bool1.y == true));
        assert((bool2.x == true) && (bool2.y == false));
        assert((bool3.x == false) && (bool3.y == true));
        assert((bool4.x == false) && (bool4.y == false));
        assert((bool5.x == true) && (bool5.y == false));
        assert((bool6.x == true) && (bool6.y == false));
        assert((bool7.x == false) && (bool7.y == true));
        assert((bool8.x == true) && (bool8.y == false));
    }

    // --- assign/construct of VectorBase from Vector2 ---
    {
        Vector2<int> f1(1, 2);
        VectorBase<int, 2> vd(f1),
                           vb(f1.yx),
                           vc = f1.yx;
        assert((vd[0] == 1) && (vd[1] == 2));
        assert((vb[0] == 2) && (vb[1] == 1));
        assert((vc[0] == 2) && (vc[1] == 1));

    }

    // --- assignment test ---
    {       
        Vector2<float> f1(1, 2),
                       f2(3.0, 4.0),
                       f3(f1.gr),
                       f4 = f1,
                       f5 = f2.yx,
                       f6 = VectorBase<int, 2>(5, 6),
                       f7 = Vector2<int>(7, 8);

        assert((static_cast<int>(f1.x) == 1) && (static_cast<int>(f1.y) == 2));
        assert((static_cast<int>(f2.x) == 3) && (static_cast<int>(f2.y) == 4));
        assert((static_cast<int>(f3.x) == 2) && (static_cast<int>(f3.y) == 1));
        assert((static_cast<int>(f4.x) == 1) && (static_cast<int>(f4.y) == 2));
        assert((static_cast<int>(f5.x) == 4) && (static_cast<int>(f5.y) == 3));
        assert((static_cast<int>(f6.x) == 5) && (static_cast<int>(f6.y) == 6));
        assert((static_cast<int>(f7.x) == 7) && (static_cast<int>(f7.y) == 8));

        std::cout << "f1 = " << f1;
    }

    // --- swizzle assignment test ---
    {
        Vector2<float> f1(1, 2),
                       f2(3.0, 4.0),
                       f3(0);

        f3.yx = f1;
        assert((static_cast<int>(f3.x) == 2) && (static_cast<int>(f3.y) == 1));

        f3.yx = f2;
        assert((static_cast<int>(f3.x) == 4) && (static_cast<int>(f3.y) == 3));

        f3.yx = f2.xx;
        assert((static_cast<int>(f3.x) == 3) && (static_cast<int>(f3.y) == 3));

        // the following should not be possible:
        //f3.xx = f2.xy;
    }

    // --- compound operators test ---
    {
        Vector2<int> i0(0),
                     i1(1.0f, 1.0),
                     i2(3, 4);

        // operation between vectors and scalars
        i0 += 1;
        assert((i0.x == 1) && (i0.y == 1));

        i0 *= 2;
        assert((i0.x == 2) && (i0.y == 2));

        i0 /= 2;
        assert((i0.x == 1) && (i0.y == 1));

        i0 -= 1;
        assert((i0.x == 0) && (i0.y == 0));

        // operation between vectors and vectors
        i0 += i1;
        assert((i0.x == 1) && (i0.y == 1));

        i0 *= Vector2<float>(2);
        assert((i0.x == 2) && (i0.y == 2));

        i0 /= VectorBase<double,2>(2);
        assert((i0.x == 1) && (i0.y == 1));

        i0 -= i1;
        assert((i0.x == 0) && (i0.y == 0));

        // operation between vectors and swizzle's
        i0 += i2.yx;
        assert((i0.x == 4) && (i0.y == 3));

        i0 -= i2.rg;
        assert((i0.x == 1) && (i0.y == -1));

        i0 *= i2.xy;
        assert((i0.x == 3) && (i0.y == -4));

        i0 /= i2.xy;
        assert((i0.x == 1) && (i0.y == -1));

        // operation between swizzle's and scalars
        i0.xy += 1;
        assert((i0.x == 2) && (i0.y == 0));

        i0.xy *= 2;
        assert((i0.x == 4) && (i0.y == 0));

        i0.xy /= 2;
        assert((i0.x == 2) && (i0.y == 0));

        i0.xy -= 1;
        assert((i0.x == 1) && (i0.y == -1));

        // operation between swizzle's and vectors
        i0 = Vector2<int>(0);

        i0.xy += i1;
        assert((i0.x == 1) && (i0.y == 1));

        i0.xy *= Vector2<float>(2);
        assert((i0.x == 2) && (i0.y == 2));

        i0.xy /= VectorBase<double, 2>(2);
        assert((i0.x == 1) && (i0.y == 1));

        i0.xy -= i1;
        assert((i0.x == 0) && (i0.y == 0));     

        // operation between swizzle's and swizzle's
        i0.xy += i2.yx;
        assert((i0.x == 4) && (i0.y == 3));

        i0.yx -= i2.xy;
        assert((i0.x == 1) && (i0.y == -1));

        i0.yx *= i2.xy;
        assert((i0.x == 3) && (i0.y == -4));

        i0.yx /= i2.xy;
        assert((i0.x == 1) && (i0.y == -1));
    }

    // --- numerical operators test ---
    {
        Vector2<int> i0(0),
                     i1(1.0f, 1.0),
                     i2(3, 4);

        // vector OP scalar
        i0 = i1 + 1;
        assert((i0.x == 2) && (i0.y == 2));

        i0 = i1 - 1;
        assert((i0.x == 0) && (i0.y == 0));

        i0 = i1 * 2;
        assert((i0.x == 2) && (i0.y == 2));

        i0 = Vector2<int>(2) / 2;
        assert((i0.x == 1) && (i0.y == 1));

        i0 = VectorBase<int, 2>(2) / 2;
        assert((i0.x == 1) && (i0.y == 1));

        // vector OP vector
        i0 = i1 + i2;
        assert((i0.x == 4) && (i0.y == 5));

        i0 = i2 - i1;
        assert((i0.x == 2) && (i0.y == 3));

        i0 = i1 * i2;
        assert((i0.x == 3) && (i0.y == 4));

        i0 = i2 / i1;
        assert((i0.x == 3) && (i0.y == 4));

        i0 = i1 + Vector2<int>(3.0f);
        assert((i0.x == 4) && (i0.y == 4));

        i0 = i1 + VectorBase<int, 2>(2.0f);
        assert((i0.x == 3) && (i0.y == 3));

        i0 = -i0;
        assert((i0.x == -3) && (i0.y == -3));

        // swizzle/vector OP swizzle
        i0 = i1 + i2.yx;
        assert((i0.x == 5) && (i0.y == 4));

        i0 = i1.yx + i2;
        assert((i0.x == 4) && (i0.y == 5));

        i0 = i1 * i2.yx;
        assert((i0.x == 4) && (i0.y == 3));

        i0 = i2.yx * i1;
        assert((i0.x == 4) && (i0.y == 3));

        i0 = i2.yx * Vector2<int>(2);
        assert((i0.x == 8) && (i0.y == 6));

        i0 = i2.yx + VectorBase<int, 2>(3);
        assert((i0.x == 7) && (i0.y == 6));

        // swizzle OP swizzle
        i0 = i1.xy + i2.yx;
        assert((i0.x == 5) && (i0.y == 4));

        i0 = i1.xy + i2.xx;
        assert((i0.x == 4) && (i0.y == 4));

        i0 = i1.xx + i2.yy;
        assert((i0.x == 5) && (i0.y == 5));

        i0 = i1.xy * i2.yx;
        assert((i0.x == 4) && (i0.y == 3));

        i0 = i2.xy * i2.xx;
        assert((i0.x == 9) && (i0.y == 12));

        i0 = -i0;
        assert((i0.x == -9) && (i0.y == -12));

        i0 = -Vector2<int>(8);
        assert((i0.x == -8) && (i0.y == -8));
    }

    // relational operators and functions
    {
        Vector2<int> i0(0, 1),
                     i1(1, 1),
                     i2(5, 5);
        bool a{ i0 > i1 },
             b(i1 < i2),
             c(i1 == 1),
             d(i1 == 3);
        assert(a == false);
        assert(b == true);
        assert(c == true);
        assert(d == false);

        Vector2<bool> f(0),
                       t(1);
        assert(any(f) == false);
        assert(any(VectorBase<bool, 2>(0)) == false);
        assert(any(t) == true);

        const Vector2<bool> fc(0);
        assert(any(fc) == false);

        assert(all(f) == false);
        assert(all(t) == true);

        auto f1 = Not(f);
        assert(all(f1) == true);

        auto f2 = Not(VectorBase<bool, 3>(0));
        assert(all(f2) == true);
    }

    // numerical functions
    {
        Vector2<float> a(-1.0f, 2.3f);
        const Vector2<float> ca(-1.0f, 2.3f);

        // unary functions
        auto b = sign(a);
        assert((static_cast<int>(b[0]) == -1) && (static_cast<int>(b[1]) == 1));

        b = sign(ca);
        assert((static_cast<int>(b[0]) == -1) && (static_cast<int>(b[1]) == 1));

        a = abs(a);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1] * 10) == 23));

        a = abs(ca);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1] * 10) == 23));

        // binary functions
        a = Vector2<float>(1, 2);
        a = pow(a, Vector2<float>(2));
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4));

        a = Vector2<float>(1, 2);
        a = pow(a, 2.0f);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4));

        a = pow(Vector2<float>(1, 2), Vector2<float>(2));
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4));
    }

    std::cout << "Vector2 test successfully finished." << std::endl;
}

void Vector3Test() {
    // --- construction test ---
    {
        Vector2<bool> b3(false, true);

        Vector3<bool> bool1(true),
                      bool2(true, false, true),
                      bool3(VectorBase<bool, 3>(false, true, false)),
                      bool4(Vector3<bool>(false, false, false)),
                      bool5(bool3.yxz),
                      bool6(1, 0, 1),
                      bool7(bool3),
                      bool8(b3.yx, true),
                      bool9(true, b3.xx),
                      bool10(Vector2<bool>(0,0), 1);

        assert(isVector3(bool1) && isVector3(bool2) && isVector3(bool3) && isVector3(bool4) &&
               isVector3(bool5) && isVector3(bool6) && isVector3(bool7) && isVector3(bool8) && isVector3(bool9) && " one of the vectors is not of type Vector3<bool>.");

        assert((bool1.x == true) && (bool1.y == true) && (bool1.z == true));
        assert((bool2.x == true) && (bool2.y == false) && (bool2.z == true));
        assert((bool3.x == false) && (bool3.y == true) && (bool3.z == false));
        assert((bool4.x == false) && (bool4.y == false) && (bool4.z == false));
        assert((bool5.x == true) && (bool5.y == false) && (bool5.z == false));
        assert((bool6.x == true) && (bool6.y == false) && (bool6.z == true));
        assert((bool7.x == false) && (bool7.y == true) && (bool7.z == false));
        assert((bool8.x == true) && (bool8.y == false) && (bool8.z == true));
        assert((bool9.x == true) && (bool9.y == false) && (bool9.z == false));
        assert((bool10.x == false) && (bool10.y == false) && (bool10.z == true));
    }

    // --- assign/construct of VectorBase from Vector3 ---
    {
        Vector3<int> f1(1, 2, 3);
        VectorBase<int, 3> vd(f1),
                           vb(f1.yxz),
                           vc = f1.yxz;
        assert((vd[0] == 1) && (vd[1] == 2) && (vd[2] == 3));
        assert((vb[0] == 2) && (vb[1] == 1) && (vb[2] == 3));
        assert((vc[0] == 2) && (vc[1] == 1) && (vc[2] == 3));

    }

    // --- assignment test ---
    {
        Vector3<float> f1(1, 2, 3),
                       f2(3.0, 4.0, 5.0),
                       f3(f1.grb),
                       f4 = f1,
                       f5 = f2.yxz,
                       f6 = VectorBase<int, 3>(5, 6, 7),
                       f7 = Vector3<int>(7, 8, 9);

        assert((static_cast<int>(f1.x) == 1) && (static_cast<int>(f1.y) == 2) && (static_cast<int>(f1.z) == 3));
        assert((static_cast<int>(f2.x) == 3) && (static_cast<int>(f2.y) == 4) && (static_cast<int>(f2.z) == 5));
        assert((static_cast<int>(f3.x) == 2) && (static_cast<int>(f3.y) == 1) && (static_cast<int>(f3.z) == 3));
        assert((static_cast<int>(f4.x) == 1) && (static_cast<int>(f4.y) == 2) && (static_cast<int>(f4.z) == 3));
        assert((static_cast<int>(f5.x) == 4) && (static_cast<int>(f5.y) == 3) && (static_cast<int>(f5.z) == 5));
        assert((static_cast<int>(f6.x) == 5) && (static_cast<int>(f6.y) == 6) && (static_cast<int>(f6.z) == 7));
        assert((static_cast<int>(f7.x) == 7) && (static_cast<int>(f7.y) == 8) && (static_cast<int>(f7.z) == 9));
    }

    // --- swizzle assignment test ---
    {
        Vector3<float> f1(1, 2, 3),
                       f2(3.0, 4.0, 5.0),
                       f3(0);

        f3.yxz = f1;
        assert((static_cast<int>(f3.x) == 2) && (static_cast<int>(f3.y) == 1) && (static_cast<int>(f3.z) == 3));

        f3.yxz = f2;
        assert((static_cast<int>(f3.x) == 4) && (static_cast<int>(f3.y) == 3) && (static_cast<int>(f3.z) == 5));

        f3.yxz = f2.xxx;
        assert((static_cast<int>(f3.x) == 3) && (static_cast<int>(f3.y) == 3) && (static_cast<int>(f3.z) == 3));

        // the following should not be possible:
        //f3.xxx = f2.xyz;
    }

    // --- compound operators test ---
    {
        Vector3<int> i0(0),
                     i1(1.0f, 1.0, 1),
                     i2(3, 4, 5);

        // operation between vectors and scalars
        i0 += 1;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        i0 *= 2;
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2));

        i0 /= 2;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        i0 -= 1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0));

        // operation between vectors and vectors
        i0 += i1;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        i0 *= Vector3<float>(2);
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2));

        i0 /= VectorBase<double, 3>(2);
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        i0 -= i1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0));

        // operation between vectors and swizzle's
        i0 += i2.yxz;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 5));

        i0 -= i2.rgr;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 2));

        i0 *= i2.xyz;
        assert((i0.x == 3) && (i0.y == -4) && (i0.z == 10));

        i0 /= i2.xyz;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 2));

        // operation between swizzle's and scalars
        i0.xyz += 1;
        assert((i0.x == 2) && (i0.y == 0) && (i0.z == 3));

        i0.xyz *= 2;
        assert((i0.x == 4) && (i0.y == 0) && (i0.z == 6));

        i0.xyz /= 2;
        assert((i0.x == 2) && (i0.y == 0) && (i0.z == 3));

        i0.xyz -= 1;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 2));

        // operation between swizzle's and vectors
        i0 = Vector3<int>(0);

        i0.xyz += i1;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        i0.xyz *= Vector3<float>(2);
        assert((i0.x == 2) && (i0.y == 2));

        i0.xyz /= VectorBase<double, 3>(2);
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        i0.xyz -= i1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0));

        // operation between swizzle's and swizzle's
        i0.xyz += i2.yxz;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 5));

        i0.yxz -= i2.xyz;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 0));

        i0.yxz *= i2.xyx;
        assert((i0.x == 3) && (i0.y == -4) && (i0.z == 0));

        i0.yxz /= i2.xyz;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 0));
    }

    // --- numerical operators test ---
    {
        Vector3<int> i0(0),
            i1(1.0f, 1.0, 1),
            i2(3, 4, 1);

        // vector OP scalar
        i0 = i1 + 1;
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2));

        i0 = i1 - 1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0));

        i0 = i1 * 2;
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2));

        i0 = Vector3<int>(2) / 2;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        i0 = VectorBase<int, 3>(2) / 2;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1));

        // vector OP vector
        i0 = i1 + i2;
        assert((i0.x == 4) && (i0.y == 5) && (i0.z == 2));

        i0 = i2 - i1;
        assert((i0.x == 2) && (i0.y == 3) && (i0.z == 0));

        i0 = i1 * i2;
        assert((i0.x == 3) && (i0.y == 4) && (i0.z == 1));

        i0 = i2 / i1;
        assert((i0.x == 3) && (i0.y == 4) && (i0.z == 1));

        i0 = i1 + Vector3<int>(3.0f);
        assert((i0.x == 4) && (i0.y == 4) && (i0.z == 4));

        i0 = i1 + VectorBase<int, 3>(2.0f);
        assert((i0.x == 3) && (i0.y == 3) && (i0.z == 3));

        i0 = -i0;
        assert((i0.x == -3) && (i0.y == -3) && (i0.z == -3));

        // swizzle/vector OP swizzle
        i0 = i1 + i2.yxz;
        assert((i0.x == 5) && (i0.y == 4) && (i0.z == 2));

        i0 = i1.yxz + i2;
        assert((i0.x == 4) && (i0.y == 5) && (i0.z == 2));

        i0 = i1 * i2.yxz;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 1));

        i0 = i2.yxz * i1;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 1));

        i0 = i2.yxz * Vector3<int>(2);
        assert((i0.x == 8) && (i0.y == 6) && (i0.z == 2));

        i0 = i2.yxz + VectorBase<int, 3>(3);
        assert((i0.x == 7) && (i0.y == 6) && (i0.z == 4));

        // swizzle OP swizzle
        i0 = i1.xyz + i2.yxz;
        assert((i0.x == 5) && (i0.y == 4) && (i0.z == 2));

        i0 = i1.xyz + i2.xxx;
        assert((i0.x == 4) && (i0.y == 4) && (i0.z == 4));

        i0 = i1.xxz + i2.yyz;
        assert((i0.x == 5) && (i0.y == 5) && (i0.z == 2));

        i0 = i1.xyz * i2.yxz;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 1));

        i0 = i2.xyz * i2.xxx;
        assert((i0.x == 9) && (i0.y == 12) && (i0.z == 3));

        i0 = -i0;
        assert((i0.x == -9) && (i0.y == -12) && (i0.z == -3));

        i0 = -Vector3<int>(8);
        assert((i0.x == -8) && (i0.y == -8) && (i0.z == -8));
    }

    // relational operators and functions
    {
        Vector3<int> i0(0, 1, 2),
                     i1(1, 1, 1),
                     i2(5, 5, 2);
        bool a{ i0 > i1 },
             b(i1 < i2),
             c(i1 == 1),
             d(i1 == 3);
        assert(a == false);
        assert(b == true);
        assert(c == true);
        assert(d == false);

        Vector3<bool> f(0),
                      t(1);
        assert(any(f) == false);
        assert(any(t) == true);

        assert(all(f) == false);
        assert(all(t) == true);

        auto f1 = Not(f);
        assert(all(f1) == true);

        auto f2 = Not(VectorBase<bool, 3>(0));
        assert(all(f2) == true);
    }

    // numerical functions
    {
        Vector3<float> a(-1.0f, 2.3f, 3.5);

        // unary functions
        auto b = sign(a);
        assert((static_cast<int>(b[0]) == -1) && (static_cast<int>(b[1]) == 1) && (static_cast<int>(b[2]) == 1));

        a = abs(a);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1] * 10) == 23) && (static_cast<int>(a[2] * 10) == 35));

        // binary functions
        a = Vector3<float>(1, 2, 3);
        a = pow(a, Vector3<float>(2));
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4) && (static_cast<int>(a[2]) == 9));

        a = Vector3<float>(1, 2, 3);
        a = pow(a, 2.0f);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4) && (static_cast<int>(a[2]) == 9));

        auto crs = cross(Vector3<float>(1, 0, 0), Vector3<float>(0, 1, 0));
        assert((static_cast<int>(crs[0]) == 0) && (static_cast<int>(crs[1]) == 0) && (static_cast<int>(crs[2]) == 1));
    }

    std::cout << "Vector3 test successfully finished." << std::endl;
}

void Vector4Test() {
    // --- construction test ---
    {
        Vector2<bool> b2(false, true);
        Vector3<bool> b3(false, true, false);

        Vector4<bool> bool1(true),
                      bool2(true, false, true, false),
                      bool3(VectorBase<bool, 4>(false, true, false, true)),
                      bool4(Vector4<bool>(false, false, false, false)),
                      bool5(bool3.yxzw),
                      bool6(1, 0, 1, 0),
                      bool7(bool3),
                      bool8(b2.yx, true, false),
                      bool9(true, b2.xx, false),
                      bool10(true, false, b2.xx),
                      bool11(Vector2<bool>(0, 0), 1, 1),
                      bool12(1, Vector2<bool>(0, 0), 1),
                      bool13(1, 1, Vector2<bool>(0, 0)),
                      bool14(1, Vector3<bool>(0)),
                      bool15(Vector3<bool>(0), 1),
                      bool16(1, b3.xxx),
                      bool17(b3.yyy, 1);

        assert(isVector4(bool1) && isVector4(bool2) && isVector4(bool3) && isVector4(bool4) &&
               isVector4(bool5) && isVector4(bool6) && isVector4(bool7) && isVector4(bool8) && isVector4(bool9) && " one of the vectors is not of type Vector4<bool>.");

        assert((bool1.x == true)   && (bool1.y == true)   && (bool1.z == true)   && (bool1.w == true));
        assert((bool2.x == true)   && (bool2.y == false)  && (bool2.z == true)   && (bool2.w == false));
        assert((bool3.x == false)  && (bool3.y == true)   && (bool3.z == false)  && (bool3.w == true));
        assert((bool4.x == false)  && (bool4.y == false)  && (bool4.z == false)  && (bool4.w == false));
        assert((bool5.x == true)   && (bool5.y == false)  && (bool5.z == false)  && (bool5.w == true));
        assert((bool6.x == true)   && (bool6.y == false)  && (bool6.z == true)   && (bool6.w == false));
        assert((bool7.x == false)  && (bool7.y == true)   && (bool7.z == false)  && (bool7.w == true));
        assert((bool8.x == true)   && (bool8.y == false)  && (bool8.z == true)   && (bool8.w == false));
        assert((bool9.x == true)   && (bool9.y == false)  && (bool9.z == false)  && (bool9.w == false));
        assert((bool10.x == true)  && (bool10.y == false) && (bool10.z == false) && (bool10.w == false));
        assert((bool11.x == false) && (bool11.y == false) && (bool11.z == true)  && (bool11.w == true));
        assert((bool12.x == true)  && (bool12.y == false) && (bool12.z == false) && (bool12.w == true));
        assert((bool13.x == true)  && (bool13.y == true)  && (bool13.z == false) && (bool13.w == false));
        assert((bool14.x == true)  && (bool14.y == false) && (bool14.z == false) && (bool14.w == false));
        assert((bool15.x == false) && (bool15.y == false) && (bool15.z == false) && (bool15.w == true));
        assert((bool16.x == true)  && (bool16.y == false) && (bool16.z == false) && (bool16.w == false));
        assert((bool17.x == true)  && (bool17.y == true)  && (bool17.z == true)  && (bool17.w == true));
    }

    // --- assign/construct of VectorBase from Vector4 ---
    {
        Vector4<int> f1(1, 2, 3, 4);
        VectorBase<int, 4> vd(f1),
                           vb(f1.wyxz),
                           vc = f1.wyxz;
        assert((vd[0] == 1) && (vd[1] == 2) && (vd[2] == 3) && (vd[3] == 4));
        assert((vb[0] == 4) && (vb[1] == 2) && (vb[2] == 1) && (vb[3] == 3));
        assert((vc[0] == 4) && (vc[1] == 2) && (vc[2] == 1) && (vc[3] == 3));
    }

    // --- assignment test ---
    {
        Vector4<float> f1(1, 2, 3, 4),
                       f2(3.0, 4.0, 5.0, 6),
                       f3(f1.agrb),
                       f4 = f1,
                       f5 = f2.wyxz,
                       f6 = VectorBase<int, 4>(5, 6, 7, 8),
                       f7 = Vector4<int>(7, 8, 9, 10);

        assert((static_cast<int>(f1.x) == 1) && (static_cast<int>(f1.y) == 2) && (static_cast<int>(f1.z) == 3) && (static_cast<int>(f1.w) == 4));
        assert((static_cast<int>(f2.x) == 3) && (static_cast<int>(f2.y) == 4) && (static_cast<int>(f2.z) == 5) && (static_cast<int>(f2.w) == 6));
        assert((static_cast<int>(f3.x) == 4) && (static_cast<int>(f3.y) == 2) && (static_cast<int>(f3.z) == 1) && (static_cast<int>(f3.w) == 3));
        assert((static_cast<int>(f4.x) == 1) && (static_cast<int>(f4.y) == 2) && (static_cast<int>(f4.z) == 3) && (static_cast<int>(f4.w) == 4));
        assert((static_cast<int>(f5.x) == 6) && (static_cast<int>(f5.y) == 4) && (static_cast<int>(f5.z) == 3) && (static_cast<int>(f5.w) == 5));
        assert((static_cast<int>(f6.x) == 5) && (static_cast<int>(f6.y) == 6) && (static_cast<int>(f6.z) == 7) && (static_cast<int>(f6.w) == 8));
        assert((static_cast<int>(f7.x) == 7) && (static_cast<int>(f7.y) == 8) && (static_cast<int>(f7.z) == 9) && (static_cast<int>(f7.w) == 10));
    }

    // --- swizzle assignment test ---
    {
        Vector4<float> f1(1, 2, 3, 4),
                       f2(3.0, 4.0, 5.0, 6),
                       f3(0);

        f3.wyxz = f1;
        assert((static_cast<int>(f3.x) == 3) && (static_cast<int>(f3.y) == 2) && (static_cast<int>(f3.z) == 4) && (static_cast<int>(f3.w) == 1));

        f3.wyxz = f2;
        assert((static_cast<int>(f3.x) == 5) && (static_cast<int>(f3.y) == 4) && (static_cast<int>(f3.z) == 6) && (static_cast<int>(f3.w) == 3));

        f3.yxzw = f2.xxxy;
        assert((static_cast<int>(f3.x) == 3) && (static_cast<int>(f3.y) == 3) && (static_cast<int>(f3.z) == 3) && (static_cast<int>(f3.w) == 4));

        // the following should not be possible:
        //f3.xxxx = f2.xyzw;
    }

    // --- compound operators test ---
    {
        Vector4<int> i0(0),
                     i1(1.0f, 1.0, 1, true),
                     i2(3, 4, 5, 6);

        // operation between vectors and scalars
        i0 += 1;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        i0 *= 2;
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2) && (i0.w == 2));

        i0 /= 2;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        i0 -= 1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0) && (i0.w == 0));

        // operation between vectors and vectors
        i0 += i1;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        i0 *= Vector4<float>(2);
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2) && (i0.w == 2));

        i0 /= VectorBase<double, 4>(2);
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        i0 -= i1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0) && (i0.w == 0));

        // operation between vectors and swizzle's
        i0 += i2.yxzw;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 5) && (i0.w == 6));

        i0 -= i2.rgrb;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 2) && (i0.w == 1));

        i0 *= i2.xyzw;
        assert((i0.x == 3) && (i0.y == -4) && (i0.z == 10) && (i0.w == 6));

        i0 /= i2.xyzw;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 2) && (i0.w == 1));

        // operation between swizzle's and scalars
        i0.xyzw += 1;
        assert((i0.x == 2) && (i0.y == 0) && (i0.z == 3) && (i0.w == 2));

        i0.xyzw *= 2;
        assert((i0.x == 4) && (i0.y == 0) && (i0.z == 6) && (i0.w == 4));

        i0.xyzw /= 2;
        assert((i0.x == 2) && (i0.y == 0) && (i0.z == 3) && (i0.w == 2));

        i0.xyzw -= 1;
        assert((i0.x == 1) && (i0.y == -1) && (i0.z == 2) && (i0.w == 1));

        // operation between swizzle's and vectors
        i0 = Vector4<int>(0);

        i0.xyzw += i1;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        i0.xyzw *= Vector4<float>(2);
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2) && (i0.w == 2));

        i0.xyzw /= VectorBase<double, 4>(2);
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        i0.xyzw -= i1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0) && (i0.w == 0));

        // operation between swizzle's and swizzle's
        i0 = Vector4<int>(0);

        i0.wxyz += i2.wyxz;
        assert((i0.x == 6) && (i0.y == 4) && (i0.z == 3) && (i0.w == 5));

        i0.wyxz -= i2.wyxz;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0) && (i0.w == 0));

        i0 = Vector4<int>(1);
        i0.wyxz *= i2.wyxz;
        assert((i0.x == 6) && (i0.y == 4) && (i0.z == 3) && (i0.w == 5));

        i0.wyxz /= i2.wyxz;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));
    }

    // --- numerical operators test ---
    {
        Vector4<int> i0(0),
                     i1(1.0f, 1.0, 1, true),
                     i2(3, 4, 1, 5);

        // vector OP scalar
        i0 = i1 + 1;
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2) && (i0.w == 2));

        i0 = i1 - 1;
        assert((i0.x == 0) && (i0.y == 0) && (i0.z == 0) && (i0.w == 0));

        i0 = i1 * 2;
        assert((i0.x == 2) && (i0.y == 2) && (i0.z == 2) && (i0.w == 2));

        i0 = Vector4<int>(2) / 2;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        i0 = VectorBase<int, 4>(2) / 2;
        assert((i0.x == 1) && (i0.y == 1) && (i0.z == 1) && (i0.w == 1));

        // vector OP vector
        i0 = i1 + i2;
        assert((i0.x == 4) && (i0.y == 5) && (i0.z == 2) && (i0.w == 6));

        i0 = i2 - i1;
        assert((i0.x == 2) && (i0.y == 3) && (i0.z == 0) && (i0.w == 4));

        i0 = i1 * i2;
        assert((i0.x == 3) && (i0.y == 4) && (i0.z == 1) && (i0.w == 5));

        i0 = i2 / i1;
        assert((i0.x == 3) && (i0.y == 4) && (i0.z == 1) && (i0.w == 5));

        i0 = i1 + Vector4<int>(3.0f);
        assert((i0.x == 4) && (i0.y == 4) && (i0.z == 4) && (i0.w == 4));

        i0 = i1 + VectorBase<int, 4>(2.0f);
        assert((i0.x == 3) && (i0.y == 3) && (i0.z == 3) && (i0.w == 3));

        i0 = -i0;
        assert((i0.x == -3) && (i0.y == -3) && (i0.z == -3) && (i0.w == -3));

        // swizzle/vector OP swizzle
        i0 = i1 + i2.yxzw;
        assert((i0.x == 5) && (i0.y == 4) && (i0.z == 2) && (i0.w == 6));

        i0 = i1.yxzw + i2;
        assert((i0.x == 4) && (i0.y == 5) && (i0.z == 2) && (i0.w == 6));

        i0 = i1 * i2.yxzw;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 1) && (i0.w == 5));

        i0 = i2.yxzw * i1;
        assert((i0.x == 4) && (i0.y == 3) && (i0.z == 1) && (i0.w == 5));

        i0 = i2.yxzw * Vector4<int>(2);
        assert((i0.x == 8) && (i0.y == 6) && (i0.z == 2) && (i0.w == 10));

        i0 = i2.yxzw + VectorBase<int, 4>(3);
        assert((i0.x == 7) && (i0.y == 6) && (i0.z == 4) && (i0.w == 8));

        // swizzle OP swizzle
                // i2(3, 4, 1, 5)
        i0 = i1.wxyz + i2.wyxz;
        assert((i0.x == 6) && (i0.y == 5) && (i0.z == 4) && (i0.w == 2));

        i0 = i1.wxyz + i2.yxxx;
        assert((i0.x == 5) && (i0.y == 4) && (i0.z == 4) && (i0.w == 4));

        i0 = i1.wxxz + i2.wyyz;
        assert((i0.x == 6) && (i0.y == 5) && (i0.z == 5) && (i0.w == 2));

        i0 = i1.wxyz * i2.wyxz;
        assert((i0.x == 5) && (i0.y == 4) && (i0.z == 3) && (i0.w == 1));

        i0 = i2.wxyz * i2.zxxx;
        assert((i0.x == 5) && (i0.y == 9) && (i0.z == 12) && (i0.w == 3));

        i0 = -i0;
        assert((i0.x == -5) && (i0.y == -9) && (i0.z == -12) && (i0.w == -3));

        i0 = -Vector4<int>(8);
        assert((i0.x == -8) && (i0.y == -8) && (i0.z == -8) && (i0.w == -8));
    }

    // relational operators and functions
    {
        Vector4<int> i0(0, 1, 2, 3),
                     i1(1, 1, 1, 1),
                     i2(5, 5, 2, 3);
        bool a{ i0 > i1 },
             b(i1 < i2),
             c(i1 == 1),
             d(i1 == 3);
        assert(a == false);
        assert(b == true);
        assert(c == true);
        assert(d == false);

        Vector4<bool> f(0),
                      t(1);
        assert(any(f) == false);
        assert(any(t) == true);

        assert(all(f) == false);
        assert(all(t) == true);

        auto f1 = Not(f);
        assert(all(f1) == true);

        auto f2 = Not(VectorBase<bool, 4>(0));
        assert(all(f2) == true);
    }

    // numerical functions
    {
        Vector4<float> a(-1.0f, 2.3f, 3.5, 6);

        // unary functions
        auto b = sign(a);
        assert((static_cast<int>(b[0]) == -1) && (static_cast<int>(b[1]) == 1) && (static_cast<int>(b[2]) == 1) && (static_cast<int>(b[3]) == 1));

        a = abs(a);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1] * 10) == 23) && (static_cast<int>(a[2] * 10) == 35) && (static_cast<int>(a[3]) == 6));

        // binary functions
        a = Vector4<float>(1, 2, 3, 4);
        a = pow(a, Vector4<float>(2));
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4) && (static_cast<int>(a[2]) == 9) && (static_cast<int>(a[3]) == 16));

        a = Vector4<float>(1, 2, 3, 4);
        a = pow(a, 2.0f);
        assert((static_cast<int>(a[0]) == 1) && (static_cast<int>(a[1]) == 4) && (static_cast<int>(a[2]) == 9) && (static_cast<int>(a[3]) == 16));
    }

    std::cout << "Vector4 test successfully finished." << std::endl;
}

void MatrixBaseTest() {

    // constructors
    {
        // 'I'
        MatrixBase<int, 3, 3> a;
        assert(isMatrixBase(a) == true && " 'a' is not a matrix");
        assert(a(0, 0) == 1); assert(a(1, 1) == 1); assert(a(2, 2) == 1);
        assert(a(0, 1) == 0); assert(a(0, 2) == 0);
        assert(a(1, 0) == 0); assert(a(1, 2) == 0);
        assert(a(2, 0) == 0); assert(a(2, 1) == 0);

        // construct from one/variadic sclars or a vector
        MatrixBase<int, 3, 4> b(2),
            c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12),
            d(VectorBase<float, 12>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));

        assert(isMatrixBase(b) == true && " 'b' is not a matrix");
        assert(isMatrixBase(c) == true && " 'c' is not a matrix");

        for_each(b, [](auto elm) { assert(elm == 2 && " 'b' was not created correctly"); });
        for_each(c, [i = 1](auto elm) mutable {
            assert(elm == i && " 'c' was not created correctly");
            ++i;
        });
        for_each(d, [i = 1](auto elm) mutable {
            assert(elm == i && " 'd' was not created correctly");
            ++i;
        });

        // consturct cubic matrix from smaller matrix
        MatrixBase<float, 2, 2> e(2, 1, 3, 2);
        MatrixBase<int, 3, 3> f(e),
            g(MatrixBase<float, 2, 2>(2, 1, 3, 2));

        VectorBase<int, 9> t(2, 1, 0, 3, 2, 0, 0, 0, 1);
        assert(f.m_data == t);
        assert(g.m_data == t);

        // construct rectangular matrix from smaller matrix
        MatrixBase<int, 2, 4> f1(e),
            g1(MatrixBase<float, 2, 2>(2, 1, 3, 2));

        VectorBase<int, 8> t1(2, 1, 0, 0, 3, 2, 0, 0);
        assert(f1.m_data == t1);
        assert(g1.m_data == t1);

        // assign a value to a matrix
        MatrixBase<int, 2, 3> av(1);
        assert(av.m_data == 1);
        av = 3;
        assert(av.m_data == 3);

        // assign a list to a matrix (converts into a VectorBase and calls the VectorBase based constructor)
        av = { 1, 2, 3, 4, 5, 6 };
        VectorBase<int, 6> av_v(1, 2, 3, 4, 5, 6);
        assert(av.m_data == av_v);

        // assign a vector to a matrix
        VectorBase<int, 6> av_v2(2, 2, 2, 4, 5, 6);
        av = av_v2;
        assert(av.m_data == av_v2);

        av = VectorBase<int, 6>(1, 2, 3, 4, 5, 6);
        assert(av.m_data == av_v);

        // check length related queries
        assert(av.length() == 6);
        static_assert(Length_v<MatrixBase<int, 2, 3>> == 6, "");

        // test column getters
        Vector3<int> col0 = av[0];  // 1, 2, 3
        Vector3<int> col1 = av[1];  // 4, 5, 6

        Vector3<int> _c(1, 2, 3);
        assert(col0 == _c);

        _c = Vector3<int>(4, 5, 6);
        assert(col1 == _c);

        // test column change
        av[0] = ivec3(212, 212, 122); // change first column
        col0 = av[0];
        Vector3<int> _col0(212, 212, 122);
        assert(col0 == _col0);

        av[1][1] = 11; // change second column second element
        col1 = av[1];
        Vector3<int> _col1(4, 11, 6);
        assert(col1 == _col1);

        // test construction via columns
        VectorBase<int, 4> __a1(1, 2, 3, 4),
                           __a2(5, 6, 7, 8),
                           __a3(9, 9, 9, 9);
        MatrixBase<int, 3, 4> fromColumn(__a1, __a2, __a3);

        ivec4 __c = fromColumn[0],
              __col(1, 2, 3, 4);
        assert(__c == __col);

        __c = fromColumn[1];
        __col = ivec4(5, 6, 7, 8);
        assert(__c == __col);

        __c = fromColumn[2];
        __col = ivec4(9, 9, 9, 9);
        assert(__c == __col);
    }

    // element wise operations with scalars
    {
        MatrixBase<int, 3, 5> a(0.0);
        for_each(a, [](auto elm) { assert(elm == 0 && " 'a' was not created correctly"); });

        a += 1;
        for_each(a, [](auto elm) { assert(elm == 1 && " '+=' operator does not worl correctly"); });

        a *= 2;
        for_each(a, [](auto elm) { assert(elm == 2 && " '*=' operator does not worl correctly"); });

        a /= 2;
        for_each(a, [](auto elm) { assert(elm == 1 && " '/=' operator does not worl correctly"); });

        a -= 1;
        for_each(a, [](auto elm) { assert(elm == 0 && " '-=' operator does not worl correctly"); });
    }

    // element wise operation with matrix
    {
        MatrixBase<int, 4, 6> a(0.0),
                              b(2.0);

        a += b;
        for_each(a, [](auto elm) { assert(elm == 2 && " '+=' was not created correctly"); });

        a -= b;
        for_each(a, [](auto elm) { assert(elm == 0 && " '-=' was not created correctly"); });

        a = MatrixBase<int, 4, 6>(4);
        a /= b;
        for_each(a, [](auto elm) { assert(elm == 2 && " '/=' was not created correctly"); });
    }

    // test standard operator overloading between matrix and scalar
    {
        MatrixBase<int, 2, 3> b(0);

        b = b + 1;
        for_each(b, [](const auto& elm) { assert(elm == 1); });

        b = b * 2;
        for_each(b, [](const auto& elm) { assert(elm == 2); });

        b = b / 2;
        for_each(b, [](const auto& elm) { assert(elm == 1); });

        b = 2 * b;
        for_each(b, [](const auto& elm) { assert(elm == 2); });

        b = b - 1;
        for_each(b, [](const auto& elm) { assert(elm == 1); });

    }

    // test standard operator overloading between matrix's
    {
        MatrixBase<int, 3, 4> a(1),
                              b(2),
                              c(0);

        auto d = -a;
        for_each(d, [](const auto& elm) { assert(elm == -1); });

        c = a + b;
        for_each(c, [](const auto& elm) { assert(elm == 3); });

        c = b - a;
        for_each(c, [](const auto& elm) { assert(elm == 1); });

        a = MatrixBase<int, 3, 4>(4);
        c = a / b;
        for_each(c, [](const auto& elm) { assert(elm == 2); });

        c = MatrixBase<int, 3, 4>(4) / MatrixBase<int, 3, 4>(2);
        for_each(c, [](const auto& elm) { assert(elm == 2); });

        a = a / MatrixBase<int, 3, 4>(2);
        for_each(c, [](const auto& elm) { assert(elm == 2); });
    }

    // test matrix product
    {
        // cubic matrix multipication via compound operator
        MatrixBase<int, 2, 2> c(1, 2, 3, 4),
                              d(10, 20, 30, 40);
        c *= d;
        assert(c(0, 0) == 70);
        assert(c(0, 1) == 100);
        assert(c(1, 0) == 150);
        assert(c(1, 1) == 220);

        std::cout << "c = " << c << "\n";

        MatrixBase<int, 4, 4> _a(1, 1, 1, 1,
                                 1, 1, 1, 1,
                                 1, 1, 1, 1,
                                 1, 1, 1, 1),
                              _b(2, 3, 4, 5,
                                 6, 7, 8, 9,
                                 5, 4, 3, 1,
                                 9, 8, 7, 6);
        _a *= _b;
        auto _aeq = MatrixBase<int, 4, 4>(14, 14, 14, 14,
                                          30, 30, 30, 30,
                                          13, 13, 13, 13,
                                          30, 30, 30, 30);
        assert(_a == _aeq);
        std::cout << "_a = " << _a << "\n";

        // cubic matrix multiplication
        c = MatrixBase<int, 2, 2>(1, 2, 3, 4) * d;
        assert(c(0, 0) == 70);
        assert(c(0, 1) == 100);
        assert(c(1, 0) == 150);
        assert(c(1, 1) == 220);

        // 3x3 matrix multiplication
        MatrixBase<int, 3, 3> a3(1, 2, 3, 4, 5, 6, 7, 8, 9),
                              b3(2, 2, 2, 4, 4, 4, 6, 6, 6),
                              d3(0);
        d3 = a3 * b3;
        assert(d3(0, 0) == 24);
        assert(d3(0, 1) == 30);
        assert(d3(0, 2) == 36);

        assert(d3(1, 0) == 48);
        assert(d3(1, 1) == 60);
        assert(d3(1, 2) == 72);

        assert(d3(2, 0) == 72);
        assert(d3(2, 1) == 90);
        assert(d3(2, 2) == 108);

        // matrix * vector (right vector is treated as column vector)
        auto m22 = MatrixBase<int, 2, 2>(1, 2, 3, 4);
        auto v2 = VectorBase<int, 2>(10, 20);
        auto m22_v2 = m22 * v2;
        assert(m22_v2[0] == 70);
        assert(m22_v2[1] == 100);

        auto m33 = MatrixBase<int, 3, 3>(1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto v3 = VectorBase<int, 3>(10, 20, 30);
        auto m33_v3 = m33 * v3;
        assert(m33_v3[0] == 300);
        assert(m33_v3[1] == 360);
        assert(m33_v3[2] == 420);

        auto m44 = MatrixBase<int, 4, 4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        auto v4 = VectorBase<int, 4>(10, 20, 30, 40);
        auto m44_v4 = m44 * v4;
        assert(m44_v4[0] == 900);
        assert(m44_v4[1] == 1000);
        assert(m44_v4[2] == 1100);
        assert(m44_v4[3] == 1200);

        auto m55 = MatrixBase<int, 5, 5>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25);
        auto v5 = VectorBase<int, 5>(10, 20, 30, 40, 50);
        auto m55_v5 = m55 * v5;
        assert(m55_v5[0] == 2150);
        assert(m55_v5[1] == 2300);
        assert(m55_v5[2] == 2450);
        assert(m55_v5[3] == 2600);
        assert(m55_v5[4] == 2750);

        // vector * matrix (left vector is treated as row vector)
        auto v2_m22 = v2 * m22;
        assert(v2_m22[0] == 50);
        assert(v2_m22[1] == 110);

        auto v3_m33 = v3 * m33;
        assert(v3_m33[0] == 140);
        assert(v3_m33[1] == 320);
        assert(v3_m33[2] == 500);

        auto v4_m44 = v4 * m44;
        assert(v4_m44[0] == 300);
        assert(v4_m44[1] == 700);
        assert(v4_m44[2] == 1100);
        assert(v4_m44[3] == 1500);

        auto v5_m55 = v5 * m55;
        assert(v5_m55[0] == 550);
        assert(v5_m55[1] == 1300);
        assert(v5_m55[2] == 2050);
        assert(v5_m55[3] == 2800);
        assert(v5_m55[4] == 3550);

        // rectangular vector-matrix multiplication
        {
            MatrixBase<int, 2, 3> a23(1, 2, 3,
                4, 5, 6);
            VectorBase<int, 3> lv(1, 2, 3);
            VectorBase<int, 2> rv(1, 2);

            auto l = lv * a23;
            assert(l[0] == 14);
            assert(l[1] == 32);

            auto r = a23 * rv;
            assert(r[0] == 9);
            assert(r[1] == 12);
            assert(r[2] == 15);
        }

        // rectangular matrix multipliation
        auto lhs = MatrixBase<int, 3, 2>(1, 4,
                                         2, 5,
                                         3, 6);
        auto rhs = MatrixBase<int, 4, 3>(9, 5, 1,
                                         8, 4, 2,
                                         7, 3, 3,
                                         6, 2, 4);
        MatrixBase<int, 4, 2> rec = lhs * rhs;
        
        MatrixBase<int, 4, 2> receq(22, 67,
                                    22, 64,
                                    22, 61,
                                    22, 58);
        assert(rec == receq);

        // element wise multiplication
        MatrixBase<int, 3, 2> blhs = matrixMatrixMul(lhs, lhs);
        auto brhs = MatrixBase<int, 3, 2>(1, 16,
                                          4, 25,
                                          9, 36);
        assert(blhs == brhs);
    }

    // matrix relational operators
    {
        MatrixBase<int, 4, 2> i0(0, 1, 2, 3, 0, 1, 2, 3),
                              i1(1, 1, 1, 1, 1, 1, 1, 1),
                              i2(5, 5, 5, 5, 5, 5, 5, 5);
        bool a{ i0 > i1 },
             b(i1 < i2),
             c(i1 == 1),
             d(i1 == 3);
        assert(a == false);
        assert(b == true);
        assert(c == true);
        assert(d == false);

        MatrixBase<bool, 3, 2> f(0),
                               t(1);
        assert(any(f) == false);
        assert(any(MatrixBase<bool, 3, 2>(0,0,1, 0, 0, 0)) == true);
        assert(any(t) == true);

        assert(all(f) == false);
        assert(all(t) == true);

        f = Not(f);
        assert(all(f) == true);

        f = Not(MatrixBase<bool, 3, 2>(0));
        assert(all(f) == true);

        const MatrixBase<bool, 3, 2> fc(0);
        f = Not(fc);
        assert(all(f) == true);
    }

    // various matrix modifiers
    {
        MatrixBase<int, 2, 3> a(1, 2, 3, 4, 5, 6);

        // swap rows
        a = SwapRows(std::move(a), 0, 2);
        assert(a(0, 0) == 3);
        assert(a(1, 0) == 6);
        assert(a(0, 2) == 1);
        assert(a(1, 2) == 4);

        // swap columns
        a = VectorBase<int, 6>(1, 2, 3, 4, 5, 6);
        a = SwapColumns(std::move(a), 0, 1);
        ivec3 c0 = a[0];
        assert(c0.x == 4);
        assert(c0.y == 5);
        assert(c0.z == 6);
        c0 = a[1];
        assert(c0.x == 1);
        assert(c0.y == 2);
        assert(c0.z == 3);

        // set row
        SetRow(a, 0, ivec2(8, 9));
        assert(a(0, 0) == 8);
        assert(a(1, 0) == 9);

        // transpose a 2x2 matrix
        MatrixBase<int, 2, 2> b(Transpose(MatrixBase<int, 2, 2>(1, 2, 3, 4)));
        assert(b(0, 0) == 1);
        assert(b(0, 1) == 3);
        assert(b(1, 0) == 2);
        assert(b(1, 1) == 4);

        // transpose a 3x3 matrix
        MatrixBase<int, 3,3> cp(1, 2, 3, 4, 5, 6, 7, 8, 9),
                             c(Transpose(cp));
        VectorBase<int, 9> cT(1, 4, 7, 2, 5, 8, 3, 6, 9);
        assert(c.m_data == cT);

        // transpose a 4x4 matrix
        MatrixBase<int, 4,4> dp(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
                             d(Transpose(dp));
        VectorBase<int, 16> dT(1,5,9,13, 2,6,10,14, 3,7,11,15, 4,8,12,16);
        assert(d.m_data == dT);

        // transpose a 5x5 matrix
        MatrixBase<int, 5,5> ep(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25),
                             e(Transpose(ep));
        VectorBase<int, 25> eT(1,6,11,16,21, 2,7,12,17,22, 3,8,13,18,23, 4,9,14,19,24, 5,10,15,20,25);
        assert(e.m_data == eT);     
    }

    // unique matrix getters
    {
        MatrixBase<int, 4, 4> a(1,  2,  3,  4,      // column 0
                                5,  6,  7,  8,      // column 1
                                9,  10, 11, 12,     // column 2
                                13, 14, 15, 16);    // column 3

        // get diagonal
        VectorBase<int, 4> diag = GetDiagonal(a);
        assert(diag[0] == 1);
        assert(diag[1] == 6);
        assert(diag[2] == 11);
        assert(diag[3] == 16);

        // lower/upper triangular
        MatrixBase<int, 4, 4> lt = GetLowerTriangular(a),
                              eqlt(1, 2, 3, 4,
                                   0, 6, 7, 8,
                                   0, 0, 11, 12,
                                   0, 0, 0, 16),
                              ut = GetUpperTriangular(a),
                              equt(1,  0,  0,  0,
                                   5,  6,  0,  0,
                                   9,  10, 11, 0,
                                   13, 14, 15, 16);

        assert(lt == eqlt);
        assert(ut == equt);

        // get a block
        auto a22 = GetBlock<0, 1, 0, 2>(a);
        auto a22eq = MatrixBase<int, 2, 3>(1,  2,  3,
                                           5,  6,  7);
    }

    // test various "named constructors"
    {
        // create an outer product
        const VectorBase<int, 3> a(1, 2, 3),
                                 b(3, 2, 1);
        MatrixBase<int, 3, 3> opeq(3, 2, 1,
                                   6, 4, 2,
                                   9, 6, 3);
        auto op = OuterProduct(a, b);
        assert(op == opeq);

        // create a ven-der-monde matrix
        const VectorBase<float, 5> c(1.0f, 1.5f, 2.0f, 2.5f, 3.0f);
        auto vnm = VanDerMonde(c);
        auto vnmeq = MatrixBase<float, 5, 5>(1.0000f, 1.0000f, 1.0000f, 1.0000f, 1.0000f,
                                             5.0625f, 3.3750f, 2.2500f, 1.5000f, 1.0000f,
                                             16.0000f, 8.0000f, 4.0000f, 2.0000f, 1.0000f,
                                             39.0625f,   15.6250f, 6.2500f, 2.5000f, 1.0000f,
                                             81.0000f,  27.0000f, 9.0000f, 3.0000f, 1.0000f);
        for_each(vnm, [&, i = 0](const auto & elm) mutable {
            assert(std::abs(elm - vnmeq.m_data[i]) < 0.001f);
            ++i;
        });

        // create a givens rotation matrix
        MatrixBase<float, 3, 3> gv0( GivensRotation<float, 3>(0.25f, 0.75f, 0) ),
                                gvEq(0.25f, -0.75f, 0.0f,
                                     0.75f,  0.25f, 0.0f,
                                     0.0f,   0.0f,  1.0f);
        assert(gv0 == gvEq);

        // create a toeplitz matrix
        auto topl = Toeplitz(a);
        auto topleq = MatrixBase<int, 3, 3>(1, 2, 3,
                                            2, 1, 2,
                                            3, 2, 1);
        assert(topl == topleq);

        // create a rotation matrix
        Vector3<double> axis(1, 0, 0);
        double angle{ -30.0 },
              d2r{ 3.1415926535897932384626433832795 / 180.0f },
              sinAngle{ std::sin(angle * d2r) },
              cosAngle{ std::cos(angle * d2r) };
        auto rot = FromAxisAngle(axis, sinAngle, cosAngle);
        auto roteq = MatrixBase<double, 3, 3>(1.0, 0.0,               0.0,
                                             0.0, std::sqrt(3.0)/2.0, 0.5,
                                             0.0f, -0.5,              std::sqrt(3.0) / 2.0);
        for_each(rot, [&, i = 0](const auto & elm) mutable {
            assert(std::abs(elm - roteq.m_data[i]) < 0.00001);
            ++i;
        });

        axis = Normalize(Vector3<double>(1, 1, 1));
        sinAngle = std::sin(120 * d2r);
        cosAngle = std::cos(120 * d2r);
        rot = FromAxisAngle(axis, sinAngle, cosAngle);
        roteq = MatrixBase<double, 3, 3>(0, 0, 1,
                                         1, 0, 0,
                                         0, 1, 0);
        for_each(rot, [&, i = 0](const auto & elm) mutable {
            assert(std::abs(elm - roteq.m_data[i]) < 0.00001);
            ++i;
        });

        axis = Normalize(Vector3<double>(-0.305995, 0.6731891, 0.6731891));
        sinAngle = std::sin(74 * d2r);
        cosAngle = std::cos(74 * d2r);
        rot = FromAxisAngle(axis, sinAngle, cosAngle);
        roteq = MatrixBase<double, 3, 3>(0.3434616, -0.7963241, 0.4978976,
                                         0.4978976, 0.6039066, 0.6224105,
                                        -0.7963241, 0.0341279, 0.6039066);
        for_each(rot, [&, i = 0](const auto & elm) mutable {
            assert(std::abs(elm - roteq.m_data[i]) < 0.00001);
            ++i;
        });
    }
    
    // test matrix queries
    {
        // test if matrix is symmetrix
        MatrixBase<int, 4, 4> mat(1,  2,  3,  4,
                                  2,  5,  6,  7,
                                  3,  6,  8,  9,
                                  4,  7,  9, 10);
        bool temp = IsSymmetric(mat);  assert(temp == true);
        temp = IsSkewSymmetric(mat);   assert(temp == false);
        temp = IsUpperTriangular(mat); assert(temp == false);
        temp = IsLowerTriangular(mat); assert(temp == false);
        temp = IsDiagonal(mat);        assert(temp == false);
        temp = IsPermutation(mat);     assert(temp == false);
        
        // test if a matrix is skew symmetric
        mat = MatrixBase<int, 4, 4>( 1,   2,   3,  4,
                                    -2,   5,   6,  7,
                                    -3,  -6,   8,  9,
                                    -4,  -7,  -9, 10);
        temp = IsSymmetric(mat);       assert(temp == false);
        temp = IsSkewSymmetric(mat);   assert(temp == true);
        temp = IsUpperTriangular(mat); assert(temp == false);
        temp = IsLowerTriangular(mat); assert(temp == false);
        temp = IsDiagonal(mat);        assert(temp == false);
        temp = IsPermutation(mat);     assert(temp == false);

        // test if a matrix is upper triangular
        mat = MatrixBase<int, 4, 4>( 1,   2,   3,  4,
                                     0,   5,   6,  7,
                                     0,   0,   8,  9,
                                     0,   0,   0, 10);
        temp = IsSymmetric(mat);       assert(temp == false);
        temp = IsSkewSymmetric(mat);   assert(temp == false);
        temp = IsUpperTriangular(mat); assert(temp == false);
        temp = IsLowerTriangular(mat); assert(temp == true);
        temp = IsDiagonal(mat);        assert(temp == false);
        temp = IsPermutation(mat);     assert(temp == false);

        // test if a matrix is lower triangular
        mat = MatrixBase<int, 4, 4>( 1,   0,   0,  0,
                                    -2,   5,   0,  0,
                                    -3,  -6,   8,  0,
                                    -4,  -7,  -9, 10);
        temp = IsSymmetric(mat);       assert(temp == false);
        temp = IsSkewSymmetric(mat);   assert(temp == false);
        temp = IsUpperTriangular(mat); assert(temp == true);
        temp = IsLowerTriangular(mat); assert(temp == false);
        temp = IsDiagonal(mat);        assert(temp == false);
        temp = IsPermutation(mat);     assert(temp == false);

        // test if a matrix is diagonal
        mat = MatrixBase<int, 4, 4>( 1,  0,  0,  0,
                                     0,  5,  0,  0,
                                     0,  0,  8,  0,
                                     0,  0,  0, 10);
        temp = IsSymmetric(mat);       assert(temp == true);
        temp = IsSkewSymmetric(mat);   assert(temp == true);
        temp = IsUpperTriangular(mat); assert(temp == true);
        temp = IsLowerTriangular(mat); assert(temp == true);
        temp = IsDiagonal(mat);        assert(temp == true);
        temp = IsPermutation(mat);     assert(temp == false);

        // test if a matrix is permutation
        mat = MatrixBase<int, 4, 4>( 1,  0,  0,  0,
                                     0,  1,  0,  0,
                                     0,  0,  1,  0,
                                     0,  0,  0,  1);
        temp = IsSymmetric(mat);       assert(temp == true);
        temp = IsSkewSymmetric(mat);   assert(temp == true);
        temp = IsUpperTriangular(mat); assert(temp == true);
        temp = IsLowerTriangular(mat); assert(temp == true);
        temp = IsDiagonal(mat);        assert(temp == true);
        temp = IsPermutation(mat);     assert(temp == true);
    }

    // inversion, determinant & linear equation system solution
    {
        // deerminant
        MatrixBase<float, 2, 2> a2(2.4f, 1.5f, 
                                   3.3f, 8.3f);
        float d = Determinant(a2);
        assert(static_cast<int>(d * 100.0f) == 1497);

        MatrixBase<float, 3, 3> a3(2.4f, 1.5f, 7.3f,
                                   3.3f, 8.3f, 0.85f,
                                   1.2f, 18.2f, -0.5f);
        d = Determinant(a3);
        assert(static_cast<int>(d * 1000.0f) == 322647);

        MatrixBase<float, 4, 4> a4(2.4f, 1.5f, 7.3f, -2.2f, 
                                   3.3f, 8.3f, 0.85f, 0.123f,
                                   1.2f, 18.2f, -0.5f, 1.0f,
                                   0.95f, 3.8f, 12.2f, -13.2f);
        d = Determinant(a4);
        assert(static_cast<int>(d * 1000.0f) == -3091128);

        MatrixBase<double, 5, 5> a5{ 12, 13,  14, 15,  16,
                                     16, 15,  14, 13,  12,
                                     38, 75, -15,  5,  11,
                                     92, 32,  27,  5, -31,
                                     19,  8,  75,  5,  55 };
        d = static_cast<float>(Determinant(a5));
        assert(static_cast<int>(d) == 7182784);

        // inverse
        auto a2inv = Inv(a2);
        MatrixBase<float, 2, 2> _a2inv(0.554442167f, -0.100200385f,
                                       -0.220440850f, 0.160320625f);
        assert(a2inv == _a2inv);

        auto a3inv = Inv(a3);
        MatrixBase<float, 3, 3> _a3inv(-0.0608094931f, 0.414105862f, -0.183838680f,
                                       0.00827529747f, -0.0308696497f, 0.0683409348f,
                                       0.155278057f, -0.129801318f, 0.0463974625f);
        assert(a3inv == _a3inv);

        auto a4inv = Inv(a4);
        MatrixBase<float, 4, 4> _a4inv(-0.0609805435f,   0.414225608f,   -0.183898360f, 9.15613055e-05f,
                                       -0.000760031398f, -0.0245457366f, 0.0651917756f, 0.00483672041f,
                                        0.215953827f,    -0.172268867f,  0.0675454289f, -0.0324804634f,
                                        0.194986135f,    -0.136472702f,  0.0679605603f, -0.104378425f);
        assert(a4inv == _a4inv);

        // orthonormalization
        MatrixBase<float, 3, 3> or3(1, 1, 0,
                                    1, 0, 1,
                                    0, 1, 1),
                                or3eq( 0.707106769f,  0.707106769f, 0.0f,
                                       0.408248276f, -0.408248276f, 0.816496551f,
                                      -0.577350318f,  0.577350318f, 0.577350259f);
        or3 = Orthonormalize(std::move(or3));
        assert(or3 == or3eq);

        // numericaly problematic orthonormalization
        MatrixBase<float, 3, 3> or2(1.0f, 0.0001f, 0.0001f,
                                    1.0f, 0.0001f, 0.0f,
                                    1.0f, 0.0f,    0.0001f),
                                or2eq(1.0f,  0.0001f,  0.0001f,
                                      0.0f,  0.0f,    -1.0f,
                                      0.0f, -1.0f,     0.0f);
        or2 = Orthonormalize(std::move(or2));
        assert(or2 == or2eq);
    }

    // decompositions and various marix related properties
    {
        // LU decomposition
        MatrixBase<double, 5, 5> luDecomp(12, 16,  38,  92, 19,
                                          13, 15,  75,  32, 8,
                                          14, 14, -15,  27, 75,
                                          15, 13,  5,   5,  5,
                                          16, 12,  11, -31, 55),
                                 lu, l, u;
        VectorBase<std::size_t, 5> pivot;
        std::int32_t sign{};
        LU(luDecomp, lu, pivot, sign);
        u = GetUpperTriangular(lu);
        l = GetLowerTriangular(lu);
        SetDiagonal(l, VectorBase<double, 5>(1.0));
        std::cout << "l = " << l << '\n';
        std::cout << "u = " << u << '\n';

        MatrixBase<double, 5, 5> luEq(92, 0.41304347826086957, 0.20652173913043478, 0.13043478260869565, 0.17391304347826086,
                                      32, 61.782608695652172, 0.022519352568613652, 0.14285714285714285, 0.15270935960591134,
                                      27, -26.152173913043477, 70.012843068261787, 0.20302397519305043, 0.18993700261086111,
                                      5, 2.9347826086956523, 3.9013019000703730, 13.136513608390940, 0.83288951291338564,
                                      -31, 23.804347826086957, 60.866115411681911, 4.2855764374184933, -1.3739815579081935);
        assert(lu == luEq);

        const double det{ Determinant(luDecomp) };
        assert(static_cast<int32_t>(det) == 7182784);

        auto inv = Inv(luDecomp);

        MatrixBase<double, 5, 5> luIv( 0.51936157345118317,   -0.44798451408255979,    -0.52021458531956166,   -0.12163500948935607,   0.60618682115458022,
                                      -0.62477863736400541,    0.53137056606463218,     0.61949725900152086,    0.23743690468765236,  -0.72781180667551426,
                                       0.015429114950414696,  -0.00087319902700673557, -0.020336961267385940,  -0.018422940185866630,  0.024203985529844610,
                                       0.043979604565583343,  -0.032807334871826736,   -0.031945830474645900,  -0.013604752697561239,  0.034378313478450530,
                                       0.0069310172768664207, -0.0039293956215305575,   0.0022336742967629690, -0.020403230836399913,  0.015167934884301080);
        assert(inv == luIv);

        // QR decomposition (gram schmidt)
        MatrixBase<double, 3, 3> QR33( 1, 1, 0,
                                       1, 0, 1,
                                       0, 1, 1),
                                  q33, r33;
        QRgramSchmidt(QR33, q33, r33);
        MatrixBase<double, 3, 3> qeq1(0.70710678118654746, 0.70710678118654746, 0.0,
                                      0.40824829046386307, -0.40824829046386307, 0.81649658092772615,
                                     -0.57735026918962562, 0.57735026918962562, 0.57735026918962573),
                                 req1(1.4142135623730949, 0.0, 0.0,
                                     0.70710678118654746, 1.2247448713915892, 0.0,
                                     0.70710678118654746, 0.40824829046386307, 1.1547005383792515);
        assert(q33 == qeq1);
        assert(r33 == req1);

        QR33 = MatrixBase<double, 3, 3>( 12,  6,   -4,
                                        -51,  167,  24,
                                         4,  -68,  -41);
        QRgramSchmidt(QR33, q33, r33);
        qeq1 = MatrixBase<double, 3, 3>(0.85714285714285710, 0.42857142857142855, -0.28571428571428570,
                                        -0.39428571428571429, 0.90285714285714280, 0.17142857142857143,
                                        -0.33142857142857146, 0.034285714285714163, -0.94285714285714284);
        req1 = MatrixBase<double, 3, 3>(13.999999999999998, 0.0, 0.0,
                                        20.999999999999996, 175.00000000000000, 0.0,
                                        -14.000000000000002, -70, 35.000000000000007);
        assert(q33 == qeq1);
        assert(r33 == req1);

        // QR decomposition (givens rotation)
        QRgivensRotations(QR33, q33, r33);
        qeq1 = MatrixBase<double, 3, 3>(0.85714285714285710, 0.42857142857142855, -0.28571428571428570,
                                        -0.39428571428571418, 0.90285714285714269, 0.17142857142857143,
                                        0.33142857142857141, -0.034285714285714308, 0.94285714285714284);
        req1 = MatrixBase<double, 3, 3>(14.000000000000000, 0.0, 0.0,
                                        21.000000000000007, 175.00000000000000, 0.0,
                                        -13.999999999999998, -70.000000000000000, -35.000000000000000);
        assert(q33 == qeq1);
        assert(r33 == req1);

        // Cholesky decomposition
        MatrixBase<double, 3, 3> chol( 4,   12, -16,
                                       12,  37, -43,
                                      -16, -43,  98),
                                 Leq(2.0, 6.0, -8.0,
                                     0.0, 1.0, 5.0,
                                     0.0, 0.0, 3.0),
                                 L;
        L = Cholesky(chol);
        assert(IsLowerTriangular(L) == true);
        assert(L == Leq);

        chol = Cholesky(std::move(chol));
        assert(chol == Leq);
        assert(IsLowerTriangular(chol) == true);

        // cubic SVD decomposition
        MatrixBase<double, 5, 5> a5{ 12, 13,  14, 15,  16,
                                     16, 15,  14, 13,  12,
                                     38, 75, -15,  5,  11,
                                     92, 32,  27,  5, -31,
                                     19,  8,  75,  5,  55 };
        a5 = Transpose(std::move(a5));
        MatrixBase<double, 5, 5> us, vt,
                                 useq(0.18229853465503387, 0.20992662095084885, 0.49637277105567007, 0.72723543161737636, 0.38398015213496334,
                                     -0.15660197031540096, -0.11401858927868934, 0.33688318093285052, 0.30187944166868086, -0.87054816598198714,
                                     0.14813115102967003, 0.10884421310769705, 0.76631051400796457, -0.61413079831026030, 0.042680886298706915,
                                     0.71790956950762330, 0.58172755256335895, -0.22904670252885992, -0.030709914366584035, -0.30462011394239286,
                                     0.63632230768688747, -0.76985489994976775, 0.020726763871499226, 0.043562523164909911, 0.0094900789400977417),
                                 vteq(0.75787245205853571, 0.21829490795834378, -0.37064171322412692, 0.038188412092547599, 0.48902254055449662,
                                     0.53099654980053324, 0.26001313425455769, 0.67086194418490230, -0.16011133055992699, -0.41802445835840024, 
                                     0.35722066658113705, -0.70847137039728691, -0.34213636568057593, -0.12894032798377478, -0.48659923118829745, 
                                     0.10376639244278839, -0.053581231807533707, 0.074147668506347852, 0.97785277175635132, -0.15705943913337661, 
                                     0.072786960902687339, -0.61639100585582607, 0.53852929613596390, 0.0091845302567769103, 0.56979472429100220);
        VectorBase<double, 5> w,
                              weq(130.11405281021621, 
                                  93.133337251022610, 
                                  62.190020788480965, 
                                  15.860483827122826, 
                                  0.60093334524763165);
        bool flag = SVD(a5, us, w, vt);
        assert(flag == true);
        assert(w == weq);
        assert(vt == vteq);
        assert(us == useq);
    }

    // linear equation system solver
    {
        // solve a cubic linear system
        MatrixBase<double, 5, 5> luDecomp(12, 16,  38,  92, 19,
                                          13, 15,  75,  32, 8,
                                          14, 14, -15,  27, 75,
                                          15, 13,  5,   5,  5,
                                          16, 12,  11, -31, 55);
        VectorBase<double, 5> b( 1.0f, 2.0f, 3.0f, 4.0f, 5.0f),
                              x( SolveSquareLU(luDecomp, b) ),
                              xeq(-0.47333485177891804, 0.46126070337072450,
                                   0.54115409846655327, 0.14153481435610418,
                                  -0.56347190727160690);
        assert(x == xeq);

        // solve using cholsky
        MatrixBase<double, 3, 3> spd( 4,   12, -16,
                                      12,  37, -43,
                                     -16, -43,  98);
        VectorBase<double, 3> bc(6, 3, 1),
                              xc( SolveCubicCholesky(spd, bc) ),
                              xceq(257.61111111111114, -70.555555555555571, 11.111111111111112);
        assert(xc == xceq);

        // solve using QR
        xc = SolveQR(spd, bc);
        xceq = VectorBase<double, 3>(257.61111111110677, -70.555555555554392, 11.111111111110915);
        assert(xc == xceq);
    }

    // specialized 2X2 matrix operations
    {
        // eigen analysis
        MatrixBase<double, 2, 2> e( 16, 2,
                                   -1 , 12);
        double eig0, eig1;
        VectorBase<double, 2> eigvec0, eigvec1;
        EigenSolver2x2(e, eig0, eig1, eigvec0, eigvec1);
        assert(eig0 == 15.414213562373096);
        assert(eig1 == 12.585786437626904);
        assert(std::abs(eigvec0[0]) == 0.95968298226066739);
        assert(std::abs(eigvec0[1]) == 0.28108463771481990);
        assert(std::abs(eigvec1[0]) == 0.50544946512442346);
        assert(std::abs(eigvec1[1]) == 0.86285620946101682);

        EigenSolver2x2(MatrixBase<double, 2, 2>( 13, -12,
                                                -1 , 9), eig0, eig1, eigvec0, eigvec1);
        assert(eig0 == 15.0);
        assert(eig1 == 7.0);
        assert(std::abs(eigvec0[0]) == 0.98639392383214375); 
        assert(std::abs(eigvec0[1]) == 0.16439898730535729);
        assert(std::abs(eigvec1[0]) == 0.89442719099991586);
        assert(std::abs(eigvec1[1]) == 0.44721359549995793);

        // symmetric 2x2 matrix SVD decomposition
        mat2 svdsym(2.5f, 3.0f,
                    3.0f, 1.8f),
                    U;
        vec2 W;
        SVDsymmetric2x2(svdsym, U, W);
        assert(std::fabs(W.x) == 5.17034817f);
        assert(std::fabs(W.y) == 0.870347679f);
        assert(std::fabs(U(0, 0)) == 0.746954083f);
        assert(std::fabs(U(0, 1)) == 0.664875627f);
        assert(std::fabs(U(1, 0)) == 0.664875627f);
        assert(std::fabs(U(1, 1)) == 0.746954083f);
        
        // 2x2 polar decomposition
        mat2 R, S;
        PolarDecomposition2x2(svdsym, R, S);
        assert(svdsym == R * S);
    }

    // specialized 3X3 matrix operations
    {
        dmat3 a( 16.0, -2.0,   6.9,
                 -2.0,  12.0,  13.0,
                  6.9,  13.0, -24.0),
              eigvec;
        dvec3 eigs;
        EigenSolverSymmetric3x3(a, eigs, eigvec);

        assert(std::abs(eigs.x) == 29.340830775078608);
        assert(std::abs(eigs.y) == 17.185270241836061);
        assert(std::abs(eigs.z) == 16.155560533242546);
    }

    std::cout << "MatrixBase test successfully finished." << std::endl;
}


int main() {
    ScalarTest();
    VectorBaseTest();
    Vector2Test();
    Vector3Test();
    Vector4Test();
    MatrixBaseTest();

    return 1;
}

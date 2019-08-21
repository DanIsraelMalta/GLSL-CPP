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
* \brief 4 elements numerical vector
*
* @param {T, in} underlying type
**/
template<typename T> class Vector4 : public VectorBase<T, 4> {

    // data structure
    public:
        union {
            alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) std::array<T, 4> m_data{};
    
            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T x, y, z, w; };
            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T r, g, b, a; };
            struct alignas(std::aligned_storage<sizeof(T), alignof(T)>::type) { T s, t, p, q; };
    
            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> xx;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 1> xy;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 2> xz;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 3> xw;
            Swizzle<VectorBase<T, 2>, T, 2, true,  1, 0> yx;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> yy;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 2> yz;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 3> yw;
            Swizzle<VectorBase<T, 2>, T, 2, true,  2, 0> zx;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 1> zy;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 2> zz;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 3> zw;
            Swizzle<VectorBase<T, 2>, T, 2, true,  3, 0> wx;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 1> wy;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 2> wz;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 3> ww;
            
            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> rr;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 1> rg;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 2> rb;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 3> ra;
            Swizzle<VectorBase<T, 2>, T, 2, true,  1, 0> gr;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> gg;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 2> gb;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 3> ga;
            Swizzle<VectorBase<T, 2>, T, 2, true,  2, 0> br;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 1> bg;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 2> bb;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 3> ba;
            Swizzle<VectorBase<T, 2>, T, 2, true,  3, 0> ar;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 1> ag;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 2> ab;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 3> aa;
            
            Swizzle<VectorBase<T, 2>, T, 2, false, 0, 0> ss;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 1> st;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 2> sp;
            Swizzle<VectorBase<T, 2>, T, 2, true,  0, 3> sq;
            Swizzle<VectorBase<T, 2>, T, 2, true,  1, 0> ts;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 1> tt;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 2> tp;
            Swizzle<VectorBase<T, 2>, T, 2, false, 1, 3> tq;
            Swizzle<VectorBase<T, 2>, T, 2, true,  2, 0> ps;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 1> pt;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 2> pp;
            Swizzle<VectorBase<T, 2>, T, 2, false, 2, 3> pq;
            Swizzle<VectorBase<T, 2>, T, 2, true,  3, 0> qs;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 1> qt;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 2> qp;
            Swizzle<VectorBase<T, 2>, T, 2, false, 3, 3> qq;

            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 0> xxx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 1> xxy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 2> xxz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 3> xxw;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 0> xyx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 1> xyy;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 2> xyz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 3> xyw;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 0> xzx;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 1> xzy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 2> xzz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 3> xzw;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 0> yxx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 1> yxy;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 2> yxz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 3> yxw;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 0> yyx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 1> yyy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 2> yyz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 3> yyw;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 0> yzx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 1> yzy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 2> yzz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 3> yzw;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 0> zxx;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 1> zxy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 2> zxz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 3> zxw;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 0> zyx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 1> zyy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 2> zyz;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 3> zyw;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 0> zzx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 1> zzy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 2> zzz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 3> zzw;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 0, 1> wxy;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 0, 2> wxz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 0, 3> wxw;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 1, 0> wyx;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 1, 1> wyy;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 1, 2> wyz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 1, 3> wyw;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 2, 0> wzx;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 2, 1> wzy;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 2, 2> wzz;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 2, 3> wzw;

            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 0> rrr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 1> rrg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 2> rrb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 3> rra;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 0> rgr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 1> rgg;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 2> rgb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 3> rga;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 0> rbr;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 1> rbg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 2> rbb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 3> rba;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 0> grr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 1> grg;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 2> grb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 3> gra;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 0> ggr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 1> ggg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 2> ggb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 3> gga;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 0> gbr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 1> gbg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 2> gbb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 3> gba;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 0> brr;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 1> brg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 2> brb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 3> bra;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 0> bgr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 1> bgg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 2> bgb;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 3> bga;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 0> bbr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 1> bbg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 2> bbb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 3> bba;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 0, 1> arg;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 0, 2> arb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 0, 3> ara;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 1, 0> agr;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 1, 1> agg;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 1, 2> agb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 1, 3> aga;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 2, 0> abr;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 2, 1> abg;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 2, 2> abb;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 2, 3> aba;

            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 0> sss;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 1> sst;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 2> ssp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 0, 3> ssq;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 0> sts;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 1, 1> stt;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 2> stp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 1, 3> stq;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 0> sps;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 1> spt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 0, 2, 2> spp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 0, 2, 3> spq;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 0> tss;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 0, 1> tst;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 2> tsp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 0, 3> tsq;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 0> tts;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 1> ttt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 2> ttp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 1, 3> ttq;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 0> tps;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 1> tpt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 1, 2, 2> tpp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 1, 2, 3> tpq;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 0> pss;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 1> pst;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 0, 2> psp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 0, 3> psq;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 0> pts;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 1> ptt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 1, 2> ptp;
            Swizzle<VectorBase<T, 3>, T, 3, true, 2, 1, 3> ptq;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 0> pps;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 1> ppt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 2> ppp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 2, 2, 3> ppq;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 0, 1> qst;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 0, 2> qsp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 0, 3> qsq;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 1, 0> qts;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 1, 1> qtt;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 1, 2> qtp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 1, 3> qtq;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 2, 0> qps;
            Swizzle<VectorBase<T, 3>, T, 3, true, 3, 2, 1> qpt;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 2, 2> qpp;
            Swizzle<VectorBase<T, 3>, T, 3, false, 3, 2, 3> qpq;

            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 0> xxxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 1> xxxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 2> xxxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 3> xxxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 0> xxyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 1> xxyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 2> xxyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 3> xxyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 0> xxzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 1> xxzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 2> xxzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 3> xxzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 0> xxwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 1> xxwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 2> xxwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 3> xxww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 0> xyxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 1> xyxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 2> xyxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 3> xyxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 0> xyyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 1> xyyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 2> xyyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 3> xyyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 0> xyzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 1> xyzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 2> xyzz;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 1, 2, 3> xyzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 0> xywx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 1> xywy;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 1, 3, 2> xywz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 3> xyww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 0> xzxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 1> xzxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 2> xzxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 3> xzxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 0> xzyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 1> xzyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 2> xzyz;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 2, 1, 3> xzyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 0> xzzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 1> xzzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 2> xzzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 3> xzzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 0> xzwx;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 2, 3, 1> xzwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 2> xzwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 3> xzww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 0> xwxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 1> xwxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 2> xwxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 3> xwxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 0> xwyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 1> xwyy;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 3, 1, 2> xwyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 3> xwyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 0> xwzx;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 3, 2, 1> xwzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 2> xwzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 3> xwzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 0> xwwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 1> xwwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 2> xwwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 3> xwww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 0> yxxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 1> yxxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 2> yxxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 3> yxxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 0> yxyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 1> yxyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 2> yxyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 3> yxyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 0> yxzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 1> yxzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 2> yxzz;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 0, 2, 3> yxzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 0> yxwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 1> yxwy;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 0, 3, 2> yxwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 3> yxww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 0> yyxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 1> yyxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 2> yyxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 3> yyxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 0> yyyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 1> yyyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 2> yyyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 3> yyyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 0> yyzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 1> yyzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 2> yyzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 3> yyzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 0> yywx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 1> yywy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 2> yywz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 3> yyww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 0> yzxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 1> yzxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 2> yzxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 3> yzxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 0> yzyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 1> yzyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 2> yzyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 3> yzyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 0> yzzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 1> yzzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 2> yzzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 3> yzzw;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 2, 3, 0> yzwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 1> yzwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 2> yzwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 3> yzww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 0> ywxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 1> ywxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 2> ywxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 3> ywxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 0> ywyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 1> ywyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 2> ywyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 3> ywyw;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 3, 2, 0> ywzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 1> ywzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 2> ywzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 3> ywzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 0> ywwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 1> ywwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 2> ywwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 3> ywww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 0> zxxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 1> zxxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 2> zxxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 3> zxxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 0> zxyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 1> zxyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 2> zxyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 3> zxyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 0> zxzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 1> zxzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 2> zxzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 3> zxzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 0> zxwx;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 0, 3, 1> zxwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 2> zxwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 3> zxww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 0> zyxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 1> zyxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 2> zyxz;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 1, 0, 3> zyxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 0> zyyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 1> zyyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 2> zyyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 3> zyyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 0> zyzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 1> zyzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 2> zyzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 3> zyzw;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 1, 3, 0> zywx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 1> zywy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 2> zywz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 3> zyww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 0> zzxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 1> zzxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 2> zzxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 3> zzxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 0> zzyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 1> zzyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 2> zzyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 3> zzyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 0> zzzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 1> zzzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 2> zzzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 3> zzzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 0> zzwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 1> zzwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 2> zzwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 3> zzww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 0> zwxx;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 3, 0, 1> zwxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 2> zwxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 3> zwxw;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 3, 1, 0> zwyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 1> zwyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 2> zwyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 3> zwyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 0> zwzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 1> zwzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 2> zwzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 3> zwzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 0> zwwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 1> zwwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 2> zwwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 3> zwww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 0> wxxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 1> wxxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 2> wxxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 3> wxxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 0> wxyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 1> wxyy;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 0, 1, 2> wxyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 3> wxyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 0> wxzx;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 0, 2, 1> wxzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 2> wxzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 3> wxzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 0> wxwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 1> wxwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 2> wxwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 3> wxww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 0> wyxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 1> wyxy;
            Swizzle<VectorBase<T, 4>, T, 4, true,  3, 1, 0, 2> wyxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 3> wyxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 0> wyyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 1> wyyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 2> wyyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 3> wyyw;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 1, 2, 0> wyzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 1> wyzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 2> wyzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 3> wyzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 0> wywx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 1> wywy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 2> wywz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 3> wyww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 0> wzxx;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 2, 0, 1> wzxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 2> wzxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 3> wzxw;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 2, 1, 0> wzyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 1> wzyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 2> wzyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 3> wzyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 0> wzzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 1> wzzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 2> wzzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 3> wzzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 0> wzwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 1> wzwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 2> wzwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 3> wzww;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 0> wwxx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 1> wwxy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 2> wwxz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 3> wwxw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 0> wwyx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 1> wwyy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 2> wwyz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 3> wwyw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 0> wwzx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 1> wwzy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 2> wwzz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 3> wwzw;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 0> wwwx;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 1> wwwy;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 2> wwwz;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 3> wwww;

            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 0> rrrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 1> rrrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 2> rrrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 3> rrra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 0> rrgr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 1> rrgg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 2> rrgb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 3> rrga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 0> rrbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 1> rrbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 2> rrbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 3> rrba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 0> rrar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 1> rrag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 2> rrab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 3> rraa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 0> rgrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 1> rgrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 2> rgrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 3> rgra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 0> rggr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 1> rggg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 2> rggb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 3> rgga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 0> rgbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 1> rgbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 2> rgbb;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 1, 2, 3> rgba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 0> rgar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 1> rgag;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 1, 3, 2> rgab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 3> rgaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 0> rbrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 1> rbrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 2> rbrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 3> rbra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 0> rbgr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 1> rbgg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 2> rbgb;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 2, 1, 3> rbga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 0> rbbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 1> rbbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 2> rbbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 3> rbba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 0> rbar;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 2, 3, 1> rbag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 2> rbab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 3> rbaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 0> rarr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 1> rarg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 2> rarb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 3> rara;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 0> ragr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 1> ragg;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 3, 1, 2> ragb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 3> raga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 0> rabr;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 3, 2, 1> rabg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 2> rabb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 3> raba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 0> raar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 1> raag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 2> raab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 3> raaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 0> grrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 1> grrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 2> grrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 3> grra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 0> grgr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 1> grgg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 2> grgb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 3> grga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 0> grbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 1> grbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 2> grbb;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 0, 2, 3> grba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 0> grar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 1> grag;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 0, 3, 2> grab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 3> graa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 0> ggrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 1> ggrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 2> ggrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 3> ggra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 0> gggr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 1> gggg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 2> gggb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 3> ggga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 0> ggbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 1> ggbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 2> ggbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 3> ggba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 0> ggar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 1> ggag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 2> ggab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 3> ggaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 0> gbrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 1> gbrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 2> gbrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 3> gbra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 0> gbgr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 1> gbgg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 2> gbgb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 3> gbga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 0> gbbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 1> gbbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 2> gbbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 3> gbba;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 2, 3, 0> gbar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 1> gbag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 2> gbab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 3> gbaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 0> garr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 1> garg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 2> garb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 3> gara;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 0> gagr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 1> gagg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 2> gagb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 3> gaga;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 3, 2, 0> gabr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 1> gabg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 2> gabb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 3> gaba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 0> gaar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 1> gaag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 2> gaab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 3> gaaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 0> brrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 1> brrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 2> brrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 3> brra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 0> brgr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 1> brgg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 2> brgb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 3> brga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 0> brbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 1> brbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 2> brbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 3> brba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 0> brar;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 0, 3, 1> brag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 2> brab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 3> braa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 0> bgrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 1> bgrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 2> bgrb;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 1, 0, 3> bgra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 0> bggr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 1> bggg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 2> bggb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 3> bgga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 0> bgbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 1> bgbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 2> bgbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 3> bgba;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 1, 3, 0> bgar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 1> bgag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 2> bgab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 3> bgaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 0> bbrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 1> bbrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 2> bbrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 3> bbra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 0> bbgr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 1> bbgg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 2> bbgb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 3> bbga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 0> bbbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 1> bbbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 2> bbbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 3> bbba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 0> bbar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 1> bbag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 2> bbab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 3> bbaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 0> barr;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 3, 0, 1> barg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 2> barb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 3> bara;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 3, 1, 0> bagr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 1> bagg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 2> bagb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 3> baga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 0> babr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 1> babg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 2> babb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 3> baba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 0> baar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 1> baag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 2> baab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 3> baaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 0> arrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 1> arrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 2> arrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 3> arra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 0> argr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 1> argg;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 0, 1, 2> argb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 3> arga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 0> arbr;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 0, 2, 1> arbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 2> arbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 3> arba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 0> arar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 1> arag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 2> arab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 3> araa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 0> agrr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 1> agrg;
            Swizzle<VectorBase<T, 4>, T, 4, true,  3, 1, 0, 2> agrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 3> agra;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 0> aggr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 1> aggg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 2> aggb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 3> agga;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 1, 2, 0> agbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 1> agbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 2> agbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 3> agba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 0> agar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 1> agag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 2> agab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 3> agaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 0> abrr;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 2, 0, 1> abrg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 2> abrb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 3> abra;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 2, 1, 0> abgr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 1> abgg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 2> abgb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 3> abga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 0> abbr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 1> abbg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 2> abbb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 3> abba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 0> abar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 1> abag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 2> abab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 3> abaa;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 0> aarr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 1> aarg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 2> aarb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 3> aara;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 0> aagr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 1> aagg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 2> aagb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 3> aaga;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 0> aabr;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 1> aabg;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 2> aabb;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 3> aaba;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 0> aaar;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 1> aaag;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 2> aaab;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 3> aaaa;

            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 0> ssss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 1> ssst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 2> sssp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 0, 3> sssq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 0> ssts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 1> sstt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 2> sstp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 1, 3> sstq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 0> ssps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 1> sspt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 2> sspp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 2, 3> sspq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 0> ssqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 1> ssqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 2> ssqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 0, 3, 3> ssqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 0> stss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 1> stst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 2> stsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 0, 3> stsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 0> stts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 1> sttt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 2> sttp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 1, 3> sttq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 0> stps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 1> stpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 2, 2> stpp;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 1, 2, 3> stpq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 0> stqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 1> stqt;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 1, 3, 2> stqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 1, 3, 3> stqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 0> spss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 1> spst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 2> spsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 0, 3> spsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 0> spts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 1> sptt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 1, 2> sptp;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 2, 1, 3> sptq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 0> spps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 1> sppt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 2> sppp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 2, 3> sppq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 0> spqs;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 2, 3, 1> spqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 2> spqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 2, 3, 3> spqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 0> sqss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 1> sqst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 2> sqsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 0, 3> sqsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 0> sqts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 1> sqtt;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 3, 1, 2> sqtp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 1, 3> sqtq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 0> sqps;
            Swizzle<VectorBase<T, 4>, T, 4, true, 0, 3, 2, 1> sqpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 2> sqpp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 2, 3> sqpq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 0> sqqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 1> sqqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 2> sqqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 0, 3, 3, 3> sqqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 0> tsss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 1> tsst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 2> tssp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 0, 3> tssq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 0> tsts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 1> tstt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 2> tstp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 1, 3> tstq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 0> tsps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 1> tspt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 2, 2> tspp;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 0, 2, 3> tspq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 0> tsqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 1> tsqt;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 0, 3, 2> tsqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 0, 3, 3> tsqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 0> ttss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 1> ttst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 2> ttsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 0, 3> ttsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 0> ttts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 1> tttt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 2> tttp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 1, 3> tttq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 0> ttps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 1> ttpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 2> ttpp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 2, 3> ttpq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 0> ttqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 1> ttqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 2> ttqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 1, 3, 3> ttqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 0> tpss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 1> tpst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 2> tpsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 0, 3> tpsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 0> tpts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 1> tptt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 2> tptp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 1, 3> tptq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 0> tpps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 1> tppt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 2> tppp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 2, 3> tppq;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 2, 3, 0> tpqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 1> tpqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 2> tpqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 2, 3, 3> tpqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 0> tqss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 1> tqst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 2> tqsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 0, 3> tqsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 0> tqts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 1> tqtt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 2> tqtp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 1, 3> tqtq;
            Swizzle<VectorBase<T, 4>, T, 4, true, 1, 3, 2, 0> tqps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 1> tqpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 2> tqpp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 2, 3> tqpq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 0> tqqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 1> tqqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 2> tqqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 1, 3, 3, 3> tqqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 0> psss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 1> psst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 2> pssp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 0, 3> pssq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 0> psts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 1> pstt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 2> pstp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 1, 3> pstq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 0> psps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 1> pspt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 2> pspp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 2, 3> pspq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 0> psqs;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 0, 3, 1> psqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 2> psqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 0, 3, 3> psqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 0> ptss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 1> ptst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 0, 2> ptsp;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 1, 0, 3> ptsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 0> ptts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 1> pttt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 2> pttp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 1, 3> pttq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 0> ptps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 1> ptpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 2> ptpp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 2, 3> ptpq;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 1, 3, 0> ptqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 1> ptqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 2> ptqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 1, 3, 3> ptqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 0> ppss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 1> ppst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 2> ppsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 0, 3> ppsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 0> ppts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 1> pptt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 2> pptp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 1, 3> pptq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 0> ppps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 1> pppt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 2> pppp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 2, 3> pppq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 0> ppqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 1> ppqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 2> ppqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 2, 3, 3> ppqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 0> pqss;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 3, 0, 1> pqst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 2> pqsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 0, 3> pqsq;
            Swizzle<VectorBase<T, 4>, T, 4, true, 2, 3, 1, 0> pqts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 1> pqtt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 2> pqtp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 1, 3> pqtq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 0> pqps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 1> pqpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 2> pqpp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 2, 3> pqpq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 0> pqqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 1> pqqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 2> pqqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 2, 3, 3, 3> pqqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 0> qsss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 1> qsst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 2> qssp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 0, 3> qssq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 0> qsts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 1> qstt;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 0, 1, 2> qstp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 1, 3> qstq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 0> qsps;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 0, 2, 1> qspt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 2> qspp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 2, 3> qspq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 0> qsqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 1> qsqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 2> qsqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 0, 3, 3> qsqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 0> qtss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 1> qtst;
            Swizzle<VectorBase<T, 4>, T, 4, true,  3, 1, 0, 2> qtsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 0, 3> qtsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 0> qtts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 1> qttt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 2> qttp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 1, 3> qttq;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 1, 2, 0> qtps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 1> qtpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 2> qtpp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 2, 3> qtpq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 0> qtqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 1> qtqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 2> qtqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 1, 3, 3> qtqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 0> qpss;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 2, 0, 1> qpst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 2> qpsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 0, 3> qpsq;
            Swizzle<VectorBase<T, 4>, T, 4, true, 3, 2, 1, 0> qpts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 1> qptt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 2> qptp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 1, 3> qptq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 0> qpps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 1> qppt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 2> qppp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 2, 3> qppq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 0> qpqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 1> qpqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 2> qpqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 2, 3, 3> qpqq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 0> qqss;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 1> qqst;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 2> qqsp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 0, 3> qqsq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 0> qqts;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 1> qqtt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 2> qqtp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 1, 3> qqtq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 0> qqps;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 1> qqpt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 2> qqpp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 2, 3> qqpq;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 0> qqqs;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 1> qqqt;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 2> qqqp;
            Swizzle<VectorBase<T, 4>, T, 4, false, 3, 3, 3, 3> qqqq;
        };

    // internal helper
    private:

        // get parent properties
        void CopyParentData() noexcept {
            std::copy(VectorBase<T, 4>::m_data.begin(), VectorBase<T, 4>::m_data.end(), Vector4::m_data.begin());
        }

        // fill Vector2 from VectorBase
        void FromVectorBase(VectorBase<T, 4>&& xi_base) noexcept {
            m_data = std::move(xi_base.m_data);
        }

    // query operations
    public:

        // extract vector size
        constexpr std::size_t length() const noexcept { return 4; }

    // constructors
    public:

        // default constructor
		Vector4() : m_data() {}
    
        // construct using 1 value
        template<typename U> explicit constexpr Vector4(const U xi_value = U{}, REQUIRE(is_ArithmeticConvertible_v<U, T>)) : VectorBase<T, 4>(xi_value) { CopyParentData(); }
    
        // construct using 4 values (of same type)
        template<typename ...Us, REQUIRE((sizeof...(Us) == 4) && Are_ArithmeticConvertible<T, Us...>::value)> explicit constexpr Vector4(Us... xi_values) : VectorBase<T, 4>(xi_values...) { CopyParentData(); }
    
        // construct using 4 values (of different type)
        template<typename U, typename V, typename W, typename R> explicit constexpr Vector4(const U u, const V v, const W w, const R r,
                 REQUIRE(Are_ArithmeticConvertible<T, U, V, W, R>::value)) :
        VectorBase<T, 4>(static_cast<T>(u), static_cast<T>(v), static_cast<T>(w), static_cast<T>(r)) { CopyParentData(); }
    
        // construct using any combination of VectorBase<U,2> child and scalar/VectorBase<U,2>/swizzle
        template<typename U, typename V, typename W> explicit constexpr Vector4(const VectorBase<U, 2>& vec, const V v, const W w,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value)) :
        VectorBase<T, 4>(static_cast<T>(vec[0]), static_cast<T>(vec[1]), static_cast<T>(v), static_cast<T>(w)) { CopyParentData(); }
    
        template<typename U, typename V, typename W> explicit constexpr Vector4(VectorBase<U, 2>&& vec, const V v, const W w,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value)) :
        VectorBase<T, 4>(static_cast<T>(std::move(vec[0])), static_cast<T>(std::move(vec[1])), static_cast<T>(v), static_cast<T>(w)) { CopyParentData(); }

        template<typename U, typename V, typename W> explicit constexpr Vector4(const V v, const VectorBase<U, 2>& vec, const W w,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value)) :
        VectorBase<T, 4>(static_cast<T>(v), static_cast<T>(vec[0]), static_cast<T>(vec[1]), static_cast<T>(w)) { CopyParentData(); }

        template<typename U, typename V, typename W> explicit constexpr Vector4(const V v, VectorBase<U, 2>&& vec, const W w,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value)) :
        VectorBase<T, 4>(static_cast<T>(v), static_cast<T>(std::move(vec[0])), static_cast<T>(std::move(vec[1])), static_cast<T>(w)) { CopyParentData(); }

        template<typename U, typename V, typename W> explicit constexpr Vector4(const V v, const W w, const VectorBase<U, 2>& vec,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value)) :
        VectorBase<T, 4>(static_cast<T>(v), static_cast<T>(w), static_cast<T>(vec[0]), static_cast<T>(vec[1])) { CopyParentData(); }

        template<typename U, typename V, typename W> explicit constexpr Vector4(const V v, const W w, VectorBase<U, 2>&& vec,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value)) :
        VectorBase<T, 4>(static_cast<T>(v), static_cast<T>(w), static_cast<T>(std::move(vec[0])), static_cast<T>(std::move(vec[1]))) { CopyParentData(); }

        // construct using a combination of VectorBase<U,2>/VectorBase<U,2>
        template<typename U, typename V> explicit constexpr Vector4(const VectorBase<U, 2>& vec0, const VectorBase<V, 2>& vec1) :
        VectorBase<T, 4>(static_cast<T>(vec0[0]), static_cast<T>(vec0[1]), static_cast<T>(vec1[0]), static_cast<T>(vec1[1])) { CopyParentData(); }

        template<typename U, typename V> explicit constexpr Vector4(VectorBase<U, 2>&& vec0, const VectorBase<V, 2>& vec1) :
        VectorBase<T, 4>(static_cast<T>(std::move(vec0[0])), static_cast<T>(std::move(vec0[1])), static_cast<T>(vec1[0]), static_cast<T>(vec1[1])) { CopyParentData(); }

        template<typename U, typename V> explicit constexpr Vector4(const VectorBase<U, 2>& vec0, VectorBase<V, 2>&& vec1) :
        VectorBase<T, 4>(static_cast<T>(vec0[0]), static_cast<T>(vec0[1]), static_cast<T>(std::move(vec1[0])), static_cast<T>(std::move(vec1[1]))) { CopyParentData(); }

        template<typename U, typename V> explicit constexpr Vector4(VectorBase<U, 2>&& vec0, VectorBase<V, 2>&& vec1) :
        VectorBase<T, 4>(static_cast<T>(std::move(vec0[0])), static_cast<T>(std::move(vec0[1])), static_cast<T>(std::move(vec1[0])), static_cast<T>(std::move(vec1[1]))) { CopyParentData(); }

        // construct using any combination of VectorBase<U,3> child and scalar
        template<typename U, typename V> explicit constexpr Vector4(const VectorBase<U, 3>& vec, const V s, REQUIRE(is_ArithmeticConvertible_v<V, T>)) :
        VectorBase<T, 4>(static_cast<T>(vec[0]), static_cast<T>(vec[1]), static_cast<T>(vec[2]), static_cast<T>(s)) { CopyParentData(); }

        template<typename U, typename V> explicit constexpr Vector4(VectorBase<U, 3>&& vec, const V s, REQUIRE(is_ArithmeticConvertible_v<V, T>)) :
        VectorBase<T, 4>(static_cast<T>(std::move(vec[0])), static_cast<T>(std::move(vec[1])), static_cast<T>(std::move(vec[2])), static_cast<T>(s)) { CopyParentData(); }

        template<typename U, typename V> explicit constexpr Vector4(const V s, const VectorBase<U, 3>& vec, REQUIRE(is_ArithmeticConvertible_v<V, T>)) :
        VectorBase<T, 4>(static_cast<T>(s), static_cast<T>(vec[0]), static_cast<T>(vec[1]), static_cast<T>(vec[2])) { CopyParentData(); }

        template<typename U, typename V> explicit constexpr Vector4(const V s, VectorBase<U, 3>&& vec, REQUIRE(is_ArithmeticConvertible_v<V, T>)) :
        VectorBase<T, 4>(static_cast<T>(s), static_cast<T>(std::move(vec[0])), static_cast<T>(std::move(vec[1])), static_cast<T>(std::move(vec[2]))) { CopyParentData(); }

        // construct using a combination of VectorBase<U,2>/swizzle
        template<typename U, typename V> explicit constexpr Vector4(const VectorBase<V, 2>& vec, U& swiz, REQUIRE(is_SwizzleOfLength_v<U, 2>)) :
        Vector4<T>(vec, VectorBase<T, 2>(swiz)) {}

        template<typename U, typename V> explicit constexpr Vector4(VectorBase<V, 2>&& vec, U& swiz, REQUIRE(is_SwizzleOfLength_v<U, 2>)) :
        Vector4<T>(std::move(vec), VectorBase<T, 2>(swiz)) {}

        template<typename U, typename V> explicit constexpr Vector4(U& swiz, const VectorBase<V, 2>& vec, REQUIRE(is_SwizzleOfLength_v<U, 2>)) :
        Vector4<T>(VectorBase<T, 2>(swiz), vec) {}

        template<typename U, typename V> explicit constexpr Vector4(U& swiz, VectorBase<V, 2>&& vec,
                 REQUIRE(is_SwizzleOfLength_v<U, 2>)) : Vector4<T>(VectorBase<T, 2>(swiz), std::move(vec)) {}

        // construct using a combination of swizzle/scalar      
        template<typename U, typename V> explicit constexpr Vector4(U& swiz, const V scalar,
                 REQUIRE(is_ArithmeticConvertible_v<V, T> && is_SwizzleOfLength_v<U, 3>)) : Vector4<T>(VectorBase<T, 3>(swiz), scalar) {}

        template<typename U, typename V> explicit constexpr Vector4(const V scalar, U& swiz,
                 REQUIRE(is_ArithmeticConvertible_v<V, T> && is_SwizzleOfLength_v<U, 3>)) : Vector4<T>(scalar, VectorBase<T, 3>(swiz)) {}

        template<typename U, typename V, typename W> explicit constexpr Vector4(U& swiz, const V v, const W w,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value && is_SwizzleOfLength_v<U, 2>)) : Vector4<T>(VectorBase<T, 2>(swiz), v, w) {}

        template<typename U, typename V, typename W> explicit constexpr Vector4(const V v, U& swiz, const W w,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value && is_SwizzleOfLength_v<U, 2>)) : Vector4<T>(v, VectorBase<T, 2>(swiz), w) {}

        template<typename U, typename V, typename W> explicit constexpr Vector4(const V v, const W w, U& swiz,
                 REQUIRE(Are_ArithmeticConvertible<T, V, W>::value && is_SwizzleOfLength_v<U, 2>)) : Vector4<T>(v, w, VectorBase<T, 2>(swiz)) {}
    
        // construct from a swizzle
        template<typename U> explicit constexpr Vector4(U& s, REQUIRE(is_SwizzleOfLength_v<U, 4>)) : VectorBase<T, 4>(s) { CopyParentData(); }
    
        // cast
        operator VectorBase<T, 4>() const {
            return VectorBase<T, 4>(m_data);
        }
        
    // assignments
    public:

        // assignment from another VectorBase child
        template<typename U, std::size_t M, REQUIRE(M >= 4)> constexpr Vector4& operator=(VectorBase<U, M>&& v) noexcept {
            for_each(m_data, [this, i = 0, temp = FWD(v)](auto& elm) mutable {
                elm = static_cast<T>(temp[i]);
                ++i;
            });

            return *this;
        }

    // access operator overloading
    public:

        // '[]' element access
        constexpr T  operator[](const std::size_t i) const { assert(i < 4); return m_data[i]; }
        constexpr T& operator[](const std::size_t i)       { assert(i < 4); return m_data[i]; }

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

    // compound operator overloading
    public:

#define M_OPERATOR(OP)                                                                                  \
        template<typename U, REQUIRE(is_ArithmeticConvertible_v<U, T>)>                                 \
        constexpr Vector4& operator OP (const U xi_value) {                                             \
            FromVectorBase(std::move(VectorBase<T,4>(*this) OP xi_value));                              \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector4& operator OP (Vector4<U>&& xi_vector) {                  \
            FromVectorBase(std::move(VectorBase<T,4>(*this) OP std::move(xi_vector)));                  \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U> constexpr Vector4& operator OP (const VectorBase<U, 4>& xi_vector) {       \
            auto _vec = FWD(static_cast<VectorBase<U, 4>>(xi_vector));                                  \
            FromVectorBase(std::move(VectorBase<T,4>(*this) OP _vec));                                  \
            return *this;                                                                               \
        }                                                                                               \
        template<typename U, REQUIRE(is_SwizzleOfLength_v<U, 4>)>                                       \
        constexpr Vector4& operator OP (U& s) {                                                         \
            FromVectorBase(std::move(VectorBase<T,4>(*this) OP s));                                     \
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
template<typename T> constexpr inline Vector4<T> operator - (const Vector4<T>& xi_vec) {
    auto v = FWD(xi_vec);
    v *= static_cast<T>(-1.0);
    return FWD(v);
}

template<typename T> constexpr inline Vector4<T> operator - (const VectorBase<T, 4>& xi_vec) {
    auto v = FWD(xi_vec);
    v *= static_cast<T>(-1.0);
    return Vector4<T>(v);
}

template<typename T, typename U, REQUIRE(is_SwizzleOfLength_v<U, 4>)>
constexpr inline Vector4<T> operator - (U& s) {
    Vector4<T> xo_vec(s);
    xo_vec = -xo_vec;
    return xo_vec;
}

}; // namespace GLSLCPP

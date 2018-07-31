// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#include "opencv2/core/hal/intrin.hpp"

#define DEF_ACC_INT_FUNCS(suffix, type, acctype) \
void acc_##suffix(const type* src, acctype* dst, \
                         const uchar* mask, int len, int cn) \
{ \
    CV_CPU_CALL_NEON(acc_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_SSE2(acc_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_VSX(acc_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_BASELINE(acc_general_, (src, dst, mask, len, cn)); \
} \
void accSqr_##suffix(const type* src, acctype* dst, \
                            const uchar* mask, int len, int cn) \
{ \
    CV_CPU_CALL_NEON(accSqr_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_SSE2(accSqr_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_VSX(accSqr_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_BASELINE(accSqr_general_, (src, dst, mask, len, cn)); \
} \
void accProd_##suffix(const type* src1, const type* src2, \
                             acctype* dst, const uchar* mask, int len, int cn) \
{ \
    CV_CPU_CALL_NEON(accProd_simd_, (src1, src2, dst, mask, len, cn)); \
    CV_CPU_CALL_SSE2(accProd_simd_, (src1, src2, dst, mask, len, cn)); \
    CV_CPU_CALL_VSX(accProd_simd_, (src1, src2, dst, mask, len, cn)); \
    CV_CPU_CALL_BASELINE(accProd_general_, (src1, src2, dst, mask, len, cn)); \
} \
void accW_##suffix(const type* src, acctype* dst, \
                          const uchar* mask, int len, int cn, double alpha) \
{ \
    CV_CPU_CALL_NEON(accW_simd_, (src, dst, mask, len, cn, alpha)); \
    CV_CPU_CALL_SSE2(accW_simd_, (src, dst, mask, len, cn, alpha)); \
    CV_CPU_CALL_VSX(accW_simd_, (src, dst, mask, len, cn, alpha)); \
    CV_CPU_CALL_BASELINE(accW_general_, (src, dst, mask, len, cn, alpha)); \
}
#define DEF_ACC_FLT_FUNCS(suffix, type, acctype) \
void acc_##suffix(const type* src, acctype* dst, \
                         const uchar* mask, int len, int cn) \
{ \
    CV_CPU_CALL_AVX(acc_avx_##suffix, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_NEON(acc_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_SSE2(acc_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_VSX(acc_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_BASELINE(acc_general_, (src, dst, mask, len, cn)); \
} \
void accSqr_##suffix(const type* src, acctype* dst, \
                            const uchar* mask, int len, int cn) \
{ \
    CV_CPU_CALL_AVX(accSqr_avx_##suffix, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_NEON(accSqr_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_SSE2(accSqr_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_VSX(accSqr_simd_, (src, dst, mask, len, cn)); \
    CV_CPU_CALL_BASELINE(accSqr_general_, (src, dst, mask, len, cn)); \
} \
void accProd_##suffix(const type* src1, const type* src2, \
                             acctype* dst, const uchar* mask, int len, int cn) \
{ \
    CV_CPU_CALL_AVX(accProd_avx_##suffix, (src1, src2, dst, mask, len, cn)); \
    CV_CPU_CALL_NEON(accProd_simd_, (src1, src2, dst, mask, len, cn)); \
    CV_CPU_CALL_SSE2(accProd_simd_, (src1, src2, dst, mask, len, cn)); \
    CV_CPU_CALL_VSX(accProd_simd_, (src1, src2, dst, mask, len, cn)); \
    CV_CPU_CALL_BASELINE(accProd_general_, (src1, src2, dst, mask, len, cn)); \
} \
void accW_##suffix(const type* src, acctype* dst, \
                          const uchar* mask, int len, int cn, double alpha) \
{ \
    CV_CPU_CALL_AVX(accW_avx_##suffix, (src, dst, mask, len, cn, alpha)); \
    CV_CPU_CALL_NEON(accW_simd_, (src, dst, mask, len, cn, alpha)); \
    CV_CPU_CALL_SSE2(accW_simd_, (src, dst, mask, len, cn, alpha)); \
    CV_CPU_CALL_VSX(accW_simd_, (src, dst, mask, len, cn, alpha)); \
    CV_CPU_CALL_BASELINE(accW_general_, (src, dst, mask, len, cn, alpha)); \
}
#define DECLARATE_ACC_FUNCS(suffix, type, acctype) \
void acc_##suffix(const type* src, acctype* dst, const uchar* mask, int len, int cn); \
void accSqr_##suffix(const type* src, acctype* dst, const uchar* mask, int len, int cn); \
void accProd_##suffix(const type* src1, const type* src2, acctype* dst, const uchar* mask, int len, int cn); \
void accW_##suffix(const type* src, acctype* dst, const uchar* mask, int len, int cn, double alpha);


namespace cv {

DECLARATE_ACC_FUNCS(8u32f, uchar, float)
DECLARATE_ACC_FUNCS(8u64f, uchar, double)
DECLARATE_ACC_FUNCS(16u32f, ushort, float)
DECLARATE_ACC_FUNCS(16u64f, ushort, double)
DECLARATE_ACC_FUNCS(32f, float, float)
DECLARATE_ACC_FUNCS(32f64f, float, double)
DECLARATE_ACC_FUNCS(64f, double, double)

CV_CPU_OPTIMIZATION_NAMESPACE_BEGIN

void acc_simd_(const uchar* src, float* dst, const uchar* mask, int len, int cn);
void acc_simd_(const ushort* src, float* dst, const uchar* mask, int len, int cn);
void acc_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn);
void acc_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn);
void acc_simd_(const float* src, float* dst, const uchar* mask, int len, int cn);
void acc_simd_(const float* src, double* dst, const uchar* mask, int len, int cn);
void acc_simd_(const double* src, double* dst, const uchar* mask, int len, int cn);
void accSqr_simd_(const uchar* src, float* dst, const uchar* mask, int len, int cn);
void accSqr_simd_(const ushort* src, float* dst, const uchar* mask, int len, int cn);
void accSqr_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn);
void accSqr_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn);
void accSqr_simd_(const float* src, float* dst, const uchar* mask, int len, int cn);
void accSqr_simd_(const float* src, double* dst, const uchar* mask, int len, int cn);
void accSqr_simd_(const double* src, double* dst, const uchar* mask, int len, int cn);
void accProd_simd_(const uchar* src1, const uchar* src2, float* dst, const uchar* mask, int len, int cn);
void accProd_simd_(const ushort* src1, const ushort* src2, float* dst, const uchar* mask, int len, int cn);
void accProd_simd_(const uchar* src1, const uchar* src2, double* dst, const uchar* mask, int len, int cn);
void accProd_simd_(const ushort* src1, const ushort* src2, double* dst, const uchar* mask, int len, int cn);
void accProd_simd_(const float* src1, const float* src2, float* dst, const uchar* mask, int len, int cn);
void accProd_simd_(const float* src1, const float* src2, double* dst, const uchar* mask, int len, int cn);
void accProd_simd_(const double* src1, const double* src2, double* dst, const uchar* mask, int len, int cn);
void accW_simd_(const uchar* src, float* dst, const uchar* mask, int len, int cn, double alpha);
void accW_simd_(const ushort* src, float* dst, const uchar* mask, int len, int cn, double alpha);
void accW_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn, double alpha);
void accW_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn, double alpha);
void accW_simd_(const float* src, float* dst, const uchar* mask, int len, int cn, double alpha);
void accW_simd_(const float* src, double* dst, const uchar* mask, int len, int cn, double alpha);
void accW_simd_(const double* src, double* dst, const uchar* mask, int len, int cn, double alpha);

// accumulate series optimized by AVX
void acc_avx_32f(const float* src, float* dst, const uchar* mask, int len, int cn);
void acc_avx_32f64f(const float* src, double* dst, const uchar* mask, int len, int cn);
void acc_avx_64f(const double* src, double* dst, const uchar* mask, int len, int cn);
void accSqr_avx_32f(const float* src, float* dst, const uchar* mask, int len, int cn);
void accSqr_avx_32f64f(const float* src, double* dst, const uchar* mask, int len, int cn);
void accSqr_avx_64f(const double* src, double* dst, const uchar* mask, int len, int cn);
void accProd_avx_32f(const float* src1, const float* src2, float* dst, const uchar* mask, int len, int cn);
void accProd_avx_32f64f(const float* src1, const float* src2, double* dst, const uchar* mask, int len, int cn);
void accProd_avx_64f(const double* src1, const double* src2, double* dst, const uchar* mask, int len, int cn);
void accW_avx_32f(const float* src, float* dst, const uchar* mask, int len, int cn, double alpha);
void accW_avx_32f64f(const float* src, double* dst, const uchar* mask, int len, int cn, double alpha);
void accW_avx_64f(const double* src, double* dst, const uchar* mask, int len, int cn, double alpha);

#ifndef CV_CPU_OPTIMIZATION_DECLARATIONS_ONLY

template <typename T, typename AT>
void acc_general_(const T* src, AT* dst, const uchar* mask, int len, int cn, int start = 0 )
{
    int i = start;

    if( !mask )
    {
        len *= cn;
        #if CV_ENABLE_UNROLLED
        for( ; i <= len - 4; i += 4 )
        {
            AT t0, t1;
            t0 = src[i] + dst[i];
            t1 = src[i+1] + dst[i+1];
            dst[i] = t0; dst[i+1] = t1;

            t0 = src[i+2] + dst[i+2];
            t1 = src[i+3] + dst[i+3];
            dst[i+2] = t0; dst[i+3] = t1;
        }
        #endif
        for( ; i < len; i++ )
        {
            dst[i] += src[i];
        }
    }
    else
    {
        src += (i * cn);
        dst += (i * cn);
        for( ; i < len; i++, src += cn, dst += cn )
        {
            if( mask[i] )
            {
                for( int k = 0; k < cn; k++ )
                {
                    dst[k] += src[k];
                }
            }
        }
    }

}

template<typename T, typename AT> void
accSqr_general_( const T* src, AT* dst, const uchar* mask, int len, int cn, int start = 0 )
{
    int i = start;

    if( !mask )
    {
        len *= cn;
        #if CV_ENABLE_UNROLLED
        for( ; i <= len - 4; i += 4 )
        {
            AT t0, t1;
            t0 = (AT)src[i]*src[i] + dst[i];
            t1 = (AT)src[i+1]*src[i+1] + dst[i+1];
            dst[i] = t0; dst[i+1] = t1;

            t0 = (AT)src[i+2]*src[i+2] + dst[i+2];
            t1 = (AT)src[i+3]*src[i+3] + dst[i+3];
            dst[i+2] = t0; dst[i+3] = t1;
        }
        #endif
        for( ; i < len; i++ )
        {
            dst[i] += (AT)src[i]*src[i];
        }
    }
    else
    {
        src += (i * cn);
        dst += (i * cn);
        for( ; i < len; i++, src += cn, dst += cn )
        {
            if( mask[i] )
            {
                for( int k = 0; k < cn; k++ )
                {
                    dst[k] += (AT)src[k]*src[k];
                }
            }
        }
    }
}

template<typename T, typename AT> void
accProd_general_( const T* src1, const T* src2, AT* dst, const uchar* mask, int len, int cn, int start = 0 )
{
    int i = start;

    if( !mask )
    {
        len *= cn;
        #if CV_ENABLE_UNROLLED
        for( ; i <= len - 4; i += 4 )
        {
            AT t0, t1;
            t0 = (AT)src1[i]*src2[i] + dst[i];
            t1 = (AT)src1[i+1]*src2[i+1] + dst[i+1];
            dst[i] = t0; dst[i+1] = t1;

            t0 = (AT)src1[i+2]*src2[i+2] + dst[i+2];
            t1 = (AT)src1[i+3]*src2[i+3] + dst[i+3];
            dst[i+2] = t0; dst[i+3] = t1;
        }
        #endif
        for( ; i < len; i++ )
        {
            dst[i] += (AT)src1[i]*src2[i];
        }
    }
    else
    {
        src1 += (i * cn);
        src2 += (i * cn);
        dst += (i * cn);
        for( ; i < len; i++, src1 += cn, src2 += cn, dst += cn )
        {
            if( mask[i] )
            {
                for( int k = 0; k < cn; k++ )
                {
                    dst[k] += (AT)src1[k]*src2[k];
                }
            }
        }
    }
}

template<typename T, typename AT> void
accW_general_( const T* src, AT* dst, const uchar* mask, int len, int cn, double alpha, int start = 0 )
{
    AT a = (AT)alpha, b = 1 - a;
    int i = start;

    if( !mask )
    {
        len *= cn;
        #if CV_ENABLE_UNROLLED
        for( ; i <= len - 4; i += 4 )
        {
            AT t0, t1;
            t0 = src[i]*a + dst[i]*b;
            t1 = src[i+1]*a + dst[i+1]*b;
            dst[i] = t0; dst[i+1] = t1;

            t0 = src[i+2]*a + dst[i+2]*b;
            t1 = src[i+3]*a + dst[i+3]*b;
            dst[i+2] = t0; dst[i+3] = t1;
        }
        #endif
        for( ; i < len; i++ )
        {
            dst[i] = src[i]*a + dst[i]*b;
        }
    }
    else
    {
        src += (i * cn);
        dst += (i * cn);
        for( ; i < len; i++, src += cn, dst += cn )
        {
            if( mask[i] )
            {
                for( int k = 0; k < cn; k++ )
                {
                    dst[k] = src[k]*a + dst[k]*b;
                }
            }
        }
    }
}

#if CV_SIMD128

#if CV_VSX
#pragma GCC push_options
#pragma GCC target("cpu=power8")
#pragma GCC target("tune=power8")
#endif

void acc_simd_(const uchar* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 16;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint8x16 v_src  = v_load(src + x);
            v_uint16x8 v_src0, v_src1;
            v_expand(v_src, v_src0, v_src1);

            v_uint32x4 v_src00, v_src01, v_src10, v_src11;
            v_expand(v_src0, v_src00, v_src01);
            v_expand(v_src1, v_src10, v_src11);

            v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src00)));
            v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src01)));
            v_store(dst + x + 8, v_load(dst + x + 8) + v_cvt_f32(v_reinterpret_as_s32(v_src10)));
            v_store(dst + x + 12, v_load(dst + x + 12) + v_cvt_f32(v_reinterpret_as_s32(v_src11)));
        }
    }
    else
    {
        v_uint8x16 v_0 = v_setall_u8(0);
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_0 == v_mask);
                v_uint8x16 v_src = v_load(src + x);
                v_src = v_src & v_mask;
                v_uint16x8 v_src0, v_src1;
                v_expand(v_src, v_src0, v_src1);

                v_uint32x4 v_src00, v_src01, v_src10, v_src11;
                v_expand(v_src0, v_src00, v_src01);
                v_expand(v_src1, v_src10, v_src11);

                v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src00)));
                v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src01)));
                v_store(dst + x + 8, v_load(dst + x + 8) + v_cvt_f32(v_reinterpret_as_s32(v_src10)));
                v_store(dst + x + 12, v_load(dst + x + 12) + v_cvt_f32(v_reinterpret_as_s32(v_src11)));
            }
        }
        else if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_0 == v_mask);
                v_uint8x16 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + (x * cn), v_src0, v_src1, v_src2);
                v_src0 = v_src0 & v_mask;
                v_src1 = v_src1 & v_mask;
                v_src2 = v_src2 & v_mask;
                v_uint16x8 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_expand(v_src0, v_src00, v_src01);
                v_expand(v_src1, v_src10, v_src11);
                v_expand(v_src2, v_src20, v_src21);

                v_uint32x4 v_src000, v_src001, v_src010, v_src011;
                v_uint32x4 v_src100, v_src101, v_src110, v_src111;
                v_uint32x4 v_src200, v_src201, v_src210, v_src211;
                v_expand(v_src00, v_src000, v_src001);
                v_expand(v_src01, v_src010, v_src011);
                v_expand(v_src10, v_src100, v_src101);
                v_expand(v_src11, v_src110, v_src111);
                v_expand(v_src20, v_src200, v_src201);
                v_expand(v_src21, v_src210, v_src211);

                v_float32x4 v_dst000, v_dst001, v_dst010, v_dst011;
                v_float32x4 v_dst100, v_dst101, v_dst110, v_dst111;
                v_float32x4 v_dst200, v_dst201, v_dst210, v_dst211;
                v_load_deinterleave(dst + (x * cn), v_dst000, v_dst100, v_dst200);
                v_load_deinterleave(dst + ((x + 4) * cn), v_dst001, v_dst101, v_dst201);
                v_load_deinterleave(dst + ((x + 8) * cn), v_dst010, v_dst110, v_dst210);
                v_load_deinterleave(dst + ((x + 12) * cn), v_dst011, v_dst111, v_dst211);

                v_store_interleave(dst + (x * cn), v_dst000 + v_cvt_f32(v_reinterpret_as_s32(v_src000)), v_dst100 + v_cvt_f32(v_reinterpret_as_s32(v_src100)), v_dst200 + v_cvt_f32(v_reinterpret_as_s32(v_src200)));
                v_store_interleave(dst + ((x + 4) * cn), v_dst001 + v_cvt_f32(v_reinterpret_as_s32(v_src001)), v_dst101 + v_cvt_f32(v_reinterpret_as_s32(v_src101)), v_dst201 + v_cvt_f32(v_reinterpret_as_s32(v_src201)));
                v_store_interleave(dst + ((x + 8) * cn), v_dst010 + v_cvt_f32(v_reinterpret_as_s32(v_src010)), v_dst110 + v_cvt_f32(v_reinterpret_as_s32(v_src110)), v_dst210 + v_cvt_f32(v_reinterpret_as_s32(v_src210)));
                v_store_interleave(dst + ((x + 12) * cn), v_dst011 + v_cvt_f32(v_reinterpret_as_s32(v_src011)), v_dst111 + v_cvt_f32(v_reinterpret_as_s32(v_src111)), v_dst211 + v_cvt_f32(v_reinterpret_as_s32(v_src211)));
            }
        }
    }

    acc_general_(src, dst, mask, len, cn, x);
}

#if CV_VSX
#pragma GCC pop_options
#endif

void acc_simd_(const ushort* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_src = v_load(src + x);
            v_uint32x4 v_src0, v_src1;
            v_expand(v_src, v_src0, v_src1);

            v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src0)));
            v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src1)));
        }
    }
    else
    {
        if (cn == 1)
        {
            v_uint16x8 v_0 = v_setall_u16(0);
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_src = v_load(src + x);
                v_src = v_src & v_mask;
                v_uint32x4 v_src0, v_src1;
                v_expand(v_src, v_src0, v_src1);

                v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src0)));
                v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src1)));
            }
        }
        else if (cn == 3)
        {
            v_uint16x8 v_0 = v_setall_u16(0);
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_src0 = v_src0 & v_mask;
                v_src1 = v_src1 & v_mask;
                v_src2 = v_src2 & v_mask;
                v_uint32x4 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_expand(v_src0, v_src00, v_src01);
                v_expand(v_src1, v_src10, v_src11);
                v_expand(v_src2, v_src20, v_src21);

                v_float32x4 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_cvt_f32(v_reinterpret_as_s32(v_src00)), v_dst10 + v_cvt_f32(v_reinterpret_as_s32(v_src10)), v_dst20 + v_cvt_f32(v_reinterpret_as_s32(v_src20)));
                v_store_interleave(dst + (x + 4) * cn, v_dst01 + v_cvt_f32(v_reinterpret_as_s32(v_src01)), v_dst11 + v_cvt_f32(v_reinterpret_as_s32(v_src11)), v_dst21 + v_cvt_f32(v_reinterpret_as_s32(v_src21)));
            }
        }
    }

    acc_general_(src, dst, mask, len, cn, x);
}

void acc_simd_(const float* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_store(dst + x, v_load(dst + x) + v_load(src + x));
            v_store(dst + x + 4, v_load(dst + x + 4) + v_load(src + x + 4));
        }
    }
    else
    {
        v_float32x4 v_0 = v_setzero_f32();
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint16x8 v_masku16 = v_load_expand(mask + x);
                v_uint32x4 v_masku320, v_masku321;
                v_expand(v_masku16, v_masku320, v_masku321);
                v_float32x4 v_mask0 = v_reinterpret_as_f32(~(v_masku320 == v_reinterpret_as_u32(v_0)));
                v_float32x4 v_mask1 = v_reinterpret_as_f32(~(v_masku321 == v_reinterpret_as_u32(v_0)));

                v_store(dst + x, v_load(dst + x) + (v_load(src + x) & v_mask0));
                v_store(dst + x + 4, v_load(dst + x + 4) + (v_load(src + x + 4) & v_mask1));
            }
        }
        else if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint16x8 v_masku16 = v_load_expand(mask + x);
                v_uint32x4 v_masku320, v_masku321;
                v_expand(v_masku16, v_masku320, v_masku321);
                v_float32x4 v_mask0 = v_reinterpret_as_f32(~(v_masku320 == v_reinterpret_as_u32(v_0)));
                v_float32x4 v_mask1 = v_reinterpret_as_f32(~(v_masku321 == v_reinterpret_as_u32(v_0)));

                v_float32x4 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_load_deinterleave(src + x * cn, v_src00, v_src10, v_src20);
                v_load_deinterleave(src + (x + 4) * cn, v_src01, v_src11, v_src21);
                v_src00 = v_src00 & v_mask0;
                v_src01 = v_src01 & v_mask1;
                v_src10 = v_src10 & v_mask0;
                v_src11 = v_src11 & v_mask1;
                v_src20 = v_src20 & v_mask0;
                v_src21 = v_src21 & v_mask1;

                v_float32x4 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 4) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    acc_general_(src, dst, mask, len, cn, x);
}

#if CV_SIMD128_64F
void acc_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 16;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint8x16 v_src  = v_load(src + x);
            v_uint16x8 v_int0, v_int1;
            v_expand(v_src, v_int0, v_int1);

            v_uint32x4 v_int00, v_int01, v_int10, v_int11;
            v_expand(v_int0, v_int00, v_int01);
            v_expand(v_int1, v_int10, v_int11);

            v_float64x2 v_src0 = v_cvt_f64(v_reinterpret_as_s32(v_int00));
            v_float64x2 v_src1 = v_cvt_f64_high(v_reinterpret_as_s32(v_int00));
            v_float64x2 v_src2 = v_cvt_f64(v_reinterpret_as_s32(v_int01));
            v_float64x2 v_src3 = v_cvt_f64_high(v_reinterpret_as_s32(v_int01));
            v_float64x2 v_src4 = v_cvt_f64(v_reinterpret_as_s32(v_int10));
            v_float64x2 v_src5 = v_cvt_f64_high(v_reinterpret_as_s32(v_int10));
            v_float64x2 v_src6 = v_cvt_f64(v_reinterpret_as_s32(v_int11));
            v_float64x2 v_src7 = v_cvt_f64_high(v_reinterpret_as_s32(v_int11));

            v_float64x2 v_dst0 = v_load(dst + x);
            v_float64x2 v_dst1 = v_load(dst + x + 2);
            v_float64x2 v_dst2 = v_load(dst + x + 4);
            v_float64x2 v_dst3 = v_load(dst + x + 6);
            v_float64x2 v_dst4 = v_load(dst + x + 8);
            v_float64x2 v_dst5 = v_load(dst + x + 10);
            v_float64x2 v_dst6 = v_load(dst + x + 12);
            v_float64x2 v_dst7 = v_load(dst + x + 14);

            v_dst0 = v_dst0 + v_src0;
            v_dst1 = v_dst1 + v_src1;
            v_dst2 = v_dst2 + v_src2;
            v_dst3 = v_dst3 + v_src3;
            v_dst4 = v_dst4 + v_src4;
            v_dst5 = v_dst5 + v_src5;
            v_dst6 = v_dst6 + v_src6;
            v_dst7 = v_dst7 + v_src7;

            v_store(dst + x, v_dst0);
            v_store(dst + x + 2, v_dst1);
            v_store(dst + x + 4, v_dst2);
            v_store(dst + x + 6, v_dst3);
            v_store(dst + x + 8, v_dst4);
            v_store(dst + x + 10, v_dst5);
            v_store(dst + x + 12, v_dst6);
            v_store(dst + x + 14, v_dst7);
        }
    }
    else
    {
        v_uint8x16 v_0 = v_setall_u8(0);
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint8x16 v_src  = v_load(src + x);
                v_src = v_src & v_mask;
                v_uint16x8 v_int0, v_int1;
                v_expand(v_src, v_int0, v_int1);

                v_uint32x4 v_int00, v_int01, v_int10, v_int11;
                v_expand(v_int0, v_int00, v_int01);
                v_expand(v_int1, v_int10, v_int11);

                v_float64x2 v_src0 = v_cvt_f64(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src1 = v_cvt_f64_high(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src2 = v_cvt_f64(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src3 = v_cvt_f64_high(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src4 = v_cvt_f64(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src5 = v_cvt_f64_high(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src6 = v_cvt_f64(v_reinterpret_as_s32(v_int11));
                v_float64x2 v_src7 = v_cvt_f64_high(v_reinterpret_as_s32(v_int11));

                v_float64x2 v_dst0 = v_load(dst + x);
                v_float64x2 v_dst1 = v_load(dst + x + 2);
                v_float64x2 v_dst2 = v_load(dst + x + 4);
                v_float64x2 v_dst3 = v_load(dst + x + 6);
                v_float64x2 v_dst4 = v_load(dst + x + 8);
                v_float64x2 v_dst5 = v_load(dst + x + 10);
                v_float64x2 v_dst6 = v_load(dst + x + 12);
                v_float64x2 v_dst7 = v_load(dst + x + 14);

                v_dst0 = v_dst0 + v_src0;
                v_dst1 = v_dst1 + v_src1;
                v_dst2 = v_dst2 + v_src2;
                v_dst3 = v_dst3 + v_src3;
                v_dst4 = v_dst4 + v_src4;
                v_dst5 = v_dst5 + v_src5;
                v_dst6 = v_dst6 + v_src6;
                v_dst7 = v_dst7 + v_src7;

                v_store(dst + x, v_dst0);
                v_store(dst + x + 2, v_dst1);
                v_store(dst + x + 4, v_dst2);
                v_store(dst + x + 6, v_dst3);
                v_store(dst + x + 8, v_dst4);
                v_store(dst + x + 10, v_dst5);
                v_store(dst + x + 12, v_dst6);
                v_store(dst + x + 14, v_dst7);
            }
        }
        else if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_0 == v_mask);
                v_uint8x16 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + (x * cn), v_src0, v_src1, v_src2);
                v_src0 = v_src0 & v_mask;
                v_src1 = v_src1 & v_mask;
                v_src2 = v_src2 & v_mask;
                v_uint16x8 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_expand(v_src0, v_src00, v_src01);
                v_expand(v_src1, v_src10, v_src11);
                v_expand(v_src2, v_src20, v_src21);

                v_uint32x4 v_src000, v_src001, v_src010, v_src011;
                v_uint32x4 v_src100, v_src101, v_src110, v_src111;
                v_uint32x4 v_src200, v_src201, v_src210, v_src211;
                v_expand(v_src00, v_src000, v_src001);
                v_expand(v_src01, v_src010, v_src011);
                v_expand(v_src10, v_src100, v_src101);
                v_expand(v_src11, v_src110, v_src111);
                v_expand(v_src20, v_src200, v_src201);
                v_expand(v_src21, v_src210, v_src211);

                v_float64x2 v_src0000, v_src0001, v_src0010, v_src0011, v_src0100, v_src0101, v_src0110, v_src0111;
                v_float64x2 v_src1000, v_src1001, v_src1010, v_src1011, v_src1100, v_src1101, v_src1110, v_src1111;
                v_float64x2 v_src2000, v_src2001, v_src2010, v_src2011, v_src2100, v_src2101, v_src2110, v_src2111;
                v_src0000 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src000)));
                v_src0001 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src000)));
                v_src0010 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src001)));
                v_src0011 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src001)));
                v_src0100 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src010)));
                v_src0101 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src010)));
                v_src0110 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src011)));
                v_src0111 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src011)));
                v_src1000 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src100)));
                v_src1001 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src100)));
                v_src1010 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src101)));
                v_src1011 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src101)));
                v_src1100 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src110)));
                v_src1101 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src110)));
                v_src1110 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src111)));
                v_src1111 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src111)));
                v_src2000 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src200)));
                v_src2001 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src200)));
                v_src2010 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src201)));
                v_src2011 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src201)));
                v_src2100 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src210)));
                v_src2101 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src210)));
                v_src2110 = v_cvt_f64(v_cvt_f32(v_reinterpret_as_s32(v_src211)));
                v_src2111 = v_cvt_f64_high(v_cvt_f32(v_reinterpret_as_s32(v_src211)));

                v_float64x2 v_dst0000, v_dst0001, v_dst0010, v_dst0011, v_dst0100, v_dst0101, v_dst0110, v_dst0111;
                v_float64x2 v_dst1000, v_dst1001, v_dst1010, v_dst1011, v_dst1100, v_dst1101, v_dst1110, v_dst1111;
                v_float64x2 v_dst2000, v_dst2001, v_dst2010, v_dst2011, v_dst2100, v_dst2101, v_dst2110, v_dst2111;
                v_load_deinterleave(dst + (x * cn), v_dst0000, v_dst1000, v_dst2000);
                v_load_deinterleave(dst + ((x + 2) * cn), v_dst0001, v_dst1001, v_dst2001);
                v_load_deinterleave(dst + ((x + 4) * cn), v_dst0010, v_dst1010, v_dst2010);
                v_load_deinterleave(dst + ((x + 6) * cn), v_dst0011, v_dst1011, v_dst2011);
                v_load_deinterleave(dst + ((x + 8) * cn), v_dst0100, v_dst1100, v_dst2100);
                v_load_deinterleave(dst + ((x + 10) * cn), v_dst0101, v_dst1101, v_dst2101);
                v_load_deinterleave(dst + ((x + 12) * cn), v_dst0110, v_dst1110, v_dst2110);
                v_load_deinterleave(dst + ((x + 14) * cn), v_dst0111, v_dst1111, v_dst2111);

                v_store_interleave(dst + (x * cn), v_dst0000 + v_src0000, v_dst1000 + v_src1000, v_dst2000 + v_src2000);
                v_store_interleave(dst + ((x + 2) * cn), v_dst0001 + v_src0001, v_dst1001 + v_src1001, v_dst2001 + v_src2001);
                v_store_interleave(dst + ((x + 4) * cn), v_dst0010 + v_src0010, v_dst1010 + v_src1010, v_dst2010 + v_src2010);
                v_store_interleave(dst + ((x + 6) * cn), v_dst0011 + v_src0011, v_dst1011 + v_src1011, v_dst2011 + v_src2011);
                v_store_interleave(dst + ((x + 8) * cn), v_dst0100 + v_src0100, v_dst1100 + v_src1100, v_dst2100 + v_src2100);
                v_store_interleave(dst + ((x + 10) * cn), v_dst0101 + v_src0101, v_dst1101 + v_src1101, v_dst2101 + v_src2101);
                v_store_interleave(dst + ((x + 12) * cn), v_dst0110 + v_src0110, v_dst1110 + v_src1110, v_dst2110 + v_src2110);
                v_store_interleave(dst + ((x + 14) * cn), v_dst0111 + v_src0111, v_dst1111 + v_src1111, v_dst2111 + v_src2111);
            }
        }
    }

    acc_general_(src, dst, mask, len, cn, x);
}

void acc_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_src  = v_load(src + x);
            v_uint32x4 v_int0, v_int1;
            v_expand(v_src, v_int0, v_int1);

            v_float64x2 v_src0 = v_cvt_f64(v_reinterpret_as_s32(v_int0));
            v_float64x2 v_src1 = v_cvt_f64_high(v_reinterpret_as_s32(v_int0));
            v_float64x2 v_src2 = v_cvt_f64(v_reinterpret_as_s32(v_int1));
            v_float64x2 v_src3 = v_cvt_f64_high(v_reinterpret_as_s32(v_int1));

            v_float64x2 v_dst0 = v_load(dst + x);
            v_float64x2 v_dst1 = v_load(dst + x + 2);
            v_float64x2 v_dst2 = v_load(dst + x + 4);
            v_float64x2 v_dst3 = v_load(dst + x + 6);

            v_dst0 = v_dst0 + v_src0;
            v_dst1 = v_dst1 + v_src1;
            v_dst2 = v_dst2 + v_src2;
            v_dst3 = v_dst3 + v_src3;

            v_store(dst + x, v_dst0);
            v_store(dst + x + 2, v_dst1);
            v_store(dst + x + 4, v_dst2);
            v_store(dst + x + 6, v_dst3);
        }
    }
    else
    {
        v_uint16x8 v_0 = v_setzero_u16();
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_src  = v_load(src + x);
                v_src = v_src & v_mask;
                v_uint32x4 v_int0, v_int1;
                v_expand(v_src, v_int0, v_int1);

                v_float64x2 v_src0 = v_cvt_f64(v_reinterpret_as_s32(v_int0));
                v_float64x2 v_src1 = v_cvt_f64_high(v_reinterpret_as_s32(v_int0));
                v_float64x2 v_src2 = v_cvt_f64(v_reinterpret_as_s32(v_int1));
                v_float64x2 v_src3 = v_cvt_f64_high(v_reinterpret_as_s32(v_int1));

                v_float64x2 v_dst0 = v_load(dst + x);
                v_float64x2 v_dst1 = v_load(dst + x + 2);
                v_float64x2 v_dst2 = v_load(dst + x + 4);
                v_float64x2 v_dst3 = v_load(dst + x + 6);

                v_dst0 = v_dst0 + v_src0;
                v_dst1 = v_dst1 + v_src1;
                v_dst2 = v_dst2 + v_src2;
                v_dst3 = v_dst3 + v_src3;

                v_store(dst + x, v_dst0);
                v_store(dst + x + 2, v_dst1);
                v_store(dst + x + 4, v_dst2);
                v_store(dst + x + 6, v_dst3);
            }
        }
        if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_src0 = v_src0 & v_mask;
                v_src1 = v_src1 & v_mask;
                v_src2 = v_src2 & v_mask;
                v_uint32x4 v_int00, v_int01, v_int10, v_int11, v_int20, v_int21;
                v_expand(v_src0, v_int00, v_int01);
                v_expand(v_src1, v_int10, v_int11);
                v_expand(v_src2, v_int20, v_int21);

                v_float64x2 v_src00 = v_cvt_f64(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src01 = v_cvt_f64_high(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src02 = v_cvt_f64(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src03 = v_cvt_f64_high(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src10 = v_cvt_f64(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src11 = v_cvt_f64_high(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src12 = v_cvt_f64(v_reinterpret_as_s32(v_int11));
                v_float64x2 v_src13 = v_cvt_f64_high(v_reinterpret_as_s32(v_int11));
                v_float64x2 v_src20 = v_cvt_f64(v_reinterpret_as_s32(v_int20));
                v_float64x2 v_src21 = v_cvt_f64_high(v_reinterpret_as_s32(v_int20));
                v_float64x2 v_src22 = v_cvt_f64(v_reinterpret_as_s32(v_int21));
                v_float64x2 v_src23 = v_cvt_f64_high(v_reinterpret_as_s32(v_int21));

                v_float64x2 v_dst00, v_dst01, v_dst02, v_dst03, v_dst10, v_dst11, v_dst12, v_dst13, v_dst20, v_dst21, v_dst22, v_dst23;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst02, v_dst12, v_dst22);
                v_load_deinterleave(dst + (x + 6) * cn, v_dst03, v_dst13, v_dst23);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
                v_store_interleave(dst + (x + 4) * cn, v_dst02 + v_src02, v_dst12 + v_src12, v_dst22 + v_src22);
                v_store_interleave(dst + (x + 6) * cn, v_dst03 + v_src03, v_dst13 + v_src13, v_dst23 + v_src23);
            }
        }
    }

    acc_general_(src, dst, mask, len, cn, x);
}

void acc_simd_(const float* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float32x4 v_src = v_load(src + x);
            v_float64x2 v_src0 = v_cvt_f64(v_src);
            v_float64x2 v_src1 = v_cvt_f64_high(v_src);

            v_store(dst + x, v_load(dst + x) + v_src0);
            v_store(dst + x + 2, v_load(dst + x + 2) + v_src1);
        }
    }
    else
    {
        v_uint64x2 v_0 = v_setzero_u64();
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint32x4 v_masku32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_masku32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));

                v_float32x4 v_src = v_load(src + x);
                v_float64x2 v_src0 = v_cvt_f64(v_src) & v_mask0;
                v_float64x2 v_src1 = v_cvt_f64_high(v_src) & v_mask1;

                v_store(dst + x, v_load(dst + x) + v_src0);
                v_store(dst + x + 2, v_load(dst + x + 2) + v_src1);
            }
        }
        else if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint32x4 v_masku32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_masku32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));

                v_float32x4 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_float64x2 v_src00 = v_cvt_f64(v_src0) & v_mask0;
                v_float64x2 v_src01 = v_cvt_f64_high(v_src0) & v_mask1;
                v_float64x2 v_src10 = v_cvt_f64(v_src1) & v_mask0;
                v_float64x2 v_src11 = v_cvt_f64_high(v_src1) & v_mask1;
                v_float64x2 v_src20 = v_cvt_f64(v_src2) & v_mask0;
                v_float64x2 v_src21 = v_cvt_f64_high(v_src2) & v_mask1;

                v_float64x2 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    acc_general_(src, dst, mask, len, cn, x);
}

void acc_simd_(const double* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float64x2 v_src0 = v_load(src + x);
            v_float64x2 v_src1 = v_load(src + x + 2);

            v_store(dst + x, v_load(dst + x) + v_src0);
            v_store(dst + x + 2, v_load(dst + x + 2) + v_src1);
        }
    }
    else
    {
        v_uint64x2 v_0 = v_setzero_u64();
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint32x4 v_masku32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_masku32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));

                v_float64x2 v_src0 = v_load(src + x);
                v_float64x2 v_src1 = v_load(src + x + 2);

                v_store(dst + x, v_load(dst + x) + (v_src0 & v_mask0));
                v_store(dst + x + 2, v_load(dst + x + 2) + (v_src1 & v_mask1));
            }
        }
        else if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint32x4 v_masku32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_masku32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));

                v_float64x2 v_src00, v_src10, v_src20, v_src01, v_src11, v_src21;
                v_load_deinterleave(src + x * cn, v_src00, v_src10, v_src20);
                v_load_deinterleave(src + (x + 2) * cn, v_src01, v_src11, v_src21);
                v_src00 = v_src00 & v_mask0;
                v_src01 = v_src01 & v_mask1;
                v_src10 = v_src10 & v_mask0;
                v_src11 = v_src11 & v_mask1;
                v_src20 = v_src20 & v_mask0;
                v_src21 = v_src21 & v_mask1;

                v_float64x2 v_dst00, v_dst10, v_dst20, v_dst01, v_dst11, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    acc_general_(src, dst, mask, len, cn, x);
}
#else
void acc_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn)
{
    acc_general_(src, dst, mask, len, cn, 0);
}

void acc_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn)
{
    acc_general_(src, dst, mask, len, cn, 0);
}

void acc_simd_(const float* src, double* dst, const uchar* mask, int len, int cn)
{
    acc_general_(src, dst, mask, len, cn, 0);
}

void acc_simd_(const double* src, double* dst, const uchar* mask, int len, int cn)
{
    acc_general_(src, dst, mask, len, cn, 0);
}
#endif

// square accumulate optimized by universal intrinsic
#if CV_VSX
#pragma GCC push_options
#pragma GCC target("cpu=power8")
#pragma GCC target("tune=power8")
#endif
void accSqr_simd_(const uchar* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 16;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint8x16 v_src  = v_load(src + x);
            v_uint16x8 v_src0, v_src1;
            v_expand(v_src, v_src0, v_src1);
            v_src0 = v_src0 * v_src0;
            v_src1 = v_src1 * v_src1;

            v_uint32x4 v_src00, v_src01, v_src10, v_src11;
            v_expand(v_src0, v_src00, v_src01);
            v_expand(v_src1, v_src10, v_src11);

            v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src00)));
            v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src01)));
            v_store(dst + x + 8, v_load(dst + x + 8) + v_cvt_f32(v_reinterpret_as_s32(v_src10)));
            v_store(dst + x + 12, v_load(dst + x + 12) + v_cvt_f32(v_reinterpret_as_s32(v_src11)));
        }
    }
    else
    {
        v_uint8x16 v_0 = v_setall_u8(0);
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_0 == v_mask);
                v_uint8x16 v_src = v_load(src + x);
                v_src = v_src & v_mask;
                v_uint16x8 v_src0, v_src1;
                v_expand(v_src, v_src0, v_src1);
                v_src0 = v_src0 * v_src0;
                v_src1 = v_src1 * v_src1;

                v_uint32x4 v_src00, v_src01, v_src10, v_src11;
                v_expand(v_src0, v_src00, v_src01);
                v_expand(v_src1, v_src10, v_src11);

                v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src00)));
                v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src01)));
                v_store(dst + x + 8, v_load(dst + x + 8) + v_cvt_f32(v_reinterpret_as_s32(v_src10)));
                v_store(dst + x + 12, v_load(dst + x + 12) + v_cvt_f32(v_reinterpret_as_s32(v_src11)));
            }
        }
        else if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_0 == v_mask);

                v_uint8x16 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_src0 = v_src0 & v_mask;
                v_src1 = v_src1 & v_mask;
                v_src2 = v_src2 & v_mask;

                v_uint16x8 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_expand(v_src0, v_src00, v_src01);
                v_expand(v_src1, v_src10, v_src11);
                v_expand(v_src2, v_src20, v_src21);
                v_src00 = v_src00 * v_src00;
                v_src01 = v_src01 * v_src01;
                v_src10 = v_src10 * v_src10;
                v_src11 = v_src11 * v_src11;
                v_src20 = v_src20 * v_src20;
                v_src21 = v_src21 * v_src21;

                v_uint32x4 v_src000, v_src001, v_src010, v_src011;
                v_uint32x4 v_src100, v_src101, v_src110, v_src111;
                v_uint32x4 v_src200, v_src201, v_src210, v_src211;
                v_expand(v_src00, v_src000, v_src001);
                v_expand(v_src01, v_src010, v_src011);
                v_expand(v_src10, v_src100, v_src101);
                v_expand(v_src11, v_src110, v_src111);
                v_expand(v_src20, v_src200, v_src201);
                v_expand(v_src21, v_src210, v_src211);

                v_float32x4 v_dst000, v_dst001, v_dst010, v_dst011;
                v_float32x4 v_dst100, v_dst101, v_dst110, v_dst111;
                v_float32x4 v_dst200, v_dst201, v_dst210, v_dst211;
                v_load_deinterleave(dst + x * cn, v_dst000, v_dst100, v_dst200);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst001, v_dst101, v_dst201);
                v_load_deinterleave(dst + (x + 8) * cn, v_dst010, v_dst110, v_dst210);
                v_load_deinterleave(dst + (x + 12) * cn, v_dst011, v_dst111, v_dst211);

                v_store_interleave(dst + x * cn, v_dst000 + v_cvt_f32(v_reinterpret_as_s32(v_src000)), v_dst100 + v_cvt_f32(v_reinterpret_as_s32(v_src100)), v_dst200 + v_cvt_f32(v_reinterpret_as_s32(v_src200)));
                v_store_interleave(dst + (x + 4) * cn, v_dst001 + v_cvt_f32(v_reinterpret_as_s32(v_src001)), v_dst101 + v_cvt_f32(v_reinterpret_as_s32(v_src101)), v_dst201 + v_cvt_f32(v_reinterpret_as_s32(v_src201)));
                v_store_interleave(dst + (x + 8) * cn, v_dst010 + v_cvt_f32(v_reinterpret_as_s32(v_src010)), v_dst110 + v_cvt_f32(v_reinterpret_as_s32(v_src110)), v_dst210 + v_cvt_f32(v_reinterpret_as_s32(v_src210)));
                v_store_interleave(dst + (x + 12) * cn, v_dst011 + v_cvt_f32(v_reinterpret_as_s32(v_src011)), v_dst111 + v_cvt_f32(v_reinterpret_as_s32(v_src111)), v_dst211 + v_cvt_f32(v_reinterpret_as_s32(v_src211)));
            }
        }
    }

    accSqr_general_(src, dst, mask, len, cn, x);
}
#if CV_VSX
#pragma GCC pop_options
#endif

void accSqr_simd_(const ushort* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_src = v_load(src + x);
            v_uint32x4 v_src0, v_src1;
            v_expand(v_src, v_src0, v_src1);

            v_float32x4 v_float0, v_float1;
            v_float0 = v_cvt_f32(v_reinterpret_as_s32(v_src0));
            v_float1 = v_cvt_f32(v_reinterpret_as_s32(v_src1));
            v_float0 = v_float0 * v_float0;
            v_float1 = v_float1 * v_float1;

            v_store(dst + x, v_load(dst + x) + v_float0);
            v_store(dst + x + 4, v_load(dst + x + 4) + v_float1);
        }
    }
    else
    {
        v_uint32x4 v_0 = v_setzero_u32();
        if (cn == 1)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint16x8 v_mask16 = v_load_expand(mask + x);
                v_uint32x4 v_mask0, v_mask1;
                v_expand(v_mask16, v_mask0, v_mask1);
                v_mask0 = ~(v_mask0 == v_0);
                v_mask1 = ~(v_mask1 == v_0);
                v_uint16x8 v_src = v_load(src + x);
                v_uint32x4 v_src0, v_src1;
                v_expand(v_src, v_src0, v_src1);
                v_src0 = v_src0 & v_mask0;
                v_src1 = v_src1 & v_mask1;

                v_float32x4 v_float0, v_float1;
                v_float0 = v_cvt_f32(v_reinterpret_as_s32(v_src0));
                v_float1 = v_cvt_f32(v_reinterpret_as_s32(v_src1));
                v_float0 = v_float0 * v_float0;
                v_float1 = v_float1 * v_float1;

                v_store(dst + x, v_load(dst + x) + v_float0);
                v_store(dst + x + 4, v_load(dst + x + 4) + v_float1);
            }
        }
        else if (cn == 3)
        {
            for ( ; x <= len - cVectorWidth ; x += cVectorWidth)
            {
                v_uint16x8 v_mask16 = v_load_expand(mask + x);
                v_uint32x4 v_mask0, v_mask1;
                v_expand(v_mask16, v_mask0, v_mask1);
                v_mask0 = ~(v_mask0 == v_0);
                v_mask1 = ~(v_mask1 == v_0);

                v_uint16x8 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_uint32x4 v_int00, v_int01, v_int10, v_int11, v_int20, v_int21;
                v_expand(v_src0, v_int00, v_int01);
                v_expand(v_src1, v_int10, v_int11);
                v_expand(v_src2, v_int20, v_int21);
                v_int00 = v_int00 & v_mask0;
                v_int01 = v_int01 & v_mask1;
                v_int10 = v_int10 & v_mask0;
                v_int11 = v_int11 & v_mask1;
                v_int20 = v_int20 & v_mask0;
                v_int21 = v_int21 & v_mask1;

                v_float32x4 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_src00 = v_cvt_f32(v_reinterpret_as_s32(v_int00));
                v_src01 = v_cvt_f32(v_reinterpret_as_s32(v_int01));
                v_src10 = v_cvt_f32(v_reinterpret_as_s32(v_int10));
                v_src11 = v_cvt_f32(v_reinterpret_as_s32(v_int11));
                v_src20 = v_cvt_f32(v_reinterpret_as_s32(v_int20));
                v_src21 = v_cvt_f32(v_reinterpret_as_s32(v_int21));
                v_src00 = v_src00 * v_src00;
                v_src01 = v_src01 * v_src01;
                v_src10 = v_src10 * v_src10;
                v_src11 = v_src11 * v_src11;
                v_src20 = v_src20 * v_src20;
                v_src21 = v_src21 * v_src21;

                v_float32x4 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 4) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    accSqr_general_(src, dst, mask, len, cn, x);
}

void accSqr_simd_(const float* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float32x4 v_src0 = v_load(src + x);
            v_float32x4 v_src1 = v_load(src + x + 4);
            v_src0 = v_src0 * v_src0;
            v_src1 = v_src1 * v_src1;

            v_store(dst + x, v_load(dst + x) + v_src0);
            v_store(dst + x + 4, v_load(dst + x + 4) + v_src1);
        }
    }
    else
    {
        v_uint32x4 v_0 = v_setzero_u32();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask16 = v_load_expand(mask + x);
                v_uint32x4 v_mask_0, v_mask_1;
                v_expand(v_mask16, v_mask_0, v_mask_1);
                v_float32x4 v_mask0 = v_reinterpret_as_f32(~(v_mask_0 == v_0));
                v_float32x4 v_mask1 = v_reinterpret_as_f32(~(v_mask_1 == v_0));
                v_float32x4 v_src0 = v_load(src + x);
                v_float32x4 v_src1 = v_load(src + x + 4);
                v_src0 = v_src0 & v_mask0;
                v_src1 = v_src1 & v_mask1;
                v_src0 = v_src0 * v_src0;
                v_src1 = v_src1 * v_src1;

                v_store(dst + x, v_load(dst + x) + v_src0);
                v_store(dst + x + 4, v_load(dst + x + 4) + v_src1);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask16 = v_load_expand(mask + x);
                v_uint32x4 v_mask_0, v_mask_1;
                v_expand(v_mask16, v_mask_0, v_mask_1);
                v_float32x4 v_mask0 = v_reinterpret_as_f32(~(v_mask_0 == v_0));
                v_float32x4 v_mask1 = v_reinterpret_as_f32(~(v_mask_1 == v_0));

                v_float32x4 v_src00, v_src10, v_src20, v_src01, v_src11, v_src21;
                v_load_deinterleave(src + x * cn, v_src00, v_src10, v_src20);
                v_load_deinterleave(src + (x + 4) * cn, v_src01, v_src11, v_src21);
                v_src00 = v_src00 & v_mask0;
                v_src01 = v_src01 & v_mask1;
                v_src10 = v_src10 & v_mask0;
                v_src11 = v_src11 & v_mask1;
                v_src20 = v_src20 & v_mask0;
                v_src21 = v_src21 & v_mask1;
                v_src00 = v_src00 * v_src00;
                v_src01 = v_src01 * v_src01;
                v_src10 = v_src10 * v_src10;
                v_src11 = v_src11 * v_src11;
                v_src20 = v_src20 * v_src20;
                v_src21 = v_src21 * v_src21;

                v_float32x4 v_dst00, v_dst10, v_dst20, v_dst01, v_dst11, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 4) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    accSqr_general_(src, dst, mask, len, cn, x);
}
#if CV_SIMD128_64F
void accSqr_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_int = v_load_expand(src + x);

            v_uint32x4 v_int0, v_int1;
            v_expand(v_int, v_int0, v_int1);

            v_float64x2 v_src0 = v_cvt_f64(v_reinterpret_as_s32(v_int0));
            v_float64x2 v_src1 = v_cvt_f64_high(v_reinterpret_as_s32(v_int0));
            v_float64x2 v_src2 = v_cvt_f64(v_reinterpret_as_s32(v_int1));
            v_float64x2 v_src3 = v_cvt_f64_high(v_reinterpret_as_s32(v_int1));
            v_src0 = v_src0 * v_src0;
            v_src1 = v_src1 * v_src1;
            v_src2 = v_src2 * v_src2;
            v_src3 = v_src3 * v_src3;

            v_float64x2 v_dst0 = v_load(dst + x);
            v_float64x2 v_dst1 = v_load(dst + x + 2);
            v_float64x2 v_dst2 = v_load(dst + x + 4);
            v_float64x2 v_dst3 = v_load(dst + x + 6);

            v_dst0 += v_src0;
            v_dst1 += v_src1;
            v_dst2 += v_src2;
            v_dst3 += v_src3;

            v_store(dst + x, v_dst0);
            v_store(dst + x + 2, v_dst1);
            v_store(dst + x + 4, v_dst2);
            v_store(dst + x + 6, v_dst3);
        }
    }
    else
    {
        v_uint16x8 v_0 = v_setzero_u16();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_src = v_load_expand(src + x);
                v_uint16x8 v_int = v_src & v_mask;

                v_uint32x4 v_int0, v_int1;
                v_expand(v_int, v_int0, v_int1);

                v_float64x2 v_src0 = v_cvt_f64(v_reinterpret_as_s32(v_int0));
                v_float64x2 v_src1 = v_cvt_f64_high(v_reinterpret_as_s32(v_int0));
                v_float64x2 v_src2 = v_cvt_f64(v_reinterpret_as_s32(v_int1));
                v_float64x2 v_src3 = v_cvt_f64_high(v_reinterpret_as_s32(v_int1));
                v_src0 = v_src0 * v_src0;
                v_src1 = v_src1 * v_src1;
                v_src2 = v_src2 * v_src2;
                v_src3 = v_src3 * v_src3;

                v_float64x2 v_dst0 = v_load(dst + x);
                v_float64x2 v_dst1 = v_load(dst + x + 2);
                v_float64x2 v_dst2 = v_load(dst + x + 4);
                v_float64x2 v_dst3 = v_load(dst + x + 6);

                v_dst0 += v_src0;
                v_dst1 += v_src1;
                v_dst2 += v_src2;
                v_dst3 += v_src3;

                v_store(dst + x, v_dst0);
                v_store(dst + x + 2, v_dst1);
                v_store(dst + x + 4, v_dst2);
                v_store(dst + x + 6, v_dst3);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - /*cVectorWidth*/16; x += cVectorWidth)
            {
                v_uint8x16 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_uint16x8 v_int0, v_int1, v_int2, dummy;
                v_expand(v_src0, v_int0, dummy);
                v_expand(v_src1, v_int1, dummy);
                v_expand(v_src2, v_int2, dummy);
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_int0 = v_int0 & v_mask;
                v_int1 = v_int1 & v_mask;
                v_int2 = v_int2 & v_mask;

                v_uint32x4 v_int00, v_int01, v_int10, v_int11, v_int20, v_int21;
                v_expand(v_int0, v_int00, v_int01);
                v_expand(v_int1, v_int10, v_int11);
                v_expand(v_int2, v_int20, v_int21);

                v_float64x2 v_src00 = v_cvt_f64(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src01 = v_cvt_f64_high(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src02 = v_cvt_f64(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src03 = v_cvt_f64_high(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src10 = v_cvt_f64(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src11 = v_cvt_f64_high(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src12 = v_cvt_f64(v_reinterpret_as_s32(v_int11));
                v_float64x2 v_src13 = v_cvt_f64_high(v_reinterpret_as_s32(v_int11));
                v_float64x2 v_src20 = v_cvt_f64(v_reinterpret_as_s32(v_int20));
                v_float64x2 v_src21 = v_cvt_f64_high(v_reinterpret_as_s32(v_int20));
                v_float64x2 v_src22 = v_cvt_f64(v_reinterpret_as_s32(v_int21));
                v_float64x2 v_src23 = v_cvt_f64_high(v_reinterpret_as_s32(v_int21));
                v_src00 = v_src00 * v_src00;
                v_src01 = v_src01 * v_src01;
                v_src02 = v_src02 * v_src02;
                v_src03 = v_src03 * v_src03;
                v_src10 = v_src10 * v_src10;
                v_src11 = v_src11 * v_src11;
                v_src12 = v_src12 * v_src12;
                v_src13 = v_src13 * v_src13;
                v_src20 = v_src20 * v_src20;
                v_src21 = v_src21 * v_src21;
                v_src22 = v_src22 * v_src22;
                v_src23 = v_src23 * v_src23;

                v_float64x2 v_dst00, v_dst01, v_dst02, v_dst03, v_dst10, v_dst11, v_dst12, v_dst13, v_dst20, v_dst21, v_dst22, v_dst23;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst02, v_dst12, v_dst22);
                v_load_deinterleave(dst + (x + 6) * cn, v_dst03, v_dst13, v_dst23);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
                v_store_interleave(dst + (x + 4) * cn, v_dst02 + v_src02, v_dst12 + v_src12, v_dst22 + v_src22);
                v_store_interleave(dst + (x + 6) * cn, v_dst03 + v_src03, v_dst13 + v_src13, v_dst23 + v_src23);
            }
        }
    }

    accSqr_general_(src, dst, mask, len, cn, x);
}

void accSqr_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_src  = v_load(src + x);
            v_uint32x4 v_int_0, v_int_1;
            v_expand(v_src, v_int_0, v_int_1);

            v_int32x4 v_int0 = v_reinterpret_as_s32(v_int_0);
            v_int32x4 v_int1 = v_reinterpret_as_s32(v_int_1);

            v_float64x2 v_src0 = v_cvt_f64(v_int0);
            v_float64x2 v_src1 = v_cvt_f64_high(v_int0);
            v_float64x2 v_src2 = v_cvt_f64(v_int1);
            v_float64x2 v_src3 = v_cvt_f64_high(v_int1);
            v_src0 = v_src0 * v_src0;
            v_src1 = v_src1 * v_src1;
            v_src2 = v_src2 * v_src2;
            v_src3 = v_src3 * v_src3;

            v_float64x2 v_dst0 = v_load(dst + x);
            v_float64x2 v_dst1 = v_load(dst + x + 2);
            v_float64x2 v_dst2 = v_load(dst + x + 4);
            v_float64x2 v_dst3 = v_load(dst + x + 6);

            v_dst0 += v_src0;
            v_dst1 += v_src1;
            v_dst2 += v_src2;
            v_dst3 += v_src3;

            v_store(dst + x, v_dst0);
            v_store(dst + x + 2, v_dst1);
            v_store(dst + x + 4, v_dst2);
            v_store(dst + x + 6, v_dst3);
        }
    }
    else
    {
        v_uint16x8 v_0 = v_setzero_u16();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_src = v_load(src + x);
                v_src = v_src & v_mask;
                v_uint32x4 v_int_0, v_int_1;
                v_expand(v_src, v_int_0, v_int_1);

                v_int32x4 v_int0 = v_reinterpret_as_s32(v_int_0);
                v_int32x4 v_int1 = v_reinterpret_as_s32(v_int_1);

                v_float64x2 v_src0 = v_cvt_f64(v_int0);
                v_float64x2 v_src1 = v_cvt_f64_high(v_int0);
                v_float64x2 v_src2 = v_cvt_f64(v_int1);
                v_float64x2 v_src3 = v_cvt_f64_high(v_int1);
                v_src0 = v_src0 * v_src0;
                v_src1 = v_src1 * v_src1;
                v_src2 = v_src2 * v_src2;
                v_src3 = v_src3 * v_src3;

                v_float64x2 v_dst0 = v_load(dst + x);
                v_float64x2 v_dst1 = v_load(dst + x + 2);
                v_float64x2 v_dst2 = v_load(dst + x + 4);
                v_float64x2 v_dst3 = v_load(dst + x + 6);

                v_dst0 += v_src0;
                v_dst1 += v_src1;
                v_dst2 += v_src2;
                v_dst3 += v_src3;

                v_store(dst + x, v_dst0);
                v_store(dst + x + 2, v_dst1);
                v_store(dst + x + 4, v_dst2);
                v_store(dst + x + 6, v_dst3);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_src0 = v_src0 & v_mask;
                v_src1 = v_src1 & v_mask;
                v_src2 = v_src2 & v_mask;
                v_uint32x4 v_int00, v_int01, v_int10, v_int11, v_int20, v_int21;
                v_expand(v_src0, v_int00, v_int01);
                v_expand(v_src1, v_int10, v_int11);
                v_expand(v_src2, v_int20, v_int21);

                v_float64x2 v_src00 = v_cvt_f64(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src01 = v_cvt_f64_high(v_reinterpret_as_s32(v_int00));
                v_float64x2 v_src02 = v_cvt_f64(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src03 = v_cvt_f64_high(v_reinterpret_as_s32(v_int01));
                v_float64x2 v_src10 = v_cvt_f64(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src11 = v_cvt_f64_high(v_reinterpret_as_s32(v_int10));
                v_float64x2 v_src12 = v_cvt_f64(v_reinterpret_as_s32(v_int11));
                v_float64x2 v_src13 = v_cvt_f64_high(v_reinterpret_as_s32(v_int11));
                v_float64x2 v_src20 = v_cvt_f64(v_reinterpret_as_s32(v_int20));
                v_float64x2 v_src21 = v_cvt_f64_high(v_reinterpret_as_s32(v_int20));
                v_float64x2 v_src22 = v_cvt_f64(v_reinterpret_as_s32(v_int21));
                v_float64x2 v_src23 = v_cvt_f64_high(v_reinterpret_as_s32(v_int21));
                v_src00 = v_src00 * v_src00;
                v_src01 = v_src01 * v_src01;
                v_src02 = v_src02 * v_src02;
                v_src03 = v_src03 * v_src03;
                v_src10 = v_src10 * v_src10;
                v_src11 = v_src11 * v_src11;
                v_src12 = v_src12 * v_src12;
                v_src13 = v_src13 * v_src13;
                v_src20 = v_src20 * v_src20;
                v_src21 = v_src21 * v_src21;
                v_src22 = v_src22 * v_src22;
                v_src23 = v_src23 * v_src23;

                v_float64x2 v_dst00, v_dst01, v_dst02, v_dst03;
                v_float64x2 v_dst10, v_dst11, v_dst12, v_dst13;
                v_float64x2 v_dst20, v_dst21, v_dst22, v_dst23;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2)* cn, v_dst01, v_dst11, v_dst21);
                v_load_deinterleave(dst + (x + 4)* cn, v_dst02, v_dst12, v_dst22);
                v_load_deinterleave(dst + (x + 6)* cn, v_dst03, v_dst13, v_dst23);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
                v_store_interleave(dst + (x + 4) * cn, v_dst02 + v_src02, v_dst12 + v_src12, v_dst22 + v_src22);
                v_store_interleave(dst + (x + 6) * cn, v_dst03 + v_src03, v_dst13 + v_src13, v_dst23 + v_src23);
            }
        }
    }

    accSqr_general_(src, dst, mask, len, cn, x);
}

void accSqr_simd_(const float* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float32x4 v_src = v_load(src + x);
            v_float64x2 v_src0 = v_cvt_f64(v_src);
            v_float64x2 v_src1 = v_cvt_f64_high(v_src);
            v_src0 = v_src0 * v_src0;
            v_src1 = v_src1 * v_src1;

            v_store(dst + x, v_load(dst + x) + v_src0);
            v_store(dst + x + 2, v_load(dst + x + 2) + v_src1);
        }
    }
    else
    {
        v_uint32x4 v_0 = v_setzero_u32();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask = v_load_expand_q(mask + x);;
                v_mask = ~(v_mask == v_0);
                v_float32x4 v_src = v_load(src + x);
                v_src = v_src & v_reinterpret_as_f32(v_mask);
                v_float64x2 v_src0 = v_cvt_f64(v_src);
                v_float64x2 v_src1 = v_cvt_f64_high(v_src);
                v_src0 = v_src0 * v_src0;
                v_src1 = v_src1 * v_src1;

                v_store(dst + x, v_load(dst + x) + v_src0);
                v_store(dst + x + 2, v_load(dst + x + 2) + v_src1);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask = v_load_expand_q(mask + x);
                v_mask = ~(v_mask == v_0);

                v_float32x4 v_src0, v_src1, v_src2;
                v_load_deinterleave(src + x * cn, v_src0, v_src1, v_src2);
                v_src0 = v_src0 & v_reinterpret_as_f32(v_mask);
                v_src1 = v_src1 & v_reinterpret_as_f32(v_mask);
                v_src2 = v_src2 & v_reinterpret_as_f32(v_mask);

                v_float64x2 v_src00 = v_cvt_f64(v_src0);
                v_float64x2 v_src01 = v_cvt_f64_high(v_src0);
                v_float64x2 v_src10 = v_cvt_f64(v_src1);
                v_float64x2 v_src11 = v_cvt_f64_high(v_src1);
                v_float64x2 v_src20 = v_cvt_f64(v_src2);
                v_float64x2 v_src21 = v_cvt_f64_high(v_src2);
                v_src00 = v_src00 * v_src00;
                v_src01 = v_src01 * v_src01;
                v_src10 = v_src10 * v_src10;
                v_src11 = v_src11 * v_src11;
                v_src20 = v_src20 * v_src20;
                v_src21 = v_src21 * v_src21;

                v_float64x2 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    accSqr_general_(src, dst, mask, len, cn, x);
}

void accSqr_simd_(const double* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float64x2 v_src0 = v_load(src + x);
            v_float64x2 v_src1 = v_load(src + x + 2);
            v_src0 = v_src0 * v_src0;
            v_src1 = v_src1 * v_src1;

            v_store(dst + x, v_load(dst + x) + v_src0);
            v_store(dst + x + 2, v_load(dst + x + 2) + v_src1);
        }
    }
    else
    {
        v_uint64x2 v_0 = v_setzero_u64();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_mask32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));
                v_float64x2 v_src0 = v_load(src + x);
                v_float64x2 v_src1 = v_load(src + x + 2);
                v_src0 = v_src0 & v_mask0;
                v_src1 = v_src1 & v_mask1;
                v_src0 = v_src0 * v_src0;
                v_src1 = v_src1 * v_src1;

                v_store(dst + x, v_load(dst + x) + v_src0);
                v_store(dst + x + 2, v_load(dst + x + 2) + v_src1);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_mask32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));

                v_float64x2 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_load_deinterleave(src + x * cn, v_src00, v_src10, v_src20);
                v_load_deinterleave(src + (x + 2) * cn, v_src01, v_src11, v_src21);
                v_src00 = v_src00 & v_mask0;
                v_src01 = v_src01 & v_mask1;
                v_src10 = v_src10 & v_mask0;
                v_src11 = v_src11 & v_mask1;
                v_src20 = v_src20 & v_mask0;
                v_src21 = v_src21 & v_mask1;
                v_src00 = v_src00 * v_src00;
                v_src01 = v_src01 * v_src01;
                v_src10 = v_src10 * v_src10;
                v_src11 = v_src11 * v_src11;
                v_src20 = v_src20 * v_src20;
                v_src21 = v_src21 * v_src21;

                v_float64x2 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    accSqr_general_(src, dst, mask, len, cn, x);
}
#else
void accSqr_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn)
{
    accSqr_general_(src, dst, mask, len, cn, 0);
}

void accSqr_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn)
{
    accSqr_general_(src, dst, mask, len, cn, 0);
}

void accSqr_simd_(const float* src, double* dst, const uchar* mask, int len, int cn)
{
    accSqr_general_(src, dst, mask, len, cn, 0);
}

void accSqr_simd_(const double* src, double* dst, const uchar* mask, int len, int cn)
{
    accSqr_general_(src, dst, mask, len, cn, 0);
}
#endif

// product accumulate optimized by universal intrinsic
#if CV_VSX
#pragma GCC push_options
#pragma GCC target("cpu=power8")
#pragma GCC target("tune=power8")
#endif
void accProd_simd_(const uchar* src1, const uchar* src2, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 16;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint8x16 v_1src = v_load(src1 + x);
            v_uint8x16 v_2src = v_load(src2 + x);

            v_uint16x8 v_1src0, v_1src1, v_2src0, v_2src1;
            v_expand(v_1src, v_1src0, v_1src1);
            v_expand(v_2src, v_2src0, v_2src1);

            v_uint16x8 v_src0, v_src1;
            v_src0 = v_1src0 * v_2src0;
            v_src1 = v_1src1 * v_2src1;

            v_uint32x4 v_src00, v_src01, v_src10, v_src11;
            v_expand(v_src0, v_src00, v_src01);
            v_expand(v_src1, v_src10, v_src11);

            v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src00)));
            v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src01)));
            v_store(dst + x + 8, v_load(dst + x + 8) + v_cvt_f32(v_reinterpret_as_s32(v_src10)));
            v_store(dst + x + 12, v_load(dst + x + 12) + v_cvt_f32(v_reinterpret_as_s32(v_src11)));
        }
    }
    else
    {
        v_uint8x16 v_0 = v_setzero_u8();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint8x16 v_1src = v_load(src1 + x);
                v_uint8x16 v_2src = v_load(src2 + x);
                v_1src = v_1src & v_mask;
                v_2src = v_2src & v_mask;

                v_uint16x8 v_1src0, v_1src1, v_2src0, v_2src1;
                v_expand(v_1src, v_1src0, v_1src1);
                v_expand(v_2src, v_2src0, v_2src1);

                v_uint16x8 v_src0, v_src1;
                v_src0 = v_1src0 * v_2src0;
                v_src1 = v_1src1 * v_2src1;

                v_uint32x4 v_src00, v_src01, v_src10, v_src11;
                v_expand(v_src0, v_src00, v_src01);
                v_expand(v_src1, v_src10, v_src11);

                v_store(dst + x, v_load(dst + x) + v_cvt_f32(v_reinterpret_as_s32(v_src00)));
                v_store(dst + x + 4, v_load(dst + x + 4) + v_cvt_f32(v_reinterpret_as_s32(v_src01)));
                v_store(dst + x + 8, v_load(dst + x + 8) + v_cvt_f32(v_reinterpret_as_s32(v_src10)));
                v_store(dst + x + 12, v_load(dst + x + 12) + v_cvt_f32(v_reinterpret_as_s32(v_src11)));
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint8x16 v_mask = v_load(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint8x16 v_1src0, v_1src1, v_1src2, v_2src0, v_2src1, v_2src2;
                v_load_deinterleave(src1 + x * cn, v_1src0, v_1src1, v_1src2);
                v_load_deinterleave(src2 + x * cn, v_2src0, v_2src1, v_2src2);
                v_1src0 = v_1src0 & v_mask;
                v_1src1 = v_1src1 & v_mask;
                v_1src2 = v_1src2 & v_mask;
                v_2src0 = v_2src0 & v_mask;
                v_2src1 = v_2src1 & v_mask;
                v_2src2 = v_2src2 & v_mask;

                v_uint16x8 v_1src00, v_1src01, v_1src10, v_1src11, v_1src20, v_1src21, v_2src00, v_2src01, v_2src10, v_2src11, v_2src20, v_2src21;
                v_expand(v_1src0, v_1src00, v_1src01);
                v_expand(v_1src1, v_1src10, v_1src11);
                v_expand(v_1src2, v_1src20, v_1src21);
                v_expand(v_2src0, v_2src00, v_2src01);
                v_expand(v_2src1, v_2src10, v_2src11);
                v_expand(v_2src2, v_2src20, v_2src21);

                v_uint16x8 v_src00, v_src01, v_src10, v_src11, v_src20, v_src21;
                v_src00 = v_1src00 * v_2src00;
                v_src01 = v_1src01 * v_2src01;
                v_src10 = v_1src10 * v_2src10;
                v_src11 = v_1src11 * v_2src11;
                v_src20 = v_1src20 * v_2src20;
                v_src21 = v_1src21 * v_2src21;

                v_uint32x4 v_src000, v_src001, v_src002, v_src003, v_src100, v_src101, v_src102, v_src103, v_src200, v_src201, v_src202, v_src203;
                v_expand(v_src00, v_src000, v_src001);
                v_expand(v_src01, v_src002, v_src003);
                v_expand(v_src10, v_src100, v_src101);
                v_expand(v_src11, v_src102, v_src103);
                v_expand(v_src20, v_src200, v_src201);
                v_expand(v_src21, v_src202, v_src203);

                v_float32x4 v_dst000, v_dst001, v_dst002, v_dst003, v_dst100, v_dst101, v_dst102, v_dst103, v_dst200, v_dst201, v_dst202, v_dst203;
                v_load_deinterleave(dst + x * cn, v_dst000, v_dst100, v_dst200);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst001, v_dst101, v_dst201);
                v_load_deinterleave(dst + (x + 8) * cn, v_dst002, v_dst102, v_dst202);
                v_load_deinterleave(dst + (x + 12) * cn, v_dst003, v_dst103, v_dst203);
                v_dst000 = v_dst000 + v_cvt_f32(v_reinterpret_as_s32(v_src000));
                v_dst001 = v_dst001 + v_cvt_f32(v_reinterpret_as_s32(v_src001));
                v_dst002 = v_dst002 + v_cvt_f32(v_reinterpret_as_s32(v_src002));
                v_dst003 = v_dst003 + v_cvt_f32(v_reinterpret_as_s32(v_src003));
                v_dst100 = v_dst100 + v_cvt_f32(v_reinterpret_as_s32(v_src100));
                v_dst101 = v_dst101 + v_cvt_f32(v_reinterpret_as_s32(v_src101));
                v_dst102 = v_dst102 + v_cvt_f32(v_reinterpret_as_s32(v_src102));
                v_dst103 = v_dst103 + v_cvt_f32(v_reinterpret_as_s32(v_src103));
                v_dst200 = v_dst200 + v_cvt_f32(v_reinterpret_as_s32(v_src200));
                v_dst201 = v_dst201 + v_cvt_f32(v_reinterpret_as_s32(v_src201));
                v_dst202 = v_dst202 + v_cvt_f32(v_reinterpret_as_s32(v_src202));
                v_dst203 = v_dst203 + v_cvt_f32(v_reinterpret_as_s32(v_src203));

                v_store_interleave(dst + x * cn, v_dst000, v_dst100, v_dst200);
                v_store_interleave(dst + (x + 4) * cn, v_dst001, v_dst101, v_dst201);
                v_store_interleave(dst + (x + 8) * cn, v_dst002, v_dst102, v_dst202);
                v_store_interleave(dst + (x + 12) * cn, v_dst003, v_dst103, v_dst203);
            }
        }
    }

    accProd_general_(src1, src2, dst, mask, len, cn, x);
}
#if CV_VSX
#pragma GCC pop_options
#endif

void accProd_simd_(const ushort* src1, const ushort* src2, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_1src = v_load(src1 + x);
            v_uint16x8 v_2src = v_load(src2 + x);

            v_uint32x4 v_1src0, v_1src1, v_2src0, v_2src1;
            v_expand(v_1src, v_1src0, v_1src1);
            v_expand(v_2src, v_2src0, v_2src1);

            v_float32x4 v_1float0 = v_cvt_f32(v_reinterpret_as_s32(v_1src0));
            v_float32x4 v_1float1 = v_cvt_f32(v_reinterpret_as_s32(v_1src1));
            v_float32x4 v_2float0 = v_cvt_f32(v_reinterpret_as_s32(v_2src0));
            v_float32x4 v_2float1 = v_cvt_f32(v_reinterpret_as_s32(v_2src1));

            v_float32x4 v_src0 = v_1float0 * v_2float0;
            v_float32x4 v_src1 = v_1float1 * v_2float1;

            v_store(dst + x, v_load(dst + x) + v_src0);
            v_store(dst + x + 4, v_load(dst + x + 4) + v_src1);
        }
    }
    else
    {
        v_uint16x8 v_0 = v_setzero_u16();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_0 == v_mask);

                v_uint16x8 v_1src = v_load(src1 + x) & v_mask;
                v_uint16x8 v_2src = v_load(src2 + x) & v_mask;

                v_uint32x4 v_1src0, v_1src1, v_2src0, v_2src1;
                v_expand(v_1src, v_1src0, v_1src1);
                v_expand(v_2src, v_2src0, v_2src1);

                v_float32x4 v_1float0 = v_cvt_f32(v_reinterpret_as_s32(v_1src0));
                v_float32x4 v_1float1 = v_cvt_f32(v_reinterpret_as_s32(v_1src1));
                v_float32x4 v_2float0 = v_cvt_f32(v_reinterpret_as_s32(v_2src0));
                v_float32x4 v_2float1 = v_cvt_f32(v_reinterpret_as_s32(v_2src1));

                v_float32x4 v_src0 = v_1float0 * v_2float0;
                v_float32x4 v_src1 = v_1float1 * v_2float1;

                v_store(dst + x, v_load(dst + x) + v_src0);
                v_store(dst + x + 4, v_load(dst + x + 4) + v_src1);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_0 == v_mask);

                v_uint16x8 v_1src0, v_1src1, v_1src2, v_2src0, v_2src1, v_2src2;
                v_load_deinterleave(src1 + x * cn, v_1src0, v_1src1, v_1src2);
                v_load_deinterleave(src2 + x * cn, v_2src0, v_2src1, v_2src2);
                v_1src0 = v_1src0 & v_mask;
                v_1src1 = v_1src1 & v_mask;
                v_1src2 = v_1src2 & v_mask;
                v_2src0 = v_2src0 & v_mask;
                v_2src1 = v_2src1 & v_mask;
                v_2src2 = v_2src2 & v_mask;

                v_uint32x4 v_1src00, v_1src01, v_1src10, v_1src11, v_1src20, v_1src21, v_2src00, v_2src01, v_2src10, v_2src11, v_2src20, v_2src21;
                v_expand(v_1src0, v_1src00, v_1src01);
                v_expand(v_1src1, v_1src10, v_1src11);
                v_expand(v_1src2, v_1src20, v_1src21);
                v_expand(v_2src0, v_2src00, v_2src01);
                v_expand(v_2src1, v_2src10, v_2src11);
                v_expand(v_2src2, v_2src20, v_2src21);

                v_float32x4 v_1float00 = v_cvt_f32(v_reinterpret_as_s32(v_1src00));
                v_float32x4 v_1float01 = v_cvt_f32(v_reinterpret_as_s32(v_1src01));
                v_float32x4 v_1float10 = v_cvt_f32(v_reinterpret_as_s32(v_1src10));
                v_float32x4 v_1float11 = v_cvt_f32(v_reinterpret_as_s32(v_1src11));
                v_float32x4 v_1float20 = v_cvt_f32(v_reinterpret_as_s32(v_1src20));
                v_float32x4 v_1float21 = v_cvt_f32(v_reinterpret_as_s32(v_1src21));
                v_float32x4 v_2float00 = v_cvt_f32(v_reinterpret_as_s32(v_2src00));
                v_float32x4 v_2float01 = v_cvt_f32(v_reinterpret_as_s32(v_2src01));
                v_float32x4 v_2float10 = v_cvt_f32(v_reinterpret_as_s32(v_2src10));
                v_float32x4 v_2float11 = v_cvt_f32(v_reinterpret_as_s32(v_2src11));
                v_float32x4 v_2float20 = v_cvt_f32(v_reinterpret_as_s32(v_2src20));
                v_float32x4 v_2float21 = v_cvt_f32(v_reinterpret_as_s32(v_2src21));

                v_float32x4 v_src00 = v_1float00 * v_2float00;
                v_float32x4 v_src01 = v_1float01 * v_2float01;
                v_float32x4 v_src10 = v_1float10 * v_2float10;
                v_float32x4 v_src11 = v_1float11 * v_2float11;
                v_float32x4 v_src20 = v_1float20 * v_2float20;
                v_float32x4 v_src21 = v_1float21 * v_2float21;

                v_float32x4 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 4) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    accProd_general_(src1, src2, dst, mask, len, cn, x);
}

void accProd_simd_(const float* src1, const float* src2, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_store(dst + x, v_load(dst + x) + v_load(src1 + x) * v_load(src2 + x));
            v_store(dst + x + 4, v_load(dst + x + 4) + v_load(src1 + x + 4) * v_load(src2 + x + 4));
        }
    }
    else
    {
        v_uint32x4 v_0 = v_setzero_u32();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask32_0 = v_load_expand_q(mask + x);
                v_uint32x4 v_mask32_1 = v_load_expand_q(mask + x + 4);
                v_float32x4 v_mask0 = v_reinterpret_as_f32(~(v_mask32_0 == v_0));
                v_float32x4 v_mask1 = v_reinterpret_as_f32(~(v_mask32_1 == v_0));

                v_store(dst + x, v_load(dst + x) + ((v_load(src1 + x) * v_load(src2 + x)) & v_mask0));
                v_store(dst + x + 4, v_load(dst + x + 4) + ((v_load(src1 + x + 4) * v_load(src2 + x + 4)) & v_mask1));
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask32_0 = v_load_expand_q(mask + x);
                v_uint32x4 v_mask32_1 = v_load_expand_q(mask + x + 4);
                v_float32x4 v_mask0 = v_reinterpret_as_f32(~(v_mask32_0 == v_0));
                v_float32x4 v_mask1 = v_reinterpret_as_f32(~(v_mask32_1 == v_0));

                v_float32x4 v_1src00, v_1src01, v_1src10, v_1src11, v_1src20, v_1src21;
                v_float32x4 v_2src00, v_2src01, v_2src10, v_2src11, v_2src20, v_2src21;
                v_load_deinterleave(src1 + x * cn, v_1src00, v_1src10, v_1src20);
                v_load_deinterleave(src2 + x * cn, v_2src00, v_2src10, v_2src20);
                v_load_deinterleave(src1 + (x + 4) * cn, v_1src01, v_1src11, v_1src21);
                v_load_deinterleave(src2 + (x + 4) * cn, v_2src01, v_2src11, v_2src21);

                v_float32x4 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + ((v_1src00 * v_2src00) & v_mask0), v_dst10 + ((v_1src10 * v_2src10) & v_mask0), v_dst20 + ((v_1src20 * v_2src20) & v_mask0));
                v_store_interleave(dst + (x + 4) * cn, v_dst01 + ((v_1src01 * v_2src01) & v_mask1), v_dst11 + ((v_1src11 * v_2src11) & v_mask1), v_dst21 + ((v_1src21 * v_2src21) & v_mask1));
            }
        }
    }

    accProd_general_(src1, src2, dst, mask, len, cn, x);
}
#if CV_SIMD128_64F
void accProd_simd_(const uchar* src1, const uchar* src2, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_1int  = v_load_expand(src1 + x);
            v_uint16x8 v_2int  = v_load_expand(src2 + x);

            v_uint32x4 v_1int_0, v_1int_1, v_2int_0, v_2int_1;
            v_expand(v_1int, v_1int_0, v_1int_1);
            v_expand(v_2int, v_2int_0, v_2int_1);

            v_int32x4 v_1int0 = v_reinterpret_as_s32(v_1int_0);
            v_int32x4 v_1int1 = v_reinterpret_as_s32(v_1int_1);
            v_int32x4 v_2int0 = v_reinterpret_as_s32(v_2int_0);
            v_int32x4 v_2int1 = v_reinterpret_as_s32(v_2int_1);

            v_float64x2 v_src0 = v_cvt_f64(v_1int0) * v_cvt_f64(v_2int0);
            v_float64x2 v_src1 = v_cvt_f64_high(v_1int0) * v_cvt_f64_high(v_2int0);
            v_float64x2 v_src2 = v_cvt_f64(v_1int1) * v_cvt_f64(v_2int1);
            v_float64x2 v_src3 = v_cvt_f64_high(v_1int1) * v_cvt_f64_high(v_2int1);

            v_float64x2 v_dst0 = v_load(dst + x);
            v_float64x2 v_dst1 = v_load(dst + x + 2);
            v_float64x2 v_dst2 = v_load(dst + x + 4);
            v_float64x2 v_dst3 = v_load(dst + x + 6);

            v_dst0 += v_src0;
            v_dst1 += v_src1;
            v_dst2 += v_src2;
            v_dst3 += v_src3;

            v_store(dst + x, v_dst0);
            v_store(dst + x + 2, v_dst1);
            v_store(dst + x + 4, v_dst2);
            v_store(dst + x + 6, v_dst3);
        }
    }
    else
    {
        v_uint16x8 v_0 = v_setzero_u16();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_1int = v_load_expand(src1 + x) & v_mask;
                v_uint16x8 v_2int = v_load_expand(src2 + x) & v_mask;

                v_uint32x4 v_1int_0, v_1int_1, v_2int_0, v_2int_1;
                v_expand(v_1int, v_1int_0, v_1int_1);
                v_expand(v_2int, v_2int_0, v_2int_1);

                v_int32x4 v_1int0 = v_reinterpret_as_s32(v_1int_0);
                v_int32x4 v_1int1 = v_reinterpret_as_s32(v_1int_1);
                v_int32x4 v_2int0 = v_reinterpret_as_s32(v_2int_0);
                v_int32x4 v_2int1 = v_reinterpret_as_s32(v_2int_1);

                v_float64x2 v_src0 = v_cvt_f64(v_1int0) * v_cvt_f64(v_2int0);
                v_float64x2 v_src1 = v_cvt_f64_high(v_1int0) * v_cvt_f64_high(v_2int0);
                v_float64x2 v_src2 = v_cvt_f64(v_1int1) * v_cvt_f64(v_2int1);
                v_float64x2 v_src3 = v_cvt_f64_high(v_1int1) * v_cvt_f64_high(v_2int1);

                v_float64x2 v_dst0 = v_load(dst + x);
                v_float64x2 v_dst1 = v_load(dst + x + 2);
                v_float64x2 v_dst2 = v_load(dst + x + 4);
                v_float64x2 v_dst3 = v_load(dst + x + 6);

                v_dst0 += v_src0;
                v_dst1 += v_src1;
                v_dst2 += v_src2;
                v_dst3 += v_src3;

                v_store(dst + x, v_dst0);
                v_store(dst + x + 2, v_dst1);
                v_store(dst + x + 4, v_dst2);
                v_store(dst + x + 6, v_dst3);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - /*cVectorWidth*/16; x += cVectorWidth)
            {
                v_uint8x16 v_1src0, v_1src1, v_1src2, v_2src0, v_2src1, v_2src2;
                v_load_deinterleave(src1 + x * cn, v_1src0, v_1src1, v_1src2);
                v_load_deinterleave(src2 + x * cn, v_2src0, v_2src1, v_2src2);

                v_uint16x8 v_1int0, v_1int1, v_1int2, v_2int0, v_2int1, v_2int2, dummy;
                v_expand(v_1src0, v_1int0, dummy);
                v_expand(v_1src1, v_1int1, dummy);
                v_expand(v_1src2, v_1int2, dummy);
                v_expand(v_2src0, v_2int0, dummy);
                v_expand(v_2src1, v_2int1, dummy);
                v_expand(v_2src2, v_2int2, dummy);

                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_1int0 = v_1int0 & v_mask;
                v_1int1 = v_1int1 & v_mask;
                v_1int2 = v_1int2 & v_mask;
                v_2int0 = v_2int0 & v_mask;
                v_2int1 = v_2int1 & v_mask;
                v_2int2 = v_2int2 & v_mask;

                v_uint32x4 v_1int00, v_1int01, v_1int10, v_1int11, v_1int20, v_1int21;
                v_uint32x4 v_2int00, v_2int01, v_2int10, v_2int11, v_2int20, v_2int21;
                v_expand(v_1int0, v_1int00, v_1int01);
                v_expand(v_1int1, v_1int10, v_1int11);
                v_expand(v_1int2, v_1int20, v_1int21);
                v_expand(v_2int0, v_2int00, v_2int01);
                v_expand(v_2int1, v_2int10, v_2int11);
                v_expand(v_2int2, v_2int20, v_2int21);

                v_float64x2 v_src00 = v_cvt_f64(v_reinterpret_as_s32(v_1int00)) * v_cvt_f64(v_reinterpret_as_s32(v_2int00));
                v_float64x2 v_src01 = v_cvt_f64_high(v_reinterpret_as_s32(v_1int00)) * v_cvt_f64_high(v_reinterpret_as_s32(v_2int00));
                v_float64x2 v_src02 = v_cvt_f64(v_reinterpret_as_s32(v_1int01)) * v_cvt_f64(v_reinterpret_as_s32(v_2int01));
                v_float64x2 v_src03 = v_cvt_f64_high(v_reinterpret_as_s32(v_1int01)) * v_cvt_f64_high(v_reinterpret_as_s32(v_2int01));
                v_float64x2 v_src10 = v_cvt_f64(v_reinterpret_as_s32(v_1int10)) * v_cvt_f64(v_reinterpret_as_s32(v_2int10));
                v_float64x2 v_src11 = v_cvt_f64_high(v_reinterpret_as_s32(v_1int10)) * v_cvt_f64_high(v_reinterpret_as_s32(v_2int10));
                v_float64x2 v_src12 = v_cvt_f64(v_reinterpret_as_s32(v_1int11)) * v_cvt_f64(v_reinterpret_as_s32(v_2int11));
                v_float64x2 v_src13 = v_cvt_f64_high(v_reinterpret_as_s32(v_1int11)) * v_cvt_f64_high(v_reinterpret_as_s32(v_2int11));
                v_float64x2 v_src20 = v_cvt_f64(v_reinterpret_as_s32(v_1int20)) * v_cvt_f64(v_reinterpret_as_s32(v_2int20));
                v_float64x2 v_src21 = v_cvt_f64_high(v_reinterpret_as_s32(v_1int20)) * v_cvt_f64_high(v_reinterpret_as_s32(v_2int20));
                v_float64x2 v_src22 = v_cvt_f64(v_reinterpret_as_s32(v_1int21)) * v_cvt_f64(v_reinterpret_as_s32(v_2int21));
                v_float64x2 v_src23 = v_cvt_f64_high(v_reinterpret_as_s32(v_1int21)) * v_cvt_f64_high(v_reinterpret_as_s32(v_2int21));

                v_float64x2 v_dst00, v_dst01, v_dst02, v_dst03, v_dst10, v_dst11, v_dst12, v_dst13, v_dst20, v_dst21, v_dst22, v_dst23;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst02, v_dst12, v_dst22);
                v_load_deinterleave(dst + (x + 6) * cn, v_dst03, v_dst13, v_dst23);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
                v_store_interleave(dst + (x + 4) * cn, v_dst02 + v_src02, v_dst12 + v_src12, v_dst22 + v_src22);
                v_store_interleave(dst + (x + 6) * cn, v_dst03 + v_src03, v_dst13 + v_src13, v_dst23 + v_src23);
            }
        }
    }

    accProd_general_(src1, src2, dst, mask, len, cn, x);
}

void accProd_simd_(const ushort* src1, const ushort* src2, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_1src  = v_load(src1 + x);
            v_uint16x8 v_2src  = v_load(src2 + x);

            v_uint32x4 v_1int_0, v_1int_1, v_2int_0, v_2int_1;
            v_expand(v_1src, v_1int_0, v_1int_1);
            v_expand(v_2src, v_2int_0, v_2int_1);

            v_int32x4 v_1int0 = v_reinterpret_as_s32(v_1int_0);
            v_int32x4 v_1int1 = v_reinterpret_as_s32(v_1int_1);
            v_int32x4 v_2int0 = v_reinterpret_as_s32(v_2int_0);
            v_int32x4 v_2int1 = v_reinterpret_as_s32(v_2int_1);

            v_float64x2 v_src0 = v_cvt_f64(v_1int0) * v_cvt_f64(v_2int0);
            v_float64x2 v_src1 = v_cvt_f64_high(v_1int0) * v_cvt_f64_high(v_2int0);
            v_float64x2 v_src2 = v_cvt_f64(v_1int1) * v_cvt_f64(v_2int1);
            v_float64x2 v_src3 = v_cvt_f64_high(v_1int1) * v_cvt_f64_high(v_2int1);

            v_float64x2 v_dst0 = v_load(dst + x);
            v_float64x2 v_dst1 = v_load(dst + x + 2);
            v_float64x2 v_dst2 = v_load(dst + x + 4);
            v_float64x2 v_dst3 = v_load(dst + x + 6);

            v_dst0 = v_dst0 + v_src0;
            v_dst1 = v_dst1 + v_src1;
            v_dst2 = v_dst2 + v_src2;
            v_dst3 = v_dst3 + v_src3;
            v_store(dst + x, v_dst0);
            v_store(dst + x + 2, v_dst1);
            v_store(dst + x + 4, v_dst2);
            v_store(dst + x + 6, v_dst3);
        }
    }
    else
    {
        v_uint16x8 v_0 = v_setzero_u16();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_1src = v_load(src1 + x);
                v_uint16x8 v_2src = v_load(src2 + x);
                v_1src = v_1src & v_mask;
                v_2src = v_2src & v_mask;

                v_uint32x4 v_1int_0, v_1int_1, v_2int_0, v_2int_1;
                v_expand(v_1src, v_1int_0, v_1int_1);
                v_expand(v_2src, v_2int_0, v_2int_1);

                v_int32x4 v_1int0 = v_reinterpret_as_s32(v_1int_0);
                v_int32x4 v_1int1 = v_reinterpret_as_s32(v_1int_1);
                v_int32x4 v_2int0 = v_reinterpret_as_s32(v_2int_0);
                v_int32x4 v_2int1 = v_reinterpret_as_s32(v_2int_1);

                v_float64x2 v_src0 = v_cvt_f64(v_1int0) * v_cvt_f64(v_2int0);
                v_float64x2 v_src1 = v_cvt_f64_high(v_1int0) * v_cvt_f64_high(v_2int0);
                v_float64x2 v_src2 = v_cvt_f64(v_1int1) * v_cvt_f64(v_2int1);
                v_float64x2 v_src3 = v_cvt_f64_high(v_1int1) * v_cvt_f64_high(v_2int1);

                v_float64x2 v_dst0 = v_load(dst + x);
                v_float64x2 v_dst1 = v_load(dst + x + 2);
                v_float64x2 v_dst2 = v_load(dst + x + 4);
                v_float64x2 v_dst3 = v_load(dst + x + 6);

                v_dst0 = v_dst0 + v_src0;
                v_dst1 = v_dst1 + v_src1;
                v_dst2 = v_dst2 + v_src2;
                v_dst3 = v_dst3 + v_src3;
                v_store(dst + x, v_dst0);
                v_store(dst + x + 2, v_dst1);
                v_store(dst + x + 4, v_dst2);
                v_store(dst + x + 6, v_dst3);
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint16x8 v_mask = v_load_expand(mask + x);
                v_mask = ~(v_mask == v_0);
                v_uint16x8 v_1src0, v_1src1, v_1src2, v_2src0, v_2src1, v_2src2;
                v_load_deinterleave(src1 + x * cn, v_1src0, v_1src1, v_1src2);
                v_load_deinterleave(src2 + x * cn, v_2src0, v_2src1, v_2src2);
                v_1src0 = v_1src0 & v_mask;
                v_1src1 = v_1src1 & v_mask;
                v_1src2 = v_1src2 & v_mask;
                v_2src0 = v_2src0 & v_mask;
                v_2src1 = v_2src1 & v_mask;
                v_2src2 = v_2src2 & v_mask;

                v_uint32x4 v_1int_00, v_1int_01, v_2int_00, v_2int_01;
                v_uint32x4 v_1int_10, v_1int_11, v_2int_10, v_2int_11;
                v_uint32x4 v_1int_20, v_1int_21, v_2int_20, v_2int_21;
                v_expand(v_1src0, v_1int_00, v_1int_01);
                v_expand(v_1src1, v_1int_10, v_1int_11);
                v_expand(v_1src2, v_1int_20, v_1int_21);
                v_expand(v_2src0, v_2int_00, v_2int_01);
                v_expand(v_2src1, v_2int_10, v_2int_11);
                v_expand(v_2src2, v_2int_20, v_2int_21);

                v_int32x4 v_1int00 = v_reinterpret_as_s32(v_1int_00);
                v_int32x4 v_1int01 = v_reinterpret_as_s32(v_1int_01);
                v_int32x4 v_1int10 = v_reinterpret_as_s32(v_1int_10);
                v_int32x4 v_1int11 = v_reinterpret_as_s32(v_1int_11);
                v_int32x4 v_1int20 = v_reinterpret_as_s32(v_1int_20);
                v_int32x4 v_1int21 = v_reinterpret_as_s32(v_1int_21);
                v_int32x4 v_2int00 = v_reinterpret_as_s32(v_2int_00);
                v_int32x4 v_2int01 = v_reinterpret_as_s32(v_2int_01);
                v_int32x4 v_2int10 = v_reinterpret_as_s32(v_2int_10);
                v_int32x4 v_2int11 = v_reinterpret_as_s32(v_2int_11);
                v_int32x4 v_2int20 = v_reinterpret_as_s32(v_2int_20);
                v_int32x4 v_2int21 = v_reinterpret_as_s32(v_2int_21);

                v_float64x2 v_src00 = v_cvt_f64(v_1int00) * v_cvt_f64(v_2int00);
                v_float64x2 v_src01 = v_cvt_f64_high(v_1int00) * v_cvt_f64_high(v_2int00);
                v_float64x2 v_src02 = v_cvt_f64(v_1int01) * v_cvt_f64(v_2int01);
                v_float64x2 v_src03 = v_cvt_f64_high(v_1int01) * v_cvt_f64_high(v_2int01);
                v_float64x2 v_src10 = v_cvt_f64(v_1int10) * v_cvt_f64(v_2int10);
                v_float64x2 v_src11 = v_cvt_f64_high(v_1int10) * v_cvt_f64_high(v_2int10);
                v_float64x2 v_src12 = v_cvt_f64(v_1int11) * v_cvt_f64(v_2int11);
                v_float64x2 v_src13 = v_cvt_f64_high(v_1int11) * v_cvt_f64_high(v_2int11);
                v_float64x2 v_src20 = v_cvt_f64(v_1int20) * v_cvt_f64(v_2int20);
                v_float64x2 v_src21 = v_cvt_f64_high(v_1int20) * v_cvt_f64_high(v_2int20);
                v_float64x2 v_src22 = v_cvt_f64(v_1int21) * v_cvt_f64(v_2int21);
                v_float64x2 v_src23 = v_cvt_f64_high(v_1int21) * v_cvt_f64_high(v_2int21);

                v_float64x2 v_dst00, v_dst01, v_dst02, v_dst03;
                v_float64x2 v_dst10, v_dst11, v_dst12, v_dst13;
                v_float64x2 v_dst20, v_dst21, v_dst22, v_dst23;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);
                v_load_deinterleave(dst + (x + 4) * cn, v_dst02, v_dst12, v_dst22);
                v_load_deinterleave(dst + (x + 6) * cn, v_dst03, v_dst13, v_dst23);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
                v_store_interleave(dst + (x + 4) * cn, v_dst02 + v_src02, v_dst12 + v_src12, v_dst22 + v_src22);
                v_store_interleave(dst + (x + 6) * cn, v_dst03 + v_src03, v_dst13 + v_src13, v_dst23 + v_src23);
            }
        }
    }

    accProd_general_(src1, src2, dst, mask, len, cn, x);
}

void accProd_simd_(const float* src1, const float* src2, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float32x4 v_1src  = v_load(src1 + x);
            v_float32x4 v_2src  = v_load(src2 + x);

            v_float64x2 v_1src0 = v_cvt_f64(v_1src);
            v_float64x2 v_1src1 = v_cvt_f64_high(v_1src);
            v_float64x2 v_2src0 = v_cvt_f64(v_2src);
            v_float64x2 v_2src1 = v_cvt_f64_high(v_2src);

            v_store(dst + x, v_load(dst + x) + (v_1src0 * v_2src0));
            v_store(dst + x + 2, v_load(dst + x + 2) + (v_1src1 * v_2src1));
        }
    }
    else
    {
        v_uint32x4 v_0 = v_setzero_u32();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask = v_load_expand_q(mask + x);
                v_mask = ~(v_mask == v_0);
                v_float32x4 v_1src = v_load(src1 + x);
                v_float32x4 v_2src = v_load(src2 + x);
                v_1src = v_1src & v_reinterpret_as_f32(v_mask);
                v_2src = v_2src & v_reinterpret_as_f32(v_mask);

                v_float64x2 v_1src0 = v_cvt_f64(v_1src);
                v_float64x2 v_1src1 = v_cvt_f64_high(v_1src);
                v_float64x2 v_2src0 = v_cvt_f64(v_2src);
                v_float64x2 v_2src1 = v_cvt_f64_high(v_2src);

                v_store(dst + x, v_load(dst + x) + (v_1src0 * v_2src0));
                v_store(dst + x + 2, v_load(dst + x + 2) + (v_1src1 * v_2src1));
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask = v_load_expand_q(mask + x);
                v_mask = ~(v_mask == v_0);
                v_float32x4 v_1src0, v_1src1, v_1src2, v_2src0, v_2src1, v_2src2;
                v_load_deinterleave(src1 + x * cn, v_1src0, v_1src1, v_1src2);
                v_load_deinterleave(src2 + x * cn, v_2src0, v_2src1, v_2src2);
                v_1src0 = v_1src0 & v_reinterpret_as_f32(v_mask);
                v_1src1 = v_1src1 & v_reinterpret_as_f32(v_mask);
                v_1src2 = v_1src2 & v_reinterpret_as_f32(v_mask);
                v_2src0 = v_2src0 & v_reinterpret_as_f32(v_mask);
                v_2src1 = v_2src1 & v_reinterpret_as_f32(v_mask);
                v_2src2 = v_2src2 & v_reinterpret_as_f32(v_mask);

                v_float64x2 v_src00 = v_cvt_f64(v_1src0) * v_cvt_f64(v_2src0);
                v_float64x2 v_src01 = v_cvt_f64_high(v_1src0) * v_cvt_f64_high(v_2src0);
                v_float64x2 v_src10 = v_cvt_f64(v_1src1) * v_cvt_f64(v_2src1);
                v_float64x2 v_src11 = v_cvt_f64_high(v_1src1) * v_cvt_f64_high(v_2src1);
                v_float64x2 v_src20 = v_cvt_f64(v_1src2) * v_cvt_f64(v_2src2);
                v_float64x2 v_src21 = v_cvt_f64_high(v_1src2) * v_cvt_f64_high(v_2src2);

                v_float64x2 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    accProd_general_(src1, src2, dst, mask, len, cn, x);
}

void accProd_simd_(const double* src1, const double* src2, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float64x2 v_src00 = v_load(src1 + x);
            v_float64x2 v_src01 = v_load(src1 + x + 2);
            v_float64x2 v_src10 = v_load(src2 + x);
            v_float64x2 v_src11 = v_load(src2 + x + 2);

            v_store(dst + x, v_load(dst + x) + (v_src00 * v_src10));
            v_store(dst + x + 2, v_load(dst + x + 2) + (v_src01 * v_src11));
        }
    }
    else
    {
        v_uint64x2 v_0 = v_setzero_u64();
        if (cn == 1)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_mask32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));

                v_float64x2 v_src00 = v_load(src1 + x);
                v_float64x2 v_src01 = v_load(src1 + x + 2);
                v_float64x2 v_src10 = v_load(src2 + x);
                v_float64x2 v_src11 = v_load(src2 + x + 2);

                v_store(dst + x, v_load(dst + x) + ((v_src00 * v_src10) & v_mask0));
                v_store(dst + x + 2, v_load(dst + x + 2) + ((v_src01 * v_src11) & v_mask1));
            }
        }
        else if (cn == 3)
        {
            for (; x <= len - cVectorWidth; x += cVectorWidth)
            {
                v_uint32x4 v_mask32 = v_load_expand_q(mask + x);
                v_uint64x2 v_masku640, v_masku641;
                v_expand(v_mask32, v_masku640, v_masku641);
                v_float64x2 v_mask0 = v_reinterpret_as_f64(~(v_masku640 == v_0));
                v_float64x2 v_mask1 = v_reinterpret_as_f64(~(v_masku641 == v_0));

                v_float64x2 v_1src00, v_1src01, v_1src10, v_1src11, v_1src20, v_1src21;
                v_float64x2 v_2src00, v_2src01, v_2src10, v_2src11, v_2src20, v_2src21;
                v_load_deinterleave(src1 + x * cn, v_1src00, v_1src10, v_1src20);
                v_load_deinterleave(src1 + (x + 2) * cn, v_1src01, v_1src11, v_1src21);
                v_load_deinterleave(src2 + x * cn, v_2src00, v_2src10, v_2src20);
                v_load_deinterleave(src2 + (x + 2) * cn, v_2src01, v_2src11, v_2src21);
                v_float64x2 v_src00 = (v_1src00 & v_mask0) * v_2src00;
                v_float64x2 v_src01 = (v_1src01 & v_mask1) * v_2src01;
                v_float64x2 v_src10 = (v_1src10 & v_mask0) * v_2src10;
                v_float64x2 v_src11 = (v_1src11 & v_mask1) * v_2src11;
                v_float64x2 v_src20 = (v_1src20 & v_mask0) * v_2src20;
                v_float64x2 v_src21 = (v_1src21 & v_mask1) * v_2src21;

                v_float64x2 v_dst00, v_dst01, v_dst10, v_dst11, v_dst20, v_dst21;
                v_load_deinterleave(dst + x * cn, v_dst00, v_dst10, v_dst20);
                v_load_deinterleave(dst + (x + 2) * cn, v_dst01, v_dst11, v_dst21);

                v_store_interleave(dst + x * cn, v_dst00 + v_src00, v_dst10 + v_src10, v_dst20 + v_src20);
                v_store_interleave(dst + (x + 2) * cn, v_dst01 + v_src01, v_dst11 + v_src11, v_dst21 + v_src21);
            }
        }
    }

    accProd_general_(src1, src2, dst, mask, len, cn, x);
}
#else
void accProd_simd_(const uchar* src1, const uchar* src2, double* dst, const uchar* mask, int len, int cn)
{
    accProd_general_(src1, src2, dst, mask, len, cn, 0);
}

void accProd_simd_(const ushort* src1, const ushort* src2, double* dst, const uchar* mask, int len, int cn)
{
    accProd_general_(src1, src2, dst, mask, len, cn, 0);
}

void accProd_simd_(const float* src1, const float* src2, double* dst, const uchar* mask, int len, int cn)
{
    accProd_general_(src1, src2, dst, mask, len, cn, 0);
}

void accProd_simd_(const double* src1, const double* src2, double* dst, const uchar* mask, int len, int cn)
{
    accProd_general_(src1, src2, dst, mask, len, cn, 0);
}
#endif

// running weight accumulate optimized by universal intrinsic
void accW_simd_(const uchar* src, float* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const v_float32x4 v_alpha = v_setall_f32((float)alpha);
    const v_float32x4 v_beta = v_setall_f32((float)(1.0f - alpha));
    const int cVectorWidth = 16;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint8x16 v_src = v_load(src + x);

            v_uint16x8 v_src0, v_src1;
            v_expand(v_src, v_src0, v_src1);

            v_uint32x4 v_src00, v_src01, v_src10, v_src11;
            v_expand(v_src0, v_src00, v_src01);
            v_expand(v_src1, v_src10, v_src11);

            v_float32x4 v_dst00 = v_load(dst + x);
            v_float32x4 v_dst01 = v_load(dst + x + 4);
            v_float32x4 v_dst10 = v_load(dst + x + 8);
            v_float32x4 v_dst11 = v_load(dst + x + 12);

            v_dst00 = (v_dst00 * v_beta) + (v_cvt_f32(v_reinterpret_as_s32(v_src00)) * v_alpha);
            v_dst01 = (v_dst01 * v_beta) + (v_cvt_f32(v_reinterpret_as_s32(v_src01)) * v_alpha);
            v_dst10 = (v_dst10 * v_beta) + (v_cvt_f32(v_reinterpret_as_s32(v_src10)) * v_alpha);
            v_dst11 = (v_dst11 * v_beta) + (v_cvt_f32(v_reinterpret_as_s32(v_src11)) * v_alpha);

            v_store(dst + x, v_dst00);
            v_store(dst + x + 4, v_dst01);
            v_store(dst + x + 8, v_dst10);
            v_store(dst + x + 12, v_dst11);
        }
    }

    accW_general_(src, dst, mask, len, cn, alpha, x);
}

void accW_simd_(const ushort* src, float* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const v_float32x4 v_alpha = v_setall_f32((float)alpha);
    const v_float32x4 v_beta = v_setall_f32((float)(1.0f - alpha));
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_src = v_load(src + x);
            v_uint32x4 v_int0, v_int1;
            v_expand(v_src, v_int0, v_int1);

            v_float32x4 v_src0 = v_cvt_f32(v_reinterpret_as_s32(v_int0));
            v_float32x4 v_src1 = v_cvt_f32(v_reinterpret_as_s32(v_int1));
            v_src0 = v_src0 * v_alpha;
            v_src1 = v_src1 * v_alpha;

            v_float32x4 v_dst0 = v_load(dst + x) * v_beta;
            v_float32x4 v_dst1 = v_load(dst + x + 4) * v_beta;

            v_store(dst + x, v_dst0 + v_src0);
            v_store(dst + x + 4, v_dst1 + v_src1);
        }
    }

    accW_general_(src, dst, mask, len, cn, alpha, x);
}

void accW_simd_(const float* src, float* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const v_float32x4 v_alpha = v_setall_f32((float)alpha);
    const v_float32x4 v_beta = v_setall_f32((float)(1.0f - alpha));
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_store(dst + x, ((v_load(dst + x) * v_beta) + (v_load(src + x) * v_alpha)));
            v_store(dst + x + 4, ((v_load(dst + x + 4) * v_beta) + (v_load(src + x + 4) * v_alpha)));
        }
    }

    accW_general_(src, dst, mask, len, cn, alpha, x);
}
#if CV_SIMD128_64F
void accW_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const v_float64x2 v_alpha = v_setall_f64(alpha);
    const v_float64x2 v_beta = v_setall_f64(1.0f - alpha);
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_src16 = v_load_expand(src + x);

            v_uint32x4 v_int_0, v_int_1;
            v_expand(v_src16, v_int_0, v_int_1);

            v_int32x4 v_int0 = v_reinterpret_as_s32(v_int_0);
            v_int32x4 v_int1 = v_reinterpret_as_s32(v_int_1);

            v_float64x2 v_src0 = v_cvt_f64(v_int0);
            v_float64x2 v_src1 = v_cvt_f64_high(v_int0);
            v_float64x2 v_src2 = v_cvt_f64(v_int1);
            v_float64x2 v_src3 = v_cvt_f64_high(v_int1);

            v_float64x2 v_dst0 = v_load(dst + x);
            v_float64x2 v_dst1 = v_load(dst + x + 2);
            v_float64x2 v_dst2 = v_load(dst + x + 4);
            v_float64x2 v_dst3 = v_load(dst + x + 6);

            v_dst0 = (v_dst0 * v_beta) + (v_src0 * v_alpha);
            v_dst1 = (v_dst1 * v_beta) + (v_src1 * v_alpha);
            v_dst2 = (v_dst2 * v_beta) + (v_src2 * v_alpha);
            v_dst3 = (v_dst3 * v_beta) + (v_src3 * v_alpha);

            v_store(dst + x, v_dst0);
            v_store(dst + x + 2, v_dst1);
            v_store(dst + x + 4, v_dst2);
            v_store(dst + x + 6, v_dst3);
        }
    }

    accW_general_(src, dst, mask, len, cn, alpha, x);
}

void accW_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const v_float64x2 v_alpha = v_setall_f64(alpha);
    const v_float64x2 v_beta = v_setall_f64(1.0f - alpha);
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_uint16x8 v_src = v_load(src + x);
            v_uint32x4 v_int_0, v_int_1;
            v_expand(v_src, v_int_0, v_int_1);

            v_int32x4 v_int0 = v_reinterpret_as_s32(v_int_0);
            v_int32x4 v_int1 = v_reinterpret_as_s32(v_int_1);

            v_float64x2 v_src00 = v_cvt_f64(v_int0);
            v_float64x2 v_src01 = v_cvt_f64_high(v_int0);
            v_float64x2 v_src10 = v_cvt_f64(v_int1);
            v_float64x2 v_src11 = v_cvt_f64_high(v_int1);

            v_float64x2 v_dst00 = v_load(dst + x);
            v_float64x2 v_dst01 = v_load(dst + x + 2);
            v_float64x2 v_dst10 = v_load(dst + x + 4);
            v_float64x2 v_dst11 = v_load(dst + x + 6);

            v_dst00 = (v_dst00 * v_beta) + (v_src00 * v_alpha);
            v_dst01 = (v_dst01 * v_beta) + (v_src01 * v_alpha);
            v_dst10 = (v_dst10 * v_beta) + (v_src10 * v_alpha);
            v_dst11 = (v_dst11 * v_beta) + (v_src11 * v_alpha);

            v_store(dst + x, v_dst00);
            v_store(dst + x + 2, v_dst01);
            v_store(dst + x + 4, v_dst10);
            v_store(dst + x + 6, v_dst11);
        }
    }

    accW_general_(src, dst, mask, len, cn, alpha, x);
}

void accW_simd_(const float* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const v_float64x2 v_alpha = v_setall_f64(alpha);
    const v_float64x2 v_beta = v_setall_f64(1.0f - alpha);
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float32x4 v_src0 = v_load(src + x);
            v_float32x4 v_src1 = v_load(src + x + 4);
            v_float64x2 v_src00 = v_cvt_f64(v_src0);
            v_float64x2 v_src01 = v_cvt_f64_high(v_src0);
            v_float64x2 v_src10 = v_cvt_f64(v_src1);
            v_float64x2 v_src11 = v_cvt_f64_high(v_src1);

            v_store(dst + x, ((v_load(dst + x) * v_beta) + (v_src00 * v_alpha)));
            v_store(dst + x + 2, ((v_load(dst + x + 2) * v_beta) + (v_src01 * v_alpha)));
            v_store(dst + x + 4, ((v_load(dst + x + 4) * v_beta) + (v_src10 * v_alpha)));
            v_store(dst + x + 6, ((v_load(dst + x + 6) * v_beta) + (v_src11 * v_alpha)));
        }
    }

    accW_general_(src, dst, mask, len, cn, alpha, x);
}

void accW_simd_(const double* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const v_float64x2 v_alpha = v_setall_f64(alpha);
    const v_float64x2 v_beta = v_setall_f64(1.0f - alpha);
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for (; x <= size - cVectorWidth; x += cVectorWidth)
        {
            v_float64x2 v_src0 = v_load(src + x);
            v_float64x2 v_src1 = v_load(src + x + 2);

            v_store(dst + x, ((v_load(dst + x) * v_beta) + (v_src0 * v_alpha)));
            v_store(dst + x + 2, ((v_load(dst + x + 2) * v_beta) + (v_src1 * v_alpha)));
        }
    }

    accW_general_(src, dst, mask, len, cn, alpha, x);
}
#else
void accW_simd_(const uchar* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    accW_general_(src, dst, mask, len, cn, alpha, 0);
}

void accW_simd_(const ushort* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    accW_general_(src, dst, mask, len, cn, alpha, 0);
}

void accW_simd_(const float* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    accW_general_(src, dst, mask, len, cn, alpha, 0);
}

void accW_simd_(const double* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    accW_general_(src, dst, mask, len, cn, alpha, 0);
}
#endif // CV_SIMD128_64F
#endif // CV_SIMD128
#if CV_AVX
// accumulate optimized by AVX
void acc_avx_32f(const float* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256 v_src = _mm256_loadu_ps(src + x);
            __m256 v_dst = _mm256_loadu_ps(dst + x);
            v_dst = _mm256_add_ps(v_src, v_dst);
            _mm256_storeu_ps(dst + x, v_dst);
        }
        acc_general_(src, dst, mask, len, cn, x);
    }
    else
    {
        acc_simd_(src, dst, mask, len, cn);
    }
}

void acc_avx_32f64f(const float* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256 v_src = _mm256_loadu_ps(src + x);
            __m256d v_src0 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src, 0));
            __m256d v_src1 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src, 1));
            __m256d v_dst0 = _mm256_loadu_pd(dst + x);
            __m256d v_dst1 = _mm256_loadu_pd(dst + x + 4);
            v_dst0 = _mm256_add_pd(v_src0, v_dst0);
            v_dst1 = _mm256_add_pd(v_src1, v_dst1);
            _mm256_storeu_pd(dst + x, v_dst0);
            _mm256_storeu_pd(dst + x + 4, v_dst1);
        }
        acc_general_(src, dst, mask, len, cn, x);
    }
    else
    {
        acc_simd_(src, dst, mask, len, cn);
    }
}

void acc_avx_64f(const double* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256d v_src = _mm256_loadu_pd(src + x);
            __m256d v_dst = _mm256_loadu_pd(dst + x);
            v_dst = _mm256_add_pd(v_dst, v_src);
            _mm256_storeu_pd(dst + x, v_dst);
        }
        acc_general_(src, dst, mask, len, cn, x);
    }
    else
    {
        acc_simd_(src, dst, mask, len, cn);
    }
}

// square accumulate optimized by avx
void accSqr_avx_32f(const float* src, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256 v_src = _mm256_loadu_ps(src + x);
            __m256 v_dst = _mm256_loadu_ps(dst + x);
            v_src = _mm256_mul_ps(v_src, v_src);
            v_dst = _mm256_add_ps(v_src, v_dst);
            _mm256_storeu_ps(dst + x, v_dst);
        }
        accSqr_general_(src, dst, mask, len, cn, x);
    }
    else
    {
        accSqr_simd_(src, dst, mask, len, cn);
    }
}

void accSqr_avx_32f64f(const float* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256 v_src = _mm256_loadu_ps(src + x);
            __m256d v_src0 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src,0));
            __m256d v_src1 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src,1));
            __m256d v_dst0 = _mm256_loadu_pd(dst + x);
            __m256d v_dst1 = _mm256_loadu_pd(dst + x + 4);
            v_src0 = _mm256_mul_pd(v_src0, v_src0);
            v_src1 = _mm256_mul_pd(v_src1, v_src1);
            v_dst0 = _mm256_add_pd(v_src0, v_dst0);
            v_dst1 = _mm256_add_pd(v_src1, v_dst1);
            _mm256_storeu_pd(dst + x, v_dst0);
            _mm256_storeu_pd(dst + x + 4, v_dst1);
        }
        accSqr_general_(src, dst, mask, len, cn, x);
    }
    else
    {
        accSqr_simd_(src, dst, mask, len, cn);
    }
}

void accSqr_avx_64f(const double* src, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256d v_src = _mm256_loadu_pd(src + x);
            __m256d v_dst = _mm256_loadu_pd(dst + x);
            v_src = _mm256_mul_pd(v_src, v_src);
            v_dst = _mm256_add_pd(v_dst, v_src);
            _mm256_storeu_pd(dst + x, v_dst);
        }
        accSqr_general_(src, dst, mask, len, cn, x);
    }
    else
    {
        accSqr_simd_(src, dst, mask, len, cn);
    }
}

// product accumulate optimized by avx
void accProd_avx_32f(const float* src1, const float* src2, float* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256 v_src0 = _mm256_loadu_ps(src1 + x);
            __m256 v_src1 = _mm256_loadu_ps(src2 + x);
            __m256 v_dst = _mm256_loadu_ps(dst + x);
            __m256 v_src = _mm256_mul_ps(v_src0, v_src1);
            v_dst = _mm256_add_ps(v_src, v_dst);
            _mm256_storeu_ps(dst + x, v_dst);
        }
        accProd_general_(src1, src2, dst, mask, len, cn, x);
    }
    else
    {
        accProd_simd_(src1, src2, dst, mask, len, cn);
    }
}

void accProd_avx_32f64f(const float* src1, const float* src2, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256 v_1src = _mm256_loadu_ps(src1 + x);
            __m256 v_2src = _mm256_loadu_ps(src2 + x);
            __m256d v_src00 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_1src,0));
            __m256d v_src01 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_1src,1));
            __m256d v_src10 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_2src,0));
            __m256d v_src11 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_2src,1));
            __m256d v_dst0 = _mm256_loadu_pd(dst + x);
            __m256d v_dst1 = _mm256_loadu_pd(dst + x + 4);
            __m256d v_src0 = _mm256_mul_pd(v_src00, v_src10);
            __m256d v_src1 = _mm256_mul_pd(v_src01, v_src11);
            v_dst0 = _mm256_add_pd(v_src0, v_dst0);
            v_dst1 = _mm256_add_pd(v_src1, v_dst1);
            _mm256_storeu_pd(dst + x, v_dst0);
            _mm256_storeu_pd(dst + x + 4, v_dst1);
        }
        accProd_general_(src1, src2, dst, mask, len, cn, x);
    }
    else
    {
        accProd_simd_(src1, src2, dst, mask, len, cn);
    }
}

void accProd_avx_64f(const double* src1, const double* src2, double* dst, const uchar* mask, int len, int cn)
{
    int x = 0;
    const int cVectorWidth = 4;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256d v_src0 = _mm256_loadu_pd(src1 + x);
            __m256d v_src1 = _mm256_loadu_pd(src2 + x);
            __m256d v_dst = _mm256_loadu_pd(dst + x);
            v_src0 = _mm256_mul_pd(v_src0, v_src1);
            v_dst = _mm256_add_pd(v_dst, v_src0);
            _mm256_storeu_pd(dst + x, v_dst);
        }
        accProd_general_(src1, src2, dst, mask, len, cn, x);
    }
    else
    {
        accProd_simd_(src1, src2, dst, mask, len, cn);
    }
}

// running weight accumulate optimized by avx
void accW_avx_32f(const float* src, float* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const __m256 v_alpha = _mm256_set1_ps((float)alpha);
    const __m256 v_beta = _mm256_set1_ps((float)(1.0f - alpha));
    const int cVectorWidth = 16;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            _mm256_storeu_ps(dst + x, _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(dst + x), v_beta), _mm256_mul_ps(_mm256_loadu_ps(src + x), v_alpha)));
            _mm256_storeu_ps(dst + x + 8, _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(dst + x + 8), v_beta), _mm256_mul_ps(_mm256_loadu_ps(src + x + 8), v_alpha)));
        }
        accW_general_(src, dst, mask, len, cn, alpha, x);
    }
    else
    {
        accW_simd_(src, dst, mask, len, cn, alpha);
    }

}

void accW_avx_32f64f(const float* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const __m256d v_alpha = _mm256_set1_pd(alpha);
    const __m256d v_beta = _mm256_set1_pd(1.0f - alpha);
    const int cVectorWidth = 16;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256 v_src0 = _mm256_loadu_ps(src + x);
            __m256 v_src1 = _mm256_loadu_ps(src + x + 8);
            __m256d v_src00 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src0,0));
            __m256d v_src01 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src0,1));
            __m256d v_src10 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src1,0));
            __m256d v_src11 = _mm256_cvtps_pd(_mm256_extractf128_ps(v_src1,1));

            _mm256_storeu_pd(dst + x, _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(dst + x), v_beta), _mm256_mul_pd(v_src00, v_alpha)));
            _mm256_storeu_pd(dst + x + 4, _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(dst + x + 4), v_beta), _mm256_mul_pd(v_src01, v_alpha)));
            _mm256_storeu_pd(dst + x + 8, _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(dst + x + 8), v_beta), _mm256_mul_pd(v_src10, v_alpha)));
            _mm256_storeu_pd(dst + x + 12, _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(dst + x + 12), v_beta), _mm256_mul_pd(v_src11, v_alpha)));
        }
        accW_general_(src, dst, mask, len, cn, alpha, x);
    }
    else
    {
        accW_simd_(src, dst, mask, len, cn, alpha);
    }
}

void accW_avx_64f(const double* src, double* dst, const uchar* mask, int len, int cn, double alpha)
{
    int x = 0;
    const __m256d v_alpha = _mm256_set1_pd(alpha);
    const __m256d v_beta = _mm256_set1_pd(1.0f - alpha);
    const int cVectorWidth = 8;

    if (!mask)
    {
        int size = len * cn;
        for ( ; x <= size - cVectorWidth ; x += cVectorWidth)
        {
            __m256d v_src0 = _mm256_loadu_pd(src + x);
            __m256d v_src1 = _mm256_loadu_pd(src + x + 4);

            _mm256_storeu_pd(dst + x, _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(dst + x), v_beta), _mm256_mul_pd(v_src0, v_alpha)));
            _mm256_storeu_pd(dst + x + 4, _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(dst + x + 4), v_beta), _mm256_mul_pd(v_src1, v_alpha)));
        }
        accW_general_(src, dst, mask, len, cn, alpha, x);
    }
    else
    {
        accW_simd_(src, dst, mask, len, cn, alpha);
    }
}
#endif
#endif // CV_CPU_OPTIMIZATION_DECLARATIONS_ONLY

CV_CPU_OPTIMIZATION_NAMESPACE_END

} // namespace cv

///* End of file. */

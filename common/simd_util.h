#pragma once
#include <immintrin.h>

__m128d simd_int64_to_double_128(__m128i x){
    x = _mm_add_epi64(x, _mm_castpd_si128(_mm_set1_pd(0x0018000000000000)));
    return _mm_sub_pd(_mm_castsi128_pd(x), _mm_set1_pd(0x0018000000000000));
}

__m128i simd_double_to_int64_128(__m128d x){
    x = _mm_add_pd(x, _mm_set1_pd(0x0018000000000000));
    return _mm_sub_epi64(
        _mm_castpd_si128(x),
        _mm_castpd_si128(_mm_set1_pd(0x0018000000000000))
    );
}

__m256d simd_int64_to_double_256(__m256i x){
    x = _mm256_add_epi64(x, _mm256_castpd_si256(_mm256_set1_pd(0x0018000000000000)));
    return _mm256_sub_pd(_mm256_castsi256_pd(x), _mm256_set1_pd(0x0018000000000000));
}

__m256i simd_double_to_int64_256(__m256d x){
    x = _mm256_add_pd(x, _mm256_set1_pd(0x0018000000000000));
    return _mm256_sub_epi64(
        _mm256_castpd_si256(x),
        _mm256_castpd_si256(_mm256_set1_pd(0x0018000000000000))
    );
}

__m256i simd_div_mulinv(__m256d x, __m256d y, __m256i y_inverse) {
    __m256d dbls = simd_int64_to_double_256(x);
    __m256d mul = _mm256_floor_pd(_mm256_mul_pd(dbls, y_inverse));
    __m256i conv = simd_double_to_int64_256(_mm256_castpd_si256(mul));
    return _mm256_mul_epu32(conv, y);
}

__m256i simd_modulo_mulinv(__m256d x, __m256d y, __m256i y_inverse) {
    __m256d dbls = simd_int64_to_double_256(x);
    __m256d mul = _mm256_floor_pd(_mm256_mul_pd(dbls, y_inverse));
    __m256i conv = simd_double_to_int64_256(_mm256_castpd_si256(mul));
    return _mm256_sub_epi64(x, _mm256_mul_epu32(conv, y));
}

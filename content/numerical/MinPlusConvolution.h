/**
 * Author: Leon van der Waal
 * Source: classic problem
 * Description: computes the vector $c_i = min_{j+k = i} (a_j + b_k)$.
 * Answers are bounded by \verb|oo|. Make sure \verb|2*oo| fits in the 
 * integer limits. If not, change to unsigned integers. Compile with 
 * optimize("O3,unroll-loops") and target("avx2,bmi")
 * Time: O(NM) \text{, arount $0.9$ seconds for $N=M=2\times 10^5$}
 * Status: stresstested
 */
#pragma once

#include <immintrin.h>
typedef __m256i V;
const int oo = 1e9;
const int N = 2e5+1e3; // >64 padding needed
alignas(32) int A[N], B[N], C[N*2];

vi mpconv(vi v, vi w){
    int n = sz(v), m = sz(w),
        M = (m+7)/8, l = n + m - 1;
    if (!n or !m) return {};
    vi ans(l, oo);
    memcpy(B, &w[0], 4*m);
    rep(i,0,40) A[i] = B[i+m] = A[n/8 + i + 32] = oo;
    for(int md = 7; md >= 0; --md){
        int AC = (n + 7 - md)/8;
        rep(i,0,AC) A[i+32] = v[md + i*8];
        fill(C, C + l, oo);
        for(int bl = 0; bl < M; bl += 4)
        for(int cl = bl; cl < bl + AC + 3; cl += 3)
        rep(bi, bl, bl+4){
            V b = _mm256_load_si256((V*)B + bi);
            rep(ci, cl, cl+3){
                V ad = _mm256_set1_epi32(A[32 + ci - bi]);
                V sum = _mm256_add_epi32(b, ad);
                V c = _mm256_load_si256((V*)C + ci);
                V mn = _mm256_min_epi32(c, sum); // _min_epu32 for unsigned ints
                _mm256_store_si256((V*)C + ci, mn);
            }
        }
        rep(i, md, l)
            ans[i] = min(ans[i], C[i - md]);
    }
    return ans;
}

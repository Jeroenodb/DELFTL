/**
 * Author: Leon van der Waal
 * Date: 2024-03-21
 * License: CC0
 * Source: based on inverse calculations in cp-algorithms.com
 * Description: Calculates the inverse of the power series $(\sum a[i] x^i) \mod x^n$. $a[0]$ must be nonzero. Uses internals of NTT, cannot be used with ConvMod.
 * Inputs must be in [0, mod).
 * Time: $O(N \log N)$
 * Status: tested on Library Checker, inv of formal power series
 */
#pragma once

#include "NumberTheoreticTransform.h"

vl inverse(vl a, int n){
    vl b = {modpow(a[0],mod-2)};
    for(int i = 2; i < n*2;){
        vl m(all(a)-max(0,sz(a)-i)), g(i*=2);
        b.resize(i), m.resize(i);
        vl f = b; ntt(m), ntt(f);
        rep(j,0,i) g[-j&(i-1)] = mul(mul(f[j],f[j]),m[j]);
        ntt(g); ll inv = modpow(mod-i, mod-2);
        rep(j,i/4,i/2) (b[j] += mul(g[j],inv)) %= mod;
    }
    b.resize(n);
    return b;
}
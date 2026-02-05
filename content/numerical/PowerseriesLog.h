/**
 * Author: Leon van der Waal
 * Date: 2024-03-21
 * License: CC0
 * Source: based on formal power series article of cp-algorithms.com
 * Description: Calculates Log and Exp of formal power series $(\sum a[i] x^i) \mod x^n$. $a[0]$ must be 1 for log, $0$ for exp. Uses NTT, but can be swapped out for ConvMod.
 * Inputs must be in [0, mod).
 * Time: $O(N \log N)$
 * Status: Tested on Log and Exp of formal power series on Library Checker
 */
#include "PowerseriesInverseFast.h"
#pragma once

vl integrate(vl a){
    vl b(sz(a)+1);
    rep(i,0,sz(a)) b[i+1] = (a[i]*modpow(i+1,mod-2))%mod;
    return b;
}

vl deriv(vl a){
    vl b(sz(a)-1);
    rep(i,1,sz(a)) b[i-1] = (i*a[i])%mod;
    return b;
}

vl polylog(vl a, int n){
    vl ad = deriv(a), ai = inverse(a,n), 
        f = conv(ad,ai), i = integrate(f);
    i.resize(n);
    return i;
}
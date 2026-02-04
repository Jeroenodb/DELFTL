/**
 * Author: Leon van der Waal
 * Source: cp-algorithms
 * Description: Calculates d such that $a = b * d + r$. Recover $a \mod b$ using $r = a = b * d$
 * Status: not tested yet
 */

#pragma once

#include "PowerseriesInverse.h"

vl polydiv(vl a, vl b){
    int n = sz(a), m = sz(b), s = n - m + 1;
    reverse(all(a)), reverse(all(b));
    a.resize(s);
    vl d = conv(a, inverse(b, n-m+1));
    d.resize(s), reverse(all(d));
    return d;
}

vl polymod(vl a, vl b) {
    vl r = conv(b, polydiv(a, b));
    rep(i,0,sz(a)) a[i] = (a[i] + mod - b[i]) % mod;
    a.resize(sz(b)-1);
    return a;
}
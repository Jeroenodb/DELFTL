/**
 * Author: Leon van der Waal
 * Source: cp-algorithms
 * Description: Given polynomials $a$ and $b$, Polydiv calculates $d$ such that $a = b \cdot d + r$ $(\text{deg}(r) < \text{deg}(b))$. Polymod recovers $a \mod b$ using $r = a - b \cdot d$
 *  $b$ has to have b.back()!=0.
 *  Make sure b is not the 0 polynomial (division by 0). Polymod can have trailing zeros. 
 * Status: librarychecker division of polynomials, tested.
 */

#pragma once

#include "PowerseriesInverseFast.h"

vl polydiv(vl a, vl b){
    int n = sz(a), m = sz(b), s = n - m + 1;
    if(s<=0) return {};
    reverse(all(a)), reverse(all(b));
    a.resize(s);
    vl d = conv(a, inverse(b, s));
    d.resize(s), reverse(all(d));
    return d;
}

vl polymod(vl a, vl b) {
    vl r = conv(b, polydiv(a, b));
    rep(i,0,sz(r)) a[i] = (a[i] + mod - r[i]) % mod;
    a.resize(sz(b)-1);
    return a;
}
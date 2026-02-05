/**
 * Author: Leon van der Waal
 * Date: 12-10-2023
 * Description: Returns the first $n$ terms of the inverse of a generating function. Only works if $n$ is a power of 2. Uses modular convolution. This version only requires convolution, not necessarily NTT.
 * Time: $O(n\log(n))$
 */

#pragma once
#include "NumberTheoreticTransform.h"


vl inverse(vl a, int n){
    vl b = {modpow(a[0],mod-2)}, m, k;
    for (int i=1, j; i<n; i*=2){
        m = vl(a.begin(),begin(a) + min(sz(a),i*2));
        k = conv(m,b);
        for (j=0, k[0]-=2; j<sz(k); ++j) k[j] = (mod-k[j])%mod;
        b = conv(k,b);
        b.resize(min(i*2,n));
    }
    b.resize(n);
    return b;
}
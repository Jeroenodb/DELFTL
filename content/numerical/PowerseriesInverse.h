/**
 * Author: Leon van der Waal
 * Date: 2024-03-21
 * License: CC0
 * Source: based on inverse calculations in 
 * Description: Calculates the inverse of the power series $(\sum a[i] x^i) \mod x^n$. $a[0]$ must be nonzero. Uses NTT, but can be swapped out for ConvMod.
 * Inputs must be in [0, mod).
 * Time: $O(N \log N)$
 * Status: untested
 */
#include "NumberTheoreticTransform.h"

vl inverse(vl a, int n){
    vl b = {modpow(a[0],mod-2)}, m, k;
    for (int i=1, j; i<n; i*=2){
        m = vl(a.begin(),min(a.end(),a.begin()+i*2));
        k = conv(m,b);
        for (j=0, k[0]-=2; j<k.size(); ++j) k[j] =  (mod-k[j])%mod;
        b = conv(k,b);
        b.resize(min(i*2,int(a.size())));
    }
    b.resize(n);
    return b;
}
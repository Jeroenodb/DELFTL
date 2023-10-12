/**
 * Author: Leon van der Waal
 * Date: 12-10-2023
 * Description: Returns the first $n$ terms of the inverse of a generating function. Only works if $n$ is a power of 2. Uses modular convolution.
 * Time: $O(n\log(n))$
 */

#pragma once



// n has to be a power of 2
vl polyInv(const vl& a, const int n){
	assert((n-1)&n==0); // n has to be a power of 2
    if(n==1) return {modpow(a[0],mod-2)};
    vl aslice=a; aslice.resize(n);
    vl b = polyInv(a, n/2);
    vl b2 = conv(b,b);
    vl ans = conv(b2,aslice);
    for(int i=0;i<n/2;++i) ans[i] -= b[i]*2;
    for(auto& x : ans) x = (mod-x)%mod;
    return {ans.begin(), ans.begin() + n};
}
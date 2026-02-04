#pragma once
#include "PowerseriesLogexp.h"

vl polyexp(vl a, int n){
    vl q = {1}, b, c;
    for (int i=1; i<2*n; i*=2){
        b = vl(a.begin(), min(a.begin()+i*2, a.end()));
        b[0] += 1;
        c = polylog(q,sz(q));
        rep(j,0,sz(c)) b[j] = (mod+b[j]-c[j])%mod;
        q = conv(q,b);
        q.resize(min(i*2,n));
    }
    return q;
}
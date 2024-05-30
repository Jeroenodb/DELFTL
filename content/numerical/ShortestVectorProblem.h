/**
 * Author: Leon van der Waal
 * Source: Micciancio and Voulgaris (2010)
 * License: MIT
 * Description: Creates short vectors that contain the shortest vector with high probability
 * Usage: Let $U = o(R)$, where $R$ is the size of the largest vector in M, and make sure that $UR\#M$ \leq 10^18$. For too small values of $U$ the algorithm may fail.
 * vvl M = {{1,1,1}, {2,1,2}, {3,5,6}};
 * vvl ans = Gauss(M, 10); // in this case, U=10 was chosen;
 * Time: $O(\left(\frac{4}{3}\right)^n * m * log(R))$, where $n$ is the dimension of the lattice, $m$ is the vector size and $R$ is the length of the largest vector in $M$.
 * Status: seems to work?
 */
#pragma once
#include "rng.h"

typedef vector<ll> vl;
typedef vector<vl> vvl;

auto inp(vl& v, vl& w){
    double s = 0;
    rep(i,0,sz(v)) s += (double) v[i]*w[i];
    return s;
}
ll mu(vl& v, vl& w){ 
    return llround(inp(v,w)/inp(w,w));
}
void sub(vl& v, vl& w, ll c){
    rep(i,0,sz(v)) v[i] -= c*w[i];
}

vvl Gauss(vvl M, ll U = 1e7){
    // n is at least the rank of M. Update n manually for many dependent vectors
    ll n = sz(M), s = exp(.15*n)*5 + 20,i,m; 
    vvl T,q;
    while(s){
        vl v;
        if (sz(q)==0){
            s--, v = M[0];
            for (vl& w : M) sub(v,w,rnd(-U,U));
        } else v = q.back(), q.pop_back();
        i = 0;
        auto l = inp(v,v);
        for (vl& w : T) {
            sub(v,w,mu(v,w));
            if (inp(v,v)<.5) goto B;
        }
        while (i<sz(T)){
            m = mu(T[i],v);
            if (m) sub(T[i],v,m), q.push_back(T[i]), T[i]=T.back(), T.pop_back();
            i++;
        }
        if (inp(v,v) < l) q.push_back(v);
        else T.push_back(v);
        B:
    }
    return T;
}
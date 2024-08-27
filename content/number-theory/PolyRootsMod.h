/**
 * Author: Leon van der Waal
 * Source: Folklore
 * License: MIT
 * Description: Calculates all distinct roots of a polynomial $\mod mod$.
 * Usage: only works for prime $mod$.
 * vi p = {mod-25,0,1};
 * vi roots = polyroots(p);
 * Time: $O(n^2 \log(mod))$, where $n$ is the degree of the polynomial
 * Status: seems to work?
 */
#pragma once
#include "rng.h"
#include "ModPow.h"

void clear(vi& a){
    while (sz(a)>0 and a.back() < 1) a.pop_back();
}

vi polymul(vi a, vi b){
    vi ans(sz(a)+sz(b)-1);
    rep(i,0,sz(a)) rep(j,0,sz(b)) 
        ans[i+j] += mul(a[i],b[j]), ans[i+j] %= mod; 
    return ans;
}

vi polymod(vi& a, vi b){
    vi p;
    for(int i = sz(a)-sz(b); i>=0; --i){
        int c = mul(a.back(),modpow(mod-b.back(),mod-2));
        rep(j,0,sz(b)) a[j+i] += mul(c,b[j]), a[j+i] %= mod;
        p.push_back(c), a.pop_back();
    }
    clear(a);
    reverse(all(p));
    return p;
}

vi polygcd(vi a, vi b){
    vi *x = &a, *y = &b;
    while (!y->empty()) 
        polymod(*x,*y), swap(x,y);
    return *x;
}

vi powgcd(vi x, ll e, vi a, ll r = 1){
    vi p = {1};
    while (e){
        if (e&1) p = polymul(p,x), polymod(p,a);
        x = polymul(x,x), polymod(x,a);
        e/=2;
    }
    if (sz(p)<r) p.resize(r);
    p[--r] += mod - 1, p[r] %= mod;
    clear(p);
    return polygcd(p,a);
}

void rec(vi a, vi& b){
    if (sz(a) == 2) b.push_back(mul(a[0],modpow(mod-a[1],mod-2)));
    else while(true){
        vi g = powgcd({rnd(0,mod-1),1},mod/2,a);
        if (sz(g)>1 and sz(g)<sz(a)){
            rec(g, b);
            rec(polymod(a,g), b);
            return;
        }
    }
}

vi polyroots(vi a){
    if (sz(a)<2) return {};
    a = powgcd({0,1},mod,a,2);
    if (sz(a)<2) return {};
    vi b;
    rec(a,b);
    return b;
}
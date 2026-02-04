/**
 * Author: Leon van der Waal
 * Source: well known
 * License: -
 * Description: Solves an ILP of the form $c^T x$ subject to $Ax \le b$, $x \ge \text{lo}$, $x \le \text$. Only works with non-fractional inputs. 
 * It is recommended to use at least long doubles.
 * Usage:
 *  vvd A = {{1,-1}, {-1,1}, {-1,-2}};
 *  vd b = {1,1,-4}, c = {-1,-1}, x;
 *  ILP ilp(A, b, c);
 *  ilp.solve(x);
 *  ll ans = llround(ilp.ans);
 * Time: Depends on the problem. Ask Leon for intuition.
 * Status: seems to work?
 */

#pragma once
#include "Simplex.h"

struct ILP{
    int n, m;
    vvd A; vd b, c, lo, hi; T ans = -inf;

    ILP(vvd A, vd b, vd c) : n(sz(b)), m(sz(c)), 
        A(A), b(b), c(c), lo(m), hi(m,inf) { }

    void solve(){
        T bal = 0;
        rep(i,0,m) {
            bal += c[i]*lo[i];
            rep(j,0,n) b[j] -= A[j][i]*lo[i];
            if (hi[i] < inf){
                vd e(m); e[i] = 1;
                A.push_back(e);
                b.push_back(hi[i]-lo[i]);
            }
        }
        LPSolver lp(A, b, c);
        vd x(m), sm(n); T res = floor(bal + lp.solve(x) + .1), me = bal;
        A.resize(n), b.resize(n);
        pair<T, pair<ll,ll>> w = {};
        rep(i,0,m){
            T r = floor(x[i] + eps), d = x[i] - r;
            w = max(w,{min(d,1-d),{i,r}}), me += r * c[i];
            rep(j,0,n) d = A[j][i] * lo[i], 
                b[j] += d, sm[j] += r * A[j][i] + d;
        }
        rep(i,0,n) if (sm[i] > b[i]) me = -inf;
        ans = max(ans, me);
        if (res > ans and w.first > eps) {
            auto [i,v] = w.second; T mx = hi[i];
            hi[i] = lo[i] + v, solve();
            hi[i] = mx, lo[i] += v + 1, solve();
            lo[i] -= v + 1;
        } 
    }
};
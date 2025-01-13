/**
 * Author: Leon van der Waal
 * License: idk...
 * Source: DPLL
 * Description: Solves SAT problems in CNF form. Variables can be retrieved from BSP::val.
 * Usage:
 * BSP problem(2);
 * problem.addClause({0,~1});
 * bool possible = problem.solve();
 * Time: didnt time yet
 * Status: Desparately needs codegolfing. 
 */
#pragma once

#define A(x) (x<0?~x:x)
#define pb(x) push_back(x)
mt19937 rng(69);
struct BCP{
    int n, m = 0, M = 0, cl = 0, g, w, t;
    vvi cs; 
    vector<bitset<1<<13>> tc; // upper bound on number of clauses the algorithm will use
    vi val, rc, tr, rv, dl, f, lc, tm; // clauses removed, number of begin removal clauses, removed vars, decision level
    void toggle(int i, bool on){
        for(int v : cs[i])
            tc[A(v)][i] = on;
        if (!on) rc.pb(i);
        m += 2*on-1;
    }
    void addClause(vi v){
        sort(all(v));
        v.erase(unique(all(v)),end(v));
        cs.pb(v);
        for(auto& i : tc) 
            i[M+1] = 1, i[M] = 0;
        toggle(M++, 1);
    }
    void av(int v, int r){
        v = A(v), dl[v] = cl;
        val[v] = r, rv.pb(v);
    }
    BCP(int n) : n(n), val(n,-1), dl(n), tc(n,1), tr(n+1), f(n+1), tm(n+1) {}
    bool dfs(int i){
        for(int j = tc[i]._Find_first(); j<M; j = tc[i]._Find_next(j)){
            g = n;
            for(int v : cs[j]){
                w = val[A(v)];
                if (w == v>=0){
                    toggle(j,0);
                    goto C;
                }
                if (w < 0){
                    if (g < n)
                        goto C;
                    g = v;
                }
            }
            tm[A(g)] = ++t, f[t] = j;
            if (g<n) av(A(g),g>=0), toggle(j,0);
            else{
                set<int> q = {t}; // this part needs to be shorter / better
                do{               // maybe dfs in/out numbers count work?
                    q.erase(t = *--end(q));
                    for(int g : cs[f[t]]){
                        if (dl[A(g)] < cl) 
                            lc.pb(g);
                        else if (tm[A(g)] < t)
                            q.insert(tm[A(g)]), i=g;
                    }
                } while(sz(q)>1);
                lc.pb(i);
                return 0;
            }
            if (!dfs(A(g))) return 0;
            C:
        }
        return 1;
    }
    bool solve(){
        S:
        for(vi v : cs)
            if (sz(v)<2 and !dfs(A(v[t = 0])))
                return 0;
        while(m){
            ++cl; // we need a bette way of picking a variable to branch on
            int nvar = find(all(val),-1)-begin(val),
                i = rng()&1;
            tr[cl] = sz(rc);
            av(nvar,i);
            tm[nvar] = t = 0;
            if (!dfs(nvar)){
                t = 0;
                for(int v : lc)
                    if (dl[v] < cl)
                        t = max(t, dl[v]);
                addClause(lc);
                lc.clear();
                rep(j,tr[t],sz(rc))
                    toggle(rc[j],1);
                rc.resize(tr[t]);
                while(sz(rv) and dl[w = rv.back()] >= t)
                    val[w] = -1, rv.pop_back();
                if ((cl = t) < 1)
                    goto S;
                cl--;
            }
        }
        return 1;
    }
};
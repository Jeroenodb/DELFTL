/**
 * Author: Leon van der Waal
 * License: idk...
 * Source: DPLL
 * Description: Solves SAT problems in CNF form. Variables can be retrieved from BSP::val.
 * Usage:
 * BSP problem(2);
 * problem.addClause({0,~1});
 * bool possible = problem.solve();
 * Time: O(N \max(w_i))
 * Status: Tested on kattis:eavesdropperevasion, stress-tested
 */
#pragma once

#define A(x) (x < 0 ? ~x : x)
mt19937 rng(69);

struct BSP {
    vector<char> val; // (1=TRUE, 0=FALSE, -1=UNASSIGNED)
    vvi cs;

    BSP(int n) : val(n, -1) {}
    void addClause(vi c) { cs.push_back(c); }

    bool bcp() {
        bool c = 1, s;
        while (c) {
            c = 0;
            for (auto it = cs.begin(); it != cs.end();) {
                vi &cl = *it, us;
                s = 0;
                for (int l : cl) {
                    int v = val[A(l)];
                    if ((l >= 0 && v == 1) || (l < 0 && v == 0)) {
                        s = 1;
                        break;
                    }
                    if (v == -1)
                        us.push_back(l);
                }
                if (s)
                    it = cs.erase(it);
                else {
                    if (!sz(us))
                        return 0;
                    if (sz(us) < 2) {
                        int v = us[0];
                        val[A(v)] = v >= 0;
                        c = 1;
                    }
                    ++it;
                }
            }
        }
        return 1;
    }

    bool solve() {
        if (!bcp())
            return 0;
        if (!sz(cs))
            return 1;

        int nv, t = rng()&1;
        for (vi &cl : cs)
            for (int l : cl)
                if (val[A(l)] == -1) {
                    nv = A(l);
                    goto C;
                }
        return 0;
    C:
        BSP old = *this;
        val[nv] = t;
        if (solve())
            return true;

        *this = old;
        val[nv] = !t;
        return solve();
    }
};
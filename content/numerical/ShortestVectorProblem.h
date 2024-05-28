/**
 * Author: Leon van der Waal
 * Source: Micciancio and Voulgaris (2010)
 * License: MIT
 * Description: Creates short vectors that contain the shortest vector with high probability
 * Usage: handles vectors with values $<$ $10^9$. For larger lattices use __int128 instead of ll.
 * vvl M = {{1,1,1}, {2,1,2}, {3,5,6}};
 * vvl ans = Gauss(M);
 * Time: O(\left(\frac{4}{3}\right)^n * m * log(U)), where $n$ is the number of independent vectors, $m$ is the vector size and U is the word size.
 * Status: seems to work?
 */

typedef vector<ll> vl;
typedef vector<vl> vvl;

double inp(vl& v, vl& w){
    double ans = 0;
    rep(i,0,sz(v)) ans += (double) v[i]*w[i];
    return ans;
}
ll mu(vl& v, vl& w){ 
    return llround(inp(v,w)/inp(w,w));
}
void sub(vl& v, vl& w, ll c){
    rep(i,0,sz(v)) v[i] -= c*w[i];
}

mt19937 gen(69);
ll rnd(ll a, ll b){
    uniform_int_distribution dist(a,b);
    return dist(gen);
}

vvl Gauss(vvl M){
    int n = sz(M), s = pow(1.16,n)*4 + 20,i;
    vvl T,q;
    while(s){
        vl v;
        if (sz(q)==0){
            s--, v = M[0];
            for (vl& w : M) sub(v,w,rnd(-1e7,1e7));
        } else v = q.back(), q.pop_back();
        i = 0;
        double l = inp(v,v);
        for (vl& w : T) {
            sub(v,w,mu(v,w));
            if (inp(v,v)<.5) goto B;
        }
        while (i<sz(T)){
            ll m = mu(T[i],v);
            if (m) sub(T[i],v,m), q.push_back(T[i]), T[i]=T.back(), T.pop_back();
            i++;
        }
        if (inp(v,v) < l) q.push_back(v);
        else T.push_back(v);
        B:
    }
    return T;
}
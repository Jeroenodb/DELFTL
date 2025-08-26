/**
 * Author: Jeroen Op de Beek
 * Date: 2025-26-08
 * License: CC0
 * Description: Calculates the intersection of $n$ halfplanes.
 * Can handle collinear halfplanes.
 * Bounding box of [-oo,oo] x [-oo,oo] is added to halfplanes.
 * Time: O(n \log n)
 * Status: tested on acmicpc.net
 */
#pragma once

#include "GeoBoilerplate.h"
bool polarcomp(const pt& a, const pt& b) {
    if(comp(0,a)!=comp(0,b)) return comp(a,b);
    return cross(a,b)>0;
}
struct line {
    pt p; // for line-line intersection, see math chapter.
    ll c; // halfplane: x s.t. in(p,x)<=c
    line(){}
    line(pt l, pt r) { // halfplane is to the left of segment l->r
        p = (r-l)*pt{0,-1};
        auto g = gcd(abs(p.X),abs(p.Y));
        p/=g; // normalize vector for easier parallel plane handling
        c = in(l,p);
    }
    bool same(const line& o) const {
        return p==o.p; // same angle of the plane
    }
    bool operator<(const line& o) const {
        if(same(o)) return c<o.c;
        return polarcomp(p,o.p);
    }
};
typedef __int128 bi; // need O(A^4), too big too fit in long long
bool ok(line d,line e, line f) {
    bi tmp = (bi)d.p.X*e.p.Y*f.c + (bi)d.p.Y*e.c*f.p.X + (bi)d.c*e.p.X*f.p.Y;
       tmp-= (bi)d.c*e.p.Y*f.p.X + (bi)d.p.X*e.c*f.p.Y + (bi)d.p.Y*e.p.X*f.c;
    return tmp>0; // 3x3 determinant of the matrix with each lines' (p.X,p.Y,c) in the rows
} // for non-strict inequalities, use tmp>=0
vector<line> halfplaneintersection(vector<line> hp) {
    pt at = {1e9,1e9}; // bounding box infinity = 1e9
    rep(i,0,4) {
        pt to = at*pt{0,1};
        hp.push_back(line{at,to});
        at=to;
    }
    sort(all(hp)); // if already sorted, can remove.
    int b=0,e=0;
    vector<line> h(sz(hp));
    for(auto l : hp) {
        if(e and h[e-1].same(l)) continue;
        while(e>1 and !ok(h[e-2], h[e-1], l)) e--;
        h[e++]=l;
    }
    while(e-b>2) {
        if(!ok(h[e-2],h[e-1],h[b]))
            e--;
        else if(!ok(h[e-1],h[b],h[b+1]))
            b++;
        else break;
    }
    h = vector(begin(h)+b,begin(h)+e);
    for(int i=0;i<sz(h);++i) {
        if(cross(h[i].p,h[(i+1)%sz(h)].p)<=0) return {};
    }
    return h;
}
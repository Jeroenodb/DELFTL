/**
 * Author: Jeroen Op de Beek
 * Date: 2021-10-23
 * License: CC0
 * Source: me
 * Description: Geometry boilerplate code using the inbuilt complex type. For easier geometry problems
 * Status: Used, works well
 */
#pragma once

typedef double G; // Change if needed!
typedef double PT; // Change if needed!
typedef complex<PT> pt; 
#define X real()
#define Y imag()
auto cross(pt u, pt v) {return (G)u.X*v.Y-(G)u.Y*v.X;}
auto sgn(const G& a) {return (a>0)-(a<0);}
auto ccw(pt p1, pt p2, pt p3) {auto u = p2-p1, v = p3-p2;return cross(u,v);}
auto in(pt p1, pt p2) {return (G)p1.X*p2.X+(G)p1.Y*p2.Y;}
auto norm(pt p) {return (G)p.X*p.X+(G)p.Y*p.Y;}
bool operator<(const pt& a, const pt& b) { return a.X<b.X or (a.X==b.X and a.Y < b.Y);}
struct PtCmp { // only needed for std::set
    bool operator()(const pt& lhs, const pt& rhs) const { return lhs<rhs; }
};
void read(pt& p) {
    PT a,b; cin >> a >> b;
    p = {a,b};
}
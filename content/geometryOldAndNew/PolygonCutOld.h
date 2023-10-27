/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Usage:
 * 	vector<pt> p = ...;
 * 	p = polygonCut(p, pt{0,0}, pt{1,0});
 *  Use doubles
 * Status: tested but not extensively
 */
#pragma once

#include "Point.h"
#include "GeoBoilerplate.h"
#include "lineIntersection.h"

typedef Point<double> P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
	vector<P> res;
	rep(i,0,sz(poly)) {
		P cur = poly[i], prev = i ? poly[i-1] : poly.back();
		bool side = s.cross(e, cur) < 0;
		if (side != (s.cross(e, prev) < 0))
			res.push_back(lineInter(s, e, cur, prev).second);
		if (side)
			res.push_back(cur);
	}
	return res;
}

// jeroen

typedef complex<double> pt;
vector<pt> polygonCut(const vector<pt>& poly, pt s, pt e) {
	vector<pt> res;
	rep(i,0,poly.size()) {
		pt cur = poly[i], prev = i ? poly[i-1] : poly.back();
		bool side = ccw(s,e, cur) < 0;
		if (side != (ccw(s,e, prev) < 0))
			res.push_back(lineInter(s, e, cur, prev).second);
		if (side)
			res.push_back(cur);
	}
	return res;
}

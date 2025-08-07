/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: Boost Software License
 * Source: https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
 * Description: Extreme point in direction queries:
 * Returns the point of a hull with the max projection onto a line.
 * For convex hull tangents, use the line: 
 * \texttt{\#define cmp(i,j) sgn(cross(dir(poly[(i)\%n]), dir(poly[(j)\%n])))}, and change \texttt{dir} to be a lambda function, 
 * returning a vector from its argument to the queried point.
 * Time: O(\log n)
 * Status: stress-tested
 */
#include "GeoBoilerplate.h"
#define cmp(i,j) sgn(cross( dir*pt{0,1},poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
int extrVertex(vector<pt>& poly, pt dir) {
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo + 1 < hi) {
		int m = (lo + hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
	}
	return lo;
}

/**
 * Author: Ulf Lundstrom
 sideof* Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $\Leftrightarrow$ left/on line/right. If the optional argument $eps$ is given 0 is returned if $p$ is within distance $eps$ from the line. pt is supposed to be Point<T> where T is e.g. double or long long. It uses products in intermediate steps so watch out for overflow if using int or long long.
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 * Status: tested
 */
#pragma once

#include "GeoBoilerplate.h"


int sideOf(pt s, pt e, pt p) { return sgn(ccw(s,e, p)); }

// This is the doubles version with an epsilon
int sideOf(const pt& s, const pt& e, const pt& p, double eps) {
	auto a = cross(e-s,p-s);
	double l = abs(e-s)*eps;
	return (a > l) - (a < -l);
}

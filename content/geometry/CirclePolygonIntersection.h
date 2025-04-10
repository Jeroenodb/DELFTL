/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-10-31
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc#L744
 * Description: Returns the area of the intersection of a circle with a
 * ccw polygon. Use complex< double >.
 * Time: O(n)
 * Status: Tested on GNYR 2019 Gerrymandering, stress-tested
 */
#pragma once

#include "GeoBoilerplate.h"

#define arg(p, q) atan2(cross(p,q), in(p,q))
double circlePoly(pt c, double r, vector<pt> ps){
	auto tri = [&](pt p, pt q){
		pt d = q - p;
		auto r2 = r*r/2, a = in(d,p)/norm(d), 
			 b=(norm(p)-r*r)/norm(d), det = a*a - b;
		if (det<=0) return arg(p,q)*r2;
		auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
		if (t<0 || 1<= s) return arg(p,q)*r2;
		pt u = p + d*s, v = p + d*t;
		return arg(p,u)*r2 + cross(u,v)/2 + arg(v,q)*r2;
	};
	double sum = 0;
	rep(i,0,ps.size())
		sum += tri(ps[i] - c, ps[(i+1)%ps.size()]-c);
	return sum;
}

/**
 * Author: Simon Lindholm
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/58747
 * Description: Finds the closest pair of points.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "GeoBoilerplate.h"

pair<pt, pt> closest(vector<pt> v) {
	assert(sz(v) > 1);
	set<pt,PtCmp> S;
	sort(all(v), [](pt a, pt b) { return a.Y < b.Y; });
	pair<ll, pair<pt, pt>> ret{LLONG_MAX, {pt(), pt()}};
	int j = 0;
	for (pt p : v) {
		pt d{1 + (ll)sqrt(ret.first), 0};
		while (v[j].Y <= p.Y - d.X) S.erase(v[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo)
			ret = min(ret, {norm(*lo - p), {*lo, p}});
		S.insert(p);
	}
	return ret.second;
}


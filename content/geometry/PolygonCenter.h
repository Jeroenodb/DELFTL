/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-08
 * License: CC0
 * Source:
 * Description: Returns the center of mass for a polygon. Use complex< double >
 * Time: O(n)
 * Status: Tested
 */
#pragma once

#include "GeoBoilerplate.h"

pt polygonCenter(const vector<pt>& v){
	pt res = 0; double a = 0;
	for (int i=0, j=v.size()-1; i<v.size(); j=i++){
		res = res + (v[i] + v[j]) * cross(v[j], v[i]);
		a += cross(v[j], v[i]);
	}
	return res/a/3.;
}
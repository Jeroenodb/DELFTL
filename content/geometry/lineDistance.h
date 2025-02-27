/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
Returns the signed distance between point p and the line containing points a and b. Positive value on left side and negative on right as seen from a towards b. a==b gives nan. 
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
#pragma once
#include "GeoBoilerplate.h"

double lineDist(pt a, pt b, pt p){
	return ccw(a,b,p)/sqrt(norm(b-a));
}

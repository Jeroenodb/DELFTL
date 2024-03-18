/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-11
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description:\\
\begin{minipage}{75mm}
The circumcirle of a triangle is the circle intersecting all three vertices. ccRadius returns the radius of the circle going through points A, B and C and ccCenter returns the center of the same circle.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{content/geometry/circumcircle}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "GeoBoilerplate.h"

double ccRadius(pt a, pt b, pt c){
	return abs(b-a)*abs(c-b)*abs(a-c)/abs(ccw(a,b,c))/2;
}

pt ccCenter(pt a, pt b, pt c){
	pt p = c - a, q = b - a;
	return a + (p*norm(q) - q*norm(p))*pt{0,0.5L}/cross(p,q);
}

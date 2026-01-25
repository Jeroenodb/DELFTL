/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Simple bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(VE)
 * Usage: vi btoa(m, -1); dfsMatching(g, btoa);
 * Status: works
 */
#pragma once

bool find(int j, vvi& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis))
			return btoa[e] = di, 1;
	return 0;
}
int dfsMatching(vvi& g, vi& btoa) {
	vi vis(sz(btoa));
	rep(i,0,sz(g)) for (int j : g[i])
		if (find(j, g, btoa, vis)) {
			btoa[j] = i;
			fill(all(vis),0);
			break;
		}
	return sz(btoa) - (int)count(all(btoa), -1);
}

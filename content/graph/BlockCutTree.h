/**
 * Author: Jeroen Op de Beek
 * Date: 2025-07-24
 * License: CC0
 * Source: folklore
 * Description: Finds the biconnected components (blocks) and the cut vertices,
 *  builds a tree on the blocks and cut vertices. 
 *  tree(n+\#blocks) forms the tree (0...n-1 for cut vertices, rest for bicon), some adjacency lists are empty.
 *  bie(\#blocks) gives the edge ids belonging to each block, wrt input order.
 *  biv(\#blocks) non-cut vertices belonging to this block.
 *  bid(n) is a block this vertex is part of.
 * Usage:
 *  vector<array<int,2>> es = {{0,1},{1,2},{0,2},{2,3}};
 *  blockcut bc(4,es);
 * Time: O(E + V)
 * Status: Still needs testing
 */
#pragma once

#include "BiconnectedComponents.h"

#define eb(...) emplace_back(__VA_ARGS__)
struct blockcut {
	int T=-1,n;
	vector<array<int,2>> es;
	vvi tree, bie, biv;
	vi cnt,bid;
	blockcut(int n, auto& es) : n(n), es(es),tree(n),cnt(n),bid(n,-1) {
		ed.assign(n,{});
		rep(eid,0,sz(es)) {
			auto [u,v] = es[eid];
			ed[u].eb(v,eid);
			ed[v].eb(u,eid);
		}
		bicomps([&](vi id) {
			tree.eb(), biv.eb();
			bie.eb(id), T++;
			for(int i : id) {
				for(int w : es[i]) if(bid[w]!=T) {
					cnt[w]++, bid[w]=T;
					biv.back().eb(w);
				}
			}
		});
		rep(i,0,sz(bie)) {
			vi& b = biv[i];
			int k = partition(all(b), [&](int j) {
				return cnt[j]==1;})-begin(b);
			rep(j,k,sz(b)) {
				int u = b[j];
				tree[u].eb(i+n);
				tree[i+n].eb(u);
			}
			b.erase(k+all(b));
		}
	}
};
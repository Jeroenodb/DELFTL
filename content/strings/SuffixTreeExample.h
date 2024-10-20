/**
 * Author: Unknown
 * Date: 2017-05-15
 * Source: https://e-maxx.ru/algo/ukkonen
 * Description: Example usage, include this code at the end of the class.  Finds longest common substring (uses ALPHA = $28$)
 * Status: stress-tested a bit
*/
	
	pii best;
	int lcs(int node, int i1, int i2, int olen) {
		if (l[node] <= i1 && i1 < r[node]) return 1;
		if (l[node] <= i2 && i2 < r[node]) return 2;
		int mask = 0, len = node ? olen + (r[node] - l[node]) : 0;
		rep(c,0,ALPHA) if (t[node][c] != -1)
			mask |= lcs(t[node][c], i1, i2, len);
		if (mask == 3)
			best = max(best, {len, r[node] - len});
		return mask;
	}
	static pii LCS(string s, string t) {
		SuffixTree st(s + (char)('z' + 1) + t + (char)('z' + 2));
		st.lcs(0, sz(s), sz(s) + 1 + sz(t), 0);
		return st.best;
	}
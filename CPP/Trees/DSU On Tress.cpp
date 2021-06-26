// DSU on Trees
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
vector<int>g[maxn];
int sz[maxn], cnt[maxn];
int color[maxn];
void getsz(int u, int p) {
	sz[u] = 1;
	for (auto v : g[u]) {
		if (v != p) {
			getsz(v, u);
			sz[u] += sz[v];
		}
	}
}
vector<int>* vec[maxn];
long long ans[maxn];
int maxi[maxn];
/*
Keep is 0 for small children and 1 for big child
*/
void dfs(int u, int p, bool keep) {
	int mx = -1, bigChild = -1;
	for (auto v : g[u])
		if (v != p)
			if (sz[v] > mx) {
				mx = sz[v], bigChild = v;
			}
	for (auto v : g[u])
		if (v != p && v != bigChild) {
			dfs(v, u, 0);
		}
	if (bigChild != -1) {
		dfs(bigChild, u, 1), vec[u] = vec[bigChild], ans[u] = ans[bigChild], maxi[u] = maxi[bigChild];
	} else {
		vec[u] = new vector<int> (), ans[u] = 0, maxi[u] = 0;
	}
	vec[u]->push_back(u);
	// Now vec has information about it's big child and itself
	// vec[v]=v+bigChild
	cnt[color[u]]++;
	if (cnt[color[u]] > maxi[u]) {
		maxi[u] = cnt[color[u]], ans[u] = 0;
	}
	if (cnt[color[u]] == maxi[u]) {
		ans[u] += color[u];
	}
	for (auto v : g[u])
		if (v != p && v != bigChild)
			for (auto x : *vec[v]) {
				cnt[color[x]]++;
				if (cnt[color[x]] > maxi[u]) {
					maxi[u] = cnt[color[x]], ans[u] = 0;
				}
				if (maxi[u] == cnt[color[x]]) {
					ans[u] += color[x];
				}
				vec[u]->push_back(x);
			}
	// Now vec has information about it's whole subtree
	// vec[v] = v + bigChild+vec[all(smallChild)]

	/*
	Go down to small child, we have to delete its information about
	color count so that the query answer of v's first child subtree
	won't affect second and so on. (because we are using global array)
	That is also the reason why we have to call small child before big
	child recur (to make bigchild and small child answer not overlap).
	*/
	if (keep == 0)
		for (auto it : *vec[u]) {
			cnt[color[it]]--;
		}
}
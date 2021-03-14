// Tree Diameter using single DFS
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5;
vector<int>g[maxn];
int d[maxn];
int ans;
void dfs(int u, int p) {
	for (auto v : g[u])
		if (v != p) {
			dfs(v, u);
			ans = max(ans, d[u] + d[v] + 1);
			d[u] = max(d[u], d[v] + 1);
		}
}
// dfs(0, -1);
// cout << ans;

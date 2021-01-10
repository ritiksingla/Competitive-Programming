// 2-Satisfiability
//
const int maxn = 1e5 + 10;
vector<int>g[maxn];
vector<int>order;
int vis[maxn], comp[maxn];
vector<bool>assignment;

// Both functions accepts 1-based index
inline int positive(int x)
{
	//As it's 2*x for zero based(unchanged)
	return (2 * (x - 1));
}
inline int negative(int x)
{
	//As it's 2*x+1 for zero based(changed)
	return (2 * (x - 1) + 1);
}

void add_edge(int u, int v)
{
	g[u].emplace_back(v);
	g[v].emplace_back(u);
}

void dfs(int u)
{
	vis[u] = 1;
	for (auto it : g[u])
	{
		if (!vis[it])
			dfs(it);
	}
	order.emplace_back(u);
}

void dfs2(int u, int c)
{
	comp[u] = c;
	for (auto it : g[u])
	{
		if (comp[it] == -1)
			dfs2(it, c);
	}
}
int main() {
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < n; i++) {
		if (!vis[i]) dfs(i);
	}
	memset(comp, -1, sizeof comp);
	for (int i = n - 1, j = 0; i >= 0; i--) {
		int v = order[i];
		if (comp[v] == -1) dfs2(v, j++);
	}
	bool flag = true;
	vector<int>ans;
	for (int i = 0; i < n; i += 2) {
		if (comp[i] == comp[i | 1]) {
			flag = false;
			break;
		}
		if (comp[i] > comp[i | 1]) {
			ans.emplace_back(i);
		}
	}
	if (flag) {
		cout << ans.size() << "\n";
		for (auto it : ans) {
			cout << (it) / 2 + 1 << " ";
		}
	}
	else
	{
		cout << "Impossible\n";
	}
	return 0;
}
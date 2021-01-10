// Kosaraju
// 
// Strongly Connected Components
void dfs(int u)
{
	vis[u] = true;
	for (auto v : g[u])
		if (!vis[v])
			dfs(v);
	order.push_back(u);
}
void scc(int u, int c)
{
	vis[u] = 1;
	comp[u] = c;
	for (auto v : rg[u])
		if (!vis[v])
			scc(v, c);
}
void kosaraju()
{
	for (int i = 0; i < n; i++)
		if (!vis[i])
			dfs(i);
	reverse(order.begin(), order.end());
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < n; i++)
	{
		int u = order[i];
		if (!vis[u])
			scc(u, u);
	}
}
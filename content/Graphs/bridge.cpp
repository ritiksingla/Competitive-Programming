// Bridges
// 
const int maxn = 1e5 + 10;
vector<int>g[maxn];
bool vis[maxn];
int timer;
vector<int>tin, low;
int n, m;
void dfs(int u, int p = -1)
{
    vis[u] = true;
    tin[u] = low[u] = timer++;
    for (int v : g[u])
    {
        if (v == p) continue;
        if (vis[v])
        {
            low[u] = min(low[u], tin[v]);
        }
        else
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u])
            {
                is_bridge(u, v);
            }
        }
    }
}
void find_bridges() {
    timer = 0;
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
        tin[i] = low[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        if (!vis[i])
            dfs(i);
    }
}
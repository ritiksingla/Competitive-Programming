// Centroid Decomposition
//
const int maxn = 1e5 + 10;
const int lg = 18;
int n, q, u, v;
vector<int>adj[maxn];
int parent[maxn][lg], decomposedparent[maxn], subtree[maxn];
int closestred[maxn], level[maxn];
namespace init
{
    void dfs(int u, int p = 0, int lev = 1)
    {
        level[u] = lev;
        parent[u][0] = p;
        for(auto it : adj[u])
        {
            if(it != p)
                dfs(it, u, lev + 1);
        }
    }
    void precompute()
    {
        for(int l = 1; l < lg; l++)
        {
            for(int i = 1; i <= n; i++)
            {
                if(parent[i][l - 1])
                {
                    parent[i][l] = parent[parent[i][l - 1]][l - 1];
                }
            }
        }
    }
}
int lca(int u, int v)
{
    if(level[u] > level[v])
        swap(u, v);
    int diff = level[v] - level[u];
    for(int i = lg - 1; i >= 0; i--)
    {
        if(diff & (1 << i))
            v = parent[v][i];
    }
    if(u == v)
        return u;
    for(int i = lg - 1; i >= 0; i--)
    {
        if(parent[u][i] && parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}
namespace centroid
{
    int nodes;
    void dfs(int u, int p)
    {
        subtree[u] = 1;
        nodes++;
        for(auto it : adj[u])
        {
            if(it != p)
            {
                dfs(it, u);
                subtree[u] += subtree[it];
            }
        }
    }
    int centroid(int u, int p)
    {
        for(auto it : adj[u])
        {
            if(it != p)
            {
                if(subtree[it] > (nodes >> 1))
                    return centroid(it, u);
            }
        }
        return u;
    }
    void decompose(int u, int p = 0)
    {
        nodes = 0;
        dfs(u, u);
        int c = centroid(u, u);
        decomposedparent[c] = p;
        for(auto it : adj[c])
        {
            adj[it].erase(remove(all(adj[it]), c), adj[it].end());
            decompose(it, c);
        }
    }
}
int distance(int u, int v) {
    return (level[u] + level[v] - 2 * level[lca(u, v)]);
}
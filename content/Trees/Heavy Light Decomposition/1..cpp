// Heavy Light Decomposition - 1
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
const int lg = 14;
int parent[maxn][lg], level[maxn];
int head[maxn], pos[maxn], heavy[maxn], rpos[maxn];
int st[2 * maxn];
int previous[maxn];
int timer;
int n;
const int inf = 1e6 + 1;
vector<pair<int, int> >adj[maxn];
void init()
{
    forn(i, 1, n)
    {
        adj[i].clear();
        head[i] = 0;
        heavy[i] = -1;
        pos[i] = 0;
        rpos[i] = 0;
        previous[i] = 0;
        st[i + n - 1] = -inf;
        forn(j, 0, lg - 1)
        parent[i][j] = 0;
    }
    timer = 1;
    return;
}
int dfs(int u, int p = 0, int lev = 1)
{
    parent[u][0] = p;
    level[u] = lev;
    int h = 1;
    int maxc = 0;
    for(auto it : adj[u])
    {
        if(it.ff != p)
        {
            previous[it.ff] = it.ss;
            int c = dfs(it.ff, u, lev + 1);
            h += c;
            if(c > maxc)
            {
                maxc = c;
                heavy[u] = it.ff;
            }
        }
    }
    return h;
}
void precompute()
{
    for(int l = 1; l < lg; l++)
    {
        for(int i = 1; i <= n; i++)
        {
            if(parent[i][l - 1])
                parent[i][l] = parent[parent[i][l - 1]][l - 1];
        }
    }
    return;
}
void hld(int u, int p)
{
    pos[timer] = u;
    rpos[u] = timer++;
    head[u] = p;
    if(heavy[u] != -1)
    {
        hld(heavy[u], p);
    }
    for(auto it : adj[u])
    {
        if(heavy[u] != it.ff && it.ff != parent[u][0])
        {
            hld(it.ff, it.ff);
        }
    }
    return;
}
void build()
{
    for(int i = n - 1; i > 0; i--)
        st[i] = max(st[i << 1], st[i << 1 | 1]);
    return;
}
int segquery(int u, int v)
{
    u--;
    int res{};
    for(u += n, v += n; u < v; u >>= 1, v >>= 1)
    {
        if(u & 1)
            res = max(res, st[u++]);
        if(v & 1)
            res = max(res, st[--v]);
    }
    return res;
}
int query(int u, int v)
{
    int res{};
    for(; head[u] != head[v]; v = parent[head[v]][0])
    {
        if(level[head[u]] > level[head[v]])
            swap(u, v);
        int curmax = segquery(rpos[head[v]], rpos[v]);
        res = max(res, curmax);
    }
    if(u == v)
        return res;
    if (level[u] > level[v])
    {
        swap(u, v);
    }
    int a = rpos[v];
    int h = head[v];
    int diff = level[v] - level[u] - 1;
    for(int l = lg - 1; l >= 0; l--)
    {
        if(diff & (1 << l))
        {
            v = parent[v][l];
        }
    }
    int curmax = segquery(rpos[v], a);
    res = max(res, curmax);
    return res;
}
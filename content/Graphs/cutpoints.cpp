// Cutpoints
// 
const int maxn = 1e5 + 5;
int to[maxn], tin[maxn];
int timer;
bool vis[maxn];
vector<int>g[maxn];
set<int>s;
void init(int n)
{
    for(int i = 0; i < n; i++)
    {
        g[i].clear();
        vis[i] = to[i] = tin[i] = 0;
    }
    timer = 0;
    s.clear();
}
void is_articulation_point(int u)
{
    s.insert(u); //Use set instead of incrementing as each vertex may be considered more than once.
}
void articulation_point(int u, int p = -1)
{
    vis[u] = 1;
    tin[u] = to[u] = timer++;
    int children = 0;
    for(auto v : g[u])
    {
        if(v == p)
            continue;
        if(vis[v])
        {
            to[u] = min(to[u], tin[v]);
        }
        else
        {
            articulation_point(v, u);
            to[u] = min(to[u], to[v]);
            if(to[v] >= tin[u] && p != -1)
            {
                is_articulation_point(u);
            }
            children++;
        }
    }
    if(p == -1 && children > 1)
    {
        is_articulation_point(u);
    }
}

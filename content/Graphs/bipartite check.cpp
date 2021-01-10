// Bipartite Check
//
vector<int>color(n, -1);
bool flag = true;
for (int i = 0; i < n && flag; i++)
{
    if (color[i] == -1)
    {
        queue<int>q;
        q.push(i);
        color[i] = 0;
        while (!q.empty() && flag)
        {
            int u = q.front();
            q.pop();
            for (auto v : g.adj[u])
            {
                if (color[v.to] == -1)
                {
                    color[v.to] = color[u] ^ 1;
                    q.push(v.to);
                }
                else
                {
                    flag &= color[v.to] != color[u];
                }
            }
        }
    }
}
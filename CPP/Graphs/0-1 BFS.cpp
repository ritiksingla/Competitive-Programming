// 0-1 BFS
//
deque<int>q;
const int inf = 1e5 + 5;
vector<int>dist(n, inf);
dist[0] = 0;
bool vis[n];
memset(vis, 0, sizeof vis);
q.push_back(0);
while (!q.empty()) {
    int u = q.front();
    q.pop_front();
    vis[u] = 1;
    for (auto v : g.edges[u]) {
        if (dist[v.to] > dist[u] + v.cost) {
            dist[v.to] = dist[u] + v.cost;
            if (v.cost) {
                q.push_back(v.to);
            } else {
                q.push_front(v.to);
            }
        }
    }
}
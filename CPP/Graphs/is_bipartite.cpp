// Bipartite Check
//
template<typename T>
bool is_bipartite(const Graph<T>& g, vector<bool>& color) {
	color.resize(g.n);
	fill(color.begin(), color.end(), false);
	vector<bool>vis(g.n, false);
	bool flag = true;

	auto bfs = [&](int st) {
		queue<int>q;
		q.push(st);
		vis[st] = true;
		while (!q.empty() && flag) {
			int u = q.front();
			q.pop();
			for (int id : g.g[u]) {
				auto& e = g.edges[id];
				int to = u ^ e.from ^ e.to;
				if (vis[to] == false) {
					vis[to] = true;
					color[to] = !color[u];
					q.push(e.to);
				} else if (color[e.to] == color[u]) {
					flag = false;
				}
			}
		}
	};

	for (int i = 0; i < g.n && flag; i++) {
		if (vis[i] == false) {
			bfs(i);
		}
	}
	return flag;
}
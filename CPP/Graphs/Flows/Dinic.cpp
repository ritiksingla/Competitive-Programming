// Dinic
//
template <typename T>
class Dinic {
  public:
	FlowGraph<T>& g;

	vector<int> ptr;
	vector<int> level;
	vector<int>q;

	Dinic(FlowGraph<T>& _g) : g(_g) {
		ptr.resize(g.n);
		level.resize(g.n);
		q.resize(g.n);
	}

	bool bfs() {
		fill(level.begin(), level.end(), -1);
		q[0] = g.st;
		level[g.st] = 0;
		int beg = 0, end = 1;
		while (beg < end) {
			int u = q[beg++];
			for (int id : g.g[u]) {
				const auto& e = g.edges[id];
				const auto& back = g.edges[id ^ 1];
				if (e.c - e.f > g.eps && level[e.to] == -1) {
					level[e.to] = level[u] + 1;
					if (e.to == g.fin) {
						return true;
					}
					q[end++] = e.to;
				}
			}
		}
		return false;
	}

	T dfs(int v, T w) {
		if (v == g.fin) {
			return w;
		}
		int& j = ptr[v];
		while (j < int(g.g[v].size())) {
			int id = g.g[v][j];
			const auto& e = g.edges[id];
			if (e.c - e.f > g.eps && level[e.to] == level[v] + 1) {
				T t = dfs(e.to, min(e.c - e.f, w));
				if (t > g.eps) {
					g.edges[id].f += t;
					g.edges[id ^ 1].f -= t;
					return t;
				}
			}
			j++;
		}
		return 0;
	}

	T max_flow() {
		while (bfs()) {
			fill(ptr.begin(), ptr.end(), 0);
			T big_add = 0;
			while (true) {
				T add = dfs(g.st, numeric_limits<T>::max());
				if (add <= g.eps) {
					break;
				}
				big_add += add;
			}
			if (big_add <= g.eps) {
				break;
			}
			g.flow += big_add;
		}
		return g.flow;
	}

	vector<bool> min_cut() {
		max_flow();
		vector<bool> ret(g.n);
		for (int i = 0; i < g.n; i++) {
			ret[i] = (level[i] != -1);
		}
		return ret;
	}
};
// Ford Fulkerson
//
template<typename T>
class FordFulkerson {

  private:
	FlowGraph<T>g;
	vector<int>pe;
	vector<int>q;
	vector<int>was;
	int attempt;

  public:
	FordFulkerson(const FlowGraph<T>& g_): g(g_) {
		attempt = 0;
		was.resize(g.n);
		pe.resize(g.n);
		q.resize(g.n);
	}

	bool bfs() {
		attempt++;
		q[0] = g.st;
		pe[g.st] = -1;
		was[g.st] = attempt;
		int beg = 0, end = 1;
		while (beg < end) {
			int u = q[beg++];
			for (int id : g.g[u]) {
				const auto& e = g.edges[id];
				if (was[e.to] != attempt && e.c - e.f > g.eps) {
					pe[e.to] = id;
					was[e.to] = attempt;
					if (e.to == g.fin) {
						return true;
					}
					q[end++] = e.to;
				}
			}
		}
		return false;
	}

	T max_flow() {
		while (bfs()) {
			T delta = numeric_limits<T>::max();
			int id = pe[g.fin];
			while (id != -1) {
				const auto& e = g.edges[id];
				delta = min(delta, e.c - e.f);
				id = pe[e.from];
			}
			id = pe[g.fin];
			while (id != -1) {
				auto& e = g.edges[id];
				auto& back = g.edges[id ^ 1];
				e.f += delta;
				back.f -= delta;
				id = pe[e.from];
			}
			g.flow += delta;
		}
		return g.flow;
	}
};
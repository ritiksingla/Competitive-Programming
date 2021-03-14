// Push Relabel (Maximum Flow)
//
// O(V^{3})
template <typename T>
class PushRelabel {
  private:
	vector<T>excess;
	vector<int>height;
	T INF;

  public:
	flow_graph<T>g;

	PushRelabel(const flow_graph<T>& g_): g(g_) {
		excess.resize(g.n);
		height.resize(g.n);
		INF = numeric_limits<T>::max();
	}

	T max_flow() {
		height[g.st] = g.n;
		excess[g.st] = INF;
		for (int id : g.g[g.st]) {
			push(g.st, id);
		}
		vector<int> current = find_max_height_vertices();
		while (!current.empty()) {
			for (int i : current) {
				if (excess[i] == 0) {
					continue;
				}
				bool pushed = false;
				for (int id : g.g[i]) {
					auto& e = g.edges[id];
					int to = e.to ^ e.from ^ i;
					if (e.c - e.f > g.eps && height[i] == height[to] + 1) {
						push(i, id);
						pushed = true;
					}
				}
				if (pushed == false) {
					relabel(i);
					break;
				}
			}
			current = find_max_height_vertices();
		}
		for (int id : g.g[g.st]) {
			auto& e = g.edges[id];
			g.flow += e.f;
		}
		return g.flow;
	}

  private:
	void push(const int& from, const int& id) {
		auto& e = g.edges[id];
		auto& back = g.edges[id ^ 1];
		int to = e.to ^ e.from ^ from;
		T d = min(excess[from], e.c - e.f);
		e.f += d;
		back.f -= d;
		excess[from] -= d;
		excess[to] += d;
	}

	void relabel(const int& from) {
		int d = g.n + 1;
		for (int id : g.g[from]) {
			auto& e = g.edges[id];
			int to = e.to ^ e.from ^ from;
			if (e.c - e.f > g.eps) {
				d = min(d, height[to]);
			}
		}
		if (d != g.n + 1) {
			height[from] = d + 1;
		}
	}

	vector<int> find_max_height_vertices() const {
		vector<int> res;
		int max_height = 0;
		for (int i = 0; i < g.n; i++) {
			if (i != g.st && i != g.fin && excess[i] != 0) {
				if (max_height < height[i]) {
					max_height =  height[i];
				}
			}
		}
		for (int i = 0; i < g.n; i++) {
			if (i != g.st && i != g.fin && excess[i] != 0) {
				if (height[i] == max_height) {
					res.emplace_back(i);
				}
			}
		}
		return res;
	}
};
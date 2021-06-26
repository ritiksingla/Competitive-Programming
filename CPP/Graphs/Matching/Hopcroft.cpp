// Hopcroft Karp's Maximum Bipartite Matching
//
struct Hopcroft {
	int N, M;
	vector<vector<int>> g;
	vector<int> pa, ldist;
	vector<int> pb, rdist;
	Hopcroft(int N_, int M_): N(N_), M(M_) {
		pa = vector<int>(N, -1);
		pb = vector<int>(M, -1);
		ldist.resize(N);
		rdist.resize(M);
		g.resize(N);
	}
	void add(int from, int to) {
		assert(from >= 0 && from < N && to >= 0 && to < M);
		g[from].push_back(to);
	}
	bool augmenting_path_exists() {
		queue<int>q;
		bool found = false;
		fill(ldist.begin(), ldist.end(), 0);
		fill(rdist.begin(), rdist.end(), 0);
		for (int i = 0; i < N; i++) {
			if (pa[i] == -1) {
				q.push(i);
			}
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : g[u]) {
				if (rdist[v] == 0) {
					rdist[v] = ldist[u] + 1;
					if (pb[v] == -1) {
						found = true;
					} else {
						ldist[pb[v]] = rdist[v] + 1;
						q.push(pb[v]);
					}
				}
			}
		}
		return found;
	}
	bool augment_path(int u) {
		for (int v : g[u]) {
			if (rdist[v] == ldist[u] + 1) {
				rdist[v] = 0;
				if (pb[v] == -1 || augment_path(pb[v])) {
					pa[u] = v;
					pb[v] = u;
					return true;
				}
			}
		}
		return false;
	}
	int solve() {
		int res = 0;
		while (augmenting_path_exists()) {
			for (int i = 0; i < N; i++)
				if (pa[i] == -1)
					if (augment_path(i)) {
						res++;
					}
		}
		return res;
	}
};
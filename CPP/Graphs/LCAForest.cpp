// Least Common Ancestor Forest
//
template <typename T>
class LCAForest : public DFSForest<T> {
  public:
	using DFSForest<T>::edges;
	using DFSForest<T>::g;
	using DFSForest<T>::n;
	using DFSForest<T>::pv;
	using DFSForest<T>::pos;
	using DFSForest<T>::end;
	using DFSForest<T>::depth;

	int h;
	vector<vector<int>> pr;

	LCAForest(int _n) : DFSForest<T>(_n) {
	}

	inline void build_lca() {
		assert(!pv.empty());
		int max_depth = 0;
		for (int i = 0; i < n; i++) {
			max_depth = max(max_depth, depth[i]);
		}
		h = 1;
		while ((1 << h) <= max_depth) {
			h++;
		}
		pr.resize(n);
		for (int i = 0; i < n; i++) {
			pr[i].resize(h);
			pr[i][0] = pv[i];
		}
		for (int j = 1; j < h; j++) {
			for (int i = 0; i < n; i++) {
				pr[i][j] = (pr[i][j - 1] == -1 ? -1 : pr[pr[i][j - 1]][j - 1]);
			}
		}
	}

	inline bool anc(int x, int y) {
		return (pos[x] <= pos[y] && end[y] <= end[x]);
	}

	inline int go_up(int x, int up) {
		assert(!pr.empty());
		up = min(up, (1 << h) - 1);
		for (int j = h - 1; j >= 0; j--) {
			if (up & (1 << j)) {
				x = pr[x][j];
				if (x == -1) {
					break;
				}
			}
		}
		return x;
	}

	inline int lca(int x, int y) {
		assert(!pr.empty());
		if (anc(x, y)) {
			return x;
		}
		if (anc(y, x)) {
			return y;
		}
		if (depth[x] > depth[y]) {
			swap(x, y);
		}
		for (int j = h - 1; j >= 0; j--) {
			if (pr[x][j] != -1 && !anc(pr[x][j], y)) {
				x = pr[x][j];
			}
		}
		return pr[x][0];
	}
};
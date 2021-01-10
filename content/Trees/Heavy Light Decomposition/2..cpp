// Heavy Light Decomposition - 2
//
struct HLD
{
	vector<vector<int>> tree;
	bool vov; // True if values are on vertices, false if values are on edges.
	segtree segment_tree;
	vector<int> parent;
	vector<int> lv;
	vector<int> head;
	vector<int> tin;
	HLD(const vector<vector<int>> &t, bool _vov): tree(t), vov(_vov), segment_tree(t.size()), parent(t.size()), lv(t.size()), head(t.size()), tin(t.size())
	{
		int time = 0;
		parent[0] = -1;
		function<int(int)> dfs1 = [&](int u)
		{
			int h = 1;
			int maxc = 0;
			for (int &v : tree[u])
			{
				if (v == parent[u])
					continue;
				parent[v] = u;
				lv[v] = lv[u] + 1;
				int c = dfs1(v);
				if (c > maxc)
				{
					maxc = c;
					swap(v, tree[u][0]);
				}
				h += c;
			}
			return h;
		};
		function<void(int)> decompose = [&](int u)
		{
			tin[u] = time++;
			for (int v : t[u])
			{
				if (v == parent[u])
					continue;
				head[v] = v == t[u][0] ? head[u] : v;
				decompose(v);
			}
		};
		dfs1(0);
		decompose(0);
	}
	segtree::node get(int u, int v) {
		segtree::node res;
		process_path(u, v, [this, &res](int a, int b) {
			res = segtree::unite(res, segment_tree.get(a, b));
		});
		return res;
	}
	void modify(int u, int v, long long delta) {
		process_path(u, v, [this, delta](int a, int b) {
			segment_tree.modify(a, b, delta);
		});
	}
	void process_path(int u, int v, const function<void(int x, int y)> &operation) {
		for (; head[u] != head[v]; v = parent[head[v]]) {
			if (lv[head[u]] > lv[head[v]])
				swap(u, v);
			operation(tin[head[v]], tin[v]);
		}
		if (u != v || vov)
			operation(min(tin[u], tin[v]) + (vov ? 0 : 1), max(tin[u], tin[v]));
	}
};
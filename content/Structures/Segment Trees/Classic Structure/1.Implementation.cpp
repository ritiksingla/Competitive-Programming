// Segtree BFS
//
template <typename T>
class segtree {
  private:
	vector<T> lz, st;
	int N;
  public:
	segtree(const int& N_) {
		N = N_;
		lz.resize(4 * N);
		st.resize(4 * N);
	}

	segtree(const vector<T>& A) {
		N = int(A.size());
		lz.resize(4 * N);
		st.resize(4 * N);
		for (int i = 0; i < N; ++i) {
			modify(i, i, A[i]);
		}
	}

	void apply(int x, T v, int sz) {
		st[x] += v * sz;
		lz[x] += v;
	}

	void push(int l, int r, int x) {
		int m = (l + r) / 2;
		if (lz[x] != 0) {
			apply(2 * x + 1, lz[x], m - l + 1); // [l, m]
			apply(2 * x + 2, lz[x], r - m); // [m+1, r]
			lz[x] = 0;
		}
	}

	void pull(int x) {
		st[x] = st[2 * x + 1] + st[2 * x + 2];
	}

	void modify(int ql, int qr, T v, int x, int l, int r) {
		if (ql <= l && r <= qr) {
			apply(x, v, r - l + 1);
			return;
		}
		push(l, r, x);
		int m = (l + r) / 2;
		if (ql <= m) {
			modify(ql, qr, v, 2 * x + 1, l, m);
		}
		if (qr > m) {
			modify(ql, qr, v, 2 * x + 2, m + 1, r);
		}
		pull(x);
	}
	void modify(int ql, int qr, T v) {
		modify(ql, qr, v, 0, 0, N - 1);
	}

	T get(int ql, int qr, int x, int l, int r) {
		if (ql <= l && r <= qr) {
			return st[x];
		}
		push(l, r, x);
		int m = (l + r) / 2;
		T res;
		if (qr <= m) {
			res = get(ql, qr, 2 * x + 1, l, m);
		} else if (ql > m) {
			res = get(ql, qr, 2 * x + 2, m + 1, r);
		} else {
			res = get(ql, qr, 2 * x + 1, l, m) + get(ql, qr, 2 * x + 2, m + 1, r);
		}
		pull(x);
		return res;
	}
	T get(int ql, int qr) {
		return get(ql, qr, 0, 0, N - 1);
	}
};
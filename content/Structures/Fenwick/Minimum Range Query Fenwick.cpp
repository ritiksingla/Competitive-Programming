// Efficient Range Query Fenwick Tree
//
// https://ioinformatics.org/journal/v9_2015_39_44.pdf
// N.log(N) preprocessing
// update is O(log(N)) and query is O(log(N))
// Faster than lazy segment tree!
template<typename T, class F = function<T(const T&, const T&)>>
class range_query_fenwick {
  private:
	vector<T>BIT1;
	vector<T>BIT2;
	F func;
	bool indexing; // Indexing values type: only (0 or 1)
	vector<T>A;
	T initializer; // Initial value (eg. 0 for sum, inf for min, -inf for max)
	int N;

	void modify1(int idx, const T& v) {
		while (idx < N) {
			BIT1[idx] = func(BIT1[idx], v);
			idx += idx & -idx;
		}
	}

	void modify2(int idx, const T& v) {
		while (idx > 0) {
			BIT2[idx] = func(BIT2[idx], v);
			idx -= idx & -idx;
		}
	}
  public:
	range_query_fenwick(int N_, const T& t, const F& f, bool indexing_ = 0): N(N_ + 1), func(f), indexing(indexing_) {
		A.resize(N + 1, t);
		initializer = t;
		BIT1.resize(N + 1, t);
		BIT2.resize(N + 1, t);
	}
	int size() const {
		assert(BIT1.size() == BIT2.size() && int(BIT1.size()) == N);
		return N;
	}
	const vector<T>& data1() const {
		return BIT1;
	}
	vector<T>& data1() {
		return BIT1;
	}
	const vector<T>& data2() const {
		return BIT2;
	}
	vector<T>& data2() {
		return BIT2;
	}
	range_query_fenwick(const vector<T>& V, const T& t, const F& f, bool indexing_ = 0): func(f), indexing(indexing_) {
		N = static_cast<int>(V.size()) + 1;
		initializer = t;
		A.resize(N + 1, t);
		BIT1.resize(N + 1, t);
		BIT2.resize(N + 1, t);
		for (int i = 1; i <= N; ++i) {
			A[i] = V[i - 1];
			modify1(i, V[i - 1]);
			modify2(i, V[i - 1]);
		}
	}

	T get(int l, int r) {
		if (indexing == 0) {
			l++, r++;
		}
		assert(l <= r && l >= 1 && r <= N - 1);
		int idx = l;
		T res = initializer;
		while (idx + (idx & -idx) <= r) {
			res = func(res, BIT2[idx]);
			idx += idx & -idx;
		}
		res = func(res, A[idx]);
		idx = r;
		while (idx - (idx & -idx) >= l) {
			res = func(res, BIT1[idx]);
			idx -= idx & -idx;
		}
		return res;
	}

	void modify(int p, const T& v) {
		if (indexing == 0) {
			p++;
		}
		assert(p >= 1 && p <= N - 1);
		A[p] = v;

		// Update BIT1
		int idx = p;
		int ptr1 =  p - 1; // pointer at BIT2[p-1]
		int ptr2 = p + 1; // pointer at BIT1[p+1]
		T res = v;
		while (idx < N) {
			int x = idx - (idx & -idx) + 1;
			int y = idx;
			T extra = initializer;
			if (p - 1 >= x) {
				while (ptr1 >= x) {
					res = func(res, BIT1[ptr1]);
					ptr1 -= (ptr1 & -ptr1);
				}
			}
			if (p + 1 <= y) {
				while (ptr2 < y) {
					res = func(res, BIT2[ptr2]);
					ptr2 += (ptr2 & -ptr2);
				}
				extra = func(extra, A[ptr2]);
			}
			BIT1[idx] = func(extra, res);
			idx += idx & -idx;
		}

		// Update BIT2
		ptr1 =  p - 1; // pointer at BIT2[p-1]
		ptr2 = p + 1; // pointer at BIT1[p+1]
		res = v;
		idx = p;
		while (idx > 0) {
			int x = idx;
			int y = idx + (idx & -idx) - 1;
			y = min(y, N - 1);
			T extra = initializer;
			if (p - 1 >= x) {
				while (ptr1 > x) {
					res = func(res, BIT1[ptr1]);
					ptr1 -= (ptr1 & -ptr1);
				}
				extra = func(extra, A[ptr1]);
			}
			if (p + 1 <= y) {
				while (ptr2 <= y) {
					res = func(res, BIT2[ptr2]);
					ptr2 += (ptr2 & -ptr2);
				}
			}
			BIT2[idx] = func(extra, res);
			idx -= idx & -idx;
		}
	}
};
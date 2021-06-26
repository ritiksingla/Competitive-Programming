// Suffix Array
//
template<typename String>
struct SuffixArray {
  public:
	String S;
	int N;
	SparseTable<int>ST;
	vector<int> sa, rank, lcp;

	SuffixArray(const String& S_): S(S_), N(int(S.size())) {
		build_sa();
		build_rank();
		build_lcp();
		build_rmq();
	}

	int get_lcp(int a, int b) const {
		if (a == b) {
			return N - a;
		}
		a = rank[a], b = rank[b];
		if (a > b) {
			swap(a, b);
		}
		return ST.get_idempotent(a, b - 1);
	}

	int compare(int a, int b, int length) const {
		if (a == b) {
			return 0;
		}

		int common = get_lcp(a, b);

		if (common >= length) {
			return 0;
		}

		if (a + common >= N || b + common >= N) {
			return a + common >= N ? -1 : 1;
		}

		return S[a + common] < S[b + common] ? -1 : (S[a + common] == S[b + common] ? 0 : 1);
	}

  private:
	const int alphabet_size = 256;
	void build_sa() {
		sa.resize(N);
		auto init = [&]() {
			vector<int> aux(alphabet_size, 0);
			for (int i = 0; i < N; i++) {
				aux[S[i]]++;
			}
			int sum = 0;
			for (int i = 0; i < alphabet_size; i++) {
				int add = aux[i];
				aux[i] = sum;
				sum += add;
			}
			for (int i = 0; i < N; i++) {
				sa[aux[S[i]]++] = i;
			}
		};
		init();

		vector<int> sorted_by_second(N);
		vector<int> ptr_group(N);
		vector<int> new_group(N);
		vector<int> group(N);
		group[sa[0]] = 0;
		for (int i = 1; i < N; i++) {
			group[sa[i]] = group[sa[i - 1]] + (!(S[sa[i]] == S[sa[i - 1]]));
		}
		int cnt = group[sa[N - 1]] + 1;
		int step = 1;
		while (cnt < N) {
			int at = 0;
			for (int i = N - step; i < N; i++) {
				sorted_by_second[at++] = i;
			}
			for (int i = 0; i < N; i++) {
				if (sa[i] - step >= 0) {
					sorted_by_second[at++] = sa[i] - step;
				}
			}
			for (int i = N - 1; i >= 0; i--) {
				ptr_group[group[sa[i]]] = i;
			}
			for (int i = 0; i < N; i++) {
				int x = sorted_by_second[i];
				sa[ptr_group[group[x]]++] = x;
			}
			new_group[sa[0]] = 0;
			for (int i = 1; i < N; i++) {
				if (group[sa[i]] != group[sa[i - 1]]) {
					new_group[sa[i]] = new_group[sa[i - 1]] + 1;
				} else {
					int pre = (sa[i - 1] + step >= N ? -1 : group[sa[i - 1] + step]);
					int cur = (sa[i] + step >= N ? -1 : group[sa[i] + step]);
					new_group[sa[i]] = new_group[sa[i - 1]] + (pre != cur);
				}
			}
			swap(group, new_group);
			cnt = group[sa[N - 1]] + 1;
			step <<= 1;
		}
	}
	void build_rank() {
		rank.resize(N);
		for (int i = 0; i < N; ++i) {
			rank[sa[i]] = i;
		}
	}

	void build_lcp() {
		assert(int(sa.size()) == N);
		lcp.resize(N);
		for (int i = 0, k = 0; i < N; ++i) {
			k = max(0, k - 1);
			if (rank[i] == N - 1) {
				k = 0;
			} else {
				int j = sa[rank[i] + 1];
				while (i + k < N && j + k < N && S[i + k] == S[j + k]) {
					k++;
				}
				lcp[rank[i]] = k;
			}
		}
	}
	void build_rmq() {
		ST = SparseTable<int>(lcp, [&](int i, int j) {
			return min(i, j);
		});
	}
  public:
	int lower_bound(const String& P) const {
		int M = int(P.size());
		auto check = [&](const int m) {
			return S.compare(sa[m], M, P);
		};
		int l = 0, r = N;
		while (l < r)  {
			int m = l + (r - l) / 2;
			if (check(m) >= 0) {
				r = m ;
			} else {
				l = m + 1;
			}
		}
		return l;
	}
	int upper_bound(const String& P) const {
		int M = int(P.size());
		auto check = [&](const int m) {
			return S.compare(sa[m], M, P);
		};
		int l = 0, r = N;
		while (l < r)  {
			int m = l + (r - l) / 2;
			if (check(m) <= 0) {
				l = m + 1;
			} else {
				r = m;
			}
		}
		return r;
	}
};
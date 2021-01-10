// Knuth Morris Pratt Algorithm
//
template<typename T>
struct knuth_morris_pratt {
	int N;
	vector<int> P;
	T S;
	knuth_morris_pratt(const T& S_) : S(S_) {
		N = int(S.size());
		P.resize(N);
		int k = 0;
		for (int i = 1; i < N; ++i) {
			while (k > 0 && !(S[i] == S[k])) {
				k = P[k - 1];
			}
			if (S[i] == S[k]) {
				k++;
			}
			P[i] = k;
		}
	}

	// returns 0-indexed positions of occurences of S in H
	vector<int> kmp_search(const T& H) {
		vector<int>res;
		int M = int(H.size());
		if (M < N) {
			return res;
		}
		int k = 0;
		for (int i = 0; i < M; ++i) {
			while (k > 0 && (k == N || !(H[i] == S[k]))) {
				k = P[k - 1];
			}
			if (H[i] == S[k]) {
				k++;
			}
			if (k == N) {
				res.emplace_back(i - N + 1);
			}
		}
		return res;
	}
};
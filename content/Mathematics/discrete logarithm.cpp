// Discrete Logarithm
//
// Solves A^{X} mod M = B mod M in X
// Solution does not always exists
template<typename T>
class discrete_logarithm {
  private:
	T A, B, M;
  public:
	discrete_logarithm(T A_, T B_, T M_): A(A_), B(B_), M(M_) {}

	// Time: O(sqrt(M))
	T solve() {
		A %= M;
		B %= M;
		T K = 1, add{};
		T g = __gcd(A, M);
		while (g > 1) {
			if (B == K) {
				return add;
			}
			if (B % g != 0) {
				return -1;
			}
			B /= g, M /= g;
			add++;
			K = (K * 1ll * A / g) % M;
			g = __gcd(A, M);
		}
		T N = sqrt(M) + 1;
		T an = 1;
		for (T i = 0; i < N; ++i) {
			an = (an * 1ll * A) % M;
		}

		unordered_map<T, T> vals;
		vals.reserve(N + 1);
		for (T q = 0, cur = B; q <= N; ++q) {
			vals[cur] = q;
			cur = (cur * 1ll * A) % M;
		}

		for (T p = 1, cur = K; p <= N; ++p) {
			cur = (cur * 1ll * an) % M;
			if (vals.count(cur)) {
				T ans = N * p - vals[cur] + add;
				return ans;
			}
		}
		return -1;
	}
};
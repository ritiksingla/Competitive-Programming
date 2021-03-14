// Factorizer
//
template<typename T>
struct factorizer {
  private:
	int precalculated = 1;
  public:
	vector<T> least = {0, 1};
	vector<T> primes; // Primes can be greater than int in segmented_sieve
	vector<bool>is_prime;
	bool trial_division(const T& N) {
		for (T x = 2; x * x <= N; x++) {
			if (N % x == 0) {
				return false;
			}
		}
		return true;
	}
	template<typename U>
	bool miller_rabin(const U& N, const vector<U>& bases) {
		if (N < 2) {
			return false;
		}
		vector<U> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
		for (const U& x : small_primes) {
			if (N % x == 0) {
				return N == x;
			}
		}
		if (N < 31 * 31) {
			return true;
		}
		int s = 0;
		U d = N - 1;
		while ((d & 1) == 0) {
			d >>= 1;
			s++;
		}
		// N - 1 = 2^{s} * d
		for (const U& a : bases) {
			if (a % N == 0) {
				continue;
			}
			modular<U>M(N);
			U cur = M.power(a, d);
			if (cur == 1) {
				continue;
			}
			bool witness = true;
			for (int r = 0; r < s; r++) {
				if (cur == N - 1) {
					witness = false;
					break;
				}
				cur = M.mul(cur, cur);
			}
			if (witness) {
				return false;
			}
		}
		return true;
	}

	bool miller_rabin(const int32_t& N) {
		return miller_rabin(N, {2, 7, 61});
	}

	bool miller_rabin(const int64_t& N) {
		return miller_rabin(N, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
	}
	// Only if you really need uint64_t version
	/* bool miller_rabin(const uint64_t &N) {
		if (N < 2) {
			return false;
		}
		vector<uint32_t> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
		for (uint32_t x : small_primes) {
			if (N == x) {
				return true;
			}
			if (N % x == 0) {
				return false;
			}
		}
		if (N < 31 * 31) {
			return true;
		}
		uint32_t s = __builtin_ctzll(N - 1);
		uint64_t d = (N - 1) >> s;
		function<bool(uint64_t)> witness = [&N, &s, &d](uint64_t a) {
			uint64_t cur = 1, p = d;
			while (p > 0) {
				if (p & 1) {
					cur = (__uint128_t) cur * a % N;
				}
				a = (__uint128_t) a * a % N;
				p >>= 1;
			}
			if (cur == 1) {
				return false;
			}
			for (uint32_t r = 0; r < s; r++) {
				if (cur == N - 1) {
					return false;
				}
				cur = (__uint128_t) cur * cur % N;
			}
			return true;
		};
		vector<uint64_t> bases_64bit = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
		for (uint64_t a : bases_64bit) {
			if (a % N == 0) {
				return true;
			}
			if (witness(a)) {
				return false;
			}
		}
		return true;
	}*/

	// Time: O(N*ln(ln(√N))) + O(N)
	// Memory: O(N)
	void slow_sieve(const T& N) {
		least.assign(N + 1, 0);
		for (T i = 2; i * i <= N; i++) {
			if (least[i] == 0) {
				for (T j = i * i; j <= N; j += i) {
					if (least[j] == 0) {
						least[j] = i;
					}
				}
			}
		}
		primes.clear();
		for (T i = 2; i <= N; i++) {
			if (least[i] == 0) {
				least[i] = i;
				primes.push_back(i);
			}
		}
		precalculated = N;
	}
	// Time: O(N)
	// Memory: O(N)
	void linear_sieve(const T& N) {
		least.assign(N + 1, 0);
		is_prime.assign(N + 1, 0);
		primes.clear();
		for (T i = 2; i <= N; i++) {
			if (least[i] == 0) {
				least[i] = i;
				is_prime[i] = 1;
				primes.push_back(i);
			}
			for (T x : primes) {
				if (x > least[i] || i * x > N) {
					break;
				}
				least[i * x] = x;
			}
		}
		precalculated = N;
	}
	// Time: O((R − L + 1).log(log(R)) + (√R)log(log(√R)))
	// Space: O(max(R - L + 1, √R))
	// NOTE: Does not update least vector
	void segmented_sieve(T l, T r) {
		// assert(l >= 1 && (r - l + 1) <= (T)1e7);
		if (r < l) {
			return;
		}
		T sqrt_r = sqrt(r);
		vector<int>mark(sqrt_r + 1, 0);
		primes.clear();
		// Primes till sqrt_r
		for (T i = 2; i <= sqrt_r; ++i) {
			if (mark[i] == 0) {
				primes.push_back(i);
				for (T j = i * i; j <= sqrt_r; j += i) {
					mark[j] = i;
				}
			}
		}
		vector<int>vis(r - l + 1, 0);
		for (T p : primes) {
			for (T i = max(p * p, (l + p - 1) / p * p); i <= r; i += p) {
				assert(i - l >= 0 && i - l <= r - l);
				if (vis[i - l] == 0) {
					vis[i - l] = p;
				}
			}
		}
		if (l == 1) {
			vis[0] = 1;
		}
		primes.clear();
		for (T i = max(l, (T)2); i <= r; ++i) {
			if (vis[i - l] == 0) {
				primes.push_back(i);
			}
		}
	}
	vector<pair<T, int>> merge_factors(const vector<pair<T, int>>& A, const vector<pair<T, int>>& B) {
		vector<pair<T, int>>C;
		int i = 0;
		int j = 0;
		while (i < int(A.size()) || j < int(B.size())) {
			if (i < int(A.size()) && j < int(B.size()) && A[i].first == B[j].first) {
				C.emplace_back(A[i].first, A[i].second + B[j].second);
				++i;
				++j;
				continue;
			}
			if (j == int(B.size()) || (i < int(A.size()) && A[i].first < B[j].first)) {
				C.push_back(A[i++]);
			} else {
				C.push_back(B[j++]);
			}
		}
		return C;
	}
	vector<pair<T, int>> pollard_rho(const T& N, const T& c) {
		if (N <= 1) {
			return {};
		}
		if ((N & 1) == 0) {
			return merge_factors({{2, 1}}, pollard_rho(N / 2, c));
		}
		if (miller_rabin(N)) {
			return {{N, 1}};
		}

		// Brent's cycle detection
		T power = 1;
		T lambda = 1;
		modular<T>M(N);
		T x = 2;
		T saved = 2;
		while (true) {
			x = M.add(M.mul(x, x), c);
			T g = __gcd(M.sub(x, saved), N);
			if (g != 1) {
				return merge_factors(pollard_rho(g, c + 1), pollard_rho(N / g, c + 1));
			}
			if (power == lambda) {
				saved = x;
				power <<= 1;
				lambda = 0;
			}
			lambda++;
		}
		return {};
	}
	vector<pair<T, int>> pollard_rho(const T& N) {
		return pollard_rho(N, static_cast<T>(1));
	}

	vector<pair<T, int>> factorize(T X) {
		if (X <= 1) {
			return {};
		}
		if (X <= precalculated) {
			vector<pair<T, int>> ret;
			while (X > 1) {
				if (!ret.empty() && ret.back().first == least[X]) {
					ret.back().second++;
				} else {
					ret.emplace_back(least[X], 1);
				}
				X /= least[X];
			}
			return ret;
		}
		if (X <= static_cast<int64_t>(precalculated) * precalculated) {
			vector<pair<T, int>> ret;
			if (!miller_rabin(X)) {
				for (T i : primes) {
					T t = X / i;
					if (i > t) {
						break;
					}
					if (X == t * i) {
						int cnt = 0;
						while (X % i == 0) {
							X /= i;
							cnt++;
						}
						ret.emplace_back(i, cnt);
						if (miller_rabin(X)) {
							break;
						}
					}
				}
			}
			if (X > 1) {
				ret.emplace_back(X, 1);
			}
			return ret;
		}
		return pollard_rho(X);
	}

	vector<T> build_divisors_from_factors(const vector<pair<T, int>>& factors) {
		vector<T> divisors = {1};
		for (auto& p : factors) {
			int sz = int(divisors.size());
			for (int i = 0; i < sz; i++) {
				T cur = divisors[i];
				for (int j = 0; j < p.second; j++) {
					cur *= p.first;
					divisors.push_back(cur);
				}
			}
		}
		sort(begin(divisors), end(divisors));
		return divisors;
	}
	// Time: O(√N)
	// Count of numbers in [1,N] coprime to N
	int euler_totient(int N) {
		T res = N;
		for (int i = 2; i * i <= N; ++i) {
			if (N % i == 0) {
				while (N % i == 0) {
					N /= i;
				}
				res -= res / i;
			}
		}
		if (N > 1) {
			res -= res / N;
		}
		return res;
	}

	// Time: O(N.log(log(N)))
	// Count each prime's contribution only once
	vector<int> euler_totient_one_to_n(const int& N) {
		vector<int>phi(N + 1);
		iota(begin(phi), end(phi), 0);
		for (int i = 2; i <= N; ++i) {
			if (phi[i] == i) {
				for (int j = i; j <= N; j += i) {
					phi[j] -= phi[j] / i;
				}
			}
		}
		return phi;
	}

	// Time: O(N.log(N))
	// As ∑ (d|n) phi(d) = n by Gauss
	vector<int> slow_euler_totient_one_to_n(const int& N) {
		vector<int>phi(N + 1);
		phi[0] = 0;
		phi[1] = 1;
		iota(begin(phi) + 2, end(phi), 1);
		for (int i = 2; i <= N; i++) {
			for (int j = 2 * i; j <= N; j += i) {
				phi[j] -= phi[i];
			}
		}
		return phi;
	}

	T number_of_divisors(const T& N) {
		auto v = factorize(N);
		T res = 1;
		for (auto x : v) {
			res *= (x.second + 1);
		}
		return res;
	}

	int64_t sum_of_divisors(const T& N) {
		int64_t res = 1;
		const int64_t MOD_ = 9223372036854775783;
		modular<int64_t>M(MOD_);
		auto v = factorize(N);
		for (auto x : v) {
			int64_t p = x.first;
			int64_t e = x.second;
			res = M.mul(res, M.mul(M.sub(M.power(p, e + 1), 1), M.inv(p - 1)));
		}
		return (int64_t)res;
	}
};
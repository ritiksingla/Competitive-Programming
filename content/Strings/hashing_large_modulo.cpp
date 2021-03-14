// String Rolling Hashing - modulo 2^61 - 1
//
// (Works for Mersenne Primes only!)
const int64_t MOD_ = int64_t(1LL << 61) - 1;
template<int64_t MOD_>
struct str_hash {

	static int64_t P;
	int N;
	string S;
	vector<int64_t>Hash, Powers;

	int64_t mul_mod(int64_t a, int64_t b) {
		const int64_t LOWER = (1LL << 30) - 1;
		const int64_t HIGHER = (1LL << 31) - 1;
		int64_t a1 = (a & LOWER), a2 = (a >> 30);
		int64_t b1 = (b & LOWER), b2 = (b >> 30);
		int64_t m = a1 * b2 + a2 * b1, h = a2 * b2;
		int64_t ans = a1 * b1 + (h >> 1) + ((h & 1) << 60) + (m >> 31) + ((m & HIGHER) << 30) + 1;
		ans = (ans & MOD_) + (ans >> 61);
		ans = (ans & MOD_) + (ans >> 61);
		return ans - 1;
	}

	str_hash(string S_) {
		N = static_cast<int>(S_.size());
		Hash.resize(N);
		Powers.resize(N);
		S = S_;
		Powers[0] = 1;
		for (int i = 1; i < N; ++i) {
			Powers[i] = mul_mod(Powers[i - 1], P);
		}
		Hash[0] = S[0];
		for (int i = 1; i < N; ++i) {
			Hash[i] = (mul_mod(Hash[i - 1], P) + S[i]) % MOD_;
		}
	}
	int64_t operator()(int l, int r) {
		assert(l <= r && l >= 0 && r < N);
		int64_t res = Hash[r];
		if (l) {
			res = res - mul_mod(Hash[l - 1], Powers[r - (l - 1)]);
		}
		if (res < 0) {
			res += MOD_;
		}
		return res;
	}

};

mt19937_64 rng((int64_t)chrono::steady_clock::now().time_since_epoch().count());

int64_t uniform(int64_t l, int64_t r) {
	uniform_int_distribution<int64_t> uid(l, r);
	return uid(rng);
}

const int ALPHABET_SIZE = 26;
template<int64_t MOD> int64_t str_hash<MOD>::P = uniform(ALPHABET_SIZE + 1, MOD - 1);
// Polynomial Rolling Hashing Function
//
// A rolling hash has two parameters (p, a) where p is the modulo and 0 ≤ a < p the base.
// 'p' should be a big prime and 'a' must be larger than the size  of the alphabet size.
// If two strings are same function never fails but it may fail if two different strings are compared.
// In the following code, fixed prime number is used and a is picked randomly over {alphabet_size + 1, p - 1}
// Let the rolling function be faild for two different strings S,T of equal length n. Therefore, h(S) = h(T)
// Sum_over_n (A^{n-i-1} * S[i]) mod p = Sum_over_n (A^{n-i-1} * T[i]) mod p
// Sum_over_n (A^{n-i-1} * S[i] - T[i]) = 0 (mod p)
// Therefore h(S) = h(T) if the equation uses A as a root of degree <= (n-1)
// Probability of choosing A as a root = (n-1)/p

template<int MOD_>
struct str_hash {

	static int P;
	int N;
	string S;
	vector<int64_t>Hash, Powers;

	str_hash(string S_) {
		N = static_cast<int>(S_.size());
		Hash.resize(N);
		Powers.resize(N);
		S = S_;
		Powers[0] = 1;
		for (int i = 1; i < N; ++i) {
			Powers[i] = Powers[i - 1] * P % MOD_;
		}
		Hash[0] = S[0];
		for (int i = 1; i < N; ++i) {
			Hash[i] = (Hash[i - 1] * P + S[i]) % MOD_;
		}
	}
	int operator()(int l, int r) {
		assert(l <= r && l >= 0 && r < N);
		int res = Hash[r];
		if (l) {
			res = res - Hash[l - 1] * Powers[r - (l - 1)] % MOD_;
		}
		if (res < 0) {
			res += MOD_;
		}
		return res;
	}

};

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

const int ALPHABET_SIZE = 26;
template<int MOD> int str_hash<MOD>::P = uniform(ALPHABET_SIZE + 1, MOD - 1);
const int MOD_ = int(1e9) + 7;
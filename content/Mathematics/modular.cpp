// Modular Arithmetic
//
template<typename T>
struct modular {
private:
	const T mod;
	int precalculated = 1;
public:
	vector<T>inverse{1, 1};
	modular(T mod_): mod(mod_) {}
	inline T add(T a, T b) {
		if (a >= mod) a %= mod;
		if (b >= mod) b %= mod;

		a += b;
		if (a >= mod) a -= mod;
		return a;
	}
	inline T sub(T a, T b) {
		if (a >= mod) a %= mod;
		if (b >= mod) b %= mod;

		a -= b;
		if (a < 0) a += mod;
		return a;
	}
	T mul(T a, T b)
	{
		long double x;
		T c;
		T r;
		if (a >= mod) a %= mod;
		if (b >= mod) b %= mod;
		x = a;
		c = x * b / mod;
		r = (T)(a * b - c * mod) % (T)mod;
		return r < 0 ? r + mod : r;
	}
	inline T power(T a, T b) {
		T res = 1;
		if (a >= mod) a %= mod;
		// If a and m are coprime, then Euler's theorem states that a^{phi(m)} mod m = 1
		// This reduces to a^{m-1}mod m = 1 for prime m which is Fermat's Little Theorem
		// Therefore, a^{n} mod m = a^{n mod phi(m)} mod m
		
		// Check if phi(mod) = m then only do b %= (m);
		
		while (b > 0) {
			if (b & 1)
				res = mul(res, a);
			a = mul(a, a);
			b = b >> 1;
		}
		return res;
	}
	inline T inv(T a) {
		a %= mod;
		if (a < 0) a += mod;
		T b = mod, u = 0, v = 1;
		while (a) {
			T t = b / a;
			b -= t * a;
			swap(a, b);
			u -= t * v;
			swap(u, v);
		}
		assert(b == 1);
		if (u < 0) u += mod;
		return u;
	}
	void inverse_inrange(const int &N) {
		if (N <= precalculated) return;
		inverse.resize(N + 1);
		for (int i = precalculated + 1; i <= N; ++i) {
			inverse[i] = sub(0, mul((mod / i), inverse[mod % i]));
		}
		precalculated = N;
	}
};
// Modular Arithmetic
//
template<typename T>
struct modular {
  private:
	const T mod;
  public:
	modular(T mod_): mod(mod_) {}
	inline T add(T a, T b) {
		a += b;
		if (a >= mod) {
			a -= mod;
		}
		return a;
	}
	inline T sub(T a, T b) {
		a -= b;
		if (a < 0) {
			a += mod;
		}
		return a;
	}
	T mul(T a, T b) {
		return (a * 1ll * b) % mod;
	}
	inline T power(T a, T b) {
		T res = 1;
		a %= mod;
		if (a < 0) {
			a += mod;
		}
		while (b > 0) {
			if (b & 1) {
				res = mul(res, a);
			}
			a = mul(a, a);
			b = b >> 1;
		}
		return res;
	}
	inline T inv(T a) {
		a %= mod;
		if (a < 0) {
			a += mod;
		}
		T b = mod, u = 0, v = 1;
		while (a) {
			T t = b / a;
			b -= t * a;
			swap(a, b);
			u -= t * v;
			swap(u, v);
		}
		assert(b == 1);
		if (u < 0) {
			u += mod;
		}
		return u;
	}
};
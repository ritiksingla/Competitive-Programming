// Mint
//
template <int MOD_>
struct modnum {
	static constexpr int MOD = MOD_;
	static_assert(MOD_ > 0, "MOD must be positive");

  private:
	int v;
	static int inv(int a, int m) {
		a %= m;
		if (a < 0) {
			a += m;
		}
		int b = m, u = 0, v = 1;
		while (a) {
			int t = b / a;
			b -= t * a;
			swap(a, b);
			u -= t * v;
			swap(u, v);
		}
		assert(b == 1);
		if (u < 0) {
			u += m;
		}
		return u;
	}

  public:
	modnum() : v(0) {}

	modnum(int64_t v_) : v(int(v_ % MOD)) {
		if (v < 0) {
			v += MOD;
		}
	}

	explicit operator int() const {
		return v;
	}

	friend std::ostream& operator << (std::ostream& out, const modnum& n) {
		return out << int(n);
	}

	friend std::istream& operator >> (std::istream& in, modnum& n) {
		int64_t v_;
		in >> v_;
		n = modnum(v_);
		return in;
	}

	friend bool operator == (const modnum& a, const modnum& b) {
		return a.v == b.v;
	}

	friend bool operator != (const modnum& a, const modnum& b) {
		return a.v != b.v;
	}

	modnum inv() const {
		modnum res;
		res.v = inv(v, MOD);
		return res;
	}

	friend modnum inv(const modnum& m) {
		return m.inv();
	}

	modnum neg() const {
		modnum res;
		res.v = v ? MOD - v : 0;
		return res;
	}

	friend modnum neg(const modnum& m) {
		return m.neg();
	}

	modnum operator- () const {
		return neg();
	}

	modnum operator+ () const {
		return modnum(*this);
	}

	modnum& operator ++ () {
		v ++;
		if (v == MOD) {
			v = 0;
		}
		return *this;
	}

	modnum& operator -- () {
		if (v == 0) {
			v = MOD;
		}
		v --;
		return *this;
	}

	modnum& operator += (const modnum& o) {
		v -= MOD - o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}

	modnum& operator -= (const modnum& o) {
		v -= o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}

	modnum& operator *= (const modnum& o) {
		v = int(int64_t(v) * int64_t(o.v) % MOD);
		return *this;
	}

	modnum& operator /= (const modnum& o) {
		return *this *= o.inv();
	}

	friend modnum operator ++ (modnum& a, int) {
		modnum r = a;
		++a;
		return r;
	}

	friend modnum operator -- (modnum& a, int) {
		modnum r = a;
		--a;
		return r;
	}

	friend modnum operator + (const modnum& a, const modnum& b) {
		return modnum(a) += b;
	}

	friend modnum operator - (const modnum& a, const modnum& b) {
		return modnum(a) -= b;
	}

	friend modnum operator * (const modnum& a, const modnum& b) {
		return modnum(a) *= b;
	}

	friend modnum operator / (const modnum& a, const modnum& b) {
		return modnum(a) /= b;
	}
};

template <typename T>
T power(T a, long long b) {
	assert(b >= 0);
	T r = 1;
	while (b) {
		if (b & 1) {
			r *= a;
		}
		b >>= 1;
		a *= a;
	}
	return r;
}

const int mod = int(1e9) + 7;
using mint = modnum<mod>;
// FFT Namespace
// 
namespace fft {

const double PI = acos(-1);

struct num {
	double x, y;

	num(double x = 0, double y = 0) : x(x), y(y) {
	}

	num operator+(const num& o) const {
		return num(x + o.x, y + o.y);
	}

	num operator-(const num& o) const {
		return num(x - o.x, y - o.y);
	}

	num operator*(const num& o) const {
		return num(x * o.x - y * o.y, x * o.y + y * o.x);
	}
};

num conj(num a) {
	return num(a.x, -a.y);
}

vector<num> fa, fb, roots = {num(0, 0), num(1, 0)};
vector<int> rev = {0, 1};
int base = 1;

void ensure_base(int nbase) {
	if (nbase <= base) {
		return;
	}
	rev.resize(1 << nbase);
	for (int i = 0; i < (1 << nbase); ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nbase - 1));
	}
	roots.resize(1 << nbase);
	while (base < nbase) {
		double angle = 2 * PI / (1 << (base + 1));
		for (int i = 1 << (base - 1); i < (1 << base); ++i) {
			roots[i << 1] = roots[i];
			double ang = angle * ((i << 1) + 1 - (1 << base));
			roots[i << 1 | 1] = num(cos(ang), sin(ang));
		}
		++base;
	}
}

void dft(vector<num>& a, int n) {
	int zeros = __builtin_ctz(n);
	ensure_base(zeros);
	int shift = base - zeros;
	for (int i = 0; i < n; ++i) {
		if (i < (rev[i] >> shift)) {
			swap(a[i], a[rev[i] >> shift]);
		}
	}
	for (int i = 1; i < n; i <<= 1) {
		for (int j = 0; j < n; j += i << 1) {
			for (int k = 0; k < i; ++k) {
				num x = a[j + k], y = a[j + k + i] * roots[i + k];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
}

vector<long long> multiply(const vector<int>& a, const vector<int>& b) {
	int need = a.size() + b.size() - 1, nbase = 0;
	while (1 << nbase < need) {
		++nbase;
	}
	ensure_base(nbase);
	bool equal = a == b;
	int sz = 1 << nbase;
	if (sz > (int) fa.size()) {
		fa.resize(sz);
	}
	if (sz > (int) fb.size()) {
		fb.resize(sz);
	}
	for (int i = 0; i < (int) a.size(); i++) {
		int x = a[i];
		fa[i] = num(x & ((1 << 15) - 1), x >> 15);
	}
	for (int i = (int) a.size(); i < sz; ++i) {
		fa[i] = num(0, 0);
	}
	dft(fa, sz);
	if (equal) {
		for (int i = 0; i < sz; ++i) {
			fb[i] = fa[i];
		}
	} else {
		for (int i = 0; i < (int) b.size(); ++i) {
			int x = b[i];
			fb[i] = num(x & ((1 << 15) - 1), x >> 15);
		}
		for (int i = (int) b.size(); i < sz; ++i) {
			fb[i] = num(0, 0);
		}
		dft(fb, sz);
	}
	double ratio = 0.25 / sz;
	num r1(1, 0), r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
	for (int i = 0; i <= sz >> 1; ++i) {
		int j = (sz - i) & (sz - 1);
		num a1 = (fa[i] + conj(fa[j])) * r1;
		num a2 = (fa[i] - conj(fa[j])) * r2;
		num b1 = (fb[i] + conj(fb[j])) * r3;
		num b2 = (fb[i] - conj(fb[j])) * r4;
		if (i != j) {
			num c1 = (fa[j] + conj(fa[i])) * r1;
			num c2 = (fa[j] - conj(fa[i])) * r2;
			num d1 = (fb[j] + conj(fb[i])) * r3;
			num d2 = (fb[j] - conj(fb[i])) * r4;
			fa[i] = c1 * d1 + c2 * d2 * r5;
			fb[i] = c1 * d2 + c2 * d1;
		}
		fa[j] = a1 * b1 + a2 * b2 * r5;
		fb[j] = a1 * b2 + a2 * b1;
	}
	dft(fa, sz);
	dft(fb, sz);
	vector<long long> c(need);
	for (int i = 0; i < need; i++) {
		long long aa = fa[i].x + 0.5;
		long long bb = fb[i].x + 0.5;
		long long cc = fa[i].y + 0.5;
		c[i] = aa + (bb << 15) + (cc << 30);
	}
	return c;
}
}

using fft::multiply;

vector<long long> operator*(vector<int>& a, const vector<int>& b) {
	return multiply(a, b);
}

template <typename T>
vector<T>& operator+=(vector<T>& a, const vector<T>& b) {
	if (a.size() < b.size()) {
		a.resize(b.size());
	}
	for (int i = 0; i < (int) b.size(); i++) {
		a[i] += b[i];
	}
	return a;
}

template <typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
	vector<T> c = a;
	return c += b;
}
// Chinese Remainder Theorem
//
// x = a1 (mod n1), x = a2 (mod n2)
// x = a1 + n1.k1 and x = a2 + n2.k2
// a1 + n1.k1 = a2 + n2.k2
// n1(-k1) + n2(k2) = a1 - a1 (Linear Diophantine Equation)
// two solutions if exist will be x1 = a1 (mod n1) = x2 and x1 = a2 (mod n2) = x2
// Therefore, x1 = x2 mod (LCM(n1, n2))
// Now just merge all congurences taking solved one x = x1 mod (LCM(n1,n2)) and x = x3 (mod n3) and so on

tuple<int64_t, int64_t, int64_t> ext_gcd(int64_t a, int64_t b) {
	if (!a) return {b, 0, 1};
	tuple<int64_t, int64_t, int64_t>T = ext_gcd(b % a, a);
	int64_t g, x, y;
	tie(g, x, y) = T;
	return {g, y - b / a * x, x};
}

struct crt {
	int64_t a, m;

	crt() : a(0), m(1) {}
	crt(int64_t a_, int64_t m_) : a(a_), m(m_) {}
	crt operator * (crt C) {
		tuple<int64_t, int64_t, int64_t>T = ext_gcd(m, C.m);
		int64_t g, x, y;
		tie(g, x, y) = T;
		if ((a - C.a) % g) a = -1;
		if (a == -1 or C.a == -1) return crt(-1, 0);
		int64_t lcm = m / g * C.m;
		int64_t ans = a + (x * (C.a - a) / g % (C.m / g)) * m;
		return crt((ans % lcm + lcm) % lcm, lcm);
	}
	crt operator *= (crt C) {
		(*this) = (*this) * C;
		return (*this);
	}
};
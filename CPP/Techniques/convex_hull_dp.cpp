// Convex Hull Trick
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define sz(x) (int)(x).size()
// dp[i] = max,min(dp[i], dp[j] + fun(i) * fun(j));
/*  Container where you can add lines of the form ax+b, and
    get_max maximum values at points x. For each line, also keeps a value p,
    which is the last (maximum) point for which the current line is dominant.
    (obviously, for the last line, p is infinity) Useful for dynamic programming.
*/
/*
    Suppose l_1, l_2, and l_3 are the second line from the top,
    the line at the top, and the line to be added, respectively.
    Then, l_2 becomes irrelevant if and only if the intersection point
    of l_1 and l_3 is to the left of the intersection of l_1 and l_2.
    (This makes sense because it means that the interval in which l_3
    is minimal subsumes that in which l_2 was previously.)
    We have assumed for the sake of simplicity that no three lines
    are concurrent.
*/

/* Simple Implementation */
vector<ll>M, C;
int p;
bool bad(ll l1, ll l2, ll l3) {
    return (C[l3] - C[l1]) * (ld)(M[l2] - M[l3]) <= (C[l3] - C[l2]) * (ld)(M[l1] - M[l3]);
}
void add(ll m, ll c) {
    M.push_back(m), C.push_back(c);
    while (sz(M) >= 3 && bad(sz(M) - 3, sz(M) - 2, sz(M) - 1)) {
        M[sz(M) - 2] = M[sz(M) - 1];
        C[sz(M) - 2] = C[sz(M) - 1];
        M.pop_back();
        C.pop_back();
    }
}
ll query(ll x) {
    if (p >= sz(M)) {
        p = sz(M) - 1;
    }
    // change sign accordingly to min,max
    while (p + 1 < sz(M) && M[p]*x + C[p] <= M[p + 1]*x + C[p + 1]) {
        p++;
    }
    return M[p] * x + C[p];
}

/* Complex Implementation */
struct Line {
	mutable long long slope, bias, p;
	bool operator<(const Line& o) const {
		return slope < o.slope;
	}
	bool operator<(long long x) const {
		return p < x;
	}
}; // Line
struct LineContainer : multiset<Line, less<>> {
	const long long inf = numeric_limits<long long>::max();
	long long div(long long a, long long b) {
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) {
			x->p = inf;
			return false;
		}
		if (x->slope == y->slope) {
			x->p = x->bias > y->bias ? inf : -inf;
		} else {
			x->p = div(y->bias - x->bias, x->slope - y->slope);
		}
		return x->p >= y->p;
	}
	void add(long long slope, long long bias) {
		auto z = insert({slope, bias, 0}), y = z++, x = y;
		while (isect(y, z)) {
			z = erase(z);
		}
		if (x != begin() && isect(--x, y)) {
			isect(x, y = erase(y));
		}
		while ((y = x) != begin() && (--x)->p >= y->p) {
			isect(x, erase(y));
		}
	}
	long long query(long long x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.slope * x + l.bias;
	}
}; // LineContainer
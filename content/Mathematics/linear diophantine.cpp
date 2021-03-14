// Linear Diophantine
//
// Solves ax + by = c (when a, b, and c are given).
// If a = b = 0 then there is no solution if c != 0 and infinitely many solutions if c = 0. We will ignore this case
// From extended_gcd algorithm find xg, yg such that a.xg + b.yg = gcd(a, b) = g(say);
// Then on solution is a.xg.c / g + b.yg.c / g = c; with x = xg.c/g and y = yg.c/g
// As g | a and g | b therefore g must also divide any linear combination of a and b.
// This gives the proof to the following algorithm.

template<typename T>
class linear_diophantine :  public linear_equations<T> {
  protected:
	using linear_equations<T>::A;
	using linear_equations<T>::B;
	using linear_equations<T>::gcd;
	using linear_equations<T>::extended_gcd;
  public:
	T C;
	linear_diophantine(T A_, T B_, T C_): linear_equations<T>(A_, B_) {
		C = C_;
	}

	vector<T> find_one_solution() {
		T x, y;
		T g = extended_gcd(abs(A), abs(B), x, y);
		if (C % g != 0) {
			return vector<T>();
		}
		vector<T> solution;
		x *= C / g;
		y *= C / g;
		if (A < 0) {
			x = -x;
		}
		if (B < 0) {
			y = -y;
		}
		assert(A * x + B * y == C);
		solution.push_back(x);
		solution.push_back(y);
		return solution;
	}

	vector<vector<T>> n_solutions(int N) {
		auto solution = find_one_solution();
		if (solution.empty()) {
			return vector<vector<T>>();
		}
		T x = solution[0], y = solution[1];
		vector<vector<T>> solutions;
		for (int i = 0; i < N; ++i) {
			T x_ = x + B / gcd * i;
			T y_ = y - A / gcd * i;
			assert(A * x_ + B * y_ == C);
			solutions.push_back({x_, y_});
		}
		return solutions;
	}
	T solve_with_one_var(T coef, T C, T lower, T upper) {
		if (C % coef != 0) {
			return 0;
		}
		T solution = -C / coef;
		return (T)(solution >= lower && solution <= upper) ? 1 : 0;
	}
	void shift_solution(T& x, T& y, T a, T b, T cnt) {
		x += cnt * b;
		y -= cnt * a;
	}
	T find_inrange(T lx, T rx, T ly, T ry) {
		if (rx < lx || ry < ly) {
			return 0;
		}

		if (A == 0 && B == 0) {
			if (C != 0) {
				return 0;
			}
			return (rx - lx + 1) * (ry - ly + 1);
		}

		if (A == 0) {
			return solve_with_one_var(B, C, ly, ry) * (rx - lx + 1);
		}
		if (B == 0) {
			return solve_with_one_var(A, C, lx, rx) * (ry - ly + 1);
		}

		if (C % gcd != 0) {
			return 0;
		}

		T u = A / gcd;
		T v = B / gcd;
		auto s = find_one_solution();

		int sign_a = u > 0 ? +1 : -1;
		int sign_b = v > 0 ? +1 : -1;
		T x = s[0], y = s[1];

		// Find lx1
		shift_solution(x, y, u, v, (lx - x) / v);
		if (x < lx) {
			shift_solution(x, y, u, v, sign_b);
		}
		T lx1 = x;

		// Find rx1
		shift_solution(x, y, u, v, (rx - x) / v);
		if (x > rx) {
			shift_solution(x, y, u, v, -sign_b);
		}
		T rx1 = x;

		if (lx1 > rx1) {
			swap(lx1, rx1);
		}

		// Find lx2
		shift_solution(x, y, u, v, -(ly - y) / u);
		if (y < ly) {
			shift_solution(x, y, u, v, -sign_a);
		}
		T lx2 = x;

		// Find rx2
		shift_solution(x, y, u, v, -(ry - y) / u);
		if (y > ry) {
			shift_solution(x, y, u, v, sign_a);
		}
		T rx2 = x;

		if (lx2 > rx2) {
			swap(lx2, rx2);
		}
		T l = max(lx1, lx2);
		T r = min(rx1, rx2);

		if (l > r) {
			return 0;
		}
		return (r - l) / abs(v) + 1;
	}
};
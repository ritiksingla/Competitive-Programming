// Linear Congruence
//
// Find solutions for AX mod B = C mod B in X
template<typename T>
class LinearCongruence {
  private:
	T A;
	T B;
	T C;
	T gcd;
  public:
	LinearCongruence(T A_, T B_, T C_): A(A_), B(B_), C(C_) {
		gcd = __gcd(A, B);
	}
	vector<T> solve() {
		if (gcd == 1) { // Unique solution
			Modular<T>M(B);
			return {M.mul(M.inv(A), C)};
		} else if (C % gcd == 0) { // Number of unique solutions = gcd;
			vector<T>solutions;
			T a = A / gcd;
			T b = B / gcd;
			T c = C / gcd;
			// aX mod b = c mod b
			Modular<T>M1(b);
			T X = M1.mul(M1.inv(a), c);
			Modular<T>M2(B);
			for (T i = 0; i < gcd; ++i) {
				solutions.emplace_back(M2.add(X, M2.mul(i, b)));
			}
			return solutions;
		} else {
			return {}; // No solution
		}
	}
};
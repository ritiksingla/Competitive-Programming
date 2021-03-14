// Linear Equations
//
// Solves the GCD, Extended GCD, and Linear Diophantine Equations
template<typename T>
class linear_equations {
  protected:
	T A, B;
	T gcd;
  public:
	linear_equations(T A_, T B_): A(A_), B(B_) {
		gcd = euclid_gcd(A, B);
	}

	// a >= 0, b > 0
	// O(log(min(a, b)))
	// Two consecutive fibonacci numbers are the worst case input for euclid's gcd
	// As g | a and g | b therefore g must also divide any linear combination of a and b.
	// This gives the proof to the following algorithm.
	T euclid_gcd(T a, T b) {
		if (b == 0) {
			return a;
		}
		return euclid_gcd(b, a % b);
	}

	T lcm() {
		// Avoid possible T-overflow when g first divides a or b
		return (T) A / gcd * B;
	}

	// ax + by = gcd(a, b) = g;
	// bx1 + (a mod b)y1 = g;
	// bx1 + [a - (a/b)*b]y1 = g;
	// ay1 + b(x1 - (a/b)y1) = g;
	// Therfore, x = y1 and y = x1 - (a/b)y1;
	T extended_gcd(T a, T b, T& x, T& y) {
		if (b == 0) {
			x = 1, y = 0;
			return a;
		}
		T x1, y1;
		T g = extended_gcd(b, a % b, x1, y1);
		x = y1;
		y = x1 - (a / b) * y1;
		return g;
	}
};
// Primitive Root
//
// g is primitive root mod N, If and only if for all A coprime to N,
// there exists an integer K such that (g^ {K} mod N) == (A mod N), i.e.,
// powers of g can generate all such A's and thus also called generator
// of the multiplicative group of integers mod N;
// K is called index or discrete logarithm of A to the base g mod N;

// In most cases N is prime. In that case K runs from 1 to N - 1 as in NTT.
// N can be {1, 2, 4, power of odd prime, 2 * (power of odd prime)}

// Number of primitive root mod N = euler_totient(euler_totient(N)) or none.
template<typename T>
class primitive_root {
  private:
	T N;
  public:
	primitive_root(T N_): N(N_) {}
	vector<T> solve(int limit = 10) {
		vector<T> fact;
		vector<T>solutions;
		solutions.reserve(limit);

		const T phi = N - 1;
		T n = phi;
		for (T i = 2; i * i <= n; ++i)
			if (n % i == 0) {
				fact.push_back(i);
				while (n % i == 0) {
					n /= i;
				}
			}
		if (n > 1) {
			fact.push_back(n);
		}

		modular<T>M(N);
		for (T res = 2; res <= N; ++res) {
			bool ok = true;
			for (size_t i = 0; i < fact.size() && ok; ++i) {
				ok &= (M.power(res, phi / fact[i]) != 1);
			}
			if (ok)  {
				solutions.emplace_back(res);
				if (int(solutions.size()) == limit) {
					return solutions;
				}
			}
		}
		return solutions;
	}
};
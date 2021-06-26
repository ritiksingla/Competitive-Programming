// Discrete Root
//
// Solves X^{K} mod N = A mod N for prime N, A, K in X
template<typename T>
class DiscreteRoot {
  private:
	T N, A, K;
  public:
	DiscreteRoot(T K_, T A_, T N_) : K(K_), A(A_), N(N_)  {}
	vector<T>solve() {
		if (A == 0) {
			return {0};
		}
		PrimitiveRoot<T>PR(N);
		auto primitive_root_solution = PR.solve(1);
		assert(int(primitive_root_solution.size()) == 1);
		T g = primitive_root_solution[0];
		Modular<T>M(N);
		DiscreteLogarithm<T>DL(M.power(g, K), A, N);
		T ans = DL.solve();
		if (ans == -1) {
			return vector<T>();
		}
		vector<T>solutions;
		T delta = (N - 1) / __gcd(K, N - 1);
		for (T cur = ans % delta; cur < N - 1; cur += delta) {
			solutions.emplace_back(M.power(g, cur));
		}
		return solutions;
	}
};
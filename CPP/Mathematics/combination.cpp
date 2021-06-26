// Combination
//
vector<mint> fact(1, 1);
vector<mint> inv_fact(1, 1);

mint C(int n, int k) {
	if (k < 0 || k > n) {
		return 0;
	}
	while ((int) fact.size() < n + 1) {
		fact.push_back(fact.back() * (int) fact.size());
		inv_fact.push_back(1 / fact.back());
	}
	return fact[n] * inv_fact[k] * inv_fact[n - k];
}
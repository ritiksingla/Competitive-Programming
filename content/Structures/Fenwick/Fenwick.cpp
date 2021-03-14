// Fenwick Tree
//
template <typename T, class F = function<T(const T&, const T&)>>
class fenwick {

  private:
	vector<T> fenw;
	int N;
	F func;
	T initializer;

  public:
	fenwick(T initializer_): N(), initializer(initializer_) {}
	fenwick(const int& N_, T initializer_, const F& f) : N(N_), func(f), initializer(initializer_) {
		fenw.resize(N, initializer);
	}

	fenwick(const vector<T>& A, T initializer_, const F& f): func(f), initializer(initializer_) {
		N = static_cast<int>(A.size());
		fenw.resize(N, initializer);
		for (int i = 0; i < N; ++i) {
			modify(i, A[i]);
		}
	}

	void modify(int x, const T& v) {
		assert(x >= 0);
		while (x < N) {
			fenw[x] = func(fenw[x], v);
			x |= (x + 1);
		}
	}

	T get(int x) {
		assert(x < N);
		T v = initializer;
		while (x >= 0) {
			v = func(v, fenw[x]);
			x = (x & (x + 1)) - 1;
		}
		return v;
	}

	void modify(int x, int y, const T& v) {
		assert(x <= y && x >= 0 && y < N);
		modify(x, v);
		modify(y + 1, -v);
	}
};
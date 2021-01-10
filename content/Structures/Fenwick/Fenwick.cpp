// Fenwick Tree
//
template <typename T>
class fenwick {
private:
	vector<T> fenw;
	int N;
public:
	fenwick (): N() {}
	fenwick(const int& N_) : N(N_) {
		fenw.resize(N);
	}

	fenwick(const vector<T>& A) {
		N = static_cast<T>(A.size());
		fenw.resize(N);
		for (int i = 0; i < N; ++i) {
			modify(i, A[i]);
		}
	}
	
	// 1. Point update and range query
	void modify(int x, const T& v) {
		assert(x >= 0);
		while (x < N) {
			fenw[x] += v;
			x |= (x + 1);
		}
	}

	T get(int x) {
		assert(x < N);
		T v{};
		while (x >= 0) {
			v += fenw[x];
			x = (x & (x + 1)) - 1;
		}
		return v;
	}

	// 2. Range update and point query
	// Have to call modify(i, i, v) for initial vector
	void modify(int x, int y, const T& v) {
		assert(x <= y && x >= 0 && y < N);
		modify(x, v);
		modify(y + 1, -v);
	}
	// Same get method for A[x] not A[0:x]
};
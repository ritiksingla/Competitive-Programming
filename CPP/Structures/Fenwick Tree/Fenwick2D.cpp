// Fenwick 2D
//
template <typename T, class F = function<T(const T&, const T&)>>
class Fenwick2D {
  private:
	vector<vector<T>> mat;
	int N, M;
	F func;
	T initializer;

  public:
	Fenwick2D(vector<vector<T>>A, T initializer_, const F& f) : initializer(initializer_), func(f) {
		N = int(A.size());
		M = int(A[0].size());
		mat.resize(N);
		for (int i = 0; i < N; i++) {
			mat[i].resize(M, initializer);
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				modify(i, j, A[i][j]);
			}
		}
	}

	Fenwick2D(int N_, int M_, T initializer_, const F& f) : N(N_), M(M_), initializer(initializer_), func(f) {
		mat.resize(N);
		for (int i = 0; i < N; i++) {
			mat[i].resize(M, initializer);
		}
	}
	inline void modify(int i, int j, T v) {
		assert(i >= 0 && j >= 0 && i < N && j < M);
		int x = i;
		while (x < N) {
			int y = j;
			while (y < M) {
				mat[x][y] = func(mat[x][y], v);
				y |= (y + 1);
			}
			x |= (x + 1);
		}
	}
	inline T get(int i, int j) {
		assert(i >= 0 && j >= 0 && i < N && j < M);
		T v = initializer;
		int x = i;
		while (x >= 0) {
			int y = j;
			while (y >= 0) {
				v = func(v, mat[x][y]);
				y = (y & (y + 1)) - 1;
			}
			x = (x & (x + 1)) - 1;
		}
		return v;
	}
};
// Fenwick 2D
//
template <typename T>
class fenwick2d {
private:
	vector<vector<T>> mat;
	int N, M;
public:
	fenwick2d(int N_, int M_) : N(N_), M(M_) {
		mat.resize(N);
		for (int i = 0; i < N; i++) {
			mat[i].resize(M);
		}
	}
	inline void modify(int i, int j, T v) {
		assert(i >= 0 && j >= 0 && i < N && j < M);
		int x = i;
		while (x < N) {
			int y = j;
			while (y < M) {
				mat[x][y] += v;
				y |= (y + 1);
			}
			x |= (x + 1);
		}
	}
	inline T get(int i, int j) {
		assert(i >= 0 && j >= 0 && i < N && j < M);
		T v{};
		int x = i;
		while (x >= 0) {
			int y = j;
			while (y >= 0) {
				v += mat[x][y];
				y = (y & (y + 1)) - 1;
			}
			x = (x & (x + 1)) - 1;
		}
		return v;
	}
	inline T get(int x1, int y1, int x2, int y2) {
		assert(x1 <= x2 && y1 <= y2 && x1 >= 0 && y1 >= 0 && x2 < N && y2 < M);
		T res{};
		res += get(x2, y2);
		if (x1 > 0)
			res -= get(x1 - 1, y2);
		if (y1 > 0)
			res -= get(x2, y1 - 1);
		if (x1 > 0 && y1 > 0)
			res += get(x1 - 1, y1 - 1);
		return res;
	}
};
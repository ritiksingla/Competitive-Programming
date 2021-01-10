// Fenwick 3D
//
template <typename T>
class fenwick3d {
private:
	tensor<T, 3>*mat;
	int A, B, C;
public:
	fenwick3d(int A_, int B_, int C_) : A(A_), B(B_), C(C_) {
		mat = new tensor<T, 3>({A, B, C});
	}
	inline void modify(int i, int j, int k, T v) {
		assert(i >= 0 && j >= 0 && i < A && j < B && k >= 0 && k < C);
		int x = i;
		while (x < A) {
			int y = j;
			while (y < B) {
				int z = k;
				while (z < C) {
					mat->at({x, y, z}) += v;
					z |= (z + 1);
				}
				y |= (y + 1);
			}
			x |= (x + 1);
		}
	}
	inline T get(int i, int j, int k) {
		assert(i >= 0 && j >= 0 && i < A && j < B && k >= 0 && k < C);
		T v{};
		int x = i;
		while (x >= 0) {
			int y = j;
			while (y >= 0) {
				int z = k;
				while (z >= 0) {
					v += mat->at({x, y, z});
					z = (z & (z + 1)) - 1;
				}
				y = (y & (y + 1)) - 1;
			}
			x = (x & (x + 1)) - 1;
		}
		return v;
	}
	inline T get(int x1, int y1, int z1, int x2, int y2, int z2) {
		assert(x1 <= x2 && y1 <= y2 && x1 >= 0 && y1 >= 0 && x2 < A && y2 < B && z1 <= z2 && z1 >= 0 && z2 < C);
		T res{};
		res += get (x2, y2, z2);
		if (x1 > 0)
			res -= get (x1 - 1, y2, z2);
		if (y1 > 0)
			res -= get (x2, y1 - 1, z2);
		if (z1 > 0)
			res -= get (x2, y2, z1 - 1);
		if (y1 > 0 && z1 > 0)
			res += get (x2, y1 - 1, z1 - 1);
		if (x1 > 0 && z1 > 0)
			res += get (x1 - 1, y2, z1 - 1);
		if (x1 > 0 && y1 > 0)
			res += get (x1 - 1, y1 - 1, z2);
		if (x1 > 0 && y1 > 0 && z1 > 0)
			res -= get (x1 - 1, y1 - 1, z1 - 1);
		return res;
	}
};
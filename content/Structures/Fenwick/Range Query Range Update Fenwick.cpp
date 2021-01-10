// Range query, range update Fenwick Tree
//
template<typename T>
class range_fenwick {
private:
	int N;
	fenwick<T>*B1, *B2;
public:
	range_fenwick(const int &N_): N(N_) {
		B1 = new fenwick<T>(N);
		B2 = new fenwick<T>(N);
	}
	void modify(int l, int r, const T& v) {
		B1->modify(l, v);
		B1->modify(r + 1, -v);
		B2->modify(l, v * (l - 1));
		B2->modify(r + 1, -v * r);
	}
	T get(int idx) {
		return B1->get(idx) * (idx) - B2->get(idx);
	}
	T get(int l, int r) {
		return get(r) - get(l - 1);
	}
};
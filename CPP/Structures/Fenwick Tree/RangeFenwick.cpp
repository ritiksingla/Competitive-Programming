// Range query, range update Fenwick Tree
//
template<typename T>
class RangeFenwick {
  private:
	int N;
	Fenwick<T>* B1, *B2;
  public:
	RangeFenwick(const int& N_): N(N_) {
		B1 = new Fenwick<T>(N);
		B2 = new Fenwick<T>(N);
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
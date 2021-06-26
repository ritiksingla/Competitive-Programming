// Sparse Table
//
// usage:
// auto fun = [&](int i, int j) { return min(i, j); };
// sparse_table<int, decltype(fun)> st(a, fun);
// or :
// sparse_table<int> st(a, [&](int i, int j) { return min(i, j); });
// vector must be immutable
template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable {
  private:
    int N;
    vector<vector<T>> mat;
    F func;
    int max_log;

  public:
    SparseTable() {}

    SparseTable(const vector<T>& a, const F& f) : func(f) {
        N = static_cast<int>(a.size());
        max_log = 32 - __builtin_clz(N);
        mat.resize(max_log);
        mat[0] = a;
        for (int j = 1; j < max_log; j++) {
            mat[j].resize(N - (1 << j) + 1);
            for (int i = 0; i <= N - (1 << j); i++) {
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get_idempotent(int from, int to) const {
        assert(0 <= from && from <= to && to <= N - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }

    T get_non_idempotent(int from, int to) const {
        assert(0 <= from && from <= to && to <= N - 1);
        T res = 0; // Change according to question
        for (int j = max_log; j >= 0; j--) {
            if ((1 << j) <= to - from + 1) {
                res = func(res, mat[j][from]);
                from += (1 << j);
            }
        }
        return res;
    }
};
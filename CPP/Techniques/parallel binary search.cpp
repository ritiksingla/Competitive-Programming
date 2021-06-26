// Parallel Binary Search
//
template <typename T>
class Fenwick {
  public:
    vector<T> fenw;
    int n;
    Fenwick(int _n) : n(_n) {
        fenw.resize(n);
    }
    Fenwick(const vector<T>& v) {
        n = v.size();
        fenw.resize(n);
        for (int i = 0; i < n; ++i) {
            modify(i, v[i]);
        }
    }
    void modify(int x, T v) {
        while (x < n) {
            fenw[x] += v;
            x |= (x + 1);
        }
    }
    long long get(int x) {
        long long v{};
        while (x >= 0) {
            v += fenw[x];
            x = (x & (x + 1)) - 1;
        }
        return v;
    }
    void apply(int l, int r, T v) {
        if (l <= r) {
            modify(l, v);
            modify(r + 1, -v);
        } else {
            modify(1, v);
            modify(r + 1, -v);
            modify(l, v);
        }
    }
};
int32_t main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int>a(m + 1);
    vector<int>owns[n + 1];

    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        owns[a[i]].push_back(i);
    }

    vector<long long>reqd(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> reqd[i];
    }

    int q; cin >> q;
    vector<int>ql(q + 1), qr(q + 1);
    vector<long long> qa(q + 1);

    for (int i = 1; i <= q; i++) {
        cin >> ql[i] >> qr[i] >> qa[i];
    }

    vector<int>lo(n + 1), hi(n + 1), mid(n + 1);

    function<void(void)>parallel_binary = [&]() {
        vector<int>vec[q + 1];
        for (int i = 1; i <= n; i++) {
            if (mid[i] > 0) {
                vec[mid[i]].emplace_back(i);
            }
        }

        Fenwick<long long>ft(m + 1);

        function<bool(int)>check = [&](int idx) {
            long long req = reqd[idx];
            for (auto& x : owns[idx]) {
                long long y = ft.get(x);
                req -= y;
                if (req < 0) {
                    break;
                }
            }
            if (req <= 0) {
                return true;
            }
            return false;
        };

        for (int i = 1; i <= q; i++) {
            ft.apply(ql[i], qr[i], qa[i]);
            for (auto& x : vec[i]) {
                if (check(x)) {
                    hi[x] = i;
                } else {
                    lo[x] = i + 1;
                }
            }
        }
    };

    function<void(void)>solve = [&]() {
        for (int i = 1; i <= n; i++) {
            lo[i] = 1, hi[i] = q + 1;
        }
        bool is_valid = true;
        while (is_valid) {
            is_valid = false;
            for (int i = 1; i <= n; i++) {
                if (lo[i] < hi[i]) {
                    is_valid = true;
                    mid[i] = (lo[i] + hi[i]) >> 1;
                } else {
                    mid[i] = -1;
                }
            }
            parallel_binary();
        }
    };

    solve();

    for (int i = 1; i <= n; i++) {
        if (lo[i] <= q) {
            cout << lo[i] << '\n';
        } else {
            cout << "NIE" << '\n';
        }
    }
    return 0;
}
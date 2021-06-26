// K_Query Offline
//
// Find each query (l,r,k) find the number of elements in range [a,b] strictly greater than k.
// Offline Segment Tree Implementation
/**
 *    author:  ritik singla
 *    created: 09.10.2020 19:59:08
**/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define rep(i,n) for(int i = 0; i < (n); i++)
#define forn(i,a,b) for(int i = (a); i <= (b); i++)
#define trav(a,x) for(auto &a : x)
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
    #define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
    #define debug(...) 42
#endif
struct segtree {
    struct node {
        ll sum = 0;
        ll add = 0;
        ll mn = 0;
        ll xr = 0;
        ll mx = 0;
        void apply(int l, int r, ll v) {
            sum += (r - l + 1) * v;
            add += v;
            mn += v;
            mx += v;
            xr += v;
        }
    };
    int n;
    vector<node>tree;
    static node unite(const node& a, const node& b) {
        node res;
        res.sum = a.sum + b.sum;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        res.xr = (a.xr ^ b.xr);
        return res;
    }
    void push(int x, int l, int r) {
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        if (tree[x].add != 0) {
            tree[x + 1].apply(l, m, tree[x].add);
            tree[y].apply(m + 1, r, tree[x].add);
            tree[x].add = 0;
        }
    }
    void pull(int x, int y) {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    template<typename T>
    void build(int x, int l, int r, const vector<T>& v) {
        if (l == r) {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(y, m + 1, r, v);
        pull(x, y);
    }
    void build(int x, int l, int r) {
        if (l == r) {
            tree[x].apply(l, r, 0ll);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m);
        build(y, m + 1, r);
        pull(x, y);
    }
    node get(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[x];
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        node res;
        if (qr <= m) {
            res = get(x + 1, l, m, ql, qr);
        } else if (ql > m) {
            res = get(y, m + 1, r, ql, qr);
        } else {
            res = unite(get(x + 1, l, m, ql, qr), get(y, m + 1, r, ql, qr));
        }
        pull(x, y);
        return res;
    }
    template<typename T>
    void modify(int x, int l, int r, int ql, int qr, const T& v) {
        if (ql <= l && r <= qr) {
            tree[x].apply(l, r, v);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        if (ql <= m) {
            modify(x + 1, l, m, ql, qr, v);
        }
        if (qr > m) {
            modify(y, m + 1, r, ql, qr, v);
        }
        pull(x, y);
    }
    template<typename T>
    segtree(const vector<T>& v) {
        n = v.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    segtree(int _n): n(_n) {
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }
    template<typename T>
    void modify(int l, int r, const T& v) {
        modify(0, 0, n - 1, l, r, v);
    }
    node get(int l, int r) {
        return get(0, 0, n - 1, l, r);
    }
    int find_first_knowingly(int x, int l, int r, const function<bool(const node&)>& f) {
        if (l == r) {
            return l;
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res;
        if (f(tree[x + 1])) {
            res = find_first_knowingly(x + 1, l, m, f);
        } else {
            res = find_first_knowingly(y, m + 1, r, f);
        }
        pull(x, y);
        return res;
    }
    int find_first(int x, int l, int r, int ql, int qr, const function<bool(const node&)>& f) {
        if (ql <= l && r <= qr) {
            if (!f(tree[x])) {
                return -1;
            }
            return find_first_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res = -1;
        if (ql <= m) {
            res = find_first(x + 1, l, m, ql, qr, f);
        }
        if (qr > m && res == -1) {
            res = find_first(y, m + 1, r, ql, qr, f);
        }
        pull(x, y);
        return res;
    }
    int find_last_knowingly(int x, int l, int r, const function<bool(const node&)>& f) {
        if (l == r) {
            return l;
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res;
        if (f(tree[y])) {
            res = find_last_knowingly(y, m + 1, r, f);
        } else {
            res = find_last_knowingly(x + 1, l, m, f);
        }
        pull(x, y);
        return res;
    }
    int find_last(int x, int l, int r, int ql, int qr, const function<bool(const node&)>& f) {
        if (ql <= l && r <= qr) {
            if (!f(tree[x])) {
                return -1;
            }
            return find_last_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res = -1;
        if (qr > m) {
            res = find_last(y, m + 1, r, ql, qr, f);
        }
        if (ql <= m && res == -1) {
            res = find_last(x + 1, l, m, ql, qr, f);
        }
        pull(x, y);
        return res;
    }
    int find_first(int ql, int qr, const function<bool(const node&)>& f) {
        assert(0 <= ql && ql <= qr && qr <= n - 1);
        return find_first(0, 0, n - 1, ql, qr, f);
    }
    int find_last(int ql, int qr, const function<bool(const node&)>& f) {
        assert(0 <= ql && ql <= qr && qr <= n - 1);
        return find_last(0, 0, n - 1, ql, qr, f);
    }
};
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll a[n];
    rep(i, n)
    cin >> a[i];
    int q;
    cin >> q;
    vi b(n, 1);
    segtree st(b);
    vector<pair<ll, pi>>query(q);
    vi p(n);
    iota(all(p), 0);
    sort(all(p), [&](int i, int j) {
        return a[i] < a[j];
    });
    vi p2(q);
    rep(i, q) {
        cin >> query[i].ss.ff >> query[i].ss.ss >> query[i].ff;
    }
    iota(all(p2), 0);
    sort(all(p2), [&](int i, int j) {
        return query[i].ff < query[j].ff;
    });
    int idx = 0;
    vi ans(q);
    rep(i, q) {
        int idx2 = p2[i];
        ll k = query[idx2].ff;
        while (idx < n && a[p[idx]] <= k) {
            st.modify(p[idx], p[idx], -1);
            idx++;
        }
        ans[idx2] = st.get(query[idx2].ss.ff - 1, query[idx2].ss.ss - 1).sum;
    }
    rep(i, q)
    cout << ans[i] << '\n';
    return 0;
}
https://www.spoj.com/problems/KQUERY
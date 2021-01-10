// K_Query Online
// 
// Find each query (l,r,k) find the number of elements in range [a,b] strictly greater than k.
// Online Segment Tree Implementation
/**
 *    author:  ritik singla
 *    created: 09.10.2020 20:29:32
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

string to_string(const string &s) {
    return '"' + s + '"';
}

string to_string(const char *s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++)
    {
        if (!first)
        {
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
    for (size_t i = 0; i < N; i++)
    {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v)
    {
        if (!first)
        {
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
struct segtree
{
    struct node
    {
        vi vec;
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node res;
        res.vec.resize(a.vec.size() + b.vec.size());
        merge(all(a.vec), all(b.vec), res.vec.begin());
        return res;
    }
    void pull(int x, int y)
    {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    template<typename T>
    void build(int x, int l, int r, const vector<T> &v)
    {
        if (l == r)
        {
            tree[x].vec.emplace_back(v[l]);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(y, m + 1, r, v);
        pull(x, y);
    }
    template<typename T>
    segtree(const vector<T> &v)
    {
        n = v.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    int count(int x, int l, int r, int ql, int qr, int k)
    {
        if (l > qr || r < ql)
            return 0;
        if (ql <= l && r <= qr)
        {
            int ans = tree[x].vec.end() - upper_bound(all(tree[x].vec), k);
            return ans;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        return count(x + 1, l, m, ql, qr, k) + count(y, m + 1, r, ql, qr, k);
    }
    int count(int l, int r, int k)
    {
        return count(0, 0, n - 1, l, r, k);
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vi a(n);
    rep(i, n)
    cin >> a[i];
    int q;
    cin >> q;
    segtree st(a);
    vi ans(q);
    int prev_ans = 0;
    rep(i, q)
    {
        int x, y, z;
        cin >> x >> y >> z;
        x ^= prev_ans;
        y ^= prev_ans;
        z ^= prev_ans;
        if (x < 1)
            x = 1;
        if (y > n)
            y = n;
        if (x > y)
        {
            ans[i] = 0;
            prev_ans = 0;
            continue;
        }
        ans[i] = st.count(x-1, y-1, z);
        prev_ans = ans[i];
    }
    rep(i, q)
    cout << ans[i] << '\n';
    return 0;
}
// https://www.spoj.com/problems/KQUERYO
// Segtree DFS
// 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct segtree
{
    struct node
    {
        ll sum = 0;
        ll add = 0;
        void apply(int l, int r, ll v)
        {
            sum += (r - l + 1) * v;
            add += v;
        }
    };
    int n;
    vector<node>tree;
    node unite(const node &a, const node &b) const
    {
        node res;
        res.sum = a.sum + b.sum;
        return res;
    }
    void push(int x, int l, int r)
    {
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        if(tree[x].add != 0)
        {
            tree[x + 1].apply(l, m, tree[x].add);
            tree[y].apply(m + 1, r, tree[x].add);
            tree[x].add = 0;
        }
        return;
    }
    void pull(int x, int y)
    {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    template<typename T>
    void build(int x, int l, int r, const vector<T> &v)
    {
        if(l == r)
        {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(y, m + 1, r, v);
        pull(x, y);
    }
    void build(int x, int l, int r)
    {
        if (l == r)
        {
            tree[x].apply(l, r, 0ll);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m);
        build(y, m + 1, r);
        pull(x, y);
    }
    node get(int x, int l, int r, int ql, int qr)
    {
        if(ql <= l && r <= qr)
            return tree[x];
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        node res;
        if(qr <= m)
            res = get(x + 1, l, m, ql, qr);
        else if(ql > m)
            res = get(y, m + 1, r, ql, qr);
        else
            res = unite(get(x + 1, l, m, ql, qr), get(y, m + 1, r, ql, qr));
        pull(x, y);
        return res;
    }
    template<typename T>
    void modify(int x, int l, int r, int ql, int qr, const T &v)
    {
        if(ql <= l && r <= qr)
        {
            tree[x].apply(l, r, v);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        if(ql <= m)
            modify(x + 1, l, m, ql, qr, v);
        if(qr > m)
            modify(y, m + 1, r, ql, qr, v);
        pull(x, y);
    }
    template<typename T>
    segtree(const vector<T> &v)
    {
        n = v.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    segtree(int _n): n(_n)
    {
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }
    node get(int l, int r)
    {
        return get(0, 0, n - 1, l, r);
    }
    template<typename T>
    void modify(int l, int r, const T &v)
    {
        modify(0, 0, n - 1, l, r, v);
    }
    // Find first element where condition is true.
    int find_first_knowingly(int x, int l, int r, const function<bool(const node &)> &f)
    {
        if (l == r)
        {
            return l;
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res;
        if (f(tree[x + 1]))
        {
            res = find_first_knowingly(x + 1, l, m, f);
        }
        else
        {
            res = find_first_knowingly(y, m + 1, r, f);
        }
        pull(x, y);
        return res;
    }
    int find_first(int x, int l, int r, int ql, int qr, const function<bool(const node &)> &f)
    {
        if (ql <= l && r <= qr)
        {
            if (!f(tree[x]))
            {
                return -1;
            }
            return find_first_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res = -1;
        if (ql <= m)
        {
            res = find_first(x + 1, l, m, ql, qr, f);
        }
        if (qr > m && res == -1)
        {
            res = find_first(y, m + 1, r, ql, qr, f);
        }
        pull(x, y);
        return res;
    }
//  Find last element where condition is true.
    int find_last_knowingly(int x, int l, int r, const function<bool(const node &)> &f)
    {
        if (l == r)
        {
            return l;
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res;
        if (f(tree[y]))
        {
            res = find_last_knowingly(y, m + 1, r, f);
        }
        else
        {
            res = find_last_knowingly(x + 1, l, m, f);
        }
        pull(x, y);
        return res;
    }
    int find_last(int x, int l, int r, int ql, int qr, const function<bool(const node &)> &f)
    {
        if (ql <= l && r <= qr)
        {
            if (!f(tree[x]))
            {
                return -1;
            }
            return find_last_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res = -1;
        if (qr > m)
        {
            res = find_last(y, m + 1, r, ql, qr, f);
        }
        if (ql <= m && res == -1)
        {
            res = find_last(x + 1, l, m, ql, qr, f);
        }
        pull(x, y);
        return res;
    }
    int find_first(int ql, int qr, const function<bool(const node &)> &f)
    {
        assert(0 <= ql && ql <= qr && qr <= n - 1);
        return find_first(0, 0, n - 1, ql, qr, f);
    }
    int find_last(int ql, int qr, const function<bool(const node &)> &f)
    {
        assert(0 <= ql && ql <= qr && qr <= n - 1);
        return find_last(0, 0, n - 1, ql, qr, f);
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--)
    {
        int n, q;
        cin >> n >> q;
        segtree st(n);
        while(q--)
        {
            bool t;
            cin >> t;
            if(t)
            {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                cout << st.get(u, v).sum << "\n";
            }
            else
            {
                int u, v;
                ll val;
                cin >> u >> v >> val;
                u--;
                v--;
                st.modify(u, v, val);
            }
        }
    }
}
// https://www.spoj.com/problems/HORRIBLE

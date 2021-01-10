// Persistent Segment Tree
//
struct perseg {
    struct node {
        node *l, *r;
        int sum;
        node (int val): l(nullptr), r(nullptr), sum(val) {}
        node (node *l, node *r): l(l), r(r), sum(0) {
            if (l) sum += l->sum;
            if (r) sum += r->sum;
        }
    };
    int n;
    vector<node*>tree; // vector of roots
    template<typename T>
    node* build(int tl, int tr, const vector<T>&v)
    {
        if (tl == tr)
        {
            return new node(v[tl]);
        }
        int tm = (tl + tr) >> 1;
        return new node(build(tl, tm, v), build(tm + 1, tr, v));
    }
    node* build(int tl, int tr)
    {
        if (tl == tr)
        {
            return new node(0);
        }
        int tm = (tl + tr) >> 1;
        return new node(build(tl, tm), build(tm + 1, tr));
    }
    template<typename T>
    perseg(const vector<T> &v)
    {
        n = (int)v.size();
        tree.clear();
        node *a = build(0, n - 1, v);
        tree.push_back(a);
    }
    perseg(int n_): n(n_)
    {
        tree.clear();
        node *a = build(0, n - 1);
        tree.push_back(a);
    }
    int get(node *root, int tl, int tr, int ql, int qr)
    {
        if (ql > tr || qr < tl)
            return 0;
        if (ql <= tl && tr <= qr)
            return root->sum;
        int tm = (tl + tr) >> 1;
        return get(root->l, tl, tm, ql, qr) + get(root->r, tm + 1, tr, ql, qr);
    }
    int get(int root, int l, int r)
    {
        return get(tree[root], 0, n - 1, l, r);
    }
    template<typename T>
    node* modify(node *root, int tl, int tr, int pos, const T &v) {
        if (tl == tr) {
            return new node(root->sum + v);
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm)
            return new node(modify(root->l, tl, tm, pos, v), root->r);
        else
            return new node(root->l, modify(root->r, tm + 1, tr, pos, v));
    }
    template<typename T>
    void modify(int root, int pos, const T &v) {
        node *a = modify(tree[root], 0, n - 1, pos, v);
        tree.push_back(a);
    }
    int query(node* u, node* v, int l, int r, int k) {
        if (l == r)
            return l;
        int m = (l + r) >> 1;
        int leftval = (v->l->sum) - (u->l->sum);
        int rightval = (v->r->sum) - (u->r->sum);
        if (leftval >= k)
            return query(u->l, v->l, l, m, k);
        else
            return query(u->r, v->r, m + 1, r, k - leftval);
    }
    int query(int u, int v, int k) {
        return query(tree[u], tree[v], 0, n - 1, k);
    }
};
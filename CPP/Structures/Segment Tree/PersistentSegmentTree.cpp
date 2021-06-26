// Persistent Segment Tree
//
struct PersistentSegmentTree {
    struct Node {
        Node* l, *r;
        int sum;
        Node(int val): l(nullptr), r(nullptr), sum(val) {}
        Node(Node* l, Node* r): l(l), r(r), sum(0) {
            if (l) {
                sum += l->sum;
            }
            if (r) {
                sum += r->sum;
            }
        }
    };
    int n;
    vector<Node*>tree; // vector of roots
    template<typename T>
    Node* build(int tl, int tr, const vector<T>& v) {
        if (tl == tr) {
            return new Node(v[tl]);
        }
        int tm = (tl + tr) >> 1;
        return new Node(build(tl, tm, v), build(tm + 1, tr, v));
    }
    Node* build(int tl, int tr) {
        if (tl == tr) {
            return new Node(0);
        }
        int tm = (tl + tr) >> 1;
        return new Node(build(tl, tm), build(tm + 1, tr));
    }
    template<typename T>
    PersistentSegmentTree(const vector<T>& v) {
        n = (int)v.size();
        tree.clear();
        Node* a = build(0, n - 1, v);
        tree.push_back(a);
    }
    PersistentSegmentTree(int n_): n(n_) {
        tree.clear();
        Node* a = build(0, n - 1);
        tree.push_back(a);
    }
    int get(Node* root, int tl, int tr, int ql, int qr) {
        if (ql > tr || qr < tl) {
            return 0;
        }
        if (ql <= tl && tr <= qr) {
            return root->sum;
        }
        int tm = (tl + tr) >> 1;
        return get(root->l, tl, tm, ql, qr) + get(root->r, tm + 1, tr, ql, qr);
    }
    int get(int root, int l, int r) {
        return get(tree[root], 0, n - 1, l, r);
    }
    template<typename T>
    Node* modify(Node* root, int tl, int tr, int pos, const T& v) {
        if (tl == tr) {
            return new Node(root->sum + v);
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return new Node(modify(root->l, tl, tm, pos, v), root->r);
        } else {
            return new Node(root->l, modify(root->r, tm + 1, tr, pos, v));
        }
    }
    template<typename T>
    void modify(int root, int pos, const T& v) {
        Node* a = modify(tree[root], 0, n - 1, pos, v);
        tree.push_back(a);
    }
    int query(Node* u, Node* v, int l, int r, int k) {
        if (l == r) {
            return l;
        }
        int m = (l + r) >> 1;
        int leftval = (v->l->sum) - (u->l->sum);
        int rightval = (v->r->sum) - (u->r->sum);
        if (leftval >= k) {
            return query(u->l, v->l, l, m, k);
        } else {
            return query(u->r, v->r, m + 1, r, k - leftval);
        }
    }
    int query(int u, int v, int k) {
        return query(tree[u], tree[v], 0, n - 1, k);
    }
};
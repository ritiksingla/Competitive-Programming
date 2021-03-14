// Treap
//
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct node {
    int mx;
    int sum;
    int add;
    int val;

    int x;//Key
    int y;//priority
    int sz;
    node* l, *r;
    node(int _x, int _val): val(_val), mx(_val), add(0), x(_x), sz(1), sum(_val), y(rng()), l(nullptr), r(nullptr) {}
    void apply(int v) {
        val += v;
        mx += v;
        sum += v * sz;
        add += v;
    }
    void push() {
        if (add != 0) {
            if (l != nullptr) {
                l->apply(add);
            }
            if (r != nullptr) {
                r->apply(add);
            }
            add = 0;
        }
    }
    void pull() {
        mx = max(val, max(get_max(l), get_max(r)));
        sum = val + get_sum(l) + get_sum(r);
        sz = 1 + get_size(l) + get_size(r);
    }
    static int get_max(node* t) {
        return (t == nullptr ? numeric_limits<int>::min() : t->mx);
    }
    static int get_sum(node* t) {
        return (t == nullptr ? 0 : t->sum);
    }
    static int get_size(node* t) {
        return (t == nullptr ? 0 : t->sz);
    }
};
// splits tree into l,r such that all keys in l are <x and in r >x
void split(node* t, int x, node*& l, node*& r) {
    if (!t) {
        l = r = nullptr;
    } else {
        t->push();
        if (t->x >= x) {
            split(t->l, x, l, t->l);
            r = t;
        } else {
            split(t->r, x, t->r, r);
            l = t;
        }
        t->pull();
    }
}
//(all keys X in T1 are smaller than keys in T2)
void merge(node*& t, node*& l, node*& r) {
    if (!l || !r) {
        t = l ? l : r;
    } else {
        l->push();
        r->push();
        if (l->y > r->y) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }
        t->pull();
    }
}
void insert(node*& t, int x, int val) {
    node* l, *r;
    split(t, x, l, r);
    auto mid = new node(x, val);
    merge(t, l, mid);
    merge(t, t, r);
}
void remove(node*& t, int x) {
    node* l1, *r1, *l2, *r2;
    split(t, x, l1, r1);
    split(r1, x + 1, l2, r2);
    delete l2;
    merge(t, l1, r2);
}

void modify(node*& t, int ql, int qr, int delta) {
    node* l1, *r1, *l2, *r2;
    split(t, qr + 1, l1, r1);
    split(l1, ql, l2, r2);
    if (r2 != nullptr) {
        r2->apply(delta);
    }
    merge(t, l2, r2);
    merge(t, t, r1);
}

node query(node*& t, int ql, int qr) {
    node* l1, *r1, *l2, *r2;
    split(t, qr + 1, l1, r1);
    split(l1, ql, l2, r2);
    node res(0, 0);
    if (r2) {
        res = *r2;
    }
    merge(t, l2, r2);
    merge(t, t, r1);
    return res;
}

void clear(node*& t) {
    if (!t) {
        return;
    }
    clear(t->l);
    clear(t->r);
    delete t;
    t = nullptr;
}

void print(node* t) {
    if (!t) {
        return;
    }
    print(t->l);
    cout << t->val << '\n';
    print(t->r);
}
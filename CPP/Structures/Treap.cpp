// Treap
//
template <typename _Ty>
mt19937_64 rng((_Ty)chrono::steady_clock::now().time_since_epoch().count());

template <class _Ty>
struct Treap {
    struct Node {
        // Extra data members
        _Ty mx;
        _Ty sum;
        _Ty add;
        int sz;

        // Core data members
        using node_ptr = Node* ;
        _Ty key;
        _Ty value;
        int priority;
        node_ptr l;
        node_ptr r;

        Node(_Ty _key, _Ty _value): value(_value), mx(_value),
            add(_Ty(0)), key(_key), sz(1), sum(_value), priority(rng<_Ty>()),
            l(nullptr), r(nullptr) {}

        void apply(_Ty v) {
            value += v;
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
            mx = max(value, max(get_max(l), get_max(r)));
            sum = value + get_sum(l) + get_sum(r);
            sz = 1 + get_size(l) + get_size(r);
        }
        static _Ty get_max(node_ptr T) {
            return (T == nullptr ? numeric_limits<_Ty>::min() : T->mx);
        }
        static _Ty get_sum(node_ptr T) {
            return (T == nullptr ? _Ty(0) : T->sum);
        }
        static int get_size(node_ptr T) {
            return (T == nullptr ? 0 : T->sz);
        }
    }; // Node

    using node_ptr = Node* ;

    void print(node_ptr T) {
        if (!T) {
            cout << "empty\n";
            return;
        }
        if (T->l) {
            cout << "L ";
            print(T->l);
        } else {
            cout << "L nullptr\n";
        }
        cout << T->key << ' ' << T->value << ' ' << T->priority << '\n';
        if (T->r) {
            cout << "R ";
            print(T->r);
        } else {
            cout << "R nullptr\n";
        }
    }

    // splits tree into l, r such that all keys in l < key and in r > key
    void split(node_ptr T, _Ty key, node_ptr& l, node_ptr& r) {
        if (!T) {
            l = r = nullptr;
        } else {
            T->push();
            if (T->key >= key) {
                split(T->l, key, l, T->l);
                r = T;
            } else {
                split(T->r, key, T->r, r);
                l = T;
            }
            T->pull();
        }
    }

    //(all keys in T1 must be strictly smaller than keys in T2)
    void merge(node_ptr& T, node_ptr& l, node_ptr& r) {
        if (!l || !r) {
            T = l ? l : r;
        } else {
            l->push();
            r->push();
            if (l->priority > r->priority) {
                merge(l->r, l->r, r);
                T = l;
            } else {
                merge(r->l, l, r->l);
                T = r;
            }
            T->pull();
        }
    }

    void insert(node_ptr& T, _Ty key, _Ty value) {
        node_ptr l = nullptr, r = nullptr;
        split(T, key, l, r);
        auto mid = new Node(key, value);
        merge(T, l, mid);
        merge(T, T, r);
    }

    void remove(node_ptr& T, _Ty key) {
        node_ptr l1 = nullptr, r1 = nullptr, l2 = nullptr, r2 = nullptr;
        split(T, key, l1, r1);
        split(r1, key + 1, l2, r2);
        delete l2;
        merge(T, l1, r2);
    }
    // Combines two trees, under the assumption that all elements are different
    node_ptr unite(node_ptr l, node_ptr r) {
        if (! l || ! r) {
            return l ? l : r;
        }
        if (l->priority < r->priority) {
            swap(l, r);
        }
        node_ptr lt = nullptr, rt = nullptr;
        split(r, l-> key, lt, rt);
        l->l = unite(l->l, lt);
        l->r = unite(l->r, rt);
        return l;
    }

    void modify(node_ptr& T, _Ty ql, _Ty qr, _Ty delta) {
        node_ptr l1 = nullptr, r1 = nullptr, l2 = nullptr, r2 = nullptr;
        // as split method splits [-INF, X) and [X, INF]
        split(T, qr + 1, l1, r1);
        split(l1, ql, l2, r2);
        // r2 now have [ql, qr] keys
        if (r2 != nullptr) {
            r2->apply(delta);
        }
        // as split method splits the original tree
        merge(T, l2, r2);
        merge(T, T, r1);
    }

    Node query(node_ptr& T, _Ty ql, _Ty qr) {
        node_ptr l1 = nullptr, r1 = nullptr, l2 = nullptr, r2 = nullptr;
        split(T, qr + 1, l1, r1);
        split(l1, ql, l2, r2);
        Node res(0, 0);
        if (r2 != nullptr) {
            res = *r2;
        }
        merge(T, l2, r2);
        merge(T, T, r1);
        return res;
    }

    void clear(node_ptr& T) {
        if (!T) {
            return;
        }
        clear(T->l);
        clear(T->r);
        delete T;
        T = nullptr;
    }
};

// main
Treap<int>T;
using node_ptr = Treap<int>::Node*;
node_ptr cur = nullptr;
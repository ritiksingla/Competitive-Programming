// Splay Trees
//
template<typename T>
struct SplayTree {
    struct Node {
        Node* ch[2], *p;
        int sz;
        T val;
        Node(T v) {
            ch[0] = ch[1] = p = nullptr;
            sz = 1;
            val = v;
        }
        void update() {
            sz = 1;
            for (int i = 0; i < 2; i++)
                if (ch[i]) {
                    sz += ch[i]->sz;
                }
        }
    };

    Node* root;

    SplayTree() {
        root = nullptr;
    }
    ~SplayTree() {
        vector<Node*> q = {root};
        while (q.size()) {
            Node* x = q.back();
            q.pop_back();
            if (!x) {
                continue;
            }
            q.push_back(x->ch[0]);
            q.push_back(x->ch[1]);
            delete x;
        }
    }
    void rotate(Node* x) { // x will stay on top
        Node* p = x->p, *pp = p->p;
        if (pp) {
            pp->ch[pp->ch[1] == p] = x;
        }
        // (d = 0) => {
        //     left child
        // } and (d = 1) => {
        //     right child
        // }
        bool d = p->ch[1] == x;
        // Right child of current becomes left child of parent or
        // Left child of current becomes right child of parent
        p->ch[d] = x->ch[!d];
        x->ch[!d] = p;
        if (p->ch[d]) {
            p->ch[d]->p = p;
        }
        x->p = pp;
        p->p = x;
        p->update();
        x->update();
    }
    Node* splay(Node* x) {
        if (!x) {
            return x;
        }
        root = x;
        while (x->p) {
            Node* p = x->p, *pp = p->p;
            if (!pp) { // Zig
                rotate(x);
                return x;
            }
            if ((pp->ch[0] == p) ^ (p->ch[0] == x)) { // ZigZag(LeftRight and RightLeft)
                rotate(x);
                rotate(x);
            } else { // ZigZig(LeftLeft and RightRight)
                rotate(p);
                rotate(x);
            }
        }
        return x;
    }
    // lower_bound lb = 1 if we need to find lower_bound
    // Thus if lb = 1 then no insertion will take place
    Node* insert(T v, bool lb = 0) {
        if (!root)
            if (lb == 1) {
                return nullptr;
            } else {
                return root = new Node(v);
            }
        Node* x = root, *last = nullptr;
        while (1) {
            // (d = 0) => {
            //     left child
            // } and (d = 1) => {
            //     right child
            // }
            bool d = x->val < v;
            // if left child then while finding lb, lb can exist in right subtree
            // hence splay again from the nearest upper val possible
            if (d == 0) {
                last = x;
            }
            if (x->val == v) {
                break;
            }
            if (x->ch[d]) {
                x = x->ch[d];
            } else {
                if (lb) {
                    break;
                }
                x->ch[d] = new Node(v);
                x->ch[d]->p = x;
                x = x->ch[d];
                break;
            }
        }
        splay(x);
        return lb ? splay(last) : x;
    }
    int size() {
        return root ? root->sz : 0;
    }
    // 1 if present and 0 if absent
    // First splay at value then check if it's equal to v
    int count(T v) {
        return (insert(v, 1) && root->val == v);
    }
    Node* lower_bound(T v) {
        return insert(v, 1);
    }
    void erase(T v) {
        if (!count(v)) {
            return;
        }
        // count(v) splay the tree and now x is current Node with val v
        Node* x = root, *l = x->ch[0];
        if (!l) {
            root = x->ch[1];
            if (root) {
                root->p = nullptr;
            }
            return delete x;
        }
        root = l, l->p = nullptr;
        // Finding the predecessor of the Node to be deleted
        while (l->ch[1]) {
            l = l->ch[1];
        }
        splay(l);
        l->ch[1] = x->ch[1];
        if (l->ch[1]) {
            l->ch[1]->p = l;
        }
        delete x;
        l->update();
    }
    // If key does not exist, it returns where it will be inserted
    // return zero-based index
    int order_of_key(T v) {
        if (!count(v)) {
            return -1;
        }
        if (!lower_bound(v)) {
            return root ? root->sz : 0;
        }
        return root->ch[0] ? root->ch[0]->sz : 0;
    }
    Node* find_by_order(int k) {
        if (k < 0 || k >= size()) {
            return nullptr;
        }
        Node* x = root;
        while (1) {
            if (x->ch[0] and x->ch[0]->sz >= k + 1) {
                x = x->ch[0];
            } else {
                if (x->ch[0]) {
                    k -= x->ch[0]->sz;
                }
                if (k == 0) {
                    return splay(x);
                }
                if (!x->ch[1]) {
                    splay(x);
                    return nullptr;
                }
                k--; // for current root
                x = x->ch[1];
            }
        }
    }
    T min() {
        Node* x = root;
        while (x->ch[0]) {
            x = x->ch[0];    // max -> ch[1]
        }
        return splay(x)->val;
    }
};
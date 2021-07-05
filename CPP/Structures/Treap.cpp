// Treap
//
template <typename _Tx>
mt19937_64 rng((_Tx)chrono::steady_clock::now().time_since_epoch().count());

template <class _Ty>
struct Treap {
	struct Node {
		int sz;
		bool rev;
		_Ty sm;
		_Ty add;
		_Ty mx;

		// Core data members
		using node_ptr = Node* ;
		_Ty value;
		long long priority;
		node_ptr l;
		node_ptr r;

		Node(_Ty _value): value(_value), priority(rng<long long>()),
			l(nullptr), r(nullptr) {
			sz = 1;
			rev = false;
			mx = sm = value;
			add = 0;
		}
		void apply(_Ty v = 0) {
			if (v == 0) {
				rev = !rev;
			} else {
				value += v;
				mx += v;
				sm += v * sz;
				add += v;
			}
		}
		void pull() {
			mx = max(value, max(get_max(l), get_max(r)));
			sm = value + get_sum(l) + get_sum(r);
			sz = 1 + get_size(l) + get_size(r);
		}
		void push() {
			if (rev == true) {
				swap(l, r);
				if (l != nullptr) {
					l->apply();
				}
				if (r != nullptr) {
					r->apply();
				}
				rev = false;
			}
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
		static _Ty get_max(node_ptr cur) {
			return (cur == nullptr ? numeric_limits<_Ty>::min() : cur->mx);
		}
		static _Ty get_sum(node_ptr cur) {
			return (cur == nullptr ? _Ty(0) : cur->sm);
		}
		static int get_size(node_ptr cur) {
			return (cur == nullptr ? 0 : cur->sz);
		}
	}; // Node

	using node_ptr = Node* ;
	node_ptr root = nullptr;
	~Treap() {
		clear(root);
	}

	void split(node_ptr cur, int idx, node_ptr& lhs, node_ptr& rhs, int offset = 0) {
		if (cur == nullptr) {
			lhs = rhs = nullptr;
		} else {
			cur->push();
			int cur_pos = offset + Node::get_size(cur->l);
			if (cur_pos >= idx) {
				split(cur->l, idx, lhs, cur->l, offset);
				rhs = cur;
			} else {
				split(cur->r, idx, cur->r, rhs, cur_pos + 1);
				lhs = cur;
			}
			cur->pull();
		}
	}

	void merge(node_ptr& cur, node_ptr& lhs, node_ptr& rhs) {
		if (lhs == nullptr || rhs == nullptr) {
			cur = (lhs ? lhs : rhs);
		} else {
			lhs->push();
			rhs->push();
			if (lhs->priority > rhs->priority) {
				merge(lhs->r, lhs->r, rhs);
				cur = lhs;
			} else {
				merge(rhs->l, lhs, rhs->l);
				cur = rhs;
			}
			cur->pull();
		}
	}

	void insert(node_ptr& cur, int idx, _Ty value) {
		node_ptr lhs = nullptr, rhs = nullptr;
		split(cur, idx, lhs, rhs);
		node_ptr mid = new Node(value);
		merge(cur, lhs, mid);
		merge(cur, cur, rhs);
	}

	void remove(node_ptr& cur, int idx) {
		node_ptr lhs, mid, rhs;
		lhs = mid = rhs = nullptr;
		split(cur, idx, lhs, mid);
		split(mid, 1, mid, rhs);
		delete mid;
		merge(cur, lhs, rhs);
	}

	// Different Tree Roots
	// Untested!!!
	node_ptr unite(node_ptr lhs, node_ptr rhs) {
		if (lhs == nullptr || rhs == nullptr) {
			return (lhs ? lhs : rhs);
		}
		if (lhs->priority < rhs->priority) {
			rhs->l = unite(lhs, rhs->l);
			return rhs;
		} else if (lhs->priority >= rhs->priority) {
			lhs->l = unite(lhs->l, rhs);
			return lhs;
		}
		// node_ptr lt = nullptr, rt = nullptr;
		// split(rhs, idx, lt, rt);
		// lhs->l = unite(lhs->l, lt);
		// lhs->r = unite(lhs->r, rt);
		// return lhs;
		return nullptr;
	}

	void modify(node_ptr& cur, int x, int y, _Ty delta) {
		node_ptr lhs, mid, rhs;
		lhs = mid = rhs = nullptr;
		split(cur, x, lhs, mid);
		split(cur, y - x + 1, mid, rhs);
		if (mid != nullptr) {
			mid->apply(delta);
		}
		merge(cur, lhs, mid);
		merge(cur, cur, rhs);
	}

	void reverse(node_ptr& cur, int x, int y) {
		node_ptr lhs, mid, rhs;
		lhs = mid = rhs = nullptr;
		split(cur, x, lhs, mid);
		split(cur, y - x + 1, mid, rhs);
		mid->add_rev = !mid->add_rev;
		merge(cur, lhs, mid);
		merge(cur, cur, rhs);
	}

	Node query(node_ptr& cur, int x, int y) {
		node_ptr lhs, mid, rhs;
		lhs = mid = rhs = nullptr;
		split(cur, x, lhs, mid);
		split(mid, y - x + 1, mid, rhs);
		Node res = Node(0);
		if (mid != nullptr) {
			res = *mid;
		}
		merge(cur, lhs, mid);
		merge(cur, cur, rhs);
		return res;
	}

	void print(node_ptr cur, int level = 0) {
		if (cur == nullptr) {
			return;
		}
		cur->push();
		if (cur->l) {
			print(cur->l, level + 1);
		}
		cout << cur->value << ' ';
		if (cur->r) {
			print(cur->r, level + 1);
		}
	}

	void clear(node_ptr& cur) {
		if (cur == nullptr) {
			return;
		}
		clear(cur->l);
		clear(cur->r);
		delete cur;
		cur = nullptr;
	}
}; // Treap

// main
// Treap<int>T;
// using node_ptr = Treap<int>::Node*; node_ptr root = nullptr; // not sure for unite operations
// or for internal root use T.root
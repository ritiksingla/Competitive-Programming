template <class _Tp>
mt19937_64 rng((_Tp)chrono::steady_clock::now().time_since_epoch().count());

template <class _Tp>
struct Treap {
	struct Node {
		int sz;
		bool rev;
		_Tp sm;
		_Tp add;
		_Tp mx;

		// Core data members
		using node_ptr = Node* ;
		_Tp value;
		int priority;
		node_ptr left;
		node_ptr right;

		Node(_Tp _value): value(_value), priority(rng<int>()),
			left(nullptr), right(nullptr) {
			sz = 1;
			rev = false;
			add = 0;
			sm = _value;
			mx = _value;
		}

		void apply(_Tp v) {
			value += v;
			mx += v;
			sm += v * sz;
			add += v;
		}

		void pull() {
			mx = max(value, max(get_max(left), get_max(right)));
			sm = value + get_sum(left) + get_sum(right);
			sz = 1 + get_size(left) + get_size(right);
		}

		void push() {
			if (rev == true) {
				if (left != nullptr) {
					left->rev = !(left->rev);
				}
				if (right != nullptr) {
					right->rev = !(right->rev);
				}
				swap(left, right);
				rev = false;
			}
			if (add != 0) {
				if (left != nullptr) {
					left->apply(add);
				}
				if (right != nullptr) {
					right->apply(add);
				}
				add = 0;
			}
			pull();
		}
		static _Tp get_max(node_ptr cur) {
			return (cur == nullptr ? numeric_limits<_Tp>::min() : cur->mx);
		}
		static _Tp get_sum(node_ptr cur) {
			return (cur == nullptr ? _Tp(0) : cur->sm);
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

	pair<node_ptr, node_ptr> split(node_ptr cur, int idx) {
		if (cur == nullptr) {
			return {nullptr, nullptr};
		}
		cur->push();
		int cur_pos = Node::get_size(cur->left);
		if (cur_pos >= idx) {
			auto res = split(cur->left, idx);
			cur->left = res.second;
			cur->pull();
			return {res.first, cur};
		} else {
			auto res = split(cur->right, idx - cur_pos - 1);
			cur->right = res.first;
			cur->pull();
			return {cur, res.second};
		}
		return {nullptr, nullptr};
	}

	node_ptr merge(node_ptr lhs, node_ptr rhs) {
		if (lhs == nullptr) {
			return rhs;
		} else if (rhs == nullptr) {
			return lhs;
		}
		lhs->push();
		rhs->push();
		if (lhs->priority > rhs->priority) {
			lhs->right = merge(lhs->right, rhs);
			lhs->pull();
			return lhs;
		} else {
			rhs->left = merge(lhs, rhs->left);
			rhs->pull();
			return rhs;
		}
	}

	node_ptr insert(node_ptr cur, int idx, _Tp value) {
		assert(idx <= Node::get_size(cur));
		if (idx == Node::get_size(cur)) {
			return merge(cur, new Node(value));
		}
		auto res = split(cur, idx);
		node_ptr mid = new Node(value);
		cur = merge(res.first, mid);
		return merge(cur, res.second);
	}

	node_ptr remove(node_ptr cur, int idx) {
		assert(idx < Node::get_size(cur));
		auto res1 = split(cur, idx);
		auto res2 = split(res1.second, 1);
		delete res2.first;
		return merge(res1.first, res2.second);
	}

	node_ptr reverse(node_ptr cur, int x, int y) {
		assert(x >= 0 && y < Node::get_size(cur) && x <= y);
		auto res1 = split(cur, x);
		auto res2 = split(res1.second, y - x + 1);
		(res2.first)->rev = !((res2.first)->rev);
		return merge(res1.first, merge(res2.first, res2.second));
	}

	node_ptr modify(node_ptr cur, int x, int y, _Tp delta) {
		assert(x >= 0 && y < Node::get_size(cur) && x <= y);
		auto res1 = split(cur, x);
		auto res2 = split(res1.second, y - x + 1);
		(res2.first)->apply(delta);
		return merge(res1.first, merge(res2.first, res2.second));
	}

	_Tp query(node_ptr cur, int x, int y) {
		assert(x >= 0 && y < Node::get_size(cur) && x <= y);
		auto res1 = split(cur, x);
		auto res2 = split(res1.second, y - x + 1);

		// Change according to question
		_Tp res = (res2.first)->sm;

		merge(res1.first, merge(res2.first, res2.second));
		return res;
	}

	void print(node_ptr cur, int level = 0) {
		if (cur == nullptr) {
			return;
		}
		cur->push();
		if (cur->left) {
			print(cur->left, level + 1);
		}
		// debug(cur->value, level);
		if (cur->right) {
			print(cur->right, level + 1);
		}
	}

	void clear(node_ptr cur) {
		if (cur == nullptr) {
			return;
		}
		clear(cur->left);
		clear(cur->right);
		delete cur;
		return;
	}
}; // Treap

// main
// Treap<int>T;
// using node_ptr = Treap<int>::Node*; node_ptr root = nullptr;
// or for internal root use T.root
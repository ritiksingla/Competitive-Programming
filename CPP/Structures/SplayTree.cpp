// Splay Tree
//
// Amortized Binary Search Tree
template<class _Tp>
struct SplayTree {
	struct Node {
		// Core data members
		using node_ptr = Node*;
		node_ptr left;
		node_ptr right;
		node_ptr par;
		_Tp value;

		// Extra data members
		int sz;
		bool rev;
		_Tp sm;
		_Tp add;
		_Tp mx;

		Node(_Tp value_ = 0, node_ptr left_ = nullptr, node_ptr right_ = nullptr) {
			left = left_;
			right = right_;
			par = nullptr;
			sz = 1;
			value = value_;
			rev = false;
			add = 0;
			sm = value_;
			mx = value_;
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

	using node_ptr = Node*;
	node_ptr root;

	SplayTree() {
		root = nullptr;
	}
	~SplayTree() {
		vector<node_ptr> q = {root};
		while (q.size()) {
			node_ptr x = q.back();
			q.pop_back();
			if (x == nullptr) {
				continue;
			}
			q.push_back(x->left);
			q.push_back(x->right);
			delete x;
		}
	}

	/* Decrese depth by 1 of node_ptr passed while still maintaining properties of BST */
	void rotate(node_ptr cur) {
		node_ptr parent = cur->par;
		node_ptr grand_parent = parent->par;
		cur->push();
		parent->push();
		if (grand_parent != nullptr) {
			grand_parent->push();
			if (grand_parent->left == parent) {
				grand_parent->left = cur;
			} else {
				grand_parent->right = cur;
			}
			grand_parent->pull();
		}
		if (parent->left == cur) {
			parent->left = cur->right;
			cur->right = parent;
		} else {
			parent->right = cur->left;
			cur->left = parent;
		}
		cur->par = grand_parent;
		keep_parent(parent);
		keep_parent(cur);
		parent->pull();
		cur->pull();
	}

	// Rootify at node_ptr passed while still maintaining properties of BST
	node_ptr splay(node_ptr cur) {
		if (cur == nullptr) {
			return cur;
		}
		root = cur;
		cur->push();
		while (cur->par != nullptr) {
			node_ptr parent = cur->par;
			parent->push();
			node_ptr grand_parent = parent->par;
			if (grand_parent == nullptr) {
				rotate(cur);
				return cur;
			} else {
				grand_parent->push();
				bool zigzag = ((grand_parent->left == parent) ^ (parent->left == cur));
				if (zigzag) {
					rotate(cur);
					rotate(cur);
				} else {
					rotate(parent);
					rotate(cur);
				}
			}
		}
		return cur;
	}

	// Splays at node with value = (lower_bound of value_)
	node_ptr find_by_value(node_ptr cur, _Tp value_) {
		if (cur == nullptr) {
			return nullptr;
		}
		cur->push();
		if (value_ == cur->value) {
			return splay(cur);
		}
		if (value_ < cur->value && cur->left != nullptr) {
			return find_by_value(cur->left, value_);
		} else if (value_ > cur->value && cur->right != nullptr) {
			return find_by_value(cur->right, value_);
		}
		return splay(cur);
	}

	// Splays at 'idx' node in sorted array
	node_ptr find_by_index(node_ptr cur, int idx) {
		if (cur == nullptr) {
			return nullptr;
		}
		cur->push();
		int cur_pos = Node::get_size(cur->left);
		if (idx == cur_pos) {
			return splay(cur);
		} else if (idx < cur_pos && cur->left != nullptr) {
			return find_by_index(cur->left, idx);
		} else if (idx > cur_pos && cur->right != nullptr) {
			return find_by_index(cur->right, idx - cur_pos - 1);
		}
		return splay(cur);
	}

	// Splits node_ptr passed according to value criterion
	// [ <= value_, > value_]
	pair<node_ptr, node_ptr> split_by_value(node_ptr cur, _Tp value_) {
		if (cur == nullptr) {
			return {nullptr, nullptr};
		}
		cur = find_by_value(cur, value_);
		cur->push();

		if (cur->value <= value_) {
			node_ptr right = cur->right;
			cur->right = nullptr;
			cur->pull();
			set_parent(right, nullptr);
			return {cur, right};
		} else {
			node_ptr left = cur->left;
			cur->left = nullptr;
			cur->pull();
			set_parent(left, nullptr);
			return {left, cur};
		}
	}

	// Splits node_ptr passed according to index criterion
	// [ <= idx, > idx]
	pair<node_ptr, node_ptr> split_by_index(node_ptr cur, int idx) {
		assert(idx >= -1 && idx < cur->sz);
		if (cur == nullptr) {
			return {nullptr, nullptr};
		}
		cur = find_by_index(cur, idx);
		cur->push();
		int cur_pos = Node::get_size(cur->left);
		if (cur_pos <= idx) {
			node_ptr right = cur->right;
			cur->right = nullptr;
			cur->pull();
			set_parent(right, nullptr);
			return {cur, right};
		} else {
			node_ptr left = cur->left;
			cur->left = nullptr;
			cur->pull();
			set_parent(left, nullptr);
			return {left, cur};
		}
	}

	// Call this for BST by values
	node_ptr insert_sorted(node_ptr& cur, _Tp value_) {
		if (cur == nullptr) {
			cur = new Node(value_);
			return cur;
		}
		cur = find_by_value(cur, value_);
		if (cur->value == value_) {
			return cur;
		}
		auto pr = split_by_value(cur, value_);
		cur = new Node(value_, pr.first, pr.second);
		keep_parent(cur);
		cur->pull();
		return cur;
	}

	// Call this for BST by index
	node_ptr insert_at(node_ptr& cur, int idx, _Tp value_) {
		int n = Node::get_size(cur);
		assert(idx <= n);
		if (idx == n) {
			node_ptr v = new Node(value_);
			v->left = cur;
			set_parent(cur, v);
			cur = v;
			cur->pull();
			return cur;
		}
		auto pr = split_by_value(cur, idx - 1);
		cur = new Node(value_, pr.first, pr.second);
		keep_parent(cur);
		cur->pull();
		return cur;
	}

	// Merge elements according to value criterion
	node_ptr merge_by_value(node_ptr lhs, node_ptr rhs) {
		if (rhs == nullptr) {
			return lhs;
		} else if (lhs == nullptr) {
			return rhs;
		}
		rhs = find_by_value(rhs, lhs->value);
		assert(rhs->value != lhs->value);
		rhs->left = lhs;
		keep_parent(rhs);
		rhs->pull();
		return rhs;
	}

	// Merge elements according to index criterion
	node_ptr merge_by_index(node_ptr lhs, node_ptr rhs) {
		if (rhs == nullptr) {
			return lhs;
		} else if (lhs == nullptr) {
			return rhs;
		}
		rhs = find_by_index(rhs, 0);
		rhs->left = lhs;
		keep_parent(rhs);
		rhs->pull();
		return rhs;
	}

	node_ptr remove(node_ptr& cur, _Tp value_) {
		if (cur == nullptr) {
			return cur;
		}
		cur = find_by_value(cur, value_);
		if (cur->value != value_) {
			return cur;
		}
		node_ptr temp = cur;
		set_parent(cur->left, nullptr);
		set_parent(cur->right, nullptr);
		cur = merge_by_value(cur->left, cur->right);
		delete temp;
		return cur;
	}

	/* Query for [l, r] for sorted array if inserted all elements by 'insert_sorted()'
	else according to index if inserted by 'insert_at()' */
	_Tp query(node_ptr cur, int l, int r) {
		_Tp res = 0;
		auto pr = split_by_index(cur, l - 1);
		auto pr2 = split_by_index(pr.second, r - l);
		res = pr2.first->sm;
		merge_by_index(pr.first, merge_by_index(pr2.first, pr2.second));
		return res;
	}

	// Add delta in range [l, r]
	void update(node_ptr cur, int l, int r, _Tp delta) {
		assert(l >= 0 && r < Node::get_size(cur) && l <= r);
		auto pr = split_by_index(cur, l - 1);
		auto pr2 = split_by_index(pr.second, r - l);
		pr2.first->apply(delta);
		merge_by_index(pr.first, merge_by_index(pr2.first, pr2.second));
		return;
	}

	// Reverse range [l, r]
	void reverse(node_ptr cur, int l, int r) {
		assert(l >= 0 && r < Node::get_size(cur) && l <= r);
		auto pr = split_by_index(cur, l - 1);
		auto pr2 = split_by_index(pr.second, r - l);
		pr2.first->rev = !(pr2.first->rev);
		merge_by_index(pr.first, merge_by_index(pr2.first, pr2.second));
		return;
	}

	void print(node_ptr cur, int level = 0) {
		if (cur == nullptr) {
			return;
		}
		if (cur->left != nullptr) {
			print(cur->left, level + 1);
		}
		debug(cur->value, cur->sz, level);
		if (cur->right != nullptr) {
			print(cur->right, level + 1);
		}
	}
  private:
	// Helper Functions for node_ptrs
	void set_parent(node_ptr child, node_ptr parent) {
		if (child != nullptr) {
			child->par = parent;
		}
	}
	void keep_parent(node_ptr v) {
		set_parent(v->left, v);
		set_parent(v->right, v);
	}
}; // SplayTree
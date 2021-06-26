namespace algorithms {
	// -------------------------- 2.0 Modifying Sequence Operations --------------------------

	// -------------------------- 2.1 Copy, Copy If --------------------------
	// copies a range of elements to a new location
	template <class _InputIter, class _OutputIter>
	_OutputIter copy(_InputIter first, _InputIter last, _OutputIter d_first) {
		while (first != last) {
			*d_first++ = *first++;
		}
		return d_first;
	}
	template <class _InputIter, class _OutputIter, class UnaryPredicate>
	_OutputIter copy_if(_InputIter first, _InputIter last, _OutputIter d_first, UnaryPredicate pred) {
		while (first != last) {
			if (pred(*first)) {
				*d_first++ = *first;
			}
			first++;
		}
		return d_first;
	}

	// -------------------------- 2.2 Copy N --------------------------
	// copies a number of elements to a new location
	template<class _InputIter, class Size, class _OutputIter>
	_OutputIter copy_n(_InputIter first, Size count, _OutputIter result) {
		if (count > 0) {
			*result++ = *first;
			for (Size i = 1; i < count; ++i) {
				*result++ = *++first;
			}
		}
		return result;
	}

	// -------------------------- 2.3 Copy Backward --------------------------
	// copies a range of elements in backwards order
	template<class _BidirIter1, class _BidirIter2>
	_BidirIter2 copy_backward(_BidirIter1 first, _BidirIter1 last, _BidirIter2 d_last) {
		while (first != last) {
			*(--d_last) = *(--last);
		}
		return d_last;
	}

	// -------------------------- 2.4 Move --------------------------
	// moves a range of elements to a new location
	template<class _InputIter, class _OutputIter>
	_OutputIter move(_InputIter first, _InputIter last, _OutputIter d_first) {
		while (first != last) {
			*d_first++ = std::move(*first++);
		}
		return d_first;
	}

	// -------------------------- 2.4 Move Backward --------------------------
	// moves a range of elements to a new location in backwards order
	template<class _BidirIter1, class _BidirIter2>
	_BidirIter2 move_backward(_BidirIter1 first, _BidirIter1 last, _BidirIter2 d_last) {
		while (first != last) {
			*(--d_last) = std::move(*(--last));
		}
		return d_last;
	}

	// -------------------------- 2.5 Fill --------------------------
	// copy-assigns the given value to every element in a range
	template<class _ForwardIter, class _Ty>
	void fill(_ForwardIter first, _ForwardIter last, const _Ty& value) {
		for (; first != last; ++first) {
			*first = value;
		}
	}

	// -------------------------- 2.6 Fill N --------------------------
	// 	copy-assigns the given value to N elements in a range
	template<class _OutputIter, class Size, class _Ty>
	_OutputIter fill_n(_OutputIter first, Size count, const _Ty& value) {
		for (Size i = 0; i < count; i++) {
			*first++ = value;
		}
		return first;
	}

	// -------------------------- 2.7 Transform --------------------------
	// applies a function to a range of elements, storing results in a destination range
	template<class _InputIter, class _OutputIter, class UnaryOperation>
	_OutputIter transform(_InputIter first1, _InputIter last1, _OutputIter d_first, UnaryOperation unary_op) {
		while (first1 != last1) {
			*d_first++ = unary_op(*first1++);
		}
		return d_first;
	}

	template<class _InputIter1, class InputIt2, class _OutputIter, class BinaryOperation>
	_OutputIter transform(_InputIter1 first1, _InputIter1 last1, InputIt2 first2, _OutputIter d_first, BinaryOperation binary_op) {
		while (first1 != last1) {
			*d_first++ = binary_op(*first1++, *first2++);
		}
		return d_first;
	}

	// -------------------------- 2.8 Generate --------------------------
	// assigns the results of successive function calls to every element in a range
	template<class _ForwardIter, class _Generator>
	void generate(_ForwardIter first, _ForwardIter last, _Generator g) {
		while (first != last) {
			*first++ = g();
		}
	}

	// -------------------------- 2.9 Generate N --------------------------
	// assigns the results of successive function calls to N elements in a range
	template<class _OutputIter, class Size, class _Generator>
	void generate_n(_OutputIter first, Size count, _Generator g) {
		for (Size i = 0; i < count; i++) {
			*first++ = g();
		}
		return first;
	}

	// -------------------------- 2.10 Remove, Remove If --------------------------
	// removes elements satisfying specific criteria
	template<class _ForwardIter, class _Ty>
	_ForwardIter remove(_ForwardIter first, _ForwardIter last, const _Ty& value) {
		first = find(first, last, value);
		if (first != last) {
			for (_ForwardIter i = first; ++i != last;)
				if (!(*i == value)) {
					*first++ = std::move(*i);
				}
		}
		return first;
	}
	template<class _ForwardIter, class UnaryPredicate>
	_ForwardIter remove_if(_ForwardIter first, _ForwardIter last, UnaryPredicate p) {
		first = find_if(first, last, p);
		if (first != last) {
			for (_ForwardIter i = first; ++i != last;)
				if (!p(*i)) {
					*first++ = std::move(*i);
				}
		}
		return first;
	}

	// -------------------------- 2.11 Remove Copy, Remove Copy If --------------------------
	// copies a range of elements omitting those that satisfy specific criteria
	template<class _InputIter, class _OutputIter, class _Ty>
	_OutputIter remove_copy(_InputIter first, _InputIter last, _OutputIter d_first, const _Ty& value) {
		for (; first != last; ++first) {
			if (!(*first == value)) {
				*d_first++ = *first;
			}
		}
		return d_first;
	}
	template<class _InputIter, class _OutputIter, class UnaryPredicate>
	_OutputIter remove_copy_if(_InputIter first, _InputIter last, _OutputIter d_first, UnaryPredicate p) {
		for (; first != last; ++first) {
			if (!p(*first)) {
				*d_first++ = *first;
			}
		}
		return d_first;
	}

	// -------------------------- 2.12 Replace, Replace If --------------------------
	// replaces all values satisfying specific criteria with another value
	template<class _ForwardIter, class T>
	void replace(_ForwardIter first, _ForwardIter last, const T& old_value, const T& new_value) {
		for (; first != last; ++first) {
			if (*first == old_value) {
				*first = new_value;
			}
		}
	}
	template<class _ForwardIter, class UnaryPredicate, class T>
	void replace_if(_ForwardIter first, _ForwardIter last, UnaryPredicate p, const T& new_value) {
		for (; first != last; ++first) {
			if (p(*first)) {
				*first = new_value;
			}
		}
	}
	// -------------------------- 2.13 Replace Copy, Replace Copy If --------------------------
	// copies a range, replacing elements satisfying specific criteria with another value
	template<class _InputIter, class _OutputIter, class T>
	_OutputIter replace_copy(_InputIter first, _InputIter last, _OutputIter d_first,
	                         const T& old_value, const T& new_value) {
		for (; first != last; ++first) {
			*d_first++ = (*first == old_value) ? new_value : *first;
		}
		return d_first;
	}
	template<class _InputIter, class _OutputIter,
	         class UnaryPredicate, class T>
	_OutputIter replace_copy_if(_InputIter first, _InputIter last, _OutputIter d_first,
	                            UnaryPredicate p, const T& new_value) {
		for (; first != last; ++first) {
			*d_first++ = p(*first) ? new_value : *first;
		}
		return d_first;
	}

	// -------------------------- 2.14 Iter Swap --------------------------
	// swaps the elements pointed to by two iterators
	// template<class _ForwardIter1, class _ForwardIter2>
	// constexpr void iter_swap(_ForwardIter1 a, _ForwardIter2 b) {
	// 	std::swap(*a, *b);
	// }

	// -------------------------- 2.15 Swap Ranges --------------------------
	// swaps two ranges of elements
	template<class _ForwardIter1, class _ForwardIter2>
	constexpr _ForwardIter2 swap_ranges(_ForwardIter1 first1, _ForwardIter1 last1, _ForwardIter2 first2) {
		while (first1 != last1) {
			std::iter_swap(first1++, first2++);
		}
		return first2;
	}

	// -------------------------- 2.16 Reverse --------------------------
	// reverses the order of elements in a range
	template<class _BidirIter>
	void reverse(_BidirIter first, _BidirIter last) {
		while ((first != last) && (first != --last)) {
			std::iter_swap(first++, last);
		}
	}

	// -------------------------- 2.17 Reverse Copy --------------------------
	// creates a copy of a range that is reversed
	template<class _BidirIter, class _OutputIter>
	_OutputIter reverse_copy(_BidirIter first, _BidirIter last, _OutputIter d_first) {
		while (first != last) {
			*(d_first++) = *(--last);
		}
		return d_first;
	}

	// -------------------------- 2.18 Rotate --------------------------
	// rotates the order of elements in a range
	template<class _ForwardIter>
	_ForwardIter rotate(_ForwardIter first, _ForwardIter n_first, _ForwardIter last) {
		if (first == n_first) {
			return last;
		}
		if (n_first == last) {
			return first;
		}

		_ForwardIter read = n_first;
		_ForwardIter write = first;
		_ForwardIter next_read = first; // read position for when "read" hits "last"

		while (read != last) {
			if (write == next_read) {
				next_read = read;    // track where "first" went
			}
			std::iter_swap(write++, read++);
		}

		// rotate the remaining sequence into place
		(rotate)(write, next_read, last);
		return write;
	}

	// -------------------------- 2.19 Rotate Copy --------------------------
	// copies and rotate a range of elements
	template<class _ForwardIter, class _OutputIter>
	_OutputIter rotate_copy(_ForwardIter first, _ForwardIter n_first, _ForwardIter last, _OutputIter d_first) {
		d_first = copy(n_first, last, d_first);
		return copy(first, n_first, d_first);
	}

	// -------------------------- 2.20 Shuffle --------------------------
	// randomly re-orders elements in a range
	template<class _RandomIter, class URBG>
	void shuffle(_RandomIter first, _RandomIter last, URBG&& g) {
		using diff_t = typename std::iterator_traits<_RandomIter>::difference_type;
		using distr_t = std::uniform_int_distribution<diff_t>;
		using param_t = typename distr_t::param_type;

		distr_t D;
		diff_t n = last - first;
		for (diff_t i = n - 1; i > 0; --i) {
			std::swap(first[i], first[D(g, param_t(0, i))]);
		}
	}

	// -------------------------- 2.21 Unique --------------------------
	// removes consecutive duplicate elements in a range
	template <class _ForwardIter>
	_ForwardIter unique(_ForwardIter first, _ForwardIter last) {
		if (first == last) {
			return last;
		}
		_ForwardIter result = first;
		while (++first != last) {
			if (!(*result == *first) && ++result != first) {
				*result = std::move(*first);
			}
		}
		return ++result;
	}

	template<class _ForwardIter, class BinaryPredicate>
	_ForwardIter unique(_ForwardIter first, _ForwardIter last, BinaryPredicate p) {
		if (first == last) {
			return last;
		}
		_ForwardIter result = first;
		while (++first != last) {
			if (!p(*result, *first) && ++result != first) {
				*result = std::move(*first);
			}
		}
		return ++result;
	}

}; // namespace algorithms
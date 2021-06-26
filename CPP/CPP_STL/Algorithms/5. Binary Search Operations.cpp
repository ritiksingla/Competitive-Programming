namespace algorithms {
	// -------------------------- 5.0 Binary Seach Operations --------------------------

	// -------------------------- 5.1 Lower Bound --------------------------
	// returns an iterator to the first element not less than the given value
	template <class _ForwardIter, class _Ty>
	_ForwardIter lower_bound(_ForwardIter first, _ForwardIter last, const _Ty& value) {
		_ForwardIter it;
		typename std::iterator_traits<_ForwardIter>::difference_type count, step;
		count = std::distance(first, last);
		while (count > 0) {
			it = first;
			step = count / 2;
			std::advance(it, step);
			if (*it < value) {
				first = ++it;
				count -= step + 1;
			} else {
				count = step;
			}
		}
		return first;
	}

	template <class _ForwardIter, class _Ty, class _Compare>
	_ForwardIter lower_bound(_ForwardIter first, _ForwardIter last, const _Ty& value, _Compare comp) {
		_ForwardIter it;
		typename std::iterator_traits<_ForwardIter>::difference_type count, step;
		count = std::distance(first, last);
		while (count > 0) {
			it = first;
			step = count / 2;
			std::advance(it, step);
			if (comp(*it, value)) {
				first = ++it;
				count -= step + 1;
			} else {
				count = step;
			}
		}
		return first;
	}

	// -------------------------- 5.2 Upper Bound--------------------------
	// returns an iterator to the first element greater than a certain value
	template <class _ForwardIter, class _Ty>
	_ForwardIter upper_bound(_ForwardIter first, _ForwardIter last, const _Ty& value) {
		_ForwardIter it;
		typename std::iterator_traits<_ForwardIter>::difference_type count, step;
		count = std::distance(first, last);
		while (count > 0) {
			it = first;
			step = count / 2;
			std::advance(it, step);
			if (!(value < *it)) {
				first = ++it;
				count -= step + 1;
			} else {
				count = step;
			}
		}
		return first;
	}

	template <class _ForwardIter, class _Ty, class _Compare>
	_ForwardIter upper_bound(_ForwardIter first, _ForwardIter last, const _Ty& value, _Compare comp) {
		_ForwardIter it;
		typename std::iterator_traits<_ForwardIter>::difference_type count, step;
		count = std::distance(first, last);
		while (count > 0) {
			it = first;
			step = count / 2;
			std::advance(it, step);
			if (!comp(value, *it)) {
				first = ++it;
				count -= step + 1;
			} else {
				count = step;
			}
		}
		return first;
	}

	// -------------------------- 5.3 Binary Search --------------------------
	// determines if an element exists in a certain range
	template<class _ForwardIter, class _Ty>
	bool binary_search(_ForwardIter first, _ForwardIter last, const _Ty& value) {
		first = lower_bound(first, last, value);
		return (!(first == last) && !(value < *first));
	}
	template<class _ForwardIter, class _Ty, class _Compare>
	bool binary_search(_ForwardIter first, _ForwardIter last, const _Ty& value, _Compare comp) {
		first = lower_bound(first, last, value, comp);
		return (!(first == last) && !comp(value, *first));
	}

	// -------------------------- 5.4 Equal Range --------------------------
	// returns range of elements matching a specific key
	template<class _ForwardIter, class _Ty>
	std::pair<_ForwardIter, _ForwardIter>
	equal_range(_ForwardIter first, _ForwardIter last, const _Ty& value) {
		return std::make_pair(lower_bound(first, last, value), upper_bound(first, last, value));
	}
	template<class _ForwardIter, class _Ty, class _Compare>
	std::pair<_ForwardIter, _ForwardIter>
	equal_range(_ForwardIter first, _ForwardIter last, const _Ty& value, _Compare comp) {
		return std::make_pair(lower_bound(first, last, value, comp), upper_bound(first, last, value, comp));
	}
}; // namespace algorithms
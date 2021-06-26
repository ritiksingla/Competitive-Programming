namespace algorithms {

	// -------------------------- 1.0 Non Modifying Sequence Operations --------------------------

	// -------------------------- 1.1 Find, Find If, Find If Not --------------------------
	// finds the first element satisfying specific criteria
	template<class _InputIter, class _Ty>
	constexpr _InputIter find(_InputIter first, _InputIter last, const _Ty& value) {
		for (; first != last; ++first) {
			if (*first == value) {
				return first;
			}
		}
		return last;
	}

	template<class _InputIter, class UnaryPredicate>
	constexpr _InputIter find_if(_InputIter first, _InputIter last, UnaryPredicate p) {
		for (; first != last; ++first) {
			if (p(*first)) {
				return first;
			}
		}
		return last;
	}

	template<class _InputIter, class UnaryPredicate>
	constexpr _InputIter find_if_not(_InputIter first, _InputIter last, UnaryPredicate q) {
		for (; first != last; ++first) {
			if (!q(*first)) {
				return first;
			}
		}
		return last;
	}

	// -------------------------- 1.2 All Of, Any Of, None Of --------------------------
	// checks if a predicate is true for all, any or none of the elements in a range
	template <class _InputIter, class UnaryPredicate>
	constexpr bool all_of(_InputIter first, _InputIter last, UnaryPredicate p) {
		return find_if_not(first, last, p) == last;
	}

	template <class _InputIter, class UnaryPredicate>
	constexpr bool any_of(_InputIter first, _InputIter last, UnaryPredicate p) {
		return find_if(first, last, p) != last;
	}

	template <class _InputIter, class UnaryPredicate>
	constexpr bool none_of(_InputIter first, _InputIter last, UnaryPredicate p) {
		return find_if(first, last, p) == last;
	}

	// -------------------------- 1.3 For Each, For Each N --------------------------
	// applies a function to a range of elements
	template <class _InputIter, class UnaryFunction>
	constexpr UnaryFunction for_each(_InputIter first, _InputIter last, UnaryFunction f) {
		for (; first != last; first++) {
			f(*first);
		}
		return f;
	}
	// applies a function object to the first n elements of a sequence
	template<class _InputIter, class Size, class UnaryFunction>
	_InputIter for_each_n(_InputIter first, Size n, UnaryFunction f) {
		for (Size i = 0; i < n; ++first, (void) ++i) {
			f(*first);
		}
		return first;
	}

	// -------------------------- 1.4 Count, Count IF --------------------------
	// returns the number of elements satisfying specific criteria
	template <class _InputIter, class _Ty>
	typename std::iterator_traits<_InputIter>::difference_type
	count(_InputIter first, _InputIter last, const _Ty& value) {
		typename std::iterator_traits<_InputIter>::difference_type res = 0;
		for (; first != last; first++) {
			if (*first == value) {
				res++;
			}
		}
		return res;
	}

	template<class _InputIter, class UnaryPredicate>
	typename std::iterator_traits<_InputIter>::difference_type
	count_if(_InputIter first, _InputIter last, UnaryPredicate p) {
		typename std::iterator_traits<_InputIter>::difference_type res = 0;
		for (; first != last; ++first) {
			if (p(*first)) {
				res++;
			}
		}
		return res;
	}

	// -------------------------- 1.5 Mismatch --------------------------
	// finds the first position where two ranges differ
	template<class _InputIterer1, class _InputIterer2>
	std::pair<_InputIterer1, _InputIterer2>
	mismatch(_InputIterer1 first1, _InputIterer1 last1, _InputIterer2 first2, _InputIterer2 last2) {
		while (first1 != last1 && first2 != last2 && *first1 == *first2) {
			++first1, ++first2;
		}
		return std::make_pair(first1, first2);
	}

	template<class _InputIterer1, class _InputIterer2, class BinaryPredicate>
	std::pair<_InputIterer1, _InputIterer2>
	mismatch(_InputIterer1 first1, _InputIterer1 last1, _InputIterer2 first2, _InputIterer2 last2, BinaryPredicate p) {
		while (first1 != last1 && first2 != last2 && p(*first1, *first2)) {
			++first1, ++first2;
		}
		return std::make_pair(first1, first2);
	}

	// -------------------------- 1.6 Search (find_begin)--------------------------
	// searches for a range of elements
	template<class _InputIterer1, class _InputIterer2>
	constexpr _InputIterer1 search(_InputIterer1 first, _InputIterer1 last, _InputIterer2 s_first, _InputIterer2 s_last) {
		for (; ; ++first) {
			_InputIterer1 it = first;
			for (_InputIterer2 s_it = s_first; ; ++it, ++s_it) {
				if (s_it == s_last) {
					return first;
				}
				if (it == last) {
					return last;
				}
				if (!(*it == *s_it)) {
					break;
				}
			}
		}
	}

	template<class _InputIterer1, class _InputIterer2, class BinaryPredicate>
	constexpr _InputIterer1 search(_InputIterer1 first, _InputIterer1 last, _InputIterer2 s_first, _InputIterer2 s_last, BinaryPredicate p) {
		for (; ; ++first) {
			_InputIterer1 it = first;
			for (_InputIterer2 s_it = s_first; ; ++it, ++s_it) {
				if (s_it == s_last) {
					return first;
				}
				if (it == last) {
					return last;
				}
				if (!p(*it, *s_it)) {
					break;
				}
			}
		}
	}

	// -------------------------- 1.7 Search N --------------------------
	// searches a range for a number of consecutive copies of an element
	template<class _InputIter, class Size, class _Ty>
	_InputIter search_n(_InputIter first, _InputIter last, Size count, const _Ty& value) {
		if (count <= 0) {
			return first;
		}
		for (; first != last; ++first) {
			if (!(*first == value)) {
				continue;
			}

			_InputIter candidate = first;
			Size cur_count = 0;

			while (true) {
				++cur_count;
				if (cur_count >= count) {
					// success
					return candidate;
				}
				++first;
				if (first == last) {
					// exhausted the list
					return last;
				}
				if (!(*first == value)) {
					// too few in a row
					break;
				}
			}
		}
		return last;
	}

	template<class _InputIter, class Size, class _Ty, class BinaryPredicate>
	_InputIter search_n(_InputIter first, _InputIter last, Size count, const _Ty& value, BinaryPredicate p) {
		if (count <= 0) {
			return first;
		}
		for (; first != last; ++first) {
			if (!p(*first, value)) {
				continue;
			}

			_InputIter candidate = first;
			Size cur_count = 0;

			while (true) {
				++cur_count;
				if (cur_count >= count) {
					// success
					return candidate;
				}
				++first;
				if (first == last) {
					// exhausted the list
					return last;
				}
				if (!p(*first, value)) {
					// too few in a row
					break;
				}
			}
		}
		return last;
	}

	// -------------------------- 1.8 Find End --------------------------
	// finds the last sequence of elements in a certain range
	template<class _InputIterer1, class _InputIterer2>
	constexpr _InputIterer1 find_end(_InputIterer1 first, _InputIterer1 last, _InputIterer2 s_first, _InputIterer2 s_last) {
		if (s_first == s_last) {
			return last;
		}
		_InputIterer1 result = last;
		while (true) {
			_InputIterer1 new_result = search(first, last, s_first, s_last);
			if (new_result == last) {
				break;
			} else {
				result = new_result;
				first = result;
				++first;
			}
		}
		return result;
	}

	template<class _InputIterer1, class _InputIterer2, class BinaryPredicate>
	constexpr _InputIterer1 find_end(_InputIterer1 first, _InputIterer1 last, _InputIterer2 s_first, _InputIterer2 s_last, BinaryPredicate p) {
		if (s_first == s_last) {
			return last;
		}
		_InputIterer1 result = last;
		while (true) {
			_InputIterer1 new_result = search(first, last, s_first, s_last, p);
			if (new_result == last) {
				break;
			} else {
				result = new_result;
				first = result;
				++first;
			}
		}
		return result;
	}

	// -------------------------- 1.9 Adjacent Find --------------------------
	// finds the first two adjacent items that are equal (or satisfy a given predicate)
	template<class _InputIter>
	_InputIter adjacent_find(_InputIter first, _InputIter last) {
		if (first == last) {
			return last;
		}
		_InputIter next = first;
		++next;
		for (; next != last; ++next, ++first) {
			if (*first == *next) {
				return first;
			}
		}
		return last;
	}
	template<class _InputIter, class BinaryPredicate>
	_InputIter adjacent_find(_InputIter first, _InputIter last, BinaryPredicate p) {
		if (first == last) {
			return last;
		}
		_InputIter next = first;
		++next;
		for (; next != last; ++next, ++first) {
			if (p(*first, *next)) {
				return first;
			}
		}
		return last;
	}

	// -------------------------- 1.10 Find First Of --------------------------
	template<class _InputIter, class _ForwardIter>
	_InputIter find_first_of(_InputIter first, _InputIter last, _ForwardIter s_first, _ForwardIter s_last) {
		for (; first != last; ++first) {
			for (_ForwardIter it = s_first; it != s_last; ++it) {
				if (*first == *it) {
					return first;
				}
			}
		}
		return last;
	}
	template<class _InputIter, class _ForwardIter, class BinaryPredicate>
	_InputIter find_first_of(_InputIter first, _InputIter last, _ForwardIter s_first, _ForwardIter s_last, BinaryPredicate p) {
		for (; first != last; ++first) {
			for (_ForwardIter it = s_first; it != s_last; ++it) {
				if (p(*first, *it)) {
					return first;
				}
			}
		}
		return last;
	}
}; // namespace algorithms
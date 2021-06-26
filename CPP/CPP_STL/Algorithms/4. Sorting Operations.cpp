namespace algorithms {
	// -------------------------- 4.0 Sorting Operations --------------------------

	// -------------------------- 4.1 Is Sorted Until --------------------------
	// finds the largest sorted subrange
	template <class _ForwardIter, class _Compare>
	bool is_sorted_until(_ForwardIter first, _ForwardIter last, _Compare comp) {
		if (first != last) {
			_ForwardIter next = first;
			while (++next != last) {
				if (comp(*next, *first)) {
					return next;
				}
				first  = next;
			}
		}
		return last;
	}

	template<class _ForwardIter>
	_ForwardIter is_sorted_until(_ForwardIter first, _ForwardIter last) {
		return is_sorted_until(first, last, std::less<>());
	}

	// -------------------------- 4.2 Is Sorted --------------------------
	// checks whether a range is sorted into ascending order
	template<class _ForwardIter>
	bool is_sorted(_ForwardIter first, _ForwardIter last) {
		return is_sorted_until(first, last) == last;
	}
	template<class _ForwardIter, class _Compare>
	bool is_sorted(_ForwardIter first, _ForwardIter last, _Compare comp) {
		return is_sorted_until(first, last, comp) == last;
	}

	// -------------------------- 4.3 Merge --------------------------
	// merges two sorted ranges
	template<class _InputIter1, class _InputIter2, class _OutputIter>
	_OutputIter merge(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first) {
		for (; first1 != last1; ++d_first) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}
			if (*first2 < *first1) {
				*d_first = *first2;
				++first2;
			} else {
				*d_first = *first1;
				++first1;
			}
		}
		return copy(first2, last2, d_first);
	}

	template<class _InputIter1, class _InputIter2, class _OutputIter, class _Compare>
	_OutputIter merge(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first, _Compare comp) {
		for (; first1 != last1; ++d_first) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}
			if (comp(*first2, *first1)) {
				*d_first = *first2;
				++first2;
			} else {
				*d_first = *first1;
				++first1;
			}
		}
		return copy(first2, last2, d_first);
	}
}; // namespace algorithms
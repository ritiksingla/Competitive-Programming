namespace algorithms {

	// -------------------------- 6.0 Set Operations (on sorted ranges) --------------------------

	// -------------------------- 6.1 Includes --------------------------
	// Returns true if the sorted range [first2, last2) is a subsequence of the sorted range
	// [first1, last1), (A subsequence need not be contiguous)
	// Both sequences must be sorted with std::less<> or comp in second implementation
	template<class _InputIter1, class _InputIter2>
	bool includes(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2) {
		for (; first2 != last2; ++first1) {
			if (first1 == last1 || *first2 < *first1) {
				return false;
			}
			if (!(*first1 < *first2)) {
				++first2;
			}
		}
		return true;
	}
	template<class _InputIter1, class _InputIter2, class _Compare>
	bool includes(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _Compare comp) {
		for (; first2 != last2; ++first1) {
			if (first1 == last1 || comp(*first2, *first1)) {
				return false;
			}
			if (!comp(*first1, *first2)) {
				++first2;
			}
		}
		return true;
	}

	// -------------------------- 6.2 Set Difference --------------------------
	// Copies the elements from the sorted range [first1, last1) which are not found in the sorted range
	// [first2, last2) to the range beginning at d_first.
	template<class _InputIter1, class _InputIter2, class _OutputIter>
	_OutputIter set_difference(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first) {
		while (first1 != last1) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}

			if (*first1 < *first2) {
				*d_first++ = *first1++;
			} else {
				if (!(*first2 < *first1)) {
					++first1;
				}
				++first2;
			}
		}
		return d_first;
	}
	template<class _InputIter1, class _InputIter2, class _OutputIter, class _Compare>
	_OutputIter set_difference(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first, _Compare comp) {
		while (first1 != last1) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}

			if (comp(*first1, *first2)) {
				*d_first++ = *first1++;
			} else {
				if (!comp(*first2, *first1)) {
					++first1;
				}
				++first2;
			}
		}
		return d_first;
	}

	// -------------------------- 6.3 Set Intersection --------------------------
	// Constructs a sorted range beginning at d_first consisting of elements that are found in both sorted ranges
	// [first1, last1) and [first2, last2). If some element is found m times in [first1, last1) and n times in
	// [first2, last2), the first std::min(m, n) elements will be copied from the first range to the destination range.
	// The order of equivalent elements is preserved. The resulting range cannot overlap with either of the input ranges.
	template<class _InputIter1, class _InputIter2, class _OutputIter>
	_OutputIter set_intersection(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				++first1;
			} else  {
				if (!(*first2 < *first1)) {
					*d_first++ = *first1++;
				}
				++first2;
			}
		}
		return d_first;
	}
	template<class _InputIter1, class _InputIter2, class _OutputIter, class _Compare>
	_OutputIter set_intersection(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first, _Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				++first1;
			} else {
				if (!comp(*first2, *first1)) {
					*d_first++ = *first1++;
				}
				++first2;
			}
		}
		return d_first;
	}

	// -------------------------- 6.4 Set Symmetric Difference --------------------------
	// (A - B) + (B - A) or (A ∪ B) - (A ∩ B)
	template<class _InputIter1, class _InputIter2, class _OutputIter>
	_OutputIter set_symmetric_difference(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first) {
		while (first1 != last1) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}

			if (*first1 < *first2) {
				*d_first++ = *first1++;
			} else {
				if (*first2 < *first1) {
					*d_first++ = *first2;
				} else {
					++first1;
				}
				++first2;
			}
		}
		return copy(first2, last2, d_first);
	}
	template<class _InputIter1, class _InputIter2, class _OutputIter, class _Compare>
	_OutputIter set_symmetric_difference(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first, _Compare comp) {
		while (first1 != last1) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}

			if (comp(*first1, *first2)) {
				*d_first++ = *first1++;
			} else {
				if (comp(*first2, *first1)) {
					*d_first++ = *first2;
				} else {
					++first1;
				}
				++first2;
			}
		}
		return copy(first2, last2, d_first);
	}

	// -------------------------- 6.5 Set Union --------------------------
	// Constructs a sorted union beginning at d_first consisting of the set of elements
	// present in one or both sorted ranges [first1, last1) and [first2, last2).
	// If some element is found m times in [first1, last1) and n times in [first2, last2),
	// then all m elements will be copied from [first1, last1) to d_first, preserving order,
	// and then exactly std::max(n-m, 0) elements will be copied from [first2, last2) to d_first, also preserving order.
	template<class _InputIter1, class _InputIter2, class _OutputIter>
	_OutputIter set_union(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first) {
		for (; first1 != last1; ++d_first) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}
			if (*first2 < *first1) {
				*d_first = *first2++;
			} else {
				*d_first = *first1;
				if (!(*first1 < *first2)) {
					++first2;
				}
				++first1;
			}
		}
		return copy(first2, last2, d_first);
	}
	template<class _InputIter1, class _InputIter2, class _OutputIter, class _Compare>
	_OutputIter set_union(_InputIter1 first1, _InputIter1 last1, _InputIter2 first2, _InputIter2 last2, _OutputIter d_first, _Compare comp) {
		for (; first1 != last1; ++d_first) {
			if (first2 == last2) {
				return copy(first1, last1, d_first);
			}
			if (comp(*first2, *first1)) {
				*d_first = *first2++;
			} else {
				*d_first = *first1;
				if (!comp(*first1, *first2)) {
					++first2;
				}
				++first1;
			}
		}
		return copy(first2, last2, d_first);
	}
};
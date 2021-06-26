namespace algorithms {
	// -------------------------- 3.0 Partitioning Operations --------------------------

	// -------------------------- 3.1 Is Partitioned --------------------------
	// determines if the range is partitioned by the given predicate
	template <class _InputIter, class UnaryPredicate>
	bool is_partitioned(_InputIter first, _InputIter last, UnaryPredicate p) {
		for (; first != last; ++first) {
			if (!p(*first)) {
				break;
			}
		}
		for (; first != last; ++first) {
			if (p(*first)) {
				return false;
			}
		}
		return true;
	}

	// -------------------------- 3.2 Partition--------------------------
	// divides a range of elements into two groups
	// NOTE: Does not guarantee relative order in the final result!
	template <class _ForwardIter, class UnaryPredicate>
	_ForwardIter partition(_ForwardIter first, _ForwardIter last, UnaryPredicate p) {
		first = find_if_not(first, last, p);
		if (first == last) {
			return last;
		}
		for (_ForwardIter it = std::next(first); it != last; ++it) {
			if (p(*it)) {
				std::iter_swap(it, first);
				++first;
			}
		}
		return first;
	}

	// -------------------------- 3.3 Partition Copy --------------------------
	// copies a range dividing the elements into two groups
	template<class _InputIter, class _OutputIter1, class _OutputIter2, class UnaryPredicate>
	std::pair<_OutputIter1, _OutputIter2> partition_copy(_InputIter first, _InputIter last, _OutputIter1 d_first_true, _OutputIter2 d_first_false, UnaryPredicate p) {
		while (first != last) {
			if (p(*first)) {
				*d_first_true = *first;
				++d_first_true;
			} else {
				*d_first_false = *first;
				++d_first_false;
			}
			++first;
		}
		return std::pair<_OutputIter1, _OutputIter2>(d_first_true, d_first_false);
	}

	// -------------------------- 3.4 Stable Partition --------------------------
	// divides elements into two groups while preserving their relative order
	template <class _ForwardIter, class UnaryPredicate>
	std::pair<_ForwardIter, _ForwardIter> stable_partition(_ForwardIter first, _ForwardIter last, UnaryPredicate p) {
		first = find_if_not(first, last, p);
		_ForwardIter mid = first;
		while (mid != last) {
			mid = find_if(mid, last, p);
			if (mid == last) {
				break;
			}
			_ForwardIter last2 = find_if_not(mid, last, p);
			rotate(first, mid, last2);
			first = std::next(first, std::distance(mid, last2));
			mid = last2;
		}
		return std::pair<_ForwardIter, _ForwardIter>(first, mid);
	}

	// -------------------------- 3.5  Partition Point--------------------------
	// locates the partition point of a partitioned range
	template <class _ForwardIter, class UnaryPredicate>
	_ForwardIter partition_point(_ForwardIter first, _ForwardIter last, UnaryPredicate p) {
		_ForwardIter res = find_if_not(first, last, p);
		return res;
	}

}; // namespace algorithms
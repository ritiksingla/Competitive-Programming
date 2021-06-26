// Sorting Algorithms
//
template<typename T>
class Sort {
  private:
	int N;
	vector<T>A;

	void check() {
		for (int i = 0; i + 1 < N; i++) {
			assert(A[i] <= A[i + 1]);
		}
	}

  public:
	Sort(const vector<T>& _A) {
		A = _A;
		N = (int)A.size();
	}

	int partition(int lo, int hi) {
		// Choosing pivot as last element
		int pivot = A[hi];
		int l = lo - 1;

		for (int r = lo; r <= hi; r++) {
			if (A[r] < pivot) {
				swap(A[++l], A[r]);
			}
		}

		swap(A[++l], A[hi]);
		return l;
	}

	void quickSort(int lo, int hi) {
		if (lo < hi) {
			int p = partition(lo, hi);
			quickSort(lo, p - 1);
			quickSort(p + 1, hi);
		}
	}

	void quickSort() {
		int lo = 0, hi = N - 1;
		quickSort(lo, hi);
		check();
	}

	void merge(int lo, int mid, int hi) {
		int n = (hi - lo + 1);
		vector<T>b(n);
		int idx{};
		int l = lo, r = mid + 1;

		for (; l <= mid && r <= hi;) {
			if (A[l] <= A[r]) {
				b[idx++] = A[l++];
			} else {
				b[idx++] = A[r++];
			}
		}

		for (; l <= mid;) {
			b[idx++] = A[l++];
		}

		for (; r <= hi;) {
			b[idx++] = A[r++];
		}

		for (int i = lo; i <= hi; i++) {
			A[i] = b[i - lo];
		}
	}

	void mergeSort(int lo, int hi) {
		if (lo >= hi) {
			return;
		}
		int mid = (lo + (hi - lo) / 2);

		mergeSort(lo, mid);
		mergeSort(mid + 1, hi);
		merge(lo, mid, hi);
	}

	void mergeSort() {
		int lo = 0, hi = N - 1;
		mergeSort(lo, hi);
		check();
	}
	void max_heapify(int idx, int n) {
		int maxi = idx;
		int l = 2 * idx + 1;
		int r = 2 * idx + 2;

		if (l < n && A[l] > A[maxi]) {
			maxi = l;
		}

		if (r < n && A[r] > A[maxi]) {
			maxi = r;
		}

		if (maxi != idx) {
			swap(A[maxi], A[idx]);
			max_heapify(maxi, n);
		}
	}
	void maxHeapSort() {
		for (int i = N / 2 - 1; i >= 0; i--) {
			max_heapify(i, N);
		}

		for (int i = N - 1; i; i--) {
			swap(A[0], A[i]);
			max_heapify(0, i);
		}
		check();
	}
	void min_heapify(int idx, int n) {
		int mini = idx;
		int l = 2 * idx + 1;
		int r = 2 * idx + 2;

		if (l < n && A[l] < A[mini]) {
			mini = l;
		}

		if (r < n && A[r] < A[mini]) {
			mini = r;
		}

		if (mini != idx) {
			swap(A[idx], A[mini]);
			min_heapify(mini, n);
		}
	}
	void minHeapSort() {
		for (int i = N / 2 - 1; i >= 0; i--) {
			min_heapify(i, N);
		}

		for (int i = N - 1; i; i--) {
			swap(A[0], A[i]);
			min_heapify(0, i);
		}
		reverse(begin(A), end(A));
		check();
	}
	void selectionSort() {
		for (int i = 0; i + 1 < N; ++i) {
			int mini = i;

			for (int j = i + 1; j < N; j++) {
				if (A[j] < A[mini]) {
					mini = j;
				}
			}
			swap(A[mini], A[i]);
		}
		check();
	}
	void insertionSort() {
		for (int i = 1; i < N; i++) {
			int j = i - 1;
			int x = A[i];

			while (j >= 0 && A[j] > x) {
				A[j + 1] = A[j];
				j--;
			}
			A[j + 1] = x;
		}
		check();
	}
	void countSort() {
		int M = *max_element(begin(A), end(A));
		int mini = *min_element(begin(A), end(A));
		assert(mini >= 0);
		vector<int>p(M + 1), B(N);

		for (int i = 0; i < N; ++i) {
			p[A[i]]++;
		}

		for (int i = 1; i <= M; ++i) {
			p[i] += p[i - 1];
		}

		for (int i = 0; i < N; ++i) {
			B[--p[A[i]]] = A[i];
		}
		A = B;
		check();
	}
	void radixSort() {
		int M = *max_element(begin(A), end(A));
		int mini = *min_element(begin(A), end(A));
		assert(mini >= 0);

		const int base = N;
		int d = 1;

		for (int power = 0; M / d > 0; power++) {
			vector<int>p(base), B(N);

			for (int i = 0; i < N; ++i) {
				p[(A[i] / d) % base]++;
			}

			for (int i = 1; i < base; ++i) {
				p[i] += p[i - 1];
			}

			for (int i = N - 1; i >= 0; --i) {
				B[--p[(A[i] / d) % base]] = A[i];
			}
			A = B;
			d *= base;
		}
		check();
	}
	void shuffle() {
		random_shuffle(begin(A), end(A));
	}
	void show() {
		for (auto& a : A) {
			cout << a << ' ';
		}
		cout << '\n';
	}
};
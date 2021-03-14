// Manacher's Algorithm
//
template<typename String>
struct Manacher {
	String S;
	int N;
	vector<int>d1, d2;
	int64_t total_palindromes;
	Manacher(String S_): S(S_) {
		N = S.size();
		d1.resize(N); d2.resize(N);
		total_palindromes = 0;
		build();
	}
	void build() {
		int l = 0, r = -1, length = 1;
		for (int i = 0; i < N; ++i) {
			if (i > r) {
				length = 1;
			} else {
				int mirror_i = l + (r - i);
				length = min(d1[mirror_i], r - i + 1);
			}
			while (i - length >= 0 && i + length < N && S[i - length] == S[i + length]) {
				length++;
			}
			total_palindromes += int64_t(length);
			d1[i] = length; length--;
			if (i + length > r) {
				l = i - length;
				r = i + length;
			}
		}

		l = 0, r = -1, length = 0;
		for (int i = 0; i < N; ++i) {
			if (i > r) {
				length = 0;
			} else {
				int mirror_i = l + (r - i) + 1;
				length = min(d2[mirror_i], r - i + 1);
			}
			while (i - length - 1 >= 0 && i + length < N && S[i - length - 1] == S[i + length]) {
				length++;
			}
			total_palindromes += length;
			d2[i] = length; length--;
			if (i + length > r) {
				l = i - length - 1;
				r = i + length;
			}
		}
	}
};
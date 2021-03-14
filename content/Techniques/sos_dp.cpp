// Iteration over submasks DP
//
// Tutorial : https://codeforces.com/blog/entry/45223
// Space Complexity : O(N),
// Time Complexity: O(N * logN),
// where N is the maximum element in the vector
const int BIT = 22, BASE = (1 << BIT) - 1;
vector<int>F(BASE);
for (int i = 0; i < N; ++i) {
	F[i] = A[i];
}
for (int bit = 0; bit < BIT; bit++) {
	for (int i = 0 ; i <= BASE; ++i) {
		if (i & (1 << bit)) {
			// Iterating over all submasks only once
			// Similarly we can iterate over all supermasks of the current index
			F[i] += F[i - (1 << bit)];
		}
	}
}
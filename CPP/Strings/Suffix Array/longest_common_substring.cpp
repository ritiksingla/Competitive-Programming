// LCS using Suffix Array
//
string longest_common_substring(const string& S, const string& T) {
	int N = int(S.size());
	const char EXTRA = '$';
	assert(S.find(EXTRA) == string::npos);
	assert(T.find(EXTRA) == string::npos);
	SuffixArray<string>SA(S + EXTRA + T);
	int split = SA.sa[0];
	int max_len = 0, idx = 0;
	for (int i = 1; i + 1 < SA.N; ++i) {
		if ((SA.sa[i] < split && SA.sa[i + 1] > split) || (SA.sa[i] > split && SA.sa[i + 1] < split)) {
			if (max_len < SA.lcp[i]) {
				max_len = SA.lcp[i];
				idx = SA.sa[i];
			}
		}
	}
	if (idx >= N) {
		return T.substr(idx - N - 1, max_len);
	} else {
		return S.substr(idx, max_len);
	}
}
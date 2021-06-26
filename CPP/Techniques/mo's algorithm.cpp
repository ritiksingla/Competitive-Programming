// Mo's Algorithm
//
// Global
int blk_sz;
int res;
vector<int>cnt;
vector<int>freq;
bool comp(const array<int, 3>& lhs, const array<int, 3>& rhs) {
	if (lhs[0] / blk_sz != rhs[0] / blk_sz) {
		return (lhs[0] / blk_sz < rhs[0] / blk_sz);
	} else {
		if ((lhs[0] / blk_sz) % 2 == 1) {
			return (lhs[1] < rhs[1]);
		} else {
			return (lhs[1] > rhs[1]);
		}
	}
};
void add(int x) {
	if (cnt[x] > 0) {
		freq[cnt[x]]--;
	}
	cnt[x]++;
	freq[cnt[x]]++;
	if (res < cnt[x]) {
		res = cnt[x];
	}
}
void remove(int x) {
	if (res == cnt[x]) {
		if (freq[cnt[x]] == 1) {
			res--;
		}
	}
	freq[cnt[x]]--;
	cnt[x]--;
	if (cnt[x] > 0) {
		freq[cnt[x]]++;
	}
}

// Main
vector<int>ans(Q);
vector<array<int, 3>>queries(Q);
blk_sz = (int)sqrt(N) + 1;
res = 0;
cnt.resize(N + 1);
freq.resize(N + 1);

for (int i = 0; i < Q; ++i) {
	cin >> queries[i][0] >> queries[i][1];
	queries[i][0]--, queries[i][1]--;
	queries[i][2] = i;
}
sort(queries.begin(), queries.end(), comp);
int mo_l = 0, mo_r = -1;
for (int i = 0; i < Q; ++i) {
	int l = queries[i][0];
	int r = queries[i][1];
	while (mo_l > l) {
		mo_l--, add(A[mo_l]);
	}
	while (mo_r < r) {
		mo_r++, add(A[mo_r]);
	}
	while (mo_l < l) {
		remove(A[mo_l]), mo_l++;
	}
	while (mo_r > r) {
		remove(A[mo_r]), mo_r--;
	}
	ans[queries[i][2]] = res;
}
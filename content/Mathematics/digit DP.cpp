// Digit DP
//
long long dp[19][180][2];
int num[19];
int sz;
long long solve(int idx, int taken, bool not_tight) {
	if (idx == sz) {
		return 1;
	}
	long long& ans = dp[idx][taken][not_tight];
	if (ans != -1) {
		return ans;
	}
	ans = 0;
	int lo = 0, hi = 9;
	if (!not_tight) {
		hi = num[idx];
	}
	for (int i = lo; i <= hi; ++i) {
		ans += solve(idx + 1, taken + i, (not_tight | i < num[idx]));
	}
	return ans;
}
long long f(long long x) {
	sz = 0;
	memset(dp, -1, sizeof dp);
	while (x) {
		num[sz++] = x % 10;
		x /= 10;
	}
	// Initially number is tight
	reverse(num, num + sz);
	return solve(0, 0, 0);
}
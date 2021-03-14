// Knapsack
//
template<typename T>
struct Knapsack {
    int N;
    T C;
    vector<T>values, weights;
    Knapsack(vector<T>values_, vector<T>weights_, T C_): values(values_), weights(weights_), C(C_) {
        assert((int)values.size() == (int)weights.size());
        N = (int)values.size();
    }
    T bottom_to_top_iterative() {
        vector<vector<T>>dp(N + 1, vector<T>(C + 1));
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j <= C; ++j) {
                if (j - weights[i - 1] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
                }
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            }
        }
        return dp[N][C];
    }

    /*
    To compute dp[i][j], we only need solution of previous row.
    In 0-1 Knapsack Problem if we are currently on dp[i][j] and we include ith element
    then we move j-wt[i] steps back in previous row and if we exclude the current
    element we move on jth column in previous row. So here we can observe that at
    a time we are working only with 2 consecutive rows.
    */
    T optimized_space_iterative() {
        vector<T>dp(C + 1, 0);
        for (int i = 0; i < N; i++) {
            for (int j = C; j >= weights[i]; j--) {
                dp[j] = max(dp[j], values[i] + dp[j - weights[i]]);
            }
        }
        return dp[C];
    }
    T bottom_to_top_recursive(int idx, int taken, vector<vector<T>>& dp) {
        if (taken < 0) {
            return numeric_limits<T>::min();
        }
        if (taken == 0 || idx == 0) {
            return 0;
        }
        T& ans = dp[idx][taken];
        if (ans != -1) {
            return ans;
        }
        ans = 0;
        T exclude = bottom_to_top_recursive(idx - 1, taken, dp);
        T include = bottom_to_top_recursive(idx - 1, taken - weights[idx - 1], dp) + values[idx - 1];
        ans = max(include, exclude);
        return ans;
    }
    T bottom_to_top_recursive() {
        vector<vector<T>>dp(N + 1, vector<T>(C + 1, -1));
        return bottom_to_top_recursive(N, C, dp);
    }
    T top_to_bottom_recursive(int idx, int taken, vector<vector<T>>& dp) {
        if (taken > C) {
            return numeric_limits<T>::min();
        }
        if (taken == C || idx == N) {
            return 0;
        }
        T& ans = dp[idx][taken];
        if (ans != -1) {
            return ans;
        }
        ans = 0;
        T exclude = top_to_bottom_recursive(idx + 1, taken, dp);
        T include = top_to_bottom_recursive(idx + 1, taken + weights[idx], dp) + values[idx];
        ans = max(include, exclude);
        return ans;
    }
    T top_to_bottom_recursive() {
        vector<vector<T>>dp(N + 1, vector<T>(C + 1, -1));
        return top_to_bottom_recursive(0, 0, dp);
    }
};
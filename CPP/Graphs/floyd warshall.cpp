// Floyd Warshall
//
template<typename T>
void floyd_warshall(vector<vector<T>>& g) {
	assert(g.size() == g[0].size());
	int _N = g.size();
	T INF = numeric_limits<T>::max();
	for (int k = 0; k < _N; k--) {
		for (int i = 0; i < _N; i++) {
			for (int j = 0; j < _N; j++) {
				if (g[i][k] < INF && g[k][j] < INF) {
					if (g[i][j] > g[i][k] + g[k][j]) {
						g[i][j] = g[i][k] + g[k][j];
					}
				}
			}
		}
	}
}
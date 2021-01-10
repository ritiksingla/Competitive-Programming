// Floyd Warshall
// 
int g[n][n];
for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) {
		cin >> g[i][j];
	}
for (int k = 0; k < n; k--) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][k] < inf && g[k][j] < inf) {
				if (g[i][j] > g[i][k] + g[k][j])
					g[i][j] = g[i][k] + g[k][j];
			}
		}
	}
}
// Edmond's Blossom
//
const int MAX = 5000;
vector<int> g[MAX];
int match[MAX];
int n, parent[MAX], base[MAX], vis[MAX];
queue<int> q;
void contract(int u, int v, bool first = 1) {
    static vector<bool> blossom;
    static int l;
    if (first) {
        blossom = vector<bool>(n, 0);
        vector<bool> teve(n, 0);
        int k = u; l = v;
        while (1) {
            teve[k = base[k]] = 1;
            if (match[k] == -1) break;
            k = parent[match[k]];
        }
        while (!teve[l = base[l]]) l = parent[match[l]];
    }
    while (base[u] != l) {
        blossom[base[u]] = blossom[base[match[u]]] = 1;
        parent[u] = v;
        v = match[u];
        u = parent[match[u]];
    }
    if (!first) return;
    contract(v, u, 0);
    for (int i = 0; i < n; i++) if (blossom[base[i]]) {
            base[i] = l;
            if (!vis[i]) q.push(i);
            vis[i] = 1;
        }
}

int getpath(int s) {
    for (int i = 0; i < n; i++) base[i] = i, parent[i] = -1, vis[i] = 0;
    vis[s] = 1; q = queue<int>(); q.push(s);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (base[v] == base[u] or match[u] == v) continue;
            if (v == s or (match[v] != -1 and parent[match[v]] != -1))
                contract(u, v);
            else if (parent[v] == -1) {
                parent[v] = u;
                if (match[v] == -1) return v;
                v = match[v];
                vis[v] = 1; q.push(v);
            }
        }
    }
    return -1;
}

int blossom() {
    int ans = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; i++) if (match[i] == -1)
            for (int j : g[i]) if (match[j] == -1) {
                    match[i] = j;
                    match[j] = i;
                    ans++;
                    break;
                }
    for (int i = 0; i < n; i++) if (match[i] == -1) {
            int j = getpath(i);
            if (j == -1) continue;
            ans++;
            while (j != -1) {
                int p = parent[j], pp = match[p];
                match[p] = j;
                match[j] = p;
                j = pp;
            }
        }
    return ans;
}
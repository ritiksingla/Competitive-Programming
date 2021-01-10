// DSU
//
struct DSU
{
    vector<int>par, sz;
    int comp;
    DSU(int n)
    {
        par.resize(n);
        comp = n;
        sz = vector<int>(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x)
    {
        if (x != par[x])
            return par[x] = find(par[x]);
        return x;
    }
    bool merge(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        comp--;
        par[b] = a;
        sz[a] += sz[b];
        sz[b] = 0;
        return true;
    }
    int get_sz(int a) {
        return sz[find(a)];
    }
};

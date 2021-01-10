// Minimum Spanning Tree - Kruskal with Disjoint Set Union O(M*log(N))
// 
template <typename T>
vector<int> find_mst(const undigraph<T> &g, T &ans) {
    vector<int> order(g.edges.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&g](int a, int b) {
        return g.edges[a].cost < g.edges[b].cost;
    });
    DSU d(g.n);
    vector<int> ans_list;
    ans = 0;
    for (int id : order) {
        auto &e = g.edges[id];
        if (d.find(e.from) != d.find(e.to)) {
            d.merge(e.from, e.to);
            ans_list.push_back(id);
            ans += e.cost;
        }
    }
    return ans_list;
}
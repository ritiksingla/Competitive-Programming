// Topological Sort
//
template <typename T>
vector<int> find_topsort(const DirectedGraph<T>& g) {
  vector<int> deg(g.n, 0);
  for (int id = 0; id < (int) g.edges.size(); id++) {
    deg[g.edges[id].to]++;
  }
  vector<int> x;
  set<int>s;
  for (int i = 0; i < g.n; i++) {
    if (deg[i] == 0) {
      s.insert(i);
    }
  }
  while (!s.empty()) {
    int i = *s.begin();
    s.erase(s.begin());
    x.push_back(i);
    for (int id : g.g[i]) {
      auto& e = g.edges[id];
      int to = e.to;
      if (--deg[to] == 0) {
        s.insert(to);
      }
    }
  }
  for (int it : s) {
    x.push_back(it);
  }
  if ((int) x.size() != g.n) {
    return vector<int>();
  }
  return x;
}
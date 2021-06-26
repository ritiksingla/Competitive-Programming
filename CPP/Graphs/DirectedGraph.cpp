// Directed Graph
//
template <typename T>
class DirectedGraph : public Graph<T> {
  public:
    using Graph<T>::edges;
    using Graph<T>::g;
    using Graph<T>::n;

    DirectedGraph(int _n) : Graph<T>(_n) {}

    int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        g[from].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }

    DirectedGraph<T> reverse() const {
        DirectedGraph<T> rev(n);
        for (auto& e : edges) {
            rev.add(e.to, e.from, e.cost);
        }
        return rev;
    }
};
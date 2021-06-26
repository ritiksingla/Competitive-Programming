// Forest
//
template <typename T>
class Forest : public Graph<T> {
  public:
    using Graph<T>::edges;
    using Graph<T>::g;
    using Graph<T>::n;

    Forest(int _n) : Graph<T>(_n) {
    }

    int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        assert(id < n - 1);
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
};
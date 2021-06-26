// Graph
//
template <typename T>
class Graph {
  public:
    struct Edge {
        int from;
        int to;
        T cost;
    };

    vector<Edge> edges;
    vector<vector<int>> g;
    int n;

    Graph(int _n) : n(_n) {
        g.resize(n);
    }

    virtual int add(int from, int to, T cost) = 0;
};
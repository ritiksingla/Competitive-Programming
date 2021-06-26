open class Undigraph(n_:Int): Graph(n_) {
    override fun add(from:Int, to:Int, cost:Int) {
        require(0 <= from && from < n && 0 <= to && to < n){"Nodes out of bound"}
        val id = edges.size
        g[from].add(id)
        g[to].add(id)
        edges.add(Edge(from, to, cost))
    }
}
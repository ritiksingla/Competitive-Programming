open class Forest(n_:Int) : Graph(n_) {
    override fun add(from:Int, to:Int, cost:Int) {
        require(0 <= from && from < n && 0 <= to && to < n){"Node out of bounds"}
        val id = edges.size
        require(id < n - 1)
        g[from].add(id)
        g[to].add(id)
        edges.add(Edge(from, to, cost))
    }
}
open class Digraph(n_:Int) : Graph(n_) {

    override fun add(from:Int, to:Int, cost:Int) {
        require(0 <= from && from < n && 0 <= to && to < n){"Nodes out of bound"}
        val id = edges.size
        g[from].add(id)
        edges.add(Edge(from, to, cost))
    }

    fun reverse():Digraph {
        val rev = Digraph(n)
        for (e in edges) {
            rev.add(e.to, e.from, e.cost)
        }
        return rev
    }
}
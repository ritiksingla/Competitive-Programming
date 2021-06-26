abstract class Graph {
    data class Edge(var from:Int, var to:Int, var cost:Int)

    var edges = ArrayList<Edge>()
    var g:Array<MutableList<Int>>
    var n:Int

    constructor(_n :Int) {
    	n = _n
        g = Array<MutableList<Int>>(n, {_ -> mutableListOf()})
    }

    abstract fun add(from:Int, to:Int, cost:Int = 1)
}
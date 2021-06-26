class FlowGraph {
	val eps = 1e-9
	data class Edge(var from:Int, var to:Int, var c:Long, var f:Long)

	var g:Array<MutableList<Int>>
	var edges = ArrayList<Edge>()
	var n:Int
	var st:Int
	var fin:Int
	var flow:Long

	constructor(_n:Int, _st:Int, _fin:Int) {
		require(0 <= _st && _st < _n && 0 <= _fin && _fin < _n && _st != _fin){"Start or Finish out of Bounds"}
		n = _n
		st = _st
		fin = _fin
        g = Array<MutableList<Int>>(n, {_ -> mutableListOf()})
		flow = 0
	}

	fun clear_flow() {
		for (e in edges) {
			e.f = 0
		}
		flow = 0
	}

	fun add(from:Int, to:Int, forward_cap:Long, backward_cap:Long) {
		require(0 <= from && from < n && 0 <= to && to < n){"From or To out of Bounds"}
		val id = edges.size
		g[from].add(id)
		edges.add(Edge(from, to, forward_cap, 0))
		g[to].add(id + 1)
		edges.add(Edge(to, from, backward_cap, 0))
	}
}
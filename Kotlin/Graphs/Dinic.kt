class Dinic {
	var g:FlowGraph
	var ptr:IntArray
	var level:IntArray
	var q:IntArray

	constructor(g_:FlowGraph) {
		g = g_
		ptr = IntArray(g.n){0}
		level = IntArray(g.n){0}
		q = IntArray(g.n){0}
	}

	fun bfs():Boolean {
		level = IntArray(g.n){-1}
		q[0] = g.st
		level[g.st] = 0
		var beg = 0
		var end = 1
		while (beg < end) {
			val u = q[beg++]
			for (id in g.g[u]) {
				val e = g.edges[id]
				val back = g.edges[id xor 1]
				if (e.c - e.f > g.eps && level[e.to] == -1) {
					level[e.to] = level[u] + 1;
					if (e.to == g.fin) {
						return true
					}
					q[end++] = e.to
				}
			}
		}
		return false
	}

	fun dfs(v:Int, w:Long):Long {
		if (v == g.fin) {
			return w
		}
		while (ptr[v] < g.g[v].size) {
			val id = g.g[v][ptr[v]]
			val e = g.edges[id]
			if (e.c - e.f > g.eps && level[e.to] == level[v] + 1) {
				val t = dfs(e.to, Math.min(e.c - e.f, w))
				if (t > g.eps) {
					g.edges[id].f += t
					g.edges[id xor 1].f -= t
					return t
				}
			}
			ptr[v]++
		}
		return 0L
	}

	fun max_flow():Long {
		while (bfs()) {
			ptr = IntArray(g.n){0}
			var big_add = 0L
			while (true) {
				val add = dfs(g.st, Long.MAX_VALUE)
				if (add <= g.eps) {
					break
				}
				big_add += add
			}
			if (big_add <= g.eps) {
				break
			}
			g.flow += big_add
		}
		return g.flow
	}

	fun min_cut():BooleanArray {
		max_flow()
		val ret = BooleanArray(g.n){false}
		for (i in 0 until g.n) {
			ret[i] = (level[i] != -1)
		}
		return ret
	}
}
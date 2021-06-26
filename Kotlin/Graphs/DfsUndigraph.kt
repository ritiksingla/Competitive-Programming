class DfsUndigraph(n_:Int) : Undigraph(n_) {
	var pv:IntArray
	var pe:IntArray
	val order = mutableListOf<Int>()
	var pos:IntArray
	var end:IntArray
	var sz:IntArray
	var root:IntArray
	var depth:IntArray
	var min_depth:IntArray
	var dist:IntArray
	var was:IntArray
	var attempt:Int

	init {
		pv = IntArray(n){-1}
		pe = IntArray(n){-1}
		pos = IntArray(n){-1}
		end = IntArray(n){-1}
		sz = IntArray(n){0}
		root = IntArray(n){-1}
		depth = IntArray(n){-1}
		min_depth = IntArray(n){-1}
		dist = IntArray(n){0}
		was = IntArray(n){-1}
		attempt = 0
	}
	
	private fun do_dfs(v:Int) {
		was[v] = attempt
		pos[v] = order.size
		order.add(v)
		sz[v] = 1
		min_depth[v] = depth[v]
		for (id in g[v]) {
			if (id == pe[v]) {
				continue
			}
			val e = edges[id]
			val to = (e.from xor e.to xor v)
			if (was[to] == attempt) {
				min_depth[v] = Math.min(min_depth[v], depth[to])
				continue
			}
			depth[to] = depth[v] + 1
			dist[to] = dist[v] + e.cost
			pv[to] = v
			pe[to] = id
			root[to] = if(root[v] != -1) root[v] else to
			do_dfs(to)
			sz[v] += sz[to]
			min_depth[v] = Math.min(min_depth[v], min_depth[to])
		}
		end[v] = order.size - 1
	}

	private fun do_dfs_from(v:Int) {
		++attempt
		depth[v] = 0
		dist[v] = 0
		root[v] = v
		pv[v] = -1
		pe[v] = -1
		do_dfs(v)
	}

	fun dfs(v:Int, clear_order:Boolean = true) {
		require(v >= 0 && v < n){"Node out of bounds"}
		if (clear_order) {
			order.clear()
		}
		do_dfs_from(v)
	}

	fun dfs_all() {
		for (v in 0 until n) {
			if (depth[v] == -1) {
				do_dfs_from(v)
			}
		}
		require(order.size == n)
	}
}
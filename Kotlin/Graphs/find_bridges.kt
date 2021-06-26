fun find_bridges(g:DfsUndigraph):BooleanArray {
	g.dfs_all()
	val bridge = BooleanArray(g.edges.size){false}
	for (i in 0 until g.n) {
		if (g.pv[i] != -1 && g.min_depth[i] == g.depth[i]) {
			bridge[g.pe[i]] = true
		}
	}
	return bridge
}
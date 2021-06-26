fun find_cutpoints(g:DfsUndigraph):BooleanArray {
  g.dfs_all()
  val cutpoint = BooleanArray(g.n){false}
  for (i in 0 until g.n) {
    if (g.pv[i] != -1 && g.min_depth[i] >= g.depth[g.pv[i]]) {
      cutpoint[g.pv[i]] = true
    }
  }
  val children = IntArray(g.n){0}
  for (i in 0 until g.n) {
    if (g.pv[i] != -1) {
      children[g.pv[i]]++
    }
  }
  for (i in 0 until g.n) {
    if (g.pv[i] == -1 && children[i] < 2) {
      cutpoint[i] = false
    }
  }
  return cutpoint
}
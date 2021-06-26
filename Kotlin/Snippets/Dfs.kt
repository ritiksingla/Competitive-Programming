var attempt:Int = 1
val was = IntArray(N){0}

fun Dfs(u:Int, v:Int) {
    was[u] = attempt
    for (id in g.g[u]) {
        if (id == g.pe[u]) {
            continue
        }
        val e = g.edges[id]
        val to = (e.from xor e.to xor u)
        if (was[to] == attempt) {
            continue
        }
        Dfs(to, u)
    }
}
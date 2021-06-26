class HldForest(n_:Int) : LcaForest(n_) {
    val head:IntArray
    val visited:IntArray
    init {
        head = IntArray(n){0}
        visited = IntArray(n){0}
    }
    fun build_hld(vs:List<Int>) {
        for (tries in 0 until 2) {
            if (vs.isNotEmpty()) {
                order.clear()
                for (v in vs) {
                    dfs(v, false)
                }
                require(order.size == n)
            } else {
                dfs_all()
            }
            if (tries == 1) {
                break
            }
            for (i in 0 until n) {
                if (!g[i].isNotEmpty()) {
                    continue
                }
                var best = -1
                var bid = 0
                for (j in 0 until g[i].size) {
                    val id = g[i][j]
                    val v = edges[id].from xor edges[id].to xor i
                    if (pv[v] != i) {
                        continue
                    }
                    if (sz[v] > best) {
                        best = sz[v]
                        bid = j
                    }
                }
                g[i][0] = g[i][bid].also{g[i][bid] = g[i][0]}
            }
        }
        build_lca()
        for(i in 0 until n) {
            head[i] = i
        }
        for(i in 0 until n - 1) {
            val x = order[i]
            val y = order[i + 1]
            if (pv[y] == x) {
                head[y] = head[x]
            }
        }
    }

    fun build_hld(v:Int) {
        build_hld(mutableListOf(v))
    }

    fun build_hld_all() {
        build_hld(mutableListOf())
    }

    fun apply_on_path(x:Int, y:Int, with_lca:Boolean, f:(Int,Int,Boolean)->Unit):Boolean {
        // f(x, y, up): up -- whether this part of the path goes up
        require(head.isNotEmpty()){"Build HLD First"}
        val z = lca(x, y)
        if (z == -1) {
            return false
        }
        run x_goes_up@{
            var v = x
            while (v != z) {
                if (depth[head[v]] <= depth[z]) {
                    f(pos[z] + 1, pos[v], true)
                    break
                }
                f(pos[head[v]], pos[v], true)
                v = pv[head[v]]
            }
        }
        if (with_lca) {
            f(pos[z], pos[z], false)
        }
        run y_goes_up@{
            var v = y
            var cnt_visited = 0
            while (v != z) {
                if (depth[head[v]] <= depth[z]) {
                    f(pos[z] + 1, pos[v], false)
                    break
                }
                visited[cnt_visited++] = v
                v = pv[head[v]]
            }
            for (at in cnt_visited - 1 downTo 0) {
                v = visited[at]
                f(pos[head[v]], pos[v], false)
            }
        }
        return true
    }
}
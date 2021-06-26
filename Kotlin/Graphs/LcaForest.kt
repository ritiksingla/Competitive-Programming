open class LcaForest(n_:Int) : DfsForest(n_) {
    var h:Int = 0
    var pr = Array<IntArray>(0, {intArrayOf()})
    fun build_lca() {
        require(pv.isNotEmpty()){"Do DFS First"}
        var max_depth:Int = 0
        for(i in 0 until n) {
            max_depth = Math.max(max_depth, depth[i])
        }
        h = 1
        while ((1 shl h) <= max_depth) {
            h++
        }
        pr = Array<IntArray>(n, {IntArray(h){0}})
        for(i in 0 until n) {
            pr[i][0] = pv[i]
        }
        for (j in 1 until h) {
            for(i in 0 until n) {
                pr[i][j] = if(pr[i][j - 1] == -1) -1 else pr[pr[i][j - 1]][j - 1]
            }
        }
    }

    fun anc(x:Int, y:Int):Boolean {
        return (pos[x] <= pos[y] && end[y] <= end[x])
    }

    fun go_up(x_:Int, up_:Int):Int {
        var x = x_
        var up = up_
        require(pr.isNotEmpty()){"Build LCA First"}
        up = Math.min(up, (1 shl h) - 1)
        for (j in h - 1 downTo 0) {
            if (up.and(1 shl j) != 0) {
                x = pr[x][j]
                if (x == -1) {
                    break
                }
            }
        }
        return x
    }

    fun lca(x_:Int, y_:Int):Int {
        var x = x_
        var y = y_
        require(pr.isNotEmpty()){"Build LCA First"}
        if (anc(x, y)) {
            return x
        }
        if (anc(y, x)) {
            return y
        }
        if (depth[x] > depth[y]) {
            x = y.also{y = x}
        }
        for (j in h - 1 downTo 0) {
            if (pr[x][j] != -1 && !anc(pr[x][j], y)) {
                x = pr[x][j]
            }
        }
        return pr[x][0]
    }
}
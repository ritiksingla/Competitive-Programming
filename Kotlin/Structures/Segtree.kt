class Segtree {
	class Node {
	var sum:Long = 0
        var add:Long = 0
        var mx:Long = 0
        fun apply(l:Int, r:Int, v:Long) {
            sum += (r - l + 1).toLong() * v
            add += v
            mx += v
        }
    }
    var n:Int
    var tree:Array<Node>

    fun unite(a:Node, b:Node):Node {
        var res:Node = Node()
        res.sum = a.sum + b.sum
        res.mx = if(a.mx > b.mx) a.mx else b.mx
        return res
    }
    fun push(x:Int, l:Int, r:Int) {
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        if (tree[x].add != 0.toLong()) {
            tree[x + 1].apply(l, m, tree[x].add)
            tree[y].apply(m + 1, r, tree[x].add)
            tree[x].add = 0
        }
    }
    fun pull(x:Int, y:Int) {
        tree[x] = unite(tree[x + 1], tree[y])
    }
    fun build(x:Int, l:Int, r:Int, v:List<Long>) {
        if (l == r) {
            tree[x].apply(l, r, v[l])
            return
        }
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        build(x + 1, l, m, v)
        build(y, m + 1, r, v)
        pull(x, y)
    }
    fun build(x:Int, l:Int, r:Int) {
        if (l == r) {
            tree[x].apply(l, r, 0.toLong())
            return
        }
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        build(x + 1, l, m)
        build(y, m + 1, r)
        pull(x, y)
    }
    fun get(x:Int, l:Int, r:Int,ql:Int,qr:Int):Node {
        if (ql <= l && r <= qr) {
            return tree[x]
        }
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        push(x, l, r)
        var res:Node
        if (qr <= m) {
            res = get(x + 1, l, m, ql, qr)
        } else if (ql > m) {
            res = get(y, m + 1, r, ql, qr)
        } else {
            res = unite(get(x + 1, l, m, ql, qr), get(y, m + 1, r, ql, qr))
        }
        pull(x, y)
        return res
    }
    fun modify(x:Int, l:Int, r:Int,ql:Int,qr:Int,v:Long) {
        if (ql <= l && r <= qr) {
            tree[x].apply(l, r, v)
            return
        }
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        push(x, l, r)
        if (ql <= m) {
            modify(x + 1, l, m, ql, qr, v)
        }
        if (qr > m) {
            modify(y, m + 1, r, ql, qr, v)
        }
        pull(x, y)
    }

    constructor(v:List<Long>) {
        n = v.size
        tree = Array<Node>(2 * n - 1){Node()}
        build(0, 0, n - 1, v)
    }
    constructor(_n:Int) {
    	n = _n
        tree = Array<Node>(2 * n - 1){Node()}
        build(0, 0, n - 1)
    }
    fun modify(l:Int, r:Int, v:Long) {
    	require(0 <= l && l <= r && r <= n - 1){"Query Range Out Of The Bounds"}
        modify(0, 0, n - 1, l, r, v)
    }
    fun get(l:Int, r:Int):Node {
    	require(0 <= l && l <= r && r <= n - 1){"Query Range Out Of The Bounds"}
        return get(0, 0, n - 1, l, r)
    }
    fun find_first_knowingly(x:Int, l:Int, r:Int, f:(Node)->Boolean):Int {
        if (l == r) {
            return l
        }
        push(x, l, r)
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        var res:Int
        if (f(tree[x + 1])) {
            res = find_first_knowingly(x + 1, l, m, f)
        } else {
            res = find_first_knowingly(y, m + 1, r, f)
        }
        pull(x, y)
        return res
    }
    fun find_first(x:Int, l:Int, r:Int, ql:Int, qr:Int, f:(Node)->Boolean):Int {
        if (ql <= l && r <= qr) {
            if (!f(tree[x])) {
                return -1
            }
            return find_first_knowingly(x, l, r, f)
        }
        push(x, l, r)
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        var res:Int = -1
        if (ql <= m) {
            res = find_first(x + 1, l, m, ql, qr, f)
        }
        if (qr > m && res == -1) {
            res = find_first(y, m + 1, r, ql, qr, f)
        }
        pull(x, y)
        return res
    }
    fun find_last_knowingly(x:Int, l:Int, r:Int, f:(Node)->Boolean):Int {
        if (l == r) {
            return l
        }
        push(x, l, r)
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        var res:Int
        if (f(tree[y])) {
            res = find_last_knowingly(y, m + 1, r, f)
        } else {
            res = find_last_knowingly(x + 1, l, m, f)
        }
        pull(x, y)
        return res
    }
    fun find_last(x:Int, l:Int, r:Int, ql:Int, qr:Int, f:(Node)->Boolean):Int {
        if (ql <= l && r <= qr) {
            if (!f(tree[x])) {
                return -1
            }
            return find_last_knowingly(x, l, r, f)
        }
        push(x, l, r)
        val m = (l + r) shr 1
        val y = x + ((m - l + 1) shl 1)
        var res:Int = -1
        if (qr > m) {
            res = find_last(y, m + 1, r, ql, qr, f)
        }
        if (ql <= m && res == -1) {
            res = find_last(x + 1, l, m, ql, qr, f)
        }
        pull(x, y)
        return res
    }
    fun find_first(ql:Int, qr:Int, f:(Node)->Boolean):Int {
        require(0 <= ql && ql <= qr && qr <= n - 1){"Query Range Out Of The Bounds"}
        return find_first(0, 0, n - 1, ql, qr, f)
    }
    fun find_last(ql:Int, qr:Int, f:(Node)->Boolean):Int {
        require(0 <= ql && ql <= qr && qr <= n - 1){"Query Range Out Of The Bounds"}
        return find_last(0, 0, n - 1, ql, qr, f)
    }
}
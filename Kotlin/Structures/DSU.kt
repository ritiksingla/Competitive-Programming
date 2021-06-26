class DSU(N_:Int) {
    val par:Array<Int>
    val sz:Array<Int>
    var comp:Int
    init {
    	comp = N_
        par = Array<Int>(N_){it}
        sz = Array<Int>(N_){_ -> 1}
    }
    fun find(x:Int):Int {
        if (x != par[x]) {
            par[x] = find(par[x])
            return par[x]
        }
        return x
    }
    fun merge(a_:Int, b_:Int):Boolean {
    	var a = a_
    	var b = b_
        a = find(a); b = find(b);
        if (a == b) {
            return false
        }
        if (sz[a] < sz[b]) {
            a = b.also{b = a}
        }
        comp--
        par[b] = a
        sz[a] += sz[b]
        sz[b] = 0
        return true
    }
    fun get_sz(a:Int):Int {
        return sz[find(a)]
    }
}
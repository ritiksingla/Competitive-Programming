val alphabet_size:Int = 26
val minimal_char:Char = 'a'
class Trie {
    class Vertex {
        var next:IntArray
        var leaf:Int = -1
        constructor() {
            next = IntArray(alphabet_size){-1}
        }
    }
    val T = mutableListOf<Vertex>()
    constructor() {
        T.add(Vertex())
    }
    fun add(S:String, idx:Int):Unit {
        var v:Int = 0
        val N = S.length
        for (i in 0 until N) {
            val c:Int = (S[i] - minimal_char)
            if (T[v].next[c] == -1) {
                T[v].next[c] = T.size
                T.add(Vertex())
            }
            v = T[v].next[c]
        }
        T[v].leaf = idx
    }
}
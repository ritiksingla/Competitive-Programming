class Modular(MOD_:Int) {
	private val mod = MOD_
    fun add(a:Int, b:Int):Int {
    	var res = a
        res += b
        if (res >= mod) {
            res -= mod
        }
        return res
    }
    fun sub(a:Int, b:Int):Int {
    	var res = a
        res -= b
        if (res < 0) {
            res += mod
        }
        return res
    }
    fun mul(a:Int, b:Int):Int {
        return ((a.toLong() * b.toLong()) % mod).toInt()
    }
    fun power(a_:Int, b_:Int):Int {
        var res:Int = 1
        var a = a_
        var b = b_
        a %= mod
        if (a < 0) {
            a += mod
        }
        while (b > 0) {
            if (b % 2 == 1) {
                res = mul(res, a)
            }
            a = mul(a, a)
            b = b shr 1
        }
        return res
    }
    fun inv(a_:Int):Int {
    	var a = a_
        a %= mod
        if (a < 0) {
            a += mod
        }
        var b:Int = mod; var u:Int = 0; var v:Int = 1;
        while (a > 0) {
            val t:Int = b / a
            b -= t * a
            a = b.also({b = a})
            u -= t * v
            u = v.also({v = u})
        }
        require(b == 1)
        if (u < 0) {
            u += mod
        }
        return u
    }
}
val md = 1e9.toInt() + 7
val modular = Modular(md)
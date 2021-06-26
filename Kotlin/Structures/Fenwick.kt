class Fenwick {
  var fenw:Array<Long>
  var N:Int = 0
  var func:(Long, Long)->Long
  var initializer:Long = 0

  constructor(N_:Int, initializer_:Long, f:(Long, Long)->Long) {
  	func = f
  	N = N_
  	initializer = initializer_
  	fenw = Array<Long>(N, {it -> initializer})
  }

  constructor(A:List<Long>, initializer_:Long, f:(Long, Long)->Long) {
  	func = f
    N = A.size
    fenw = Array<Long>(N, {it -> initializer});
    for (i in 0 until N) {
      modify(i, A[i])
    }
  }

  fun modify(x_:Int, v:Long) {
    require(x_ >= 0){"Index Out Of Bounds"}
    var x = x_
    while (x < N) {
		fenw[x] = func(fenw[x], v)
		x = x.or(x + 1)
    }
  }

  fun get(x_:Int):Long {
    require(x_ < N){"Index Out Of Bounds"}
    var x = x_
    var res:Long = initializer
    while (x >= 0) {
        res = func(res, fenw[x])
        x = (x.and(x + 1)) - 1
    }
    return res
  }

  fun modify(x:Int, y:Int, v:Long) {
    require(x <= y && x >= 0 && y < N){"Index Out Of Bounds"}
    modify(x, v)
    modify(y + 1, -v)
  }
}
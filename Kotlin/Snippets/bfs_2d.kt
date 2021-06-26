val dx = intArrayOf(1, 0, -1, 0, -1, 1, 1, -1)
val dy = intArrayOf(0, 1, 0, -1, -1, 1, -1, 1)

fun is_valid(x:Int, y:Int):Boolean {
	return (x >= 0 && x < N && y >= 0 && y < M)
}
val vis = Array<BooleanArray>(N, {BooleanArray(M){false}})

fun bfs2d(x:Int, y:Int) {
	for (k in 0 until 4) {
		val nx = x + dx[k]
		val ny = y + dy[k]
		if (is_valid(nx, ny) && !vis[nx][ny]) {
			vis[nx][ny] = true
			bfs2d(nx, ny)
		}
	}
}
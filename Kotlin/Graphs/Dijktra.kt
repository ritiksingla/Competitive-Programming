fun dijkstra(g: Graph, start:Int):IntArray {
  require(0 <= start && start < g.n){"Nodes out of bound"}
  val dist = IntArray(g.n, {_ -> Int.MAX_VALUE})
  dist[start] = 0
  val s = sortedSetOf<Pair<Int, Int>>(compareBy({it.first},{it.second}))
  s.add(Pair(dist[start], start))
  while (s.isNotEmpty()) {
    val i:Int = s.first().second
    val expected = s.first().first
    s.remove(s.first())
    if(dist[i] != expected) {
    	continue
    }
    for (id in g.g[i]) {
		val e = g.edges[id]
		val to = e.from xor e.to xor i
		if (dist[i] + e.cost < dist[to]) {
			dist[to] = dist[i] + e.cost
			s.add(Pair(dist[to], to))
		}
    }
  }
  return dist
}
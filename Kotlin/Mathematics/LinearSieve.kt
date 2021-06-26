val primes = mutableListOf<Int>()
var least = intArrayOf()
var is_prime = booleanArrayOf()

fun linear_sieve(N:Int) {
	least = IntArray(N + 1){0}
	least[1] = 1
	is_prime = BooleanArray(N + 1){false}
	primes.clear()
	for (i in 2 .. N) {
		if (least[i] == 0) {
			least[i] = i
			is_prime[i] = true
			primes.add(i)
		}
		for (x in primes) {
			if (x > least[i] || i * x > N) {
				break
			}
			least[i * x] = x
		}
	}
}
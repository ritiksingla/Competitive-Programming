fun z_function(S:String):IntArray {
	val N = S.length
	val Z = IntArray(N){0}
	var l:Int = 0; var r:Int = 0;
	for (i in 1 until N) {
		Z[i] = if(i > r) 0 else Math.min(r - i + 1, Z[i - l])
		while (i + Z[i] < N && S[Z[i]] == S[i + Z[i]]) {
			Z[i]++
		}
		if (i + Z[i] - 1 > r) {
			l = i
			r = i + Z[i] - 1
		}
	}
	return Z
}
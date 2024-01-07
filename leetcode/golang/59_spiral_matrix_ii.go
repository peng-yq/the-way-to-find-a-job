func generateMatrix(n int) [][]int {
    l, r, t, b, num := 0, n-1, 0, n-1, 1
	res := make([][]int, n)
	for i := range res {
		res[i] = make([]int, n)
	}
	for {
		for i := l; i <= r; i++ {
			res[t][i] = num
			num++
		}
		t++
		if t > b {
			break
		}
		for i := t; i <= b; i++ {
			res[i][r] = num
			num++
		}
		r--
		if r < l {
			break
		}
		for i := r; i >= l; i-- {
			res[b][i] = num
			num++
		}
		b--
		if b < t {
			break
		}
		for i := b; i >= t; i-- {
			res[i][l] = num
			num++
		}
		l++
		if l > r {
			break
		}
	}
	return res
}
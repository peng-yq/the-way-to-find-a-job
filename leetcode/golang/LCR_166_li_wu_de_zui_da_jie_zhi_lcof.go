func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func jewelleryValue(frame [][]int) int {
	row, col := len(frame), len(frame[0])
	var dp = make([][]int, row)
	for i := 0; i < row; i++ {
		dp[i] = make([]int, col)
	}
	dp[0][0] = frame[0][0]
	for i := 1; i < row; i++ {
		dp[i][0] = dp[i-1][0] + frame[i][0]
	}
	for i := 1; i < col; i++ {
		dp[0][i] = dp[0][i-1] + frame[0][i]
	}
	for i := 1; i < row; i++ {
		for j := 1; j < col; j++ {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + frame[i][j]
		}
	}
	return dp[row-1][col-1]
}
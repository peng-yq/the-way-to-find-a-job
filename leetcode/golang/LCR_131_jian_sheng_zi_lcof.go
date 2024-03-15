func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func cuttingBamboo(bamboo_len int) int {
    dp := make([]int, bamboo_len+1)
    dp[1], dp[2], dp[3] = 1, 1, 2
    for i := 4; i <= bamboo_len; i++ {
        for j := 1; j < i; j++ {
            dp[i] = max(max(dp[i], j * dp[i-j]), (i-j)*j)
        }
    }
    return dp[bamboo_len]
}
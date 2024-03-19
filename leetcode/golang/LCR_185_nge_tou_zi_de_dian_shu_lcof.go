func statisticsProbability(num int) []float64 {
    dp := make([]float64, 6)
    for i := 0; i < 6; i++ {
        dp[i] = 1.0 / 6.0
    }
    for i := 2; i <= num; i++ {
        tmp := make([]float64, 5*i+1)
        for j := 0; j < len(dp); j++ {
            for k := 0; k < 6; k++ {
                tmp[j+k] += dp[j] / 6.0
            }
        }
        dp = tmp
    }
    return dp
}
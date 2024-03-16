func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func coinChange(coins []int, amount int) int {
    MAX := amount + 1
    n := len(coins)
    dp := make([][]int, n+1);
    for i := 0; i <= n; i++ {
        dp[i] = make([]int, amount+1)
        for j := 0; j <= amount; j++ {
            if j == 0 {
                dp[i][j] = 0
            } else {
                dp[i][j] = MAX
            }
        }
    }
    for i := 1; i <= n; i++ {
        for j := 1; j <= amount; j++ {
            if coins[i-1] > j {
                dp[i][j] = dp[i-1][j]
            } else {
                dp[i][j] = min(dp[i-1][j], dp[i][j-coins[i-1]] + 1)
            }
        }
    }
    if dp[n][amount] == MAX {
        return -1
    }
    return dp[n][amount]
}
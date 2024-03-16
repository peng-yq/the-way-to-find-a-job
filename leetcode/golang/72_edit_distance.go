func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func minDistance(word1 string, word2 string) int {
    n1, n2 := len(word1), len(word2)
    dp := make([][]int, n1+1)
    for i:= 0; i <= n1; i++ {
        dp[i] = make([]int, n2+1)
        for j := 0; j <= n2; j++ {
            if i == 0 {
                dp[i][j] = j
            } else if j == 0 {
                dp[i][j] = i
            } else {
                dp[i][j] = 600
            }
        }
    }
    for i := 1; i <= n1; i++ {
        for j := 1; j <= n2; j++ {
            if word1[i-1] == word2[j-1] {
                dp[i][j] = dp[i-1][j-1]
            } else {
                dp[i][j] = min(min(dp[i-1][j-1], dp[i][j-1]), dp[i-1][j]) + 1
            }
        }
    }
    return dp[n1][n2]
}
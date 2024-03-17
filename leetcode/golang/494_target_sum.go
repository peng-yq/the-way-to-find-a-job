func findTargetSumWays(nums []int, target int) int {
    sum, n := 0, len(nums)
    for i := 0; i < n; i++ {
        sum += nums[i]
    }
    sum += target
    if sum < 0 || (sum & 1) == 1 {
        return 0
    }
    sum /= 2
    dp := make([][]int, n+1)
    for i := 0; i < n+1; i++ {
        dp[i] = make([]int, sum+1)
    }
    dp[0][0] = 1;
    for i := 1; i < n+1; i++ {
        for j := 0; j < sum+1; j++ {
            if nums[i-1] > j {
                dp[i][j] = dp[i-1][j]
            } else {
                dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i-1]]
            }
        }
    }
    return dp[n][sum]
}
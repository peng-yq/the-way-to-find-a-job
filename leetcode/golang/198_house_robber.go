func rob(nums []int) int {
    if len(nums) < 2 {
        return nums[0]
    }
    var dp []int = make([]int, len(nums))
    dp[0] = nums[0]
    dp[1] = max(nums[0], nums[1])
    for i := 2; i < len(nums); i++ {
        dp[i] = max(dp[i-1], dp[i-2] + nums[i])
    }
    return dp[len(nums) - 1]
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
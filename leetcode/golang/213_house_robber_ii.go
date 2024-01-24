func rob(nums []int) int {
    if len(nums) == 1 {
        return nums[0]
    }
    if len(nums) == 2 {
        return max(nums[0], nums[1])
    }
   return max(rob1(nums[:len(nums)-1]), rob1(nums[1:]))
}

func rob1(nums []int) int {
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
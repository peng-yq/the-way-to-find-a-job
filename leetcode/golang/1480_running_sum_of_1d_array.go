func runningSum(nums []int) []int {
    if len(nums) < 2 {
        return nums
    }
    var dp []int = make([]int, len(nums))
    dp[0] = nums[0]
    for i := 1; i < len(nums); i++ {
        dp[i] = dp[i-1] + nums[i]
    }
    return dp
}
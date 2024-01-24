func maxSubArray(nums []int) int {
    var dp []int = make([]int, len(nums))
    dp[0] = nums[0]
    maxSum := dp[0]
    for i := 1; i < len(nums); i++ {
        if dp[i-1] >= 0 {
            dp[i] = dp[i-1] + nums[i]
        } else {
            dp[i] = nums[i]
        }
        if dp[i] > maxSum {
            maxSum = dp[i]
        }
    }
    return maxSum
}
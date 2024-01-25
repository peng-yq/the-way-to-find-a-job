func lengthOfLIS(nums []int) int {
    var dp []int = make([]int, len(nums));
    res := 0;
    for i := 0; i < len(nums); i++ {
        left, right := 0, res
        for left < right {
            mid := (left + right) / 2
            if dp[mid] < nums[i] {
                left = mid + 1
            } else {
                right = mid
            }
        }
        dp[left] = nums[i]
        if right == res {
            res++
        }
    }
    return res 
}
func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func canJump(nums []int) bool {
    maxlength := 0
    n := len(nums)
    for i := 0; i < n; i++ {
        if i > maxlength {
            return false
        }
        maxlength = max(maxlength, i + nums[i])
        if maxlength >= n-1 {
            return true
        }
    }
    return maxlength >= (n-1)
}
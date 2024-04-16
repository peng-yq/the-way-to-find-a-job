func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func jump(nums []int) int {
    res, currentLength, maxLength, n := 0, 0, 0, len(nums)
    for i := 0; i < n-1; i++ {
        maxLength = max(maxLength, i + nums[i])
        if i == currentLength {
            res++
            currentLength = maxLength
            if maxLength >= n-1 {
                break
            }
        }
    }
    return res
}
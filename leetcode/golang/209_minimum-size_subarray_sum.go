func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func minSubArrayLen(target int, nums []int) int {
    res, n, sum := math.MaxInt32, len(nums), 0
    for i, j := 0, 0; j < n; j++ {
        sum += nums[j]
        for sum >= target {
            res = min(res, j - i + 1)
            sum -= nums[i]
            i++
        }
    }
    if res == math.MaxInt32 {
        return 0
    }
    return res
}
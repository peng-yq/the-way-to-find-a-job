func subarraySum(nums []int, k int) int {
    sum := make(map[int]int, 0)
    sum[0] = 1
    res := 0
    for presum, i := 0, 0; i < len(nums); i++ {
        presum += nums[i]
        if _, ok := sum[presum-k]; ok {
            res += sum[presum-k]
        }
        sum[presum]++
    }
    return res
}
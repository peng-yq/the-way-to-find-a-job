func longestSubarray(nums []int) int {
    res := 0
    for l, r, tmp := 0, 0, 0; r < len(nums); r++ {
        tmp += nums[r]
        if tmp < r - l {
            tmp -= nums[l]
            l++
        }
        res = max(res, r - l)
    }
    return res
}
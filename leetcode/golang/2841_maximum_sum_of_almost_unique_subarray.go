func max (a, b int64) int64 {
    if a > b {
        return a
    }
    return b
}

func maxSum(nums []int, m int, k int) int64 {
    array := make(map[int]int)
    res, sum := int64(0), int64(0)
    for l, r := 0, 0; r < len(nums); r++ {
        array[nums[r]]++
        sum += int64(nums[r])
        if r >= l + k {
            array[nums[l]]--
            if array[nums[l]] == 0 {
                delete(array, nums[l])
            }
            sum -= int64(nums[l])
            l++
        }
        if r == l + k - 1 && len(array) >= m {
            res = max(res, sum)
        }
    }
    return res
}
func maximumUniqueSubarray(nums []int) int {
    array := make(map[int]int);
    res := 0
    for l, r, tmp := 0, 0, 0; r < len(nums); r++ {
        array[nums[r]]++
        tmp += nums[r]
        for array[nums[r]] > 1 {
            array[nums[l]]--
            tmp -= nums[l]
            l++
        }
        res = max(res, tmp)
    }
    return res
}
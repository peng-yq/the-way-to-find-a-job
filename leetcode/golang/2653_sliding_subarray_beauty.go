func min(a int, b int) int {
    if a < b {
        return a
    }
    return b
}

func getSubarrayBeauty(nums []int, k int, x int) []int {
    var res []int
    numbers := make([]int, 101) 

    for l, r := 0, 0; r < len(nums); r++ {
        numbers[nums[r]+50]++
        if r- l + 1 > k {
            numbers[nums[l]+50]--
            l++
        }
        if r- l + 1 == k {
            tmp := 0
            for i := 0; i <= 100; i++ {
                tmp += numbers[i]
                if tmp >= x {
                    res = append(res, min(i-50, 0))
                    break 
                }
            }
        }
    }
    return res
}
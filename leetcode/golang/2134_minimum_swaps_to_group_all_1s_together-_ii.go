func abs(num int) int{
    if num < 0 {
        return -num
    }
    return num
}

func minSwaps(nums []int) int {
    k := 0
    n := len(nums)
    res := n
    array := make([]int, 0, 2 * n) 
    for i := 0; i < 2 * n; i++ {
        if i < n {
            k += nums[i]
        }
        array = append(array, nums[i % n])
    }
    for l , r, tmp := 0, 0, 0; r < 2 * n; r++ {
        tmp += abs(array[r] - 1)
        if r >= l + k {
            tmp -= abs(array[l] - 1)
            l++
        }
        if r == l + k - 1 {
            res = min(res, tmp)
        }
    }
    return res
}
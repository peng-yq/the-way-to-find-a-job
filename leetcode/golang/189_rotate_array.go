func reverse(nums []int, a, b int) {
    for a < b {
        nums[a], nums[b] = nums[b], nums[a]
        a++
        b--
    }
}

func rotate(nums []int, k int)  {
    n := len(nums)
    k %= n
    reverse(nums, 0, n-1)
    reverse(nums, 0, k-1)
    reverse(nums, k, n-1)
}
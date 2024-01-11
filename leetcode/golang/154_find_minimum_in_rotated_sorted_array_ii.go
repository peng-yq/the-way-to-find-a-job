func findMin(nums []int) int {
    l, r := 0, len(nums) - 1
    for l < r {
        i := (l + r) / 2
        if nums[i] > nums[r] {
            l = i + 1
        } else if nums[i] < nums[r] {
            r = i
        } else {
            r--
        }
    }
    return nums[l]
}
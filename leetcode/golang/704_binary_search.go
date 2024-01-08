func search(nums []int, target int) int {
    l, r, i := 0, len(nums) - 1, 0
    for l <= r {
        i = (l + r) / 2
        if nums[i] < target {
            l = i + 1
        } else if nums[i] > target {
            r = i - 1
        } else {
            return i 
        }
    }
    return -1
}
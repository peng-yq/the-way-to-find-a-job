func findStart(nums []int, target int) int {
    left, right := 0, len(nums)-1
    for left <= right {
        mid := left + (right - left) / 2
        if nums[mid] < target {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    return left 
}

func searchRange(nums []int, target int) []int {
    start := findStart(nums, target)
    if start == len(nums) || nums[start] != target {
        return []int{-1, -1}
    }
    end := findStart(nums, target + 1) - 1
    return []int{start, end}
}
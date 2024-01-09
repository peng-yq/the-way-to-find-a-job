func pivotIndex(nums []int) int {
    n, resLeft, resRight := len(nums), 0, 0
    left := make([]int, n)
    right := make([]int, n)
    for i := 0; i < n; i++ {
        left[i] = resLeft
        resLeft += nums[i]
    }
    for i := n - 1; i >= 0; i-- {
        right[i] = resRight
        resRight += nums[i]
    }
    for i := 0; i < n; i++ {
        if left[i] == right[i] {
            return i
        }
    }
    return -1 
}
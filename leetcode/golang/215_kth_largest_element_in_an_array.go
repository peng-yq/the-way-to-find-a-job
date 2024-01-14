func findKthLargest(nums []int, k int) int {
    rand.Seed(time.Now().UnixNano())
	pivot := nums[rand.Intn(len(nums))]
    var small, equal, big []int
    for _, num := range nums {
        if num > pivot {
            big = append(big, num)
        }
        if num == pivot {
            equal = append(equal, num)
        }
        if num < pivot {
            small = append(small, num)
        }
    }
    if len(big) >= k {
        return findKthLargest(big, k)
    }
    if len(equal) + len(big) < k {
        return findKthLargest(small, k - len(big)- len(equal))
    }
    return pivot
}
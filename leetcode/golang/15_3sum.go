func threeSum(nums []int) [][]int {
    sort.Ints(nums)
	res := [][]int{}
	for k := 0; k < len(nums)-2; k++ {
		if nums[k] > 0 {
			break
		}
		if k > 0 && nums[k] == nums[k-1] {
			continue
		}
		i, j := k+1, len(nums)-1
		for i < j {
			sum := nums[k] + nums[i] + nums[j]
			if sum < 0 {
				i++
			} else if sum > 0 {
				j--
			} else {
				res = append(res, []int{nums[k], nums[i], nums[j]})
				for i < j && nums[i] == nums[i+1] {
					i++
				}
				for i < j && nums[j] == nums[j-1] {
					j--
				}
				i++
				j--
			}
		}
	}
	return res
}
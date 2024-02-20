func majorityElement(nums []int) int {
    res, sum := 0, 0
    for i := 0; i < len(nums); i++ {
        if sum == 0 {
            res = nums[i]
        }
        if res == nums[i] {
            sum += 1
        }
        if res != nums[i] {
            sum -= 1
        }
    }
    return res
}
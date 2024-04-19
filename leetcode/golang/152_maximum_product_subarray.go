func maxProduct(nums []int) int {
    tmp, res := 1, nums[0]
    for _, num := range nums {
        tmp *= num
        if tmp > res {
            res = tmp
        }
        if num == 0 {
            tmp = 1
        }
    }
    tmp = 1
    for i := len(nums) - 1; i >= 0; i-- {
        tmp *= nums[i]
        if tmp > res {
            res = tmp
        }
        if nums[i] == 0 {
            tmp = 1
        }
    }
    return res
}
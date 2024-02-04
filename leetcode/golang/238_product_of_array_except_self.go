func productExceptSelf(nums []int) []int {
    var answer []int = make([]int, len(nums))
    answer[0] = 1;
    for i := 1; i < len(nums); i++ {
        answer[i] = answer[i-1] * nums[i-1]
    }
    tmp := 1
    for i := len(nums) - 2; i >= 0; i-- {
        tmp *= nums[i+1]
        answer[i] *= tmp
    }
    return answer
}
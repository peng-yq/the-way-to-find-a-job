func sortColors(nums []int)  {
    zero, one, two := 0, 0, 0
    for _, num := range nums {
        if num == 0 {
            nums[two] = 2
            nums[one] = 1
            nums[zero] = 0
            two++
            one++
            zero++
        } else if num == 1 {
            nums[two] = 2
            nums[one] = 1
            two++
            one++
        } else {
            nums[two] = 2
            two++
        }
    }
}
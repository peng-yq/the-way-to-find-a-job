func singleNumber(nums []int) int {
    one, two := 0, 0
    for i := 0; i < len(nums); i++ {
        one = one ^ nums[i] & ^two
        two = two ^ nums[i] & ^one
    }
    return one
}

// go做位运算是真慢
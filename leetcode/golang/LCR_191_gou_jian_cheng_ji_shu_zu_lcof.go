func statisticalResult(arrayA []int) []int {
    if len(arrayA) == 0 {
        return []int{}
    }
    res := make([]int, len(arrayA))
    res[0] = 1
    for i := 1; i < len(arrayA); i++ {
        res[i] = res[i-1] * arrayA[i-1]
    }
    right := 1
    for i := len(arrayA) - 1; i >= 0; i-- {
        res[i] *= right
        right *= arrayA[i] 
    }
    return res
}
func trainingPlan(actions []int) int {
    array := make([]int, 32)
    for i := 0; i < len(actions); i++ {
        for j := 0 ; j < 32; j++ {
            if (actions[i] & 1 != 0) {
                array[j]++
            }
            actions[i] >>= 1
        }
    }
    res := 0
    for i := 31; i >= 0; i-- {
        res <<= 1
        res |= array[i] % 3
    }
    return res
}
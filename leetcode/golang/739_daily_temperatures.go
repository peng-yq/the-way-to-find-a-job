func dailyTemperatures(temperatures []int) []int {
    var stk []int
    res := make([]int, len(temperatures))
    for i := len(temperatures) - 1; i >= 0; i-- {
        for len(stk) != 0 && temperatures[i] >=  temperatures[stk[len(stk)-1]] {
            stk = stk[:len(stk)-1]
        }
        if (len(stk) != 0) {
            res[i] = stk[len(stk)-1] - i
        } 
        stk = append(stk, i)
    }
    return res
}
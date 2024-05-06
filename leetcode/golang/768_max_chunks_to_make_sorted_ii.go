func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func maxChunksToSorted(arr []int) int {
    var stk []int
    for i := 0; i < len(arr); i++ {
        if len(stk) != 0 && stk[len(stk) - 1] > arr[i] {
            tmp := 0
            for len(stk) != 0 && stk[len(stk) - 1] > arr[i] {
                tmp = max(tmp, stk[len(stk) - 1])
                stk = stk[:len(stk) - 1]
            }
            stk = append(stk, tmp)
        } else {
            stk = append(stk, arr[i])
        }
    }
    return len(stk)
}
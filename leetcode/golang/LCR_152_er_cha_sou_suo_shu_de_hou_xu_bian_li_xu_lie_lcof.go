func verifyTreeOrder(postorder []int) bool {
    root := math.MaxInt
    var stk []int
    for i := len(postorder) - 1; i >= 0; i-- {
        if postorder[i] > root {
            return false
        }
        for len(stk) != 0 && stk[len(stk)-1] > postorder[i] {
            root = stk[len(stk)-1]
            stk = stk[:len(stk)-1]
        }
        stk = append(stk, postorder[i])
    }
    return true
}
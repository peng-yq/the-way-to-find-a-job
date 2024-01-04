func validateStackSequences(pushed []int, popped []int) bool {
    var numStack []int
    j := 0
    for i := 0; i < len(pushed); i++{
        numStack = append(numStack, pushed[i])
        for len(numStack) != 0 && numStack[len(numStack) - 1] == popped[j] {
            numStack = numStack[:len(numStack) - 1]
            j++
        }
    }
    if j == len(popped) {
        return true
    }
    return false
}
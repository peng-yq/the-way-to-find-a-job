func validateBookSequences(putIn []int, takeOut []int) bool {
    var st []int
    j := 0
    for i := 0; i < len(putIn); i++ {
        st = append(st, putIn[i])
        for len(st) != 0 && st[len(st) - 1] == takeOut[j] {
            st = st[:len(st) - 1]
            j++
        }
    }
    return j == len(takeOut)
}
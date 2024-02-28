func spiralArray(array [][]int) []int {
    if len(array) == 0 || len(array[0]) == 0 {
        return []int{}
    }
    l, r, t, b := 0, len(array[0]) - 1, 0, len(array) - 1
    var res []int
    for true {
        for i := l; i <= r; i++ {
            res = append(res, array[t][i])
        }
        t++
        if t > b {
            break
        }
        for i := t; i <= b; i++ {
            res = append(res, array[i][r])
        } 
        r--
        if r < l {
            break
        }
        for i := r; i >= l; i-- {
            res = append(res, array[b][i])
        }
        b--
        if b < t {
            break
        }
        for i := b; i >= t; i-- {
            res = append(res, array[i][l])
        }
        l++
        if l > r {
            break
        }
    }
    return res
}
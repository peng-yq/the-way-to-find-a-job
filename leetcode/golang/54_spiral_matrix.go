func spiralOrder(matrix [][]int) []int {
    if len(matrix) == 0 || len(matrix[0]) == 0 {
        return []int{}
    }
    l, r, t, b := 0, len(matrix[0]) - 1, 0, len(matrix) - 1
    res := make([]int, 0)
    for {
        for i := l; i <= r; i++ {
            res = append(res, matrix[t][i])
        }
        t++
        if t > b {
            break
        }
        for i := t; i <= b; i++ {
            res = append(res, matrix[i][r])
        }
        r--
        if r < l {
            break
        }
        for i := r; i >= l; i-- {
            res = append(res, matrix[b][i])
        }
        b--
        if b < t {
            break
        }
        for i := b; i >= t; i-- {
            res = append(res, matrix[i][l])
        }
        l++
        if l > r {
            break
        }
    }
    return res
}
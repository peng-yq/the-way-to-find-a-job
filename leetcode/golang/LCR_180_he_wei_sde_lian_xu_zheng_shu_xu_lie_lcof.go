func fileCombination(target int) [][]int {
    var res [][]int
    var tmp []int
    sum := 0
    for i, j := 1, 1; j <= target / 2 + 1; j++ {
        sum += j
        tmp = append(tmp, j)
        for sum > target {
            sum -= i
            i++
        }
        if sum == target {
            res = append(res, tmp[i-1:j])
        }
    }
    return res
}
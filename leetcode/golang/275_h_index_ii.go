func hIndex(citations []int) int {
    l, r, res := 0, len(citations) - 1, 0
    for l <= r {
        m := l + (r-l) / 2
        if citations[m] >= len(citations) - m {
            res = len(citations) - m
            r = m - 1
        } else {
            l = m + 1
        }
    }
    return res
}
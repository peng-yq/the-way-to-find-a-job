func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func nthUglyNumber(n int) int {
    var dp = make([]int, n)
    dp[0] = 1
    a, b, c := 0, 0, 0
    for i := 1; i < n; i++ {
        resA, resB, resC := dp[a]*2, dp[b]*3, dp[c]*5
        res := min(min(resA, resB), resC)
        dp[i] = res
        if (res == resA) {
            a++
        }
        if (res == resB) {
            b++
        }
        if (res == resC) {
            c++
        }
    }
    return dp[n-1]
}
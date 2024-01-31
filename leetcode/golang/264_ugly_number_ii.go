func nthUglyNumber(n int) int {
    var dp []int = make([]int, n)
    dp[0] = 1
    a, b, c := 0, 0, 0
    for i := 1; i < n; i++ {
        resA, resB, resC := dp[a] * 2, dp[b] * 3, dp[c] * 5
        dp[i] = min(resA, min(resB, resC))
        if dp[i] == resA {
            a++
        }
        if dp[i] == resB {
            b++
        }
        if dp[i] == resC {
            c++
        }
    }
    return dp[n-1]
}

func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}
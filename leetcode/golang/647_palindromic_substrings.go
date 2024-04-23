func countSubstrings(s string) int {
    n := len(s)
    dp := make([][]bool, n)
    res := 0
    for i := 0; i < n; i++ {
        dp[i] = make([]bool, n)
    }
    for j := 0; j < n; j++ {
        for i := 0; i <= j; i++ {
            if s[i] == s[j] && (j - i < 2 || dp[i+1][j-1]) {
                dp[i][j] = true
                res++
            }
        }
    }
    return res
}

func countSubstrings(s string) int {
    n, res := len(s), 0
    for center := 0; center < 2 * n - 1; center++ {
        left := center / 2
        right := left + center % 2
        for left >= 0 && right < n && s[left] == s[right] {
            res++
            left--
            right++
        }
    } 
    return res
}
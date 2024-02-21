func findTheWinner(n int, k int) int {
    p := 0
    for i := 2; i <= n; i++ {
        p = (p + k) % i
    }
    return p+1
}

// 使用公式直接，时间复杂度为O(n)，空间复杂度为O(1)
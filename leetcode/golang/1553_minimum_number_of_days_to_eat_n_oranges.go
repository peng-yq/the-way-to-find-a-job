func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func minDays(n int) int {
    cache := make(map[int]int)
    var dfs func(n int) int
    dfs = func(n int) int {
        if n < 2 {
            return n
        }
        if _, ok := cache[n]; ok {
            return cache[n]
        }
        cache[n] = min(dfs(n / 2) + n % 2, dfs(n / 3) + n % 3) + 1
        return cache[n]
    }
    return dfs(n)
}
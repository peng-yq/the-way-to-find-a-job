func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func bestTiming(prices []int) int {
    if len(prices) < 2 {
        return 0
    }
    a, b, buyPrice := 0, 0, prices[0]
    for i := 1; i < len(prices); i++ {
        b = max(prices[i] - buyPrice, a)
        a = b
        if prices[i] < buyPrice {
            buyPrice = prices[i]
        }
    }
    return b
}
func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func maxProfit(prices []int) int {
    min_price := prices[0]
    max_profit := 0
    for i := 0; i < len(prices); i++ {
        min_price = min(min_price, prices[i])
        max_profit = max(max_profit, prices[i] - min_price)
    }
    return max_profit
}
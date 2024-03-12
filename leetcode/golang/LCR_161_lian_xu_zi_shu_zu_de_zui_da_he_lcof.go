func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func maxSales(sales []int) int {
    a, b, res := 0, 0, sales[0]
    a = sales[0]
    for i := 1; i < len(sales); i++ {
        if a >= 0 {
            b = a + sales[i]
        } else {
            b = sales[i]
        }
        a = b
        res = max(res, b)
    }
    return res
}
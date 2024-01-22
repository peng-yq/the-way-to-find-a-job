func myPow(x float64, n int) float64 {
    if n < 0 {
        n = -n
        x = 1 / x
    }
    tmp := x
    res := 1.0
    for i := n; i > 0; i /= 2 {
        if i % 2 == 1 {
            res *= tmp;
        }
        tmp *= tmp;
    }
    return res
}
func myPow(x float64, n int) float64 {
    if n == 0 {
        return 1
    }
    if n == -1 {
        return 1 / x
    }
    if n & 1 == 1 {
        return x * myPow(x*x, n>>1)
    }
    return myPow(x*x, n>>1)
}
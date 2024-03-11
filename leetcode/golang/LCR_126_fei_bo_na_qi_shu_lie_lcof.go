func fib(n int) int {
    if n < 2 {
        return n
    }
    const mod = 1000000007
    a, b, sum := 0, 1, 0
    for i := 2; i <= n; i++ {
        sum = (a + b) % mod
        a = b
        b = sum
    }
    return sum 
}
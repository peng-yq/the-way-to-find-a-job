func trainWays(num int) int {
    if num < 2 {
        return 1
    }
    const mod = 1000000007
    a, b, sum := 1, 1, 0
    for i := 2; i <= num; i++ {
        sum = (a + b) % mod
        a = b
        b = sum 
    }
    return sum
}
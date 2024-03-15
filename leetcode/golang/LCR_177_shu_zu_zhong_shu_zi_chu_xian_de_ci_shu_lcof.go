func sockCollocation(sockets []int) []int {
    res := 0
    for i := 0; i < len(sockets); i++ {
        res ^= sockets[i]
    }
    m := 1
    for (res & m) == 0 {
        m <<= 1
    }
    x, y := 0, 0
     for i := 0; i < len(sockets); i++ {
        if (m & sockets[i]) == 0 {
            x ^= sockets[i]
        } else {
            y ^= sockets[i]
        }
    }
    return []int{x, y}
}
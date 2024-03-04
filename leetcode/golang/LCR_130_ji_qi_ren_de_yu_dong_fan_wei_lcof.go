func digit(i int) int {
    res := 0
    for i != 0 {
        res += i % 10
        i /= 10
    }
    return res
}

func check(m int, n int, i int, j int, cnt int, visited [][]bool, res *int) {
    if i >= m || j >= n || visited[i][j] || digit(i) + digit(j) > cnt {
        return
    }
    visited[i][j] = true
    *res++
    check(m, n, i+1, j, cnt, visited, res)
    check(m, n, i, j+1, cnt, visited, res)
}

func wardrobeFinishing(m int, n int, cnt int) int {
    res := 0
    visited := make([][]bool, m)
    for i := 0; i < m; i++ {
        visited[i] = make([]bool, n)
    }
    check(m, n, 0, 0, cnt, visited, &res)
    return res
}
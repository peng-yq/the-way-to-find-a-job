func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func cherryPickup(grid [][]int) int {
    row, col := len(grid), len(grid[0])
    cache := make([][][]int, row)
    for i := 0; i < row; i++ {
        cache[i] = make([][]int, col)
        for j := 0; j < col; j++ {
            cache[i][j] = make([]int, col)
            for k := 0; k < col; k++ {
                cache[i][j][k] = -1
            }
        }
    }
    var dfs func(i, j, k int) int
    dfs = func(i, j, k int) int {
        if (i == row || j < 0 || j >= col || k < 0 || k >= col) {
            return 0
        }
        res := &cache[i][j][k]
        if *res != -1 {
            return *res
        }
        for m := j - 1; m <= j + 1; m++ {
            for n := k - 1; n <= k + 1; n++ {
                *res = max(*res, dfs(i + 1, m , n))
            } 
        }
        if (j == k) {
            *res += grid[i][j]
        } else {
            *res += grid[i][j] + grid[i][k]
        }
        return *res
    }
    return dfs(0, 0, col - 1)
}
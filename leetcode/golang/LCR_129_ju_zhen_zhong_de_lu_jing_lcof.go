func wordPuzzle(grid [][]byte, target string) bool {
    row, col := len(grid), len(grid[0])
    var dfs func(grid [][]byte, target string, i int, j int, k int) bool
    dfs = func(grid [][]byte, target string, i int, j int, k int) bool {
        if i < 0 || i >= row || j < 0 || j >= col || grid[i][j] != target[k] {
            return false
        }
        if k == len(target) - 1 {
            return true
        }
        grid[i][j] = ' '
        res := dfs(grid, target, i+1, j, k+1) || dfs(grid, target, i-1, j, k+1) || dfs(grid, target, i, j+1, k+1) || dfs(grid, target, i, j-1, k+1)
        grid[i][j] = target[k]
        return res
    }
    for i := 0; i < row; i++ {
        for j := 0; j < col; j++ {
            if dfs(grid, target, i, j, 0) {
                return true
            }
        }
    }
    return false
}
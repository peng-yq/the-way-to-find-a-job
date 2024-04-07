func numIslands(grid [][]byte) int {
    row, col, res := len(grid), len(grid[0]), 0
    var dfs func(grid [][]byte, i , j int) 
    dfs = func(grid [][]byte, i , j int) {
        if i < 0 || i >= row || j < 0 || j >= col || grid[i][j] != '1' {
            return
        }
        grid[i][j] = '0'
        dfs(grid, i+1, j)
        dfs(grid, i-1, j)
        dfs(grid, i, j+1)
        dfs(grid, i, j-1)
    }
    for i := 0; i < row; i++ {
        for j := 0; j < col; j++ {
            if grid[i][j] == '1' {
                dfs(grid, i, j)
                res++
            }
        }
    }
    return res    
}
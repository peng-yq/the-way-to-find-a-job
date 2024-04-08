func orangesRotting(grid [][]int) int {
    row, col, count, res := len(grid), len(grid[0]), 0, 0
    var que [][]int
    directions := [][]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}
    for i := 0; i < row; i++ {
        for j := 0; j < col; j++ {
            if grid[i][j] == 1 {
                count++
            }
            if grid[i][j] == 2 {
                que = append(que, []int{i, j})
            }
        }
    }
    for len(que) != 0 && count > 0 {
        for i := len(que); i > 0; i-- {
            bad := que[0]
            que = que[1:len(que)]
            for _, dir := range directions {
                j := bad[0] + dir[0]
                k := bad[1] + dir[1]
                if j >= 0 && j < row && k >= 0 && k < col && grid[j][k] == 1 {
                    count--
                    grid[j][k] = 2
                    que = append(que, []int{j, k})
                }
            }
        }
        res++
    }
    if count == 0 {
        return res
    }
    return -1
}
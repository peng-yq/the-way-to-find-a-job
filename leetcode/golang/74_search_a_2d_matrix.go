func searchMatrix(matrix [][]int, target int) bool {
    row, col := len(matrix), len(matrix[0])
    i, j := 0, col-1
    for i >= 0 && i < row && j >= 0 && j < col {
        if matrix[i][j] == target {
            return true
        } else if matrix[i][j] < target {
            i++
        } else {
            j--
        }
    }
    return false
}
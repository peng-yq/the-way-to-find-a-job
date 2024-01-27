func searchMatrix(matrix [][]int, target int) bool {
    i, j := len(matrix) - 1, 0
    for i >= 0 && j < len(matrix[0]) {
        if matrix[i][j] > target {
            i--
        } else if matrix[i][j] < target {
            j++
        } else {
            return true
        }
    }
    return false
}
func findTargetIn2DPlants(plants [][]int, target int) bool {
    i, j := len(plants) - 1, 0
    for i >= 0 && j < len(plants[0]) {
        if plants[i][j] < target {
            j++
        } else if plants[i][j] > target {
            i--
        } else {
            return true
        }
    } 
    return false
}
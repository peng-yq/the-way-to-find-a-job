func floodFill(image [][]int, sr int, sc int, color int) [][]int {
    if image[sr][sc] == color {
        return image
    }
    row, col := len(image), len(image[0])
    var dfs func(i, j, color, baseNum int)
    dfs = func(i, j, color, baseNum int) {
        if i < 0 || i >= row || j < 0 || j >= col || image[i][j] != baseNum {
            return
        }
        image[i][j] = color
        dfs(i+1, j, color, baseNum)
        dfs(i-1, j, color, baseNum)
        dfs(i, j+1, color, baseNum)
        dfs(i, j-1, color, baseNum)
    }
    dfs(sr, sc, color, image[sr][sc])
    return image
}
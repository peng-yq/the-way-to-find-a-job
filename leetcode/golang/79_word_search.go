func exist(board [][]byte, word string) bool {
    row := len(board)
    col := len(board[0])
    var dfs func(board [][]byte, word string, i int, j int, k int) bool 
    dfs = func(board [][]byte, word string, i int, j int, k int) bool {
        if i < 0 || i >= row || j < 0 || j >= col || board[i][j] != word[k] {
            return false
        }
        if k == len(word) - 1{
            return true
        }
        board[i][j] = byte(0)
        res := dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i - 1, j, k + 1) || dfs(board, word, i, j - 1, k + 1)
        board[i][j] = word[k]
        return res
    }
    for i := 0; i < row; i++ {
        for j := 0; j < col; j++ {
            if dfs(board, word, i, j, 0) == true {
                return true
            }
        }
    }
    return false
}
type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}
   
func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func abs(a int) int {
    if a < 0 {
        return -a
    }
    return a
}

func isBalanced(root *TreeNode) bool {
    res := true
    var dfs func(root *TreeNode) int
    dfs = func(root *TreeNode) int {
        if root == nil || !res {
            return 0
        }
        l := dfs(root.Left)
        r := dfs(root.Right)
        if abs(l - r) > 1 {
            res = false
            return 0
        }
        return max(l, r) + 1
    }
    dfs(root)
    return res
}
type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func isSymmetric(root *TreeNode) bool {
    var dfs func(left *TreeNode, right *TreeNode) bool
    dfs = func(left *TreeNode, right *TreeNode) bool {
        if left == nil && right == nil {
            return true 
        }
        if left == nil || right == nil || left.Val != right.Val {
            return false
        }
        return dfs(left.Left, right.Right) && dfs(left.Right, right.Left)
    }
    return root==nil || dfs(root.Left, root.Right)
}
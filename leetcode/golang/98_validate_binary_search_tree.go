type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func dfs(root *TreeNode, pre **TreeNode) bool {
    if root == nil {
        return true
    }
    if !dfs(root.Left, pre) {
        return false
    } 
    if *pre != nil && (*pre).Val >= root.Val {
        return false
    }
    *pre = root
    return dfs(root.Right, pre)
}

func isValidBST(root *TreeNode) bool {
    var pre *TreeNode
    return dfs(root, &pre)
}
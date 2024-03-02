type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}

   
func dfs(root *TreeNode) {
    if root == nil {
        return
    }
    root.Left, root.Right = root.Right, root.Left
    dfs(root.Left)
    dfs(root.Right)
}
func mirrorTree(root *TreeNode) *TreeNode {
    dfs(root)
    return root
}
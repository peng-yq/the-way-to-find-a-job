type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func invertTree(root *TreeNode) *TreeNode {
    var dfs func(root *TreeNode)
    dfs = func(root *TreeNode) {
        if root == nil {
            return 
        }
        tmp := root.Right
        root.Right = root.Left
        root.Left = tmp
        dfs(root.Left)
        dfs(root.Right)
    }
    dfs(root)
    return root
}
type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}

func findTargetNode(root *TreeNode, cnt int) int {
    var res int 
    var dfs = func(root *TreeNode) {}
    dfs = func(root *TreeNode) {
        if root == nil || cnt == 0 {
            return
        }
        dfs(root.Right)
        cnt--
        if cnt == 0 {
            res = root.Val
            return
        }
        dfs(root.Left)
    }
    dfs(root)
    return res
}
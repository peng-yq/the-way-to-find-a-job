type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func kthSmallest(root *TreeNode, k int) int {
    count, res := 0, 0;
    var dfs func(root *TreeNode)
    dfs = func(root *TreeNode) {
        if root == nil || count >= k {
            return;
        }
        dfs(root.Left)
        count++
        if count == k {
            res = root.Val
            return
        }
        dfs(root.Right)
    }
    dfs(root)
    return res
}

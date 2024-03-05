type TreeNode struct {
         Val   int
         Left  *TreeNode
         Right *TreeNode
}

   
func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
    if root == nil {
        return nil 
    }
    if root.Val < p.Val && root.Val < q.Val {
        return lowestCommonAncestor(root.Right, p, q)
    }
    if root.Val > p.Val && root.Val > q.Val {
        return lowestCommonAncestor(root.Left, p, q)
    }
    return root
}
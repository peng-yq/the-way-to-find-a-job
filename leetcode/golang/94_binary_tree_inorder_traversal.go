type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}

func inorderTraversal(root *TreeNode) []int {
    var res []int
    var inorder func(root *TreeNode) 
    inorder = func(root* TreeNode) {
        if root == nil {
            return
        }
        inorder(root.Left)
        res = append(res, root.Val)
        inorder(root.Right)
    }
    inorder(root)
    return res 
}
   
type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func rightSideView(root *TreeNode) []int {
    var que []*TreeNode
    var res []int
    if root != nil {
        que = append(que, root)
    }
    for len(que) != 0 {
        for i := len(que)-1; i >= 0; i-- {
            node := que[0]
            que = que[1:len(que)]
            if i == 0 {
                res = append(res, node.Val)
            }
            if node.Left != nil {
                que = append(que, node.Left)
            }
            if node.Right != nil {
                que = append(que, node.Right)
            }
        }
        
    }
    return res
}
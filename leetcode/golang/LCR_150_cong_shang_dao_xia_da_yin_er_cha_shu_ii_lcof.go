type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}

func decorateRecord(root *TreeNode) [][]int {
    var res [][]int
    var que []*TreeNode
    if root != nil {
        que = append(que, root)
    } else {
        return res
    }
    for len(que) != 0 {
        var tmp []int
        for i := len(que); i > 0; i-- {
            node := que[0]
            que = que[1:]
            tmp = append(tmp, node.Val)
            if node.Left != nil {
                que = append(que, node.Left)
            }
            if node.Right != nil {
                que = append(que, node.Right)
            }
        }
        res = append(res, tmp)
    }
    return res
}
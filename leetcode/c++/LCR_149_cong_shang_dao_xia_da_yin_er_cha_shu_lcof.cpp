type TreeNode struct {
      Val int
      Left *TreeNode
      Right *TreeNode
}

func decorateRecord(root *TreeNode) []int {
    var que []*TreeNode 
    var res []int
    if root != nil {
        que = append(que, root)
    } else {
        return res
    }
    for len(que) != 0 {
        tmp := que[0]
        que = que[1:]
        res = append(res, tmp.Val)
        if tmp.Left != nil {
            que = append(que, tmp.Left)
        }
        if tmp.Right != nil {
            que = append(que, tmp.Right)
        }
    }
    return res
}
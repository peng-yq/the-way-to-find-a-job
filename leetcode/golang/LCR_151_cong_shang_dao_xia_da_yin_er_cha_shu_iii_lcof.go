type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}

func decorateRecord(root *TreeNode) [][]int {
    if root == nil {
        return [][]int{}
    }
    var res [][]int
    que := []*TreeNode{root}
    flag := true
    for len(que) != 0 {
        num := len(que)
        tmp := make([]int, num)
        for i := 0; i < num; i++ {
            node := que[0]
            que = que[1:]
            if flag {
                tmp[i] = node.Val
            } else {
                tmp[num-i-1] = node.Val
            }
            if node.Left != nil {
                que = append(que, node.Left)
            }
            if node.Right != nil {
                que = append(que, node.Right)
            }
        }
        flag = !flag
        res = append(res, tmp)
    }
    return res
}
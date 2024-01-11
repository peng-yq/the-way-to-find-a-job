
type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

 func levelOrder(root *TreeNode) [][]int {
    var queue [] *TreeNode
    var res [][]int
    if root!= nil {
        queue = append(queue, root)
    }
    for len(queue) != 0 {
        var tmp []int
        for i := len(queue); i > 0; i-- {
            tmpNode := queue[0]
            queue = queue[1:]
            tmp = append(tmp, tmpNode.Val)
            if tmpNode.Left != nil {
                queue = append(queue, tmpNode.Left)
            }
            if tmpNode.Right != nil {
                queue = append(queue, tmpNode.Right)
            }
        }
        res = append(res, tmp)
    }
    return res
}
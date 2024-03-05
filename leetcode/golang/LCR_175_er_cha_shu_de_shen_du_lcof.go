type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}

func calculateDepth(root *TreeNode) int {
    if root == nil {
        return 0
    }
    res := 0
    var queue = []*TreeNode {root}
    for len(queue) != 0 {
        res++
        for i := len(queue); i > 0; i-- {
            node := queue[0]
            queue = queue[1:]
            if node.Left != nil {
                queue = append(queue, node.Left)
            }
            if node.Right != nil {
                queue = append(queue, node.Right)
            }
        } 
    }
    return res
}
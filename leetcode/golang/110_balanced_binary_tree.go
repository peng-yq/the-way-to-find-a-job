type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func isBalanced(root *TreeNode) bool {
    var recur func(root *TreeNode) int
    recur = func(root *TreeNode) int {
        if root == nil {
            return 0
        }
        left := recur(root.Left)
        if left == -1 {
            return -1
        }
        right := recur(root.Right)
        if right == -1 {
            return -1
        }
        if math.Abs(float64(left - right)) <= 1 {
            return max(left, right) + 1
        }
        return -1
    }
    return recur(root) != -1
}
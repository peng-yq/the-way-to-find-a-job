type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

   
func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func maxPathSum(root *TreeNode) int {
    res := math.MinInt32
    var maxSum func(root *TreeNode) int
    maxSum = func(root *TreeNode) int {
        if root == nil {
            return 0
        }
        leftVal := max(maxSum(root.Left), 0)
        rightVal := max(maxSum(root.Right), 0)
        sum := leftVal + rightVal + root.Val
        res = max(res, sum)
        return max(leftVal, rightVal) + root.Val
    }
    maxSum(root)
    return res
}
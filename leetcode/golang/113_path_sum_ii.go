type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func pathSum(root *TreeNode, targetSum int) [][]int {
    var res [][]int
    var path []int
    var recur func(root *TreeNode, targetSum int)
    recur = func(root *TreeNode, targetSum int) {
        if root == nil {
            return
        }
        path = append(path, root.Val)
        targetSum -= root.Val
        if targetSum == 0 && root.Left == nil && root.Right == nil {
            res = append(res, append([]int(nil), path...))
        }
        recur(root.Left, targetSum)
        recur(root.Right, targetSum)
        path = path[:len(path) - 1]
    }
    recur(root, targetSum)
    return res
}
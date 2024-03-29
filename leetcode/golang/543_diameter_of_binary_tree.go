type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func diameterOfBinaryTree(root *TreeNode) int {
	res := 0
	var dfs func(root *TreeNode, res *int) int
	dfs = func(root *TreeNode, res *int) int {
		if root == nil {
			return 0
		}
		left := dfs(root.Left, res)
		right := dfs(root.Right, res)
		*res = max(*res, left+right)
		return max(left, right) + 1
	}
	dfs(root, &res)
	return res
}
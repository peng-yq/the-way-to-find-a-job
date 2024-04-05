type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func sortedArrayToBST(nums []int) *TreeNode {
    var dfs func(nums []int, i, j int) *TreeNode
    dfs = func(nums []int, i, j int) *TreeNode {
        if i > j {
            return nil
        }
        mid := i + (j-i) / 2
        root := &TreeNode{
            nums[mid],
            nil,
            nil,
        }
        root.Left = dfs(nums, i, mid-1)
        root.Right = dfs(nums, mid+1, j)
        return root
    }
    return dfs(nums, 0, len(nums)-1)
}
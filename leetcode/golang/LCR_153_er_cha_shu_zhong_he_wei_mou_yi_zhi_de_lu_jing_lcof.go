type TreeNode struct {
        Val int
        Left *TreeNode
        Right *TreeNode
}

func pathTarget(root *TreeNode, target int) [][]int {
    if root == nil {
        return [][]int{}
    }
    var res [][]int
    var tmp []int
    var find  func(root *TreeNode, target int) 
    find = func(root *TreeNode, target int) {
        if root == nil {
            return
        }
        tmp = append(tmp, root.Val)
        if root.Left == nil && root.Right == nil && root.Val == target {
            res = append(res, append([]int(nil), tmp...))
        } else {
            find(root.Left, target-root.Val)
            find(root.Right, target-root.Val)
        }
        tmp = tmp[:len(tmp)-1]
    }
    find(root, target)
    return res
}

// res = append(res, append([]int(nil), tmp...))这个是关键，直接添加tmp的话，相当于只添加了tmp对象，后面改就会更改，所以需要添加tmp的复制
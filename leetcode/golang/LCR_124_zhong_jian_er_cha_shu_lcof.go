type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func dfs(preorder []int, index map[int]int, i int, l int, r int) *TreeNode {
    if r < l {
        return nil
    }
    m := index[preorder[i]]
    root := &TreeNode{
        Val : preorder[i],
        Left : dfs(preorder, index, i+1, l, m-1),
        Right : dfs(preorder, index, i+m-l+1, m+1, r),
    }
    return root
}

func deduceTree(preorder []int, inorder []int) *TreeNode {
    var index = make(map[int]int)
    for i := 0; i < len(inorder); i++ {
        index[inorder[i]] = i
    }
    root := dfs(preorder, index, 0, 0, len(inorder)-1)
    return root
}
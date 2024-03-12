type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

type FindElements struct {
    treeRoot *TreeNode
    s    map[int]bool
}


func Constructor(root *TreeNode) FindElements {
    f := FindElements {
        treeRoot: root,
        s : make(map[int]bool),
    }
    var dfs func (root *TreeNode, val int) 
    dfs = func (root *TreeNode, val int) {
        if root == nil {
            return 
        }
        root.Val = val
        f.s[val] = true
        dfs(root.Left, val*2+1)
        dfs(root.Right, val*2+2)
    }
    dfs(root, 0)
    return f
}


func (this *FindElements) Find(target int) bool {
    return this.s[target]
}
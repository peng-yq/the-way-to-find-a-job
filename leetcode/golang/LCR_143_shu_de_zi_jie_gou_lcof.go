type TreeNode struct {
         Val int
         Left *TreeNode
         Right *TreeNode
}

   
func check(a, b *TreeNode) bool {
    if b == nil {
        return true
    }
    if a == nil || a.Val != b.Val {
        return false
    }
    return check(a.Left, b.Left) && check(a.Right, b.Right)
}

func isSubStructure(A *TreeNode, B *TreeNode) bool {
    if A == nil || B == nil {
        return false
    }
    return check(A, B) || isSubStructure(A.Left, B) || isSubStructure(A.Right, B)
}
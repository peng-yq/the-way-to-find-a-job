
type ListNode struct {
    Val int
    Next *ListNode
}

 func deleteNode(node *ListNode) {
    tmp := node.Next
    node.Val = tmp.Val
    node.Next = tmp.Next 
}
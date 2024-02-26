type ListNode struct {
    Val int
    Next *ListNode
}

func deleteNode(head *ListNode, val int) *ListNode {
    if head.Val == val {
        return head.Next
    }
    pre, node := head, head.Next
    for node.Val != val && node != nil {
        pre = pre.Next
        node = node.Next
    }
    if node.Val == val {
        pre.Next = node.Next
    }
    return head
}
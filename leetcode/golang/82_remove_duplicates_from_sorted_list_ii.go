
type ListNode struct {
    Val int
    Next *ListNode
}

func deleteDuplicates(head *ListNode) *ListNode {
    node := &ListNode {
        Val : 0,
        Next : head,
    }
    cur := node
    for head != nil {
        if head.Next != nil && (head.Next.Val == head.Val) {
            x := head.Val
            for head != nil && head.Val == x {
                head = head.Next
            }
            cur.Next = head
        } else {
            cur = cur.Next
            head = head.Next
        }
    }
    return node.Next
}
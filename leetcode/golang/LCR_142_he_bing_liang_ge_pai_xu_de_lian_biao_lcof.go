type ListNode struct {
    Val int
    Next *ListNode
}

func trainningPlan(l1 *ListNode, l2 *ListNode) *ListNode {
    head := &ListNode {
        Val:0,
        Next:nil,
    }
    tmp := head
    for l1 != nil && l2 != nil {
        if l1.Val <= l2.Val {
            tmp.Next = l1
            l1 = l1.Next
        } else {
            tmp.Next = l2
            l2 = l2.Next
        }
        tmp = tmp.Next
    }
    if l1 != nil {
        tmp.Next = l1
    } 
    if l2 != nil {
        tmp.Next = l2
    }
    return head.Next
}
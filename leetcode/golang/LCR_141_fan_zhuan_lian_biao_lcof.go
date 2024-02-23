type ListNode struct {
     Val int
     Next *ListNode
}

func trainningPlan(head *ListNode) *ListNode {
    var tmp = &ListNode{}
    node := head
    tmpHead := head
    for tmpHead != nil {
        node = tmpHead.Next
        tmpHead.Next = tmp.Next
        tmp.Next = tmpHead
        tmpHead = node
    }
    return tmp.Next
}
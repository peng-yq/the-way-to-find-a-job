type ListNode struct {
    Val int
    Next *ListNode
}

 func reverseList(head *ListNode) *ListNode {
    newhead := ListNode {
        0,
        nil,
    }
    var tmp *ListNode
    for head != nil {
        tmp = head.Next
        head.Next = newhead.Next
        newhead.Next = head
        head = tmp
    }
    return newhead.Next
}
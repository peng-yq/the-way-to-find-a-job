type ListNode struct {
    Val int
    Next *ListNode
}

func reverseBookList(head *ListNode) []int {
    var tmp = &ListNode{}
    var res []int
    for head != nil {
        node := head.Next
        head.Next = tmp.Next
        tmp.Next = head
        head = node
    }
    tmp = tmp.Next
    for tmp != nil {
        res = append(res, tmp.Val)
        tmp = tmp.Next
    }
    return res
}
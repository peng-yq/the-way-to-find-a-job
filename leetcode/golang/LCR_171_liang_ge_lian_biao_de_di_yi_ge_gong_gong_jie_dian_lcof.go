type ListNode struct {
    Val int
    Next *ListNode
}

func getIntersectionNode(headA, headB *ListNode) *ListNode {
    tmp1, tmp2 := headA, headB
    for tmp1 != tmp2 {
        if tmp1 != nil {
            tmp1 = tmp1.Next
        } else {
            tmp1 = headB
        }
        if tmp2 != nil {
            tmp2 = tmp2.Next
        } else {
            tmp2 = headA
        }
    }
    return tmp1
}
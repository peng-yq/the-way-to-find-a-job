type ListNode struct {
    Val int
    Next *ListNode
}

func getIntersectionNode(headA, headB *ListNode) *ListNode {
    tmpA, tmpB := headA, headB;
    for tmpA != tmpB {
        if tmpA == nil {
            tmpA = headB
        } else {
            tmpA = tmpA.Next
        }      
        if tmpB == nil {
            tmpB = headA
        } else {
            tmpB = tmpB.Next
        }
    }
    return tmpA
}
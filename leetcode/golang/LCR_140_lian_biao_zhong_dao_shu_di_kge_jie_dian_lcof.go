type ListNode struct {
    Val int
    Next *ListNode
}

func trainingPlan(head *ListNode, cnt int) *ListNode {
    if head == nil {
        return nil
    }
    fast, slow := head, head
    for i := 0; i < cnt; i++ {
        fast = fast.Next
    }
    for fast != nil {
        fast = fast.Next
        slow = slow.Next
    }
    return slow
}
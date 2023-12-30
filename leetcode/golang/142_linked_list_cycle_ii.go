type ListNode struct {
    Val int
    Next *ListNode
}

func detectCycle(head *ListNode) *ListNode {
    slow, fast := head, head;
    for true {
        if fast == nil || fast.Next == nil {
            return nil
        }
        slow = slow.Next
        fast = fast.Next.Next
        if slow == fast {
            break
        }
    }
    fast = head
    for slow != fast {
        slow = slow.Next
        fast = fast.Next
    }
    return slow
}
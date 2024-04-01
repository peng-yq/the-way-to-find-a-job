type ListNode struct {
    Val int
    Next *ListNode
}

func midCutList(head *ListNode) *ListNode {
    slow, fast := head, head
    for fast.Next != nil && fast.Next.Next != nil {
        slow = slow.Next
        fast = fast.Next.Next
    }
    res := slow.Next
    slow.Next = nil
    return res
}

func mergeList(left, right *ListNode) *ListNode {
    dummy := &ListNode {
            0,
            nil,
        }
    res := dummy
    for left != nil && right != nil {
        if left.Val <= right.Val {
            node := left.Next
            left.Next = dummy.Next
            dummy.Next = left
            dummy = left
            left = node
        } else {
            node := right.Next
            right.Next = dummy.Next
            dummy.Next = right
            dummy = right
            right = node
        }
    }
    if left != nil {
        dummy.Next = left
    } else {
        dummy.Next = right
    }
    return res.Next
}

func sortList(head *ListNode) *ListNode {
    if head == nil || head.Next == nil {
        return head
    }
    mid := midCutList(head)
    left := sortList(head)
    right := sortList(mid)
    return mergeList(left, right)
}
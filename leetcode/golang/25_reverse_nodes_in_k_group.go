type ListNode struct {
    Val int
    Next *ListNode
}

func reverseKGroup(head *ListNode, k int) *ListNode {
    n := 0
    for tmp := head; tmp != nil; tmp = tmp.Next {
        n++
    }
    dummy := &ListNode {
        0,
        head,
    }
    cur, pre, preHead := head, (*ListNode)(nil), dummy
    for ; n >= k; n -= k {
        for i := 0; i < k; i++ {
            nxt := cur.Next
            cur.Next = pre
            pre = cur
            cur = nxt
        }
        tail := preHead.Next
        tail.Next = cur
        preHead.Next = pre
        preHead = tail
    }
    return dummy.Next
}

// 需要注意的是，go使用nil必须指明其类型，因此上述赋值时做个转换

// 递归

func reverseKGroup(head *ListNode, k int) *ListNode {
    tmp := head
    for i := 0; i < k; i++ {
        if tmp == nil {
            return head
        }
        tmp = tmp.Next
    }
    cur, pre := head, (*ListNode)(nil)
    for i := 0; i < k; i++ {
        nxt := cur.Next
        cur.Next = pre
        pre = cur
        cur = nxt
    }
    head.Next = reverseKGroup(cur, k)
    return pre
}
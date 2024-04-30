type ListNode struct {
    Val int
    Next *ListNode
}

func merge(a, b *ListNode) *ListNode {
    dummy := &ListNode {
        0,
        nil,
    }
    tmp := dummy
    for a != nil && b != nil {
        if a.Val < b.Val {
            tmp.Next = a
            a = a.Next
        } else {
            tmp.Next = b
            b = b.Next
        }
        tmp = tmp.Next
    }
    if a != nil {
        tmp.Next = a
    } else {
        tmp.Next = b
    }
    return dummy.Next
}

func mergeLists(lists []*ListNode, i, j int) *ListNode {
    if i > j {
        return nil
    }
    if i == j {
        return lists[i]
    }
    mid := i + (j - i) / 2
    left := mergeLists(lists, i, mid)
    right := mergeLists(lists, mid + 1, j)
    return merge(left, right)
}

func mergeKLists(lists []*ListNode) *ListNode {
    n := len(lists)
    if n == 0 {
        return nil
    }
    return mergeLists(lists, 0, n-1)
}
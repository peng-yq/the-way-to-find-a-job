type ListNode struct {
    Val int
    Next *ListNode
}

func isPalindrome(head *ListNode) bool {
    var stk []int
    node := head
    for node != nil {
        stk = append(stk, node.Val)
        node = node.Next
    }
    for head != nil {
        if head.Val != stk[len(stk)-1] {
            return false
        }
        head = head.Next
        stk = stk[:len(stk)-1]
    }
    return true
}
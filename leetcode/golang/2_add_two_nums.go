// Definition for singly-linked list.

type ListNode struct {
    Val int
    Next *ListNode
}

 func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    var head *ListNode
    var tail *ListNode
    pre := 0
    for l1 !=nil || l2 !=nil {
        left, right := 0, 0
        if l1 != nil {
            left = l1.Val
            l1 = l1.Next
        }
        if l2 != nil {
            right = l2.Val
            l2 = l2.Next
        }
        sum := left + right + pre
        if head ==nil{
            head = &ListNode{Val : sum % 10}
            tail = head
        }else{
            tail.Next = &ListNode{Val : sum % 10}
            tail = tail.Next
        }
        pre = sum / 10
    }
    if pre > 0{
        tail.Next = &ListNode{Val : pre}
    }
    return head
}
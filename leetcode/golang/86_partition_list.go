/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
 func partition(head *ListNode, x int) *ListNode {
    list1 := ListNode {}
    list2 := ListNode {}
    end1 := &list1
    end2 := &list2
    for head != nil {
        if head.Val < x {
            end1.Next = head
            end1 = end1.Next
        } else {
            end2.Next = head
            end2 = end2.Next
        }
        head = head.Next
    }
    end1.Next = list2.Next
    end2.Next = nil
    return list1.Next
}
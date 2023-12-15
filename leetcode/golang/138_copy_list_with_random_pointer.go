/**
 * Definition for a Node.
 * type Node struct {
 *     Val int
 *     Next *Node
 *     Random *Node
 * }
 */

 func copyRandomList(head *Node) *Node {
    newhead1 , newhead2 := head, head
    hashArray := make(map[*Node]*Node)
    for newhead1 != nil {
        hashArray[newhead1] = &Node {
            Val: newhead1.Val,
        }
        newhead1 = newhead1.Next
    }
    for newhead2 != nil {
        hashArray[newhead2].Next = hashArray[newhead2.Next] 
        hashArray[newhead2].Random = hashArray[newhead2.Random] 
        newhead2 = newhead2.Next
    }
    return hashArray[head]
}
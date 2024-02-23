type Node struct {
    Val int
    Next *Node
    Random *Node
}

   
func copyRandomList(head *Node) *Node {
    tmp := head
    var hashMap = make(map[*Node]*Node)
    for tmp != nil {
        hashMap[tmp] = &Node{
            Val: tmp.Val, 
        }
        tmp = tmp.Next
    }
    tmp = head
    for tmp != nil {
        hashMap[tmp].Next = hashMap[tmp.Next]
        hashMap[tmp].Random = hashMap[tmp.Random]
        tmp = tmp.Next
    }
    return hashMap[head]
}
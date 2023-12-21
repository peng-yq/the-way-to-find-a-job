type MyQueue struct {
    A []int
    B []int
}


func Constructor() MyQueue {
    return MyQueue{}
}


func (this *MyQueue) Push(x int)  {
    this.A = append(this.A, x)
}


func (this *MyQueue) Pop() int {
    peek := this.Peek()
    if peek != -1 {
        this.B = this.B[:len(this.B) - 1]
    }
    return peek
}


func (this *MyQueue) Peek() int {
    if (len(this.B) != 0) {
        return this.B[len(this.B) - 1]
    }
    if (len(this.A) == 0) {
        return -1
    }
    for len(this.A) != 0 {
        this.B = append(this.B, this.A[len(this.A) - 1])
        this.A = this.A[:len(this.A) - 1]
    }
    return this.B[len(this.B) - 1]
}


func (this *MyQueue) Empty() bool {
    return len(this.A) == 0 && len(this.B) == 0
}


/**
 * Your MyQueue object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * param_2 := obj.Pop();
 * param_3 := obj.Peek();
 * param_4 := obj.Empty();
 */
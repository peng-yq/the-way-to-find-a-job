package main

import "fmt"

type myQueue struct {
    data   []int
    head     int
    tail     int
    count    int
    capacity int 
}

func NewQueue(size int) *myQueue {
    return &myQueue {
        data: make([]int, size),
        head: 0,
        tail: 0,
        count: 0,
        capacity: size,
    }
}

func (q *myQueue) EnQueue(val int) {
    if q.IsFull() {
        fmt.Println("The queue is full.")
    } else {
        q.data[q.tail] = val
        q.tail = (q.tail + 1) % q.capacity
        q.count++
    }
}

func (q *myQueue) Dequeue() int{
    if q.IsEmpty() {
        fmt.Println("The queue is empty.")
        return -1
    } else {
        num := q.front()
        q.head = (q.head + 1) % q.capacity
        q.count--
        return num
    }
}

func (q *myQueue) IsFull() bool {
    return q.count == q.capacity
}

func (q *myQueue) IsEmpty() bool {
    return q.count == 0
}

func (q *myQueue) size() int {
    return q.count
}

func (q *myQueue) front() int {
    if q.IsEmpty() {
        fmt.Println("The queue is empty.")
        return -1
    }
    return q.data[q.head]
}

func (q *myQueue) back() int {
    if q.IsEmpty() {
        fmt.Println("The queue is empty.")
        return -1
    }
    return q.data[(q.tail - 1 + q.capacity) % q.capacity]
}
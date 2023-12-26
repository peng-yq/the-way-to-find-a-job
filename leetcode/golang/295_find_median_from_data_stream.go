package main

import (
	"container/heap"
)

// An IntHeap is a min-heap of ints for the small top heap.
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] } // This creates a min heap.
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

// An IntMaxHeap is a max-heap of ints for the large top heap.
type IntMaxHeap []int

func (h IntMaxHeap) Len() int           { return len(h) }
func (h IntMaxHeap) Less(i, j int) bool { return h[i] > h[j] } // This creates a max heap.
func (h IntMaxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntMaxHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}

func (h *IntMaxHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

type MedianFinder struct {
	small *IntMaxHeap // max heap
	large *IntHeap    // min heap
}

func Constructor() MedianFinder {
	small := &IntMaxHeap{}
	large := &IntHeap{}
	heap.Init(small)
	heap.Init(large)
	return MedianFinder{small: small, large: large}
}

func (this *MedianFinder) AddNum(num int) {
	heap.Push(this.small, num) // Add to max heap

	// Balance heaps
	if this.small.Len() > 0 && this.large.Len() > 0 && (*this.small)[0] > (*this.large)[0] {
		heap.Push(this.large, heap.Pop(this.small))
	}

	// Maintain size property
	if this.small.Len() > this.large.Len()+1 {
		heap.Push(this.large, heap.Pop(this.small))
	} else if this.large.Len() > this.small.Len() {
		heap.Push(this.small, heap.Pop(this.large))
	}
}

func (this *MedianFinder) FindMedian() float64 {
	if this.small.Len() > this.large.Len() {
		return float64((*this.small)[0])
	} else if this.large.Len() > this.small.Len() {
		return float64((*this.large)[0])
	}
	return float64((*this.small)[0]+(*this.large)[0]) / 2.0
}
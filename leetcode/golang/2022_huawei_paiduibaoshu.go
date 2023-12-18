package main

import (
	"fmt"
)

func main() {
	var n int
	fmt.Scan(&n)
	array := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&array[i])
	}
	height := make(map[int]int)
	res := make([]int, n)
	for i := n - 1; i >= 0; i-- {
		height[array[i]]++
		for j := 40; j < array[i]; j++ {
			res[i] += height[j]
		}
	}
	for i := 0; i < n; i++ {
		fmt.Printf("%d ", res[i])
	}
}

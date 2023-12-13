package main

import (
	"fmt"
)

func main() {
	var n, x int
	fmt.Scan(&n, &x)
	nums := make([]int, n)
	for i := range nums {
		fmt.Scan(&nums[i])
	}

	count := make(map[int]int)
	res := 0
	for l, r := 0, 0; r < n; r++ {
		count[nums[r]]++
		for count[nums[r]] >= x {
			res += n - r
			count[nums[l]]--
			l++
		}
	}
	fmt.Println(res)
}

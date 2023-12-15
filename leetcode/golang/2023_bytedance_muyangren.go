package main

import (
    "fmt"
    "sort"
)

func min(a int, b int) int{
    if a < b {
        return a
    }
    return b
}

func main() {
    var n int
    fmt.Scan(&n)
    sheep := make([]int, n)
    for i := 0; i < n; i++ {
        fmt.Scan(&sheep[i])
    }
    sort.Ints(sheep)
    res := n
    for l, r := 0, 0; r < n; r++ {
        for sheep[r] - sheep[l] + 1 > n {
            l++
        }
        res = min (res, n-(r-l+1))
    }
    fmt.Println(res)
}
func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func largestRectangleArea(heights []int) int {
    n := len(heights)
    var stk []int
    left := make([]int, n)
    for i := 0; i < n; i++ {
        left[i] = -1
    }
    right := make([]int, n)
    for i := 0; i < n; i++ {
        right[i] = n
    }
    for i := 0; i < n; i++ {
        for len(stk) != 0 && heights[i] <= heights[stk[len(stk)-1]] {
            stk = stk[:len(stk)-1]
        }
        if len(stk) != 0 {
            left[i] = stk[len(stk)-1]
        }
        stk = append(stk, i)
    }
    stk = stk[:0]
    for i := n-1; i >= 0; i-- {
        for len(stk) != 0 && heights[i] <= heights[stk[len(stk)-1]] {
            stk = stk[:len(stk)-1]
        }
        if len(stk) != 0 {
            right[i] = stk[len(stk)-1]
        }
        stk = append(stk, i)
    }
    res := 0
    for i := 0; i < n; i++ {
        res = max(res, heights[i] * (right[i] - left[i] -1))
    }
    return res
}

// 属实是又臭又长
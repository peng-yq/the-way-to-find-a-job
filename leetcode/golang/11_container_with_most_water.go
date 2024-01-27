func maxArea(height []int) int {
    i, j := 0, len(height) - 1
    res := 0
    for i < j {
        res = max(res, (j-i) * min(height[i], height[j]))
        if height[i] < height[j] {
            i++
        } else {
            j--
        }
    }
    return res
}

func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
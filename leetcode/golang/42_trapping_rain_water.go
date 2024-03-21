func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func trap(height []int) int {
    res, i, j, left_max, right_max := 0, 0, len(height)-1, 0, 0
    for i < j {
        left_max = max(left_max, height[i])
        right_max = max(right_max, height[j])
        if left_max < right_max {
            res += left_max - height[i]
            i++
        } else {
            res += right_max - height[j]
            j--
        }
    }
    return res
}
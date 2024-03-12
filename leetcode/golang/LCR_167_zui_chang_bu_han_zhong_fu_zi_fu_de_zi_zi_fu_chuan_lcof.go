func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func dismantlingAction(arr string) int {
    var check = make(map[byte]int)
    res := 0
    for i, j := -1, 0; j < len(arr); j++ {
        if val, ok := check[arr[j]]; ok{
            i = max(i, val)
        }
        check[arr[j]] = j;
        res = max(res, j-i);
    }
    return res
}
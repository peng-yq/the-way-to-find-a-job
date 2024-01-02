func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func lengthOfLongestSubstring(s string) int {
    sMap := make(map[byte]int)
    res := 0
    for i, j := 0, -1; i < len(s); i++ {
        if _, ok := sMap[s[i]]; ok {
            j = max(j, sMap[s[i]])
        }
        sMap[s[i]] = i;
        res = max(res, i - j)
    }
    return res
}
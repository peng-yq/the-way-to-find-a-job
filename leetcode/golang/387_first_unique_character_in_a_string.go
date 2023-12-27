func firstUniqChar(s string) int {
    sMap := make(map[byte]int)
    res := -1
    for i := 0; i < len(s); i++ {
        sMap[s[i]]++
    }
    for i := 0; i < len(s); i++ {
        if sMap[s[i]] == 1 {
            res = i
            break
        }
    }
    return res
}
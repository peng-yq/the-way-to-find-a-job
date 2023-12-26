func isAnagram(s string, t string) bool {
    sMap := make(map[byte]int)
    tMap := make(map[byte]int)
    for i := 0; i < len(s); i++ {
        sMap[s[i]]++
    }
    for i := 0; i < len(t); i++ {
        tMap[t[i]]++
    }
    if len(sMap) != len(tMap) {
        return false
    }
    for i := 0; i < len(s); i++ {
        if sMap[s[i]] != tMap[s[i]] {
            return false
        }
    }
    return true
}
func isIsomorphic(s string, t string) bool {
    if len(s) != len(t) {
        return false
    }
    sMap := make(map[byte]byte)
    tMap := make(map[byte]byte)
    for i := 0; i < len(s); i++ {
        a := s[i]
        b := t[i]
        _, ok := sMap[a]
        _, right := tMap[b]
        if ok && sMap[a] != b ||  right && tMap[b] != a {
            return false
        }
        sMap[a] = b
        tMap[b] = a
    }
    return true
}
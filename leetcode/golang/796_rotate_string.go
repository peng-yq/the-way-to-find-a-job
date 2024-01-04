func rotateString(s string, goal string) bool {
    if len(s) != len(goal) {
        return false
    }
    var temp string 
    for i := 0; i < len(s); i++ {
        if s[i] == goal[0] {
            sumStr := s[i:] + temp
            if sumStr == goal {
                return true
            }
        }
        temp += string(s[i])
    }
    return false
}
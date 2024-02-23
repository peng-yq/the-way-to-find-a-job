func validNumber(s string) bool {
    k := 0
    for k < len(s) && s[k] == ' ' {
        k++
    }
    if !isNum(s, &k, 1) {
        return false
    }
    if k < len(s) && (s[k] == 'e' || s[k] == 'E') {
        k++
        if !isNum(s, &k, 0) {
            return false
        }
    }
    for k < len(s) && s[k] == ' ' {
        k++
    }
    return k == len(s)
}

func isNum(s string, k *int, spot int) bool {
    for *k < len(s) && (s[*k] == '+' || s[*k] == '-') {
        *k++
    }
    num := 0
    for *k < len(s) && (s[*k] >= '0' && s[*k] <= '9' || s[*k] == '.') {
        if s[*k] == '.' {
            spot--
            if spot < 0 {
                return false
            }
        } else {
            num++
        }
        *k++
    }
    return num > 0
}
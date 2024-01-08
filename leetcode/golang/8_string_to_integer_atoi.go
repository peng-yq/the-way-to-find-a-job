func myAtoi(s string) int {
    if len(s) == 0 {
        return 0
    }
    res, i, flag, boundary := 0, 0, 1, (math.MaxInt32 / 10);
    for s[i] == ' ' {
        i++
        if i == len(s) {
            return 0;
        }
    }
    if s[i] == '-' {
        flag = -1
    }
    if s[i] == '-' || s[i] == '+' {
        i++
    }
    for ; i < len(s); i++ {
        if s[i] < '0' || s[i] > '9' {
            break
        }
        if res > boundary || res == boundary && s[i] > '7' {
            if flag == 1 {
                return math.MaxInt32
            }
            return math.MinInt32
        }
        res = res * 10 + int(s[i] - '0')
    }
    return res * flag
}
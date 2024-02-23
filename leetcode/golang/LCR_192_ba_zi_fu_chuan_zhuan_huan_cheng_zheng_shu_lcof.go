func myAtoi(str string) int {
    if len(str) == 0 {
        return 0
    }
    i, res, flag := 0, 0, 1
    for str[i] == ' ' {
        i++
        if i == len(str) {
            return 0
        }
    }
    if str[i] == '-' || str[i] == '+' {
        if str[i] == '-' {
            flag = -1
        }
        i++
    }
    for i < len(str) {
        if str[i] < '0' || str[i] > '9' {
            break
        }
        if res > math.MaxInt32 / 10 || res == math.MaxInt32 / 10 && str[i] > '7' {
            if flag == 1 {
                return math.MaxInt32
            } 
            return math.MinInt32
        }
        res = res * 10 + int(str[i] - '0')
        i++
    }
    return res * flag
}
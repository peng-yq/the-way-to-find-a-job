func reverseMessage(message string) string {
    j := len(message) - 1
    var res []byte
    for j >= 0 && message[j] == ' ' {
        j--
    }
    for j >= 0 {
        end := j
        for j >= 0 && message[j] != ' ' {
            j--
        }
        for i := j + 1; i <= end; i++ {
            res = append(res, message[i])
        }
        res = append(res, ' ')
        for j >= 0 && message[j] == ' ' {
            j-- 
        }
    }
    if len(res) > 0 && res[len(res) - 1] == ' ' {
        res = res[: len(res) - 1]
    }
    return string(res)
}
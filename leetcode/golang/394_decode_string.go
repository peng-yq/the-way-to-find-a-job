func decodeString(s string) string {
    var res string
    var numStack []int
    var resStack []string
    num := 0
    for i := 0; i < len(s); i++ {
        if s[i] == '[' {
            numStack = append(numStack, num)
            resStack = append(resStack, res)
            num = 0
            res = ""
        } else if s[i] == ']' {
            tmp := ""
            for j := 0; j < numStack[len(numStack)-1]; j++ {
                tmp += res
            }
            numStack = numStack[: len(numStack)-1]
            res = resStack[len(resStack)-1] + tmp
            resStack = resStack[: len(resStack)-1]
        } else if s[i] >= '0' && s[i] <= '9' {
            num = num * 10 + int(s[i] - '0')
        } else {
            res += string(s[i])
        }
    }
    return res
}
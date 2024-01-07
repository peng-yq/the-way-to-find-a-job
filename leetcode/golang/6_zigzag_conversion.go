func convert(s string, numRows int) string {
    if numRows < 2 {
        return s
    }
    res := make([]string, numRows)
    i, flag := 0, -1
    for j := 0; j < len(s); j++ {
        res[i] += string(s[j])
        if i == 0 || i == numRows -1 {
            flag = -flag
        }
        i += flag
    }
    var resString string
    for i = 0; i < numRows; i++ {
        resString += res[i]
    } 
    return resString
}
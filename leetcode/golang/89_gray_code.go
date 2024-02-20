func grayCode(n int) []int {
    var res []int = make([]int, 1, 1<<n)
    res[0] = 0
    head := 1
    for i := 0; i < n; i++ {
        for j := len(res) - 1; j >= 0; j-- {
            res = append(res, head + res[j]);
        }
        head <<= 1
    }
    return res
}

// var res []int = make([]int, 1, 1<<n)，表示容量为1<<n，初始长度为1；
// var res []int = make([]int, 1<<n)，表示容量为1<<n，初始长度为1<<n
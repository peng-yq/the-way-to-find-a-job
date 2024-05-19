func getWinner(arr []int, k int) int {
    pre, count := arr[0], 0
    for i := 1; i < len(arr); i++ {
        if count == k {
            return pre
        }
        if pre > arr[i] {
            count++
        } else {
            pre = arr[i]
            count = 1
        }
    }
    return pre
}
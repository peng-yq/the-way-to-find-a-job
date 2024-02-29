func stockManagement(stock []int) int {
    i, j := 0, len(stock) - 1
    for i <= j {
        m := i + (j-i) / 2
        if stock[m] < stock[j] {
            j = m
        } else if stock[m] > stock[j] {
            i = m + 1
        } else {
            j--
        }
    }
    return stock[i]
}
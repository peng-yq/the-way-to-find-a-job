func quickSort(stock []int, l, r int) {
    if l >= r {
        return
    }
    i, j := l, r
    for i < j {
        for i < j && stock[j] >= stock[l] {
            j--
        }
        for i < j && stock[i] <= stock[l] {
            i++
        }
        stock[i], stock[j] = stock[j], stock[i] 
    }
    stock[i], stock[l] = stock[l], stock[i]
    quickSort(stock, l, i-1)
    quickSort(stock, i+1, r)
}

func inventoryManagement(stock []int, cnt int) []int {
    quickSort(stock, 0, len(stock) - 1)
    return stock[:cnt]
}
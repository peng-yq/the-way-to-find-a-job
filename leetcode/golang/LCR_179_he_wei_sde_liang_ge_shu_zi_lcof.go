func twoSum(price []int, target int) []int {
    i, j := 0, len(price) - 1
    for i < j {
        if price[i] + price[j] < target {
            i++
        } else if price[i] + price[j] > target {
            j--
        } else {
            return []int {price[i], price[j]}
        }
    }
    return []int{}
}
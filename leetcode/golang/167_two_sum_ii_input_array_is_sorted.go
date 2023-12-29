func twoSum(numbers []int, target int) []int {
    i, j := 0, len(numbers) - 1
    var res []int
    for i < j {
        if numbers[i] + numbers[j] < target {
            i++
        } else if numbers[i] + numbers[j] > target {
            j--
        } else {
            res = append(res, i+1, j+1)
            return res
        }
    }
    return res
}
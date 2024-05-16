func minimumRounds(tasks []int) int {
    res := 0
    taskMap := make(map[int]int)
    for _, task := range tasks {
        taskMap[task]++
    }
    for _, val := range taskMap {
        if val == 1 {
            return -1
        }
        if val % 3 == 0 {
            res += val / 3
        } else {
            res += val / 3 + 1
        }
    }
    return res
}
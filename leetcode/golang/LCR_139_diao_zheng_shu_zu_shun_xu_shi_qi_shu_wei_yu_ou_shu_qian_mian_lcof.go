func trainingPlan(actions []int) []int {
    i, j := 0, len(actions) - 1
    for i < j {
        for i < j && (actions[i] & 1) == 1 {
            i++
        }
        for i < j && (actions[j] & 1) == 0 {
            j--
        }
        actions[i], actions[j] = actions[j], actions[i]
    }
    return actions
}
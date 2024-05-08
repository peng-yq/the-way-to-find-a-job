func wateringPlants(plants []int, capacity int) int {
    res, n, tmp := 0, len(plants), capacity
    for i := 0; i < n; i++ {
        if tmp >= plants[i] {
            res += 1
            tmp -= plants[i]
        } else {
            res += i * 2 + 1
            tmp = capacity
            tmp -= plants[i]
        }
    }
    return res
}
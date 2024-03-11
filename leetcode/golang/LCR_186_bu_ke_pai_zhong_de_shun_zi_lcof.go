func checkDynasty(places []int) bool {
    count := 0
    sort.Ints(places)
    for i := 0; i < len(places) - 1; i++ {
        if places[i] == 0 {
            count++
        } else if places[i+1] == places[i] {
            return false
        }
    }
    return places[4] - places[count] < 5
}
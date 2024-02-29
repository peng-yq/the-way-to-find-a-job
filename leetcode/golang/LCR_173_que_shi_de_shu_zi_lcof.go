func takeAttendance(records []int) int {
    if records[0] == 1 {
        return 0
    }
    i, j := 0, len(records) - 1
    for i <= j {
        m := i + (j-i) / 2
        if records[m] == m {
            i = m + 1
        } else {
            j = m - 1
        }
    }
    return i
}
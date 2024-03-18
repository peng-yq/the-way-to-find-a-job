func digitOneInNumber(num int) int {
    count, digit, tmp := 0, 1, num
    for tmp > 0 {
        cur := num / digit % 10
        low := num % digit
        high := num / digit / 10
        tmp /= 10
        if cur > 1 {
            count += (high + 1) * digit
        } else if cur == 1 {
            count += high * digit + low + 1
        } else {
            count += high * digit
        }
        digit *= 10
    }
    return count
}
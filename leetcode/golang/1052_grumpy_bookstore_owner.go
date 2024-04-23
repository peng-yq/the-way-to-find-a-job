func maxSatisfied(customers []int, grumpy []int, minutes int) int {
    n, res, sum, tmp := len(customers), 0, 0, 0
    for i, j := 0, 0; j < n; j++ {
        if grumpy[j] == 1 {
            tmp += customers[j]
        } else {
            res += customers[j]
        }
        if j - i + 1 > minutes {
            if grumpy[i] == 1 {
                tmp -= customers[i]
            }
            i++
        }
        if j - i + 1 == minutes && tmp > sum{
            sum = tmp
        }
    }
    return res + sum
}
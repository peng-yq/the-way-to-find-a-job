func countTarget(scores []int, target int) int {
    i, j := 0, len(scores) - 1
    if j >= 0 && scores[0] > target {
        return 0
    }
    for i <= j {
        mid := i + (j - i) / 2
        if scores[mid] < target {
            i = mid + 1
        } else if scores[mid] > target {
            j = mid - 1
        } else {
            if scores[i] == scores[j] {
                return j - i + 1
            } 
            if scores[i] < target {
                i++
            }
            if scores[j] > target {
                j--
            }
        }
    }
    return 0
}
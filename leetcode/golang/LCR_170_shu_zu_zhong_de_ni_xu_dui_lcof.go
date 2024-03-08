func mergeSort(record []int, tmp []int, left, right int) int {
    if left >= right {
        return 0
    }
    mid := left + (right - left) / 2
    res := mergeSort(record, tmp, left, mid) + mergeSort(record, tmp, mid+1, right)
    for k := left; k <= right; k++ {
        tmp[k] = record[k]
    }
    leftStart, rightStart := left, mid+1
    for k := left; k <= right; k++ {
        if leftStart == mid+1 {
            record[k] = tmp[rightStart]
            rightStart++
        } else if rightStart == right+1 || tmp[leftStart] <= tmp[rightStart] {
            record[k] = tmp[leftStart]
            leftStart++
        } else {
            record[k] = tmp[rightStart]
            rightStart++
            res += mid - leftStart + 1
        }
    }
    return res;
}

func reversePairs(record []int) int {
    tmp := make([]int, len(record))
    return mergeSort(record, tmp, 0, len(record)-1)
}
func maxSlidingWindow(nums []int, k int) []int {
    var res []int
    var numQue []int
    for i, j := 0, 0; j < len(nums); j++ {
        for len(numQue) > 0 && numQue[len(numQue) - 1] < nums[j] {
            numQue = numQue[: len(numQue) - 1]
        }
        numQue = append(numQue, nums[j])
        if j - i + 1 > k {
            if numQue[0] == nums[i] {
                numQue = numQue[1:]
            }
            i++
        }
        if j - i + 1 == k {
            res = append(res, numQue[0])
        }
    }
    return res;
}
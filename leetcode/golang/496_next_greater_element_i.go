func nextGreaterElement(nums1 []int, nums2 []int) []int {
    n1, n2 := len(nums1), len(nums2)
    index := make(map[int]int)
    var stk []int
    var res []int
    for i := n2-1; i >= 0; i-- {
        for len(stk) != 0 && nums2[i] >= stk[len(stk)-1] {
            stk = stk[:len(stk)-1]
        }
        if len(stk) != 0 {
            index[nums2[i]] = stk[len(stk)-1]
        } else {
            index[nums2[i]] = -1
        }
        stk = append(stk, nums2[i])
    }
    for i := 0; i < n1; i++ {
        res = append(res, index[nums1[i]])
    }
    return res
}
func subsets(nums []int) [][]int {
    var res [][]int
    var tmp []int
    var dfs func (start, num int)
    dfs = func (start, num int) {
        if len(tmp) == num {
            res = append(res, append([]int(nil), tmp...))
        }
        for i := start; i < len(nums); i++ {
            tmp = append(tmp, nums[i])
            dfs(i+1, num)
            tmp = tmp[:len(tmp)-1]
        }
    }
    for i := 0; i <= len(nums); i++ {
        dfs(0, i)
    }
    return res
}
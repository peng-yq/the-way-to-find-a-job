func permuteUnique(nums []int) [][]int {
    sort.Ints(nums)
    var res [][]int
    var state []int
    selected := make([]bool, len(nums))
    var dfs func(nums []int, selected []bool)
    dfs = func(nums []int, selected []bool) {
        if len(state) == len(nums) {
            res = append(res, append([]int(nil), state...))
            return
        }
        for i := 0; i < len(nums); i++ {
            if i > 0 && nums[i] == nums[i-1] && !selected[i-1] {
                continue
            }
            if (!selected[i]) {
                state = append(state, nums[i])
                selected[i] = true
                dfs(nums, selected)
                selected[i] = false
                state = state[:len(state) - 1]
            }
        }
    }
    dfs(nums, selected)
    return res
}
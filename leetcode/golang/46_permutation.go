func permute(nums []int) [][]int {
    var res [][]int
    var state []int
    selected := make([]bool, len(nums))
    var dfs func(nums []int, selected []bool)
    dfs = func(nums []int, selected []bool) {
        if len(state) == len(nums) {
            res = append(res, append([]int(nil), state...))
        }
        for i := 0; i < len(nums); i++ {
            if selected[i] == false {
                state = append(state, nums[i])
                selected[i] = true
                dfs(nums, selected)
                state = state[:len(state) - 1]
                selected[i] = false
            }
        }
    }
    dfs(nums, selected)
    return res
}


func combinationSum(candidates []int, target int) [][]int {
    sort.Ints(candidates);
    var res [][]int
    var state []int
    var dfs func(candidates []int, target int, start int) 
    dfs = func(candidates []int, target int, start int) {
        if target == 0 {
            res = append(res, append([]int(nil), state...))
            return
        }
        for i := start; i < len(candidates); i++ {
            if target >= candidates[i] {
                state = append(state, candidates[i])
                dfs(candidates, target - candidates[i], i)
                state = state[:len(state) - 1]
            }
        }
    }
    dfs(candidates, target, 0)
    return res
}
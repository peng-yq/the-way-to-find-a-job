func combinationSum2(candidates []int, target int) [][]int {
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
               if i > start && candidates[i] == candidates[i-1] {
                   continue
               }
                state = append(state, candidates[i])
                dfs(candidates, target - candidates[i], i + 1)
                state = state[:len(state) - 1]
            }
        }
    }
    sort.Ints(candidates)
    dfs(candidates, target, 0)
    return res
}
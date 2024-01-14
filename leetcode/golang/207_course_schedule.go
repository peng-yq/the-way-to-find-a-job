func canFinish(numCourses int, prerequisites [][]int) bool {
    inDegree := make([]int, numCourses)
    numMap := make(map[int][]int)
    for i := 0; i < len(prerequisites); i++{
        inDegree[prerequisites[i][0]]++
        numMap[prerequisites[i][1]] = append(numMap[prerequisites[i][1]], prerequisites[i][0])
    }
    var que []int
    for i := 0; i < numCourses; i++ {
        if inDegree[i] == 0 {
            que = append(que, i)
        }
    }
    count := 0
    for len(que) != 0 {
        tmp := que[0]
        que = que[1:]
        count++
        for i := 0; i < len(numMap[tmp]); i++ {
            if inDegree[numMap[tmp][i]] > 0 {
                inDegree[numMap[tmp][i]]--
                if inDegree[numMap[tmp][i]] == 0 {
                    que = append(que, numMap[tmp][i])
                }
            }
        }
    }
    if count == numCourses {
        return true
    }
    return false
}
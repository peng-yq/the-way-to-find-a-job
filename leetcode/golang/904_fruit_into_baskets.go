func totalFruit(fruits []int) int {
    fruit := make(map[int]int)
    res := 0
    for l, r := 0, 0; r < len(fruits); r++ {
        fruit[fruits[r]]++
        if len(fruit) > 2 {
            fruit[fruits[l]] -- 
            if (fruit[fruits[l]] == 0) {
                delete(fruit, fruits[l])
            }
            l++
        }
        res = max(res, r - l + 1)
    }
    return res
}
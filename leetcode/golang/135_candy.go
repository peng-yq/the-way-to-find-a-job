func candy(ratings []int) int {
    var candies []int = make([]int, len(ratings));
    for i := 0; i < len(candies); i++ {
        candies[i] = 1
    }
    for i := 1; i < len(candies); i++ {
        if ratings[i] > ratings[i-1] && candies[i] <= candies[i-1] {
            candies[i] = candies[i-1] + 1
        }
    }
    for i := len(candies) - 1; i > 0; i-- {
        if ratings[i-1] > ratings[i] && candies[i-1] <= candies[i]{
            candies[i-1] = candies[i] + 1
        }
    }
    res := 0;
    for i := 0; i < len(candies); i++ {
        res += candies[i]
    }
    return res
}
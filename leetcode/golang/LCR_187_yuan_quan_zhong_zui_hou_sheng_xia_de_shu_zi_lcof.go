func iceBreakingGame(num int, target int) int {
    if num == 1 {
        return 0
    }
    return (iceBreakingGame(num-1, target) + target) % num
}
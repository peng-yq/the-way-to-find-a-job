func matchPlayersAndTrainers(players []int, trainers []int) int {
    sort.Ints(players)
    sort.Ints(trainers)
    i := 0
    j := 0
    res := 0
    for i < len(players) && j < len(trainers) {
      if players[i] <= trainers[j] {
        i++
        res++
      }
      j++
    }
    return res
  }
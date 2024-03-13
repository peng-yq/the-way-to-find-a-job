func inventoryManagement(stock []int) int {
  vote, x := 0, 0
  for i := 0; i < len(stock); i++ {
      if vote == 0 {
          x = stock[i]
      }
      if x == stock[i] {
          vote += 1
      } else {
          vote -= 1
      }
  }
  return x
}
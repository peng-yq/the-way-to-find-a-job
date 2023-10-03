func twoSum(nums []int, target int) []int {
    for i, x := range nums {
        for j := i + 1; j < len(nums); j++ {
            if x + nums[j] == target {
                return [] int{i, j}
            }
        }
    }
    return nil
}

func twoSumHash(nums []int, target int) []int {
    hashTable := map[int]int{}
    for i, x := range nums{
        if p, ok := hashTable[target - x]; ok{
            return []int {p, i}
        }
        hashTable[x] = i
    }
    return []int{}
 }
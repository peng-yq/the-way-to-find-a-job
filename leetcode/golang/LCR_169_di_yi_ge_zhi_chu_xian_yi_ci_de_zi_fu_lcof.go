func dismantlingAction(arr string) byte {
    charCount := make(map[byte]int)
	for i := 0; i < len(arr); i++ {
		charCount[arr[i]]++
	}
	for i := 0; i < len(arr); i++ {
		if charCount[arr[i]] == 1 {
			return arr[i]
		}
	}
	return ' '
}
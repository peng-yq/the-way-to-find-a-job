func findRepeatDocument(documents []int) int {
    i := 0
    for i < len(documents){
        if documents[i] != i {
            if documents[documents[i]] == documents[i] {
                return documents[i]
            } else {
                documents[i], documents[documents[i]] = documents[documents[i]], documents[i]
            }
        } else {
            i++
        }
    }
    return -1
}

// 原地交换，O(n), O(1)
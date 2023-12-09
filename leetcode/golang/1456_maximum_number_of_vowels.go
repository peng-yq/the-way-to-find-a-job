func max(a int, b int) int {
    if a > b{
        return a
    }
    return b
}

func maxVowels(s string, k int) int {
    vowels := map[byte]bool {
        'a':true,
        'e':true,
        'i':true,
        'o':true,
        'u':true,
    }
    res := 0
    for l, r , tmp :=0, 0, 0; r < len(s); r++ {
        if vowels[s[r]] {
            tmp++
        }
        if r >= l + k {
            if vowels[s[l]] {
                tmp--
            }
            l++
        }
        res = max(res, tmp)
    }
    return res
}
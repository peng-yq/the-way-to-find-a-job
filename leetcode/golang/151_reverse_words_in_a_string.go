func reverseWords(s string) string {
    t := strings.Fields(s)
    for i := 0; i < len(t) / 2; i++ {
        t[i], t[len(t) - 1 - i] = t[len(t) - 1- i], t[i]; 
    }
    new := strings.Join(t, " ")
    return new
}
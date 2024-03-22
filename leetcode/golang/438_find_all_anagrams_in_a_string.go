func isEqual(a, b []int) bool {
	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}

func findAnagrams(s string, p string) []int {
	if len(s) < len(p) {
		return []int{}
	}
	s_check := make([]int, 26)
	p_check := make([]int, 26)
	var res []int
	for i := 0; i < len(p); i++ {
		p_check[p[i]-'a']++
	}
	for i, j := 0, 0; j < len(s); j++ {
		s_check[s[j]-'a']++
		if j-i+1 == len(p) {
			if isEqual(s_check, p_check) {
				res = append(res, i)
			}
			s_check[s[i]-'a']--
			i++
		}
	}
	return res
}
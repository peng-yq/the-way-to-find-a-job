func addStrings(num1 string, num2 string) string {
	i, j := len(num1)-1, len(num2)-1
	var carry int
	var res strings.Builder

	for i >= 0 || j >= 0 || carry > 0 {
		var digit1, digit2 int
		if i >= 0 {
			digit1 = int(num1[i] - '0')
		}
		if j >= 0 {
			digit2 = int(num2[j] - '0')
		}
		sum := digit1 + digit2 + carry
		carry = sum / 10
		sum = sum % 10
		res.WriteByte(byte('0' + sum))
		i--
		j--
	}

	return reverseString(res.String())
}

func reverseString(s string) string {
	runes := []rune(s)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}
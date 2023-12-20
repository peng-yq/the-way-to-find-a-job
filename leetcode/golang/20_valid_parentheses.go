func isValid(s string) bool {
    stack := []byte{}
    for i := 0; i < len(s); i++ {
        if (len(stack) == 0 && (s[i] == ')' || s[i] == ']' || s[i] == '}')) {
            return false
        }
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack = append(stack, s[i])
        } else if (stack[len(stack) - 1] == '(' && s[i] == ')' || stack[len(stack) - 1] == '[' && s[i] == ']' || stack[len(stack) - 1] == '{' && s[i] == '}') {
            stack = stack[: len(stack) - 1]
        } else {
            return false;
        }   
    }
    return len(stack) == 0
}
func dynamicPassword(password string, target int) string {
    return password[target:len(password)] + password[:target]
}
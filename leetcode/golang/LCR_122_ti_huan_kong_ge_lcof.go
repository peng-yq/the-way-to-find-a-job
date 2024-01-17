func pathEncryption(path string) string {
    return strings.Replace(path, ".", " ", -1)
}
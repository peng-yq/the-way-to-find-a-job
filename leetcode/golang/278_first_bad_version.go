func firstBadVersion(n int) int {
    l, r, i := 1, n, 0;
    for l <= r {
        i = l - (l - r) / 2
        if !isBadVersion(i) {
            l = i + 1
        } else if isBadVersion(i) && isBadVersion(i - 1) {
            r = i - 1
        } else {
            return i
        }
    }
    return 0;
}
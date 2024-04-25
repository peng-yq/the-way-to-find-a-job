// https://leetcode.cn/problems/total-distance-traveled

func distanceTraveled(mainTank int, additionalTank int) int {
    res, count := 0, 0
    for mainTank != 0 {
        res += 10
        count++
        mainTank--
        if count % 5 == 0 && additionalTank > 0{
            mainTank++
            additionalTank--
        }
    }
    return res
}

// 模拟，时间复杂度为O(n)
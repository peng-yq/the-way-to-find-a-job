package main

import "fmt"

func main() {
    var n int
    for {
        _, err := fmt.Scanf("%d", &n)
        if err != nil {
            break
        }
        for n > 0 {
            var m int
            sum, tmp := 0, 0
            _, err := fmt.Scanf("%d", &m)
            if err != nil {
                break
            }
            for m > 0 {
                _, err := fmt.Scanf("%d", &tmp)
                if err != nil {
                    break
                }
                sum += tmp 
                m--
            }
            fmt.Println(sum)
            if (n != 1) {
                fmt.Println()
            }
            n--
        }
    }
}
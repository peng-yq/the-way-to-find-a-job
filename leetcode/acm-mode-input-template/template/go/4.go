package main

import "fmt"

func main() {
    var n int
    for {
        _, err := fmt.Scanf("%d", &n)
        if err != nil || n == 0 {
            break   
        }
        sum, a := 0, 0
        for n > 0 {
            _, err := fmt.Scanf("%d", &a)
            if err != nil {
                break
            }
            sum += a
            n--
        }
        fmt.Println(sum)
    }
}
package main

import "fmt"

func main() {
    var n, a, b int
    for {
        _, err := fmt.Scanf("%d", &n)
        if err != nil {
            break
        }
        for n > 0 {
            _, err := fmt.Scanf("%d %d", &a, &b)
            if err != nil {
                break
            } 
            fmt.Println(a + b)
            n--
        }
    }
}
package main

import "fmt"

func main() {
    var a int 
    var b int
    for {
        _, err := fmt.Scanf("%d %d", &a, &b)
        if err != nil {
            break
        }
        fmt.Println(a + b)
    }
}
package main

import (
    "fmt"
    "unicode"
    "strings"
    "os"
    "strconv"
)

func check(e error) {
    if e != nil {
        panic(e)
    }
}

func main(){
    data, err := os.ReadFile("./calibration.txt")
    check(err)
    temp := strings.Split(string(data), "\n")
    var s []int
    for _, element2 := range temp{
        var t string
        element := string(element2)
        for _, char := range element{
            if unicode.IsDigit(char){
                 t += string(char)
                break
            }
        }
        for i := len(element)-1; i>=0; i--{
            if unicode.IsDigit(rune(element[i])){
                t += string(element[i])
               break
           }
        }
        if t == "" {
            continue
        }

        newNumber, err := strconv.Atoi(t)
       fmt.Println(t)
        check(err)
        s = append(s, newNumber)
    }
    fmt.Println(s)

    var res int

    for _, number := range s {
        res += number
    }
    fmt.Println(res)
}

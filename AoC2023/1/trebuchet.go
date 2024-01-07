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
    digits := []string{"zero", "one" ,"two" ,"three" ,"four" ,"five" ,"six" ,"seven" ,"eight" ,"nine"}
    for _, element2 := range temp{
        var bestIndex int = 10000
        var lastIndex int = -1
        numberAtBestIndex := 0
        numberAtLastIndex := 0

        for i, element := range digits{
            index := strings.Index(element2, element)
                fmt.Println("Found in position:", element, index, element2)
                fmt.Println("Best index until now: ", bestIndex)

            if(index < bestIndex && index >= 0){
                bestIndex = index
                numberAtBestIndex = i
                fmt.Println("Found better index:",numberAtBestIndex)
                fmt.Println()
            }
            index = strings.LastIndex(element2, element)
            if(index > lastIndex && index >= 0){
                lastIndex = index
                numberAtLastIndex = i
                fmt.Println("Found last index:",numberAtLastIndex)
                fmt.Println()
            }
        }

        var t string
        element := string(element2)
        fmt.Println(element)
        for i, char := range element{
            if unicode.IsDigit(char){
                if i <= bestIndex {
                    t = string(char)
                    fmt.Println("T is currently like so: ", t, "by adding", char)
                    break
                }else{
                    fmt.Println("Number at best position: ", numberAtBestIndex)
                    t = strconv.Itoa(numberAtBestIndex)
                    fmt.Println("T is currently like so: ", t, "by adding", strconv.Itoa(numberAtBestIndex))
                    break
                }
            }
        }
        for i := len(element)-1; i>=0; i--{
            if unicode.IsDigit(rune(element[i])){
                if i > lastIndex{
                    t += string(element[i])
                    fmt.Println("T is currently like so: ", t, "by adding", string(element[i]))
                    break
                } else{
                    t += strconv.Itoa(numberAtLastIndex)
                    fmt.Println("T is currently like so: ", t, "by adding", strconv.Itoa(numberAtLastIndex))
                    break
                }
           }
        }
        if t == "" {
            continue
        }

        newNumber, err := strconv.Atoi(t)
        fmt.Println("Final number found: ",t)
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

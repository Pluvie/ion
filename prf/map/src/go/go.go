package main

import (
  "fmt"
)

func insert() {
  m := make(map[int]int)

  for i := 0; i < 1000000; i++ {
    m[i] = i;
  }

  fmt.Println("Done: ", m[999999])
}

func main() {
  insert()
}

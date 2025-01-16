package main

import (
  "fmt"
)

func insert() {
  m := make(map[int]int)

  for i := 0; i < 10000; i++ {
    for j := 0; j < 1000; j++ {
      m[j] = i;
    }
  }

  fmt.Println("Done: ", m[999])
}

func main() {
  insert()
}

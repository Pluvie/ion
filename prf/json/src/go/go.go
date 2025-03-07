package main

import (
  "fmt"
  "os"
  "encoding/json"
)

type Data struct {
  Users []User    `json:"users"`
}

type User struct {
  Name  string    `json:"name"`
  Age   int       `json:"age"`
  Roles []string  `json:"roles"`
}

func main() {
  filepath := "decode.json"
  fileContent, err := os.ReadFile(filepath)
  if err != nil {
    panic(err)
  }

  var data Data
  err = json.Unmarshal(fileContent, &data)
  if err != nil {
    panic(err)
  }

  fmt.Println("Done: ", data.Users[0])
  fmt.Println("Done: ", data.Users[99999])
}

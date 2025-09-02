package main

import (
	"fmt"
	"os"
  "encoding/json"
)

type Coordinate struct {
	X, Y, Z float64
}

type TestStruct struct {
	Coordinates []Coordinate
}

func (t TestStruct) Average() Coordinate {
	var coord Coordinate
	for i := range t.Coordinates {
		coord.X += t.Coordinates[i].X
		coord.Y += t.Coordinates[i].Y
		coord.Z += t.Coordinates[i].Z
	}
	count := float64(len(t.Coordinates))
	coord.X /= count
	coord.Y /= count
	coord.Z /= count
	return coord
}

func verify(calc func([]byte) (Coordinate, error)) error {
	right := Coordinate{2.0, 0.5, 0.25}
	for _, v := range []string{
		`{"coordinates":[{"x":2.0,"y":0.5,"z":0.25}]}`,
		`{"coordinates":[{"y":0.5,"x":2.0,"z":0.25}]}`} {
		left, err := calc([]byte(v))
		if err != nil {
			return err
		}
		if left != right {
			return fmt.Errorf("%+v != %+v\n", left, right)
		}
	}
	return nil
}

func Run(name string, calc func([]byte) (Coordinate, error)) error {
	err := verify(calc)
	if err != nil {
		return err
	}

	data, err := os.ReadFile("exe/benchmark.json")
	if err != nil {
		return err
	}
	var result Coordinate
	result, err = calc(data)
	if err != nil {
		return err
	}
	fmt.Printf("%+v\n", result)
	return nil
}

func calc(bytes []byte) (Coordinate, error) {
  obj := TestStruct{}
  err := json.Unmarshal(bytes, &obj)
  if err != nil {
    return Coordinate{}, err
  }
  return obj.Average(), nil
}

func main() {
  err := Run("", calc)
  if err != nil {
    panic(err)
  }
}

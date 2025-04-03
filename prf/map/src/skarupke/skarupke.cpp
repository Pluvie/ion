#include <iostream>
#include <unordered_map>
#include "skarupke.hpp"
#include "numbers.hpp"

void insert () {
  ska::flat_hash_map<int, int> map = {};

  for (int i = 0; i < 1000000; i++) {
      map[i] = i;
  }

  std::cout << "Done: " << map[999999] << "\n";
}

void lookup() {
  ska::flat_hash_map<int, int> map;

  int length = sizeof(numbers) / sizeof(*numbers);
  for (int i = 0; i < length; i++) {
    map[numbers[i]] = i;
  }

  int v;
  for (int j = 0; j < 10000; j++) {
    for (int i = 0; i < length; i++) {
      v = map[numbers[i]];
    }
  }

  std::cout << "Done: " << v << std::endl;
}

int main() {
  //insert();
  lookup();
  return 0;
}

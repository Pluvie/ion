#include <iostream>
#include "absl/container/flat_hash_map.h"
#include "numbers.hpp"

void insert() {
  absl::flat_hash_map<int, int> map;

  for (int i = 0; i < 1000000; i++) {
    map[i] = i;
  }

  std::cout << "Done: " << map[999999] << std::endl;
}

void lookup() {
  absl::flat_hash_map<int, int> map;

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

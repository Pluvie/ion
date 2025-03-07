#include <iostream>
#include "absl/container/flat_hash_map.h"

void insert() {
  absl::flat_hash_map<int, int> map;

  for (int i = 0; i < 1000000; i++) {
    map[i] = i;
  }

  std::cout << "Done: " << map[999999] << std::endl;
}

int main() {
  insert();
  return 0;
}

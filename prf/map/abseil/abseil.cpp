#include <iostream>
#include "absl/container/flat_hash_map.h"

void insert() {
  absl::flat_hash_map<int, int> map;

  for (int i = 0; i < 10000; i++) {
    for (int j = 0; j < 1000; j++) {
      map[j] = i;
    }
  }

  std::cout << "Done: " << map[999] << std::endl;
}

int main() {
  insert();
  return 0;
}

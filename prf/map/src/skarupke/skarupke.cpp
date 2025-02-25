#include <iostream>
#include <unordered_map>
#include "skarupke.hpp"
#include <string>

void insert () {
  ska::flat_hash_map<int, int> map = {};

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 10000; j++) {
      map[j] = i;
    }
  }

  std::cout << "Done: " << map[999] << "\n";
}

int main() {
  insert();
  return 0;
}

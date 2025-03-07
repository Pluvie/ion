#include <iostream>
#include <unordered_map>
#include "skarupke.hpp"
#include <string>

void insert () {
  ska::flat_hash_map<int, int> map = {};

  for (int i = 0; i < 1000000; i++) {
      map[i] = i;
  }

  std::cout << "Done: " << map[999999] << "\n";
}

int main() {
  insert();
  return 0;
}

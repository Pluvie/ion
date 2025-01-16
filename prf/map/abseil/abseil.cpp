#include <iostream>
#include "absl/container/flat_hash_map.h"

int main() {
  absl::flat_hash_map<std::string, int> my_map;

  // Inserting elements
  my_map["apple"] = 1;
  my_map["banana"] = 2;
  my_map["cherry"] = 3;

  // Accessing elements
  std::cout << "apple: " << my_map["apple"] << std::endl;  // Output: apple: 1
  std::cout << "banana: " << my_map["banana"] << std::endl;  // Output: banana: 2
  std::cout << "cherry: " << my_map["cherry"] << std::endl;  // Output: cherry: 3

  // Checking if a key exists
  if (my_map.contains("banana")) {
    std::cout << "banana exists in the map" << std::endl;
  }

  return 0;
}

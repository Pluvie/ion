#include <iostream>
#include <unordered_map>
#include "flat_hash_map.hpp"
#include <string>

int main() {
    // Create an unordered_map of three strings (that map to strings)
    std::unordered_map<std::string, std::string> u = {
        {"RED", "#FF0000"},
        {"GREEN", "#00FF00"},
        {"BLUE", "#0000FF"}
    };

    // Helper lambda function to print key-value pairs
    auto print_key_value = [](const auto& key, const auto& value) {
        std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };

    // Iterate and print key-value pairs of unordered_map, being explicit with their types
    std::cout << "Iterate and print key-value pairs of unordered_map, being\n"
                 "explicit with their types:\n";
    for (const std::pair<std::string, std::string>& n : u)
        print_key_value(n.first, n.second);

    // Iterate and print key-value pairs using C++17 structured binding
    std::cout << "\nIterate and print key-value pairs using C++17 structured binding:\n";
    for (const auto& [key, value] : u)
        print_key_value(key, value);

    // Add two new entries to the unordered_map
    u["BLACK"] = "#000000";
    u["WHITE"] = "#FFFFFF";

    // Output values by key
    std::cout << "\nOutput values by key:\n"
                 "The HEX of color RED is:[" << u["RED"] << "]\n"
                 "The HEX of color BLACK is:[" << u["BLACK"] << "]\n\n";

    // Use operator[] with non-existent key to insert a new key-value pair
    print_key_value("new_key", u["new_key"]);

    // Iterate and print key-value pairs, using `auto`
    std::cout << "\nIterate and print key-value pairs, using `auto`;\n"
                 "new_key is now one of the keys in the map:\n";
    for (const auto& n : u)
        print_key_value(n.first, n.second);

    return 0;
}

#include <iostream>
#include "simdjson.h"

using namespace simdjson;

int main(void) {
    ondemand::parser parser;
    padded_string json = padded_string::load("exe/decode.json");
    ondemand::document data = parser.iterate(json);
    ondemand::array users;
    auto error = data.find_field("users").get_array().get(users);

    ondemand::object user;
    user = users.at(0);
    std::cout << "Done: " << user["name"] << std::endl;
    users.reset();
    user = users.at(9999999);
    std::cout << "Done: " << user["name"] << std::endl;
    users.reset();
    user = users.at(10000000);
    std::cout << "Done: " << user["name"] << std::endl;
}

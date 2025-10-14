#include "str_equal.h"

spec( str_equal ) {
  argument(str v);
  argument(str u);

  when("both strings contain a nullptr") {
    v = (str) { nullptr, 17 };
    u = (str) { nullptr, 7 };
    bool result = str_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the first string contains a nullptr") {
    v = (str) { nullptr, 17 };
    u = (str) { "abc", 3 };
    bool result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the second string contains a nullptr") {
    v = (str) { "abc", 3 };
    u = (str) { nullptr, 17 };
    bool result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("both strings have the same chars, but have different length") {
    v = (str) { "abc", 3 };
    u = (str) { "abc", 17 };
    bool result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the strings have different chars, but have the same length") {
    v = (str) { "abc", 3 };
    u = (str) { "def", 3 };
    bool result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the strings have the same chars, and have the same length") {
    v = (str) { "abc", 3 };
    u = (str) { "abc", 3 };
    bool result = str_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();
}

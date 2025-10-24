#include "str_compare.h"

spec( str_compare ) {
  argument(str v);
  argument(str u);

  when("both strings contain a nullptr") {
    v = (str) { nullptr, 17 };
    u = (str) { nullptr, 7 };
    int result = str_compare(v, u);

    must("return 0");
      verify(result == 0);

    success();
  } end();

  when("the first string contains a nullptr") {
    v = (str) { nullptr, 17 };
    u = (str) { "abc", 3 };
    int result = str_compare(v, u);

    must("return -1");
      verify(result == -1);

    success();
  } end();

  when("the second string contains a nullptr") {
    v = (str) { "abc", 3 };
    u = (str) { nullptr, 17 };
    int result = str_compare(v, u);

    must("return 1");
      verify(result == 1);

    success();
  } end();

  when("both strings have the same chars, but the first has greater length") {
    v = (str) { "abc", 17 };
    u = (str) { "abc", 3 };
    int result = str_compare(v, u);

    must("return 1");
      verify(result == 1);

    success();
  } end();

  when("both strings have the same chars, but the second has greater length") {
    v = (str) { "abc", 3 };
    u = (str) { "abc", 17 };
    int result = str_compare(v, u);

    must("return -1");
      verify(result == -1);

    success();
  } end();

  when("the strings have different chars, but have the same length") {
    v = (str) { "def", 3 };
    u = (str) { "abc", 3 };
    int result = str_compare(v, u);

    must("return a positive value");
      verify(result > 0);

    success();
  } end();

  when("the strings have different chars, but have the same length") {
    v = (str) { "abc", 3 };
    u = (str) { "def", 3 };
    int result = str_compare(v, u);

    must("return a negative value");
      verify(result < 0);

    success();
  } end();

  when("the strings have the same chars, and have the same length") {
    v = (str) { "abc", 3 };
    u = (str) { "abc", 3 };
    int result = str_compare(v, u);

    must("return 0");
      verify(result == 0);

    success();
  } end();
}

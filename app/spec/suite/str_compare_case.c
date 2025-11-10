#include "str_compare_case.h"

spec( str_compare_case ) {
  argument(str v);
  argument(str u);
  returns(int result);

  when("both strings contain a nullptr") {
    v.chars = nullptr; v.length = 17;
    u.chars = nullptr; u.length = 7;
    result = str_compare_case(v, u);

    must("return 0");
      verify(result == 0);

    success();
  } end();

  when("the first string contains a nullptr") {
    v.chars = nullptr; v.length = 17;
    u.chars = "abc"; u.length = 3;
    result = str_compare_case(v, u);

    must("return -1");
      verify(result == -1);

    success();
  } end();

  when("the second string contains a nullptr") {
    v.chars = "abc"; v.length = 3;
    u.chars = nullptr; u.length = 17;
    result = str_compare_case(v, u);

    must("return 1");
      verify(result == 1);

    success();
  } end();

  when("both strings have the same chars, but the first has greater length") {
    v.chars = "abc"; v.length = 17;
    u.chars = "abc"; u.length = 3;
    result = str_compare_case(v, u);

    must("return 1");
      verify(result == 1);

    success();
  } end();

  when("both strings have the same chars, but the second has greater length") {
    v.chars = "abc"; v.length = 3;
    u.chars = "abc"; u.length = 17;
    result = str_compare_case(v, u);

    must("return -1");
      verify(result == -1);

    success();
  } end();

  when("the strings have different chars, but have the same length") {
    v.chars = "def"; v.length = 3;
    u.chars = "abc"; u.length = 3;
    result = str_compare_case(v, u);

    must("return a positive value");
      verify(result > 0);

    success();
  } end();

  when("the strings have different chars, but have the same length") {
    v.chars = "abc"; v.length = 3;
    u.chars = "def"; u.length = 3;
    result = str_compare_case(v, u);

    must("return a negative value");
      verify(result < 0);

    success();
  } end();

  when("the strings have the same chars, and have the same length") {
    v.chars = "abc"; v.length = 3;
    u.chars = "abc"; u.length = 3;
    result = str_compare_case(v, u);

    must("return 0");
      verify(result == 0);

    success();
  } end();

  when("the strings have the same case insensitive chars, and have the same length") {
    v.chars = "abC"; v.length = 3;
    u.chars = "aBc"; u.length = 3;
    result = str_compare_case(v, u);

    must("return 0");
      verify(result == 0);

    success();
  } end();
}

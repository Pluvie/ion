#include "str_equal.h"

spec( str_equal ) {
  argument(str v);
  argument(str u);
  returns(bool result);

  when("both strings contain a nullptr") {
    v.chars = nullptr; v.length = 17;
    u.chars = nullptr; u.length = 7;
    result = str_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the first string contains a nullptr") {
    v.chars = nullptr; v.length = 17;
    u.chars = "abc"; u.length = 3;
    result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the second string contains a nullptr") {
    v.chars = "abc"; v.length = 3;
    u.chars = nullptr; u.length = 17;
    result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("both strings have the same chars, but have different length") {
    v.chars = "abc"; v.length = 3;
    u.chars = "abc"; u.length = 17;
    result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the strings have different chars, but have the same length") {
    v.chars = "abc"; v.length = 3;
    u.chars = "def"; u.length = 3;
    result = str_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the strings have the same chars, and have the same length") {
    v.chars = "abc"; v.length = 3;
    u.chars = "abc"; u.length = 3;
    result = str_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();
}

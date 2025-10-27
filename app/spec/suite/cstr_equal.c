#include "cstr_equal.h"

spec( cstr_equal ) {
  argument(const cstr v);
  argument(const cstr u);
  returns(bool result);

  when("both strings are nullptr") {
    v = nullptr;
    u = nullptr;
    result = cstr_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the first string is nullptr") {
    v = nullptr;
    u = "abc";
    result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the second string is nullptr") {
    v = "abc";
    u = nullptr;
    result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the strings have different chars") {
    v = "abc";
    u = "def";
    result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("both strings have the same chars") {
    v = "abc";
    u = "abc";
    result = cstr_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("both strings have the same initial chars") {
    v = "abc";
    u = "abcdef";
    result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();
}

#include "cstr_equal.h"

spec( cstr_equal ) {
  argument(const char* v);
  argument(const char* u);

  when("both strings are nullptr") {
    v = nullptr;
    u = nullptr;
    bool result = cstr_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the first string is nullptr") {
    v = nullptr;
    u = "abc";
    bool result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the second string is nullptr") {
    v = "abc";
    u = nullptr;
    bool result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the strings have different chars") {
    v = "abc";
    u = "def";
    bool result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("both strings have the same chars") {
    v = "abc";
    u = "abc";
    bool result = cstr_equal(v, u);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("both strings have the same initial chars") {
    v = "abc";
    u = "abcdef";
    bool result = cstr_equal(v, u);

    must("return false");
      verify(result == false);

    success();
  } end();
}

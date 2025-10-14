#include "cstr_compare.h"

spec( cstr_compare ) {
  argument(const char* v);
  argument(const char* u);

  when("both strings are nullptr") {
    v = nullptr;
    u = nullptr;
    int result = cstr_compare(v, u);

    must("return 0");
      verify(result == 0);

    success();
  } end();

  when("the second string is nullptr") {
    v = "abc";
    u = nullptr;
    int result = cstr_compare(v, u);

    must("return a positive value");
      verify(result > 0);

    success();
  } end();

  when("the first string is nullptr") {
    v = nullptr;
    u = "abc";
    int result = cstr_compare(v, u);

    must("return a negative value matching the first char of the second string");
      verify(result < 0);

    success();
  } end();

  when("both string have the same chars") {
    v = "abc";
    u = "abc";
    int result = cstr_compare(v, u);

    must("return zero");
      verify(result == 0);

    success();
  } end();

  when("the first string has chars whose value is greater than the second string") {
    v = "def";
    u = "abc";
    int result = cstr_compare(v, u);

    must("return a positive value");
      verify(result > 0);

    success();
  } end();

  when("the first string has chars whose value is lesser than the second string") {
    v = "abc";
    u = "def";
    int result = cstr_compare(v, u);

    must("return a negative value");
      verify(result < 0);

    success();
  } end();
}

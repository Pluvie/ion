#include "memory_equal.h"

spec( memory_equal ) {
  argument(const void* v);
  argument(const void* u);
  argument(uint length);
  returns(bool result);

  length = 3;

  when("both values are nullptr") {
    v = nullptr;
    u = nullptr;
    result = memory_equal(v, u, length);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the second value is nullptr") {
    v = "abc";
    u = nullptr;
    result = memory_equal(v, u, length);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the first value is nullptr") {
    v = nullptr;
    u = "abc";
    result = memory_equal(v, u, length);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("both values have the same bytes") {
    v = "abc";
    u = "abc";
    result = memory_equal(v, u, length);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the values have different bytes") {
    v = "def";
    u = "abc";
    result = memory_equal(v, u, length);

    must("return false");
      verify(result == false);

    success();
  } end();
}

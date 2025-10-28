#include "memory_compare.h"

spec( memory_compare ) {
  argument(const void* v);
  argument(const void* u);
  argument(uint length);
  returns(int result);

  length = 3;

  when("both values are nullptr") {
    v = nullptr;
    u = nullptr;
    result = memory_compare(v, u, length);

    must("return 0");
      verify(result == 0);

    success();
  } end();

  when("the second value is nullptr") {
    v = "abc";
    u = nullptr;
    result = memory_compare(v, u, length);

    must("return a positive value");
      verify(result > 0);

    success();
  } end();

  when("the first value is nullptr") {
    v = nullptr;
    u = "abc";
    result = memory_compare(v, u, length);

    must("return a negative value");
      verify(result < 0);

    success();
  } end();

  when("both values have the same bytes") {
    v = "abc";
    u = "abc";
    result = memory_compare(v, u, length);

    must("return zero");
      verify(result == 0);

    success();
  } end();

  when("the first value has bytes whose value is greater than the second value") {
    v = "def";
    u = "abc";
    result = memory_compare(v, u, length);

    must("return a positive value");
      verify(result > 0);

    success();
  } end();

  when("the first value has bytes whose value is lesser than the second value") {
    v = "abc";
    u = "def";
    result = memory_compare(v, u, length);

    must("return a negative value");
      verify(result < 0);

    success();
  } end();
}

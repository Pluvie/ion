#include "str_to_int.h"

spec( str_to_int ) {
  argument(str* source);

  precondition("a valid source string");
  precondition("the source string must have at least one padding character at the end");
    #define preconditions \
      source = allocator_push(spec_allocator, sizeof(str));

  when("the source string contains a valid number") {
    apply(preconditions);
    *source = string("17788");
    int result = str_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17788 == result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part") {
    apply(preconditions);
    *source = string("17788.44");
    int result = str_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17788 == result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part and exponent") {
    apply(preconditions);
    *source = string("17788.44e-3");
    int result = str_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17 == result);

    success();
  } end();

  when("the source string contains a valid number with an exponent") {
    apply(preconditions);
    *source = string("17788e+2");
    int result = str_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 1778800 == result);

    success();
  } end();

  when("the source string contains a valid number followed by other characters") {
    apply(preconditions);
    *source = string("17aaa:0");
    int result = str_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17 == result);

    success();
  } end();

  when("the source string contains an overflowing number") {
    apply(preconditions);
    *source = string("9" INT_MAXNUM);
    int result = str_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(cstr_equal(failure.message, "number overflow"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();

  when("the source string contains a very big overflowing number") {
    apply(preconditions);
    *source = string("9" INT_MAXNUM INT_MAXNUM);
    int result = str_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(cstr_equal(failure.message, "number overflow"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();

  when("the source string contains a valid number and an overflowing exponent") {
    apply(preconditions);
    *source = string("777e+100");
    int result = str_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(cstr_equal(failure.message, "exponent overflow"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();

  when("the source string does not contain a valid number") {
    apply(preconditions);
    *source = string("aaa:0");
    int result = str_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(cstr_equal(failure.message, "expected a number"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();
}

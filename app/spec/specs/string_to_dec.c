#include "string_to_dec.h"

spec( string_to_dec ) {
  argument(string* source);

  precondition("a valid source string");
  precondition("the source string must have at least one padding character at the end");
    #define preconditions \
      source = allocator_push(spec_allocator, sizeof(string));

  when("the source string contains a valid number") {
    apply(preconditions);
    *source = string("17788");
    dec result = string_to_dec(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its decimal equivalent");
      verify((dec) 17788 == result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part") {
    apply(preconditions);
    *source = string("17788.44");
    dec result = string_to_dec(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its decimal equivalent");
      verify((dec) 17788.44 == result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part and exponent") {
    apply(preconditions);
    *source = string("17788.44e-3");
    dec result = string_to_dec(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its decimal equivalent");
      verify((dec) 17.78844 == result);

    success();
  } end();

  when("the source string contains a valid number with an exponent") {
    apply(preconditions);
    *source = string("17788e+2");
    dec result = string_to_dec(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its decimal equivalent");
      verify((dec) 1778800 == result);

    success();
  } end();

  when("the source string contains a valid number with a big exponent") {
    apply(preconditions);
    *source = string("17788.99e+159");
    dec result = string_to_dec(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its decimal equivalent");
      verify((dec) 17788.99 == (result / 1e159));

    success();
  } end();

  when("the source string contains a valid number with a small exponent") {
    apply(preconditions);
    *source = string("17788.99e-199");
    dec result = string_to_dec(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its decimal equivalent");
      verify((dec) 17788.99 == (result * 1e199));

    success();
  } end();

  when("the source string contains a valid number followed by other characters") {
    apply(preconditions);
    *source = string("17aaa:0");
    dec result = string_to_dec(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its decimal equivalent");
      verify((dec) 17 == result);

    success();
  } end();

  when("the source string contains an overflowing number") {
    apply(preconditions);
    *source = string("9.223372036854775936");
    dec result = string_to_dec(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(streq(failure.message, "number overflow"));

    must("return 0");
      verify((dec) 0 == result);

    success();
  } end();

  when("the source string contains a double overflowing number") {
    apply(preconditions);
    *source = string("9.223372036854775939223372036854775936");
    dec result = string_to_dec(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(streq(failure.message, "number overflow"));

    must("return 0");
      verify((dec) 0 == result);

    success();
  } end();

  when("the source string contains a valid number and an overflowing exponent") {
    apply(preconditions);
    *source = string("777e+400");
    dec result = string_to_dec(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(streq(failure.message, "exponent overflow"));

    must("return 0");
      verify((dec) 0 == result);

    success();
  } end();

  when("the source string does not contain a valid number") {
    apply(preconditions);
    *source = string("aaa:0");
    dec result = string_to_dec(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(streq(failure.message, "expected a number"));

    must("return 0");
      verify((dec) 0 == result);

    success();
  } end();
}

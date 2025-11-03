#include "str_to_dec.h"

spec( str_to_dec ) {
  argument(str* source);
  argument(dec* result);
  returns(enum result parse_result);

  precondition("a valid source string");
  precondition("a valid result decimal pointer");
  precondition("the source string must have at least one padding character at the end");
    #define preconditions \
      dec result_holder = 0; result = &result_holder; \
      source = &source_string;

  when("the source string contains a valid number") {
    str source_string = str("17788");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its decimal equivalent");
      verify((dec) 17788 == *result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part") {
    str source_string = str("17788.44");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its decimal equivalent");
      verify((dec) 17788.44 == *result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part and exponent") {
    str source_string = str("17788.44e-3");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its decimal equivalent");
      verify((dec) 17.78844 == *result);

    success();
  } end();

  when("the source string contains a valid number with an exponent") {
    str source_string = str("17788e+2");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its decimal equivalent");
      verify((dec) 1778800 == *result);

    success();
  } end();

  when("the source string contains a valid number with a big exponent") {
    str source_string = str("17788.99e+159");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its decimal equivalent");
      verify((dec) 17788.99 == (*result / 1e159));

    success();
  } end();

  when("the source string contains a valid number with a small exponent") {
    str source_string = str("17788.99e-199");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its decimal equivalent");
      verify((dec) 17788.99 == (*result * 1e199));

    success();
  } end();

  when("the source string contains a valid number followed by other characters") {
    str source_string = str("17aaa:0");
    cstr source_begin = source_string.chars;
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source until the first invalid char");
      verify(*source->chars == 'a');
      verify(source->chars - source_begin == 2);

    must("return its decimal equivalent");
      verify((dec) 17 == *result);

    success();
  } end();

  when("the source string contains an overflowing number") {
    str source_string = str("9.223372036854775936");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "number overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a very big overflowing number") {
    str source_string = str("9.223372036854775939223372036854775936");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "number overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a valid number and an overflowing exponent") {
    str source_string = str("777e+9999");
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "exponent overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string does not contain a valid number") {
    str source_string = str("aaa:0");
    cstr source_begin = source_string.chars;
    apply(preconditions);
    parse_result = str_to_dec(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "invalid number"));

    must("consume the source until the first valid char");
      verify(*source->chars == 'a');
      verify(source->chars - source_begin == 0);

    success();
  } end();
}

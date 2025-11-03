#include "str_to_int.h"

spec( str_to_int ) {
  argument(str* source);
  argument(int* result);
  returns(enum result parse_result);

  precondition("a valid source string");
  precondition("a valid result integer pointer");
  precondition("the source string must have at least one padding character at the end");
    #define preconditions \
      int result_holder = 0; result = &result_holder; \
      source = &source_string;

  when("the source string contains a valid number") {
    str source_string = str("17788");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its integer equivalent");
      verify((int) 17788 == *result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part") {
    str source_string = str("17788.44");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its integer equivalent");
      verify((int) 17788 == *result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part and exponent") {
    str source_string = str("17788.44e-3");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its integer equivalent");
      verify((int) 17 == *result);

    success();
  } end();

  when("the source string contains a valid number with an exponent") {
    str source_string = str("17788e+2");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its integer equivalent");
      verify((int) 1778800 == *result);

    success();
  } end();

  when("the source string contains a valid number followed by other characters") {
    str source_string = str("17aaa:0");
    cstr source_begin = source_string.chars;
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source until the first invalid char");
      verify(*source->chars == 'a');
      verify(source->chars - source_begin == 2);

    must("return its integer equivalent");
      verify((int) 17 == *result);

    success();
  } end();

  when("the source string contains an overflowing number") {
    str source_string = str("9" INT_MAXNUM);
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "number overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a very big overflowing number") {
    str source_string = str("9" INT_MAXNUM INT_MAXNUM);
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "number overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains the maximum representable number") {
    str source_string = str(INT_MAXNUM);
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its integer equivalent");
      verify((int) (((uint) -1) >> 1) == *result);

    success();
  } end();

  when("the source string contains a just by one overflowing number") {
    #if   INT_BITSIZE == 32
    str source_string = str("2147483648"); /* INT_MAXNUM + 1 */
    #elif INT_BITSIZE == 64
    str source_string = str("9223372036854775808"); /* INT_MAXNUM + 1 */
    #endif
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "number overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a valid number and a valid exponent") {
    str source_string = str("777e+5");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its integer equivalent");
      verify((int) 777*100000 == *result);

    success();
  } end();

  when("the source string contains a valid number and a valid exponent resulting "\
       "just below the maximum representable number") {
    #if   INT_BITSIZE == 32
    str source_string = str("21474836e2"); /* 2147483600 < INT_MAXNUM */
    #elif INT_BITSIZE == 64
    str source_string = str("92233720368547758e2"); /* 9223372036854775800 < INT_MAXNUM */
    #endif
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("successfully parse the source string");
      verify(parse_result == Success);

    must("consume the source");
      verify(*source->chars == 0);

    must("return its integer equivalent");
      #if   INT_BITSIZE == 32
      verify((int) 2147483600 == *result);
      #elif INT_BITSIZE == 64
      verify((int) 9223372036854775800 == *result);
      #endif

    success();
  } end();

  when("the source string contains a valid number and an overflowing exponent") {
    str source_string = str("777e+9999");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "exponent overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a valid number and an exponent which would " \
       "overflow by a large margin") {
    str source_string = str("777e+100");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "number overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a valid number and an exponent which would "\
       "overflow by a tiny margin") {
    #if   INT_BITSIZE == 32
    str source_string = str("21474837e2"); /* 2147483700 > INT_MAXNUM */
    #elif INT_BITSIZE == 64
    str source_string = str("92233720368547759e2"); /* 9223372036854775900 > INT_MAXNUM */
    #endif
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail to parse the source string");
      verify(parse_result == Failure);

    must("set the failure message");
      verify(cstr_equal(failure.message, "number overflow"));

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string does not contain a valid number") {
    str source_string = str("aaa:0");
    cstr source_begin = source_string.chars;
    apply(preconditions);
    parse_result = str_to_int(source, result);

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

#include "str_to_int.h"

spec( str_to_int ) {
  argument(str* source);
  argument(int* result);
  returns(enum parse_number_results parse_result);

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

    must("not fail");
      verify(parse_result == Parse_Number_Success);

    must("return its integer equivalent");
      verify((int) 17788 == *result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part") {
    str source_string = str("17788.44");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("not fail");
      verify(parse_result == Parse_Number_Success);

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

    must("not fail");
      verify(parse_result == Parse_Number_Success);

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

    must("not fail");
      verify(parse_result == Parse_Number_Success);

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

    must("not fail");
      verify(parse_result == Parse_Number_Success);

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

    must("fail with a specific error");
      verify(parse_result == Parse_Number_Overflow);

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a very big overflowing number") {
    str source_string = str("9" INT_MAXNUM INT_MAXNUM);
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail with a specific error");
      verify(parse_result == Parse_Number_Overflow);

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string contains a valid number and an overflowing exponent") {
    str source_string = str("777e+100");
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail with a specific error");
      verify(parse_result == Parse_Number_Overflow_Exponent);

    must("consume the source");
      verify(*source->chars == 0);

    success();
  } end();

  when("the source string does not contain a valid number") {
    str source_string = str("aaa:0");
    cstr source_begin = source_string.chars;
    apply(preconditions);
    parse_result = str_to_int(source, result);

    must("fail with a specific error");
      verify(parse_result == Parse_Number_Empty);

    must("consume the source until the first valid char");
      verify(*source->chars == 'a');
      verify(source->chars - source_begin == 0);

    success();
  } end();
}

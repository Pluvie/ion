#include "str_strip.h"

spec( str_strip ) {
  argument(str source);
  returns(str result);

  when("the source string contains no whitespaces at the edges") {
    source.chars = "abc"; source.length = 3;
    result = str_strip(source);

    must("return the same string");
      verify(str_equal(result, source));

    success();
  } end();

  when("the source string contains whitespaces ahead") {
    source.chars = " \tabc"; source.length = 5;
    result = str_strip(source);

    must("return the string stripped of whitespaces");
      expected_result.chars = "abc";
      expected_result.length = 3;
      verify(str_equal(result, expected_result));

    success();
  } end();

  when("the source string contains whitespaces behind") {
    source.chars = "abc \n"; source.length = 5;
    result = str_strip(source);

    must("return the string stripped of whitespaces");
      expected_result.chars = "abc";
      expected_result.length = 3;
      verify(str_equal(result, expected_result));

    success();
  } end();

  when("the source string contains whitespaces at the edges") {
    source.chars = "\ta bc \n"; source.length = 7;
    result = str_strip(source);

    must("return the string stripped of whitespaces");
      expected_result.chars = "a bc";
      expected_result.length = 4;
      verify(str_equal(result, expected_result));

    success();
  } end();
}

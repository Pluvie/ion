#include "str_empty.h"

spec( str_empty ) {
  argument(str source);
  returns(bool result);

  when("the source string contains a nullptr") {
    source.chars = nullptr; source.length = 17;
    result = str_empty(source);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the source string contains a zero length") {
    source.chars = "abc"; source.length = 0;
    result = str_empty(source);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the source string contains a valid pointer and a greater than zero length") {
    source.chars = "abc"; source.length = 3;
    result = str_empty(source);

    must("return false");
      verify(result == false);

    success();
  } end();
}

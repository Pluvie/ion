#include "str_empty.h"

spec( str_empty ) {
  argument(str source);

  when("the source string contains a nullptr") {
    source = (str) { nullptr, 17 };
    bool result = str_empty(source);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the source string contains a zero length") {
    source = (str) { "abc", 0 };
    bool result = str_empty(source);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the source string contains a valid pointer and a greater than zero length") {
    source = (str) { "abc", 3 };
    bool result = str_empty(source);

    must("return false");
      verify(result == false);

    success();
  } end();
}

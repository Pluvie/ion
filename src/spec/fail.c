/*
#include "fail.h"

spec( fail ) {
  argument(const char* format);

  const char previous_message[] = "previous message";
  snprintf(failure.message, previous_message, sizeof(previous_message));

  fail("some error ", f(&(int) { 42 }), ", reutilizing ", f(previous_message));

  must("set the failure message using the formatted input");
    verify(streq(failure.message, "some error, reutilizing previous message"));

  success();
}
*/

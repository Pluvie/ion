#include "fail.h"

spec( fail ) {
  const char previous_message[] = "previous message";
  snprintf(failure.message, sizeof(previous_message), previous_message);

  int error_number = 42;
  fail("some error ", f(error_number), ", reutilizing ", previous_message);

  must("set the failure message using the formatted input");
    verify(streq(failure.message, "some error 42, reutilizing previous message"));

  success();
}

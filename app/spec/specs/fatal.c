#include "fatal.h"

spec( fatal ) {
  const char previous_message[] = "previous message";
  snprintf(failure.message, sizeof(previous_message), previous_message);

  int error_number = 42;
  fatal("some error ", f(error_number), ", reutilizing ", previous_message);

  must("set the failure message using the formatted input");
    verify(cstr_equal(failure.message, "some error 42, reutilizing previous message"));
  must("abort the program");
    verify(sim.aborted == true);

  success();
}

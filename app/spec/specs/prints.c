#include "prints.h"

spec( prints ) {

  char output[1024] = { 0 };
  prints(output, sizeof(output),
    f(true),
    f((char) 'y'),
    f((unsigned char) 0xff),
    f(-88),
    f((unsigned int) 88),
    f(-77.7),
    f(example_string),
    f(example_pointer)
  );

  must("print the arguments on the string according to their format");
    verify(cstr_equal(output, "trueyff-8888-77.700000\"abc\"(nil)"));

  success();
}

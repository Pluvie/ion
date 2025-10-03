#include "print.h"

spec( printl ) {

  void* tmp = tmpfile();
  printl(
    f((bool) { true }),
    f((char) { 'y' }),
    f((unsigned char) { 0xff }),
    f((int) { -88 }),
    f((unsigned int) { 88 }),
    f((dec) { -77.7 }),
    f(example_string),
    f(example_pointer)
  );

  must("print the arguments on the string according to their format and add a newline");
    char output[1024] = { 0 };
    fseek(tmp, 0L, SEEK_SET);
    fread(output, sizeof(output), 1, tmp);
    verify(streq(output, "trueyff-8888-77.700000\"abc\"(nil)\n"));

  success();
    fclose(tmp);
}

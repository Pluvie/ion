#include "print.h"

spec( printl ) {

  void* tmp = tmpfile();
  printl(
    f(true),
    f((char) 'y'),
    f((unsigned char) 0xff),
    f(-88),
    f((unsigned int) 88),
    f(-77.7),
    f(example_string),
    f(example_pointer)
  );


  must("print the arguments on the string according to their format and add a newline");
    char output[1024] = { 0 };
    fseek(tmp, 0L, SEEK_SET);
    int result = fread(output, sizeof(output), 1, tmp);
    verify(result != -1);
    verify(cstr_equal(output, "trueyff-8888-77.700000\"abc\"(nil)\n"));

  success();
    fclose(tmp);
}

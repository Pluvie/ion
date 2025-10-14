#include "hash_djb2_cstr.h"

spec( hash_djb2_cstr ) {
  argument(char* data);

  precondition("a pointer to valid data");
    #define preconditions \
      data = "abc";

  must("return the correct hash value of the data");
    apply(preconditions);
    unsigned int result = hash_djb2_cstr(data);
    verify(result == 193485963);

  success();
}

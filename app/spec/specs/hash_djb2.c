#include "hash_djb2.h"

spec( hash_djb2 ) {
  argument(void* data);
  argument(unsigned int length);

  precondition("a pointer to valid data");
  precondition("a valid pointer length");
    #define preconditions \
      data = (unsigned char[]) { 0x00, 0x01, 0x02 }; \
      length = 3;

  must("return the correct hash value of the data");
    apply(preconditions);
    unsigned int result = hash_djb2(data, length);
    verify(result == 193377032);

  success();
}

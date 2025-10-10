#include "json_decode_internal.h"

void json_decode (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  printl();
  char* source_begin = source->chars;
  json_decode_value(source, target, reflection, allocator);

  if (unlikely(failure.occurred)) {
    char error[4096] = { 0 };
    unsigned int position = source->chars - source_begin;
    memory_copy(error, source_begin, source->length);
    error[position] = '@';
    printl(error);
  }
}

#include "json_decode_internal.c"

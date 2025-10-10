#include "json_decode_internal.h"

void json_decode (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
)
{
  //char* source_begin = source->chars;
  json_decode_value(source, target, reflection, allocator);

  if (unlikely(failure.occurred)) {
    /* Expose the error in a nice way. */
  }
}

#include "json_decode_internal.c"

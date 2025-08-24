static inline void json_encode_pointer (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  struct reflection* element_rfx = rfx->element;
  element_rfx->parent = rfx;

  void* element_obj = *(void**) obj;

  if (element_obj == NULL)
    goto encode_null;

  /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
  if (element_rfx->type == CHAR)
    goto encode_string;
  else
    goto encode_pointer;

encode_string:
  char* string_content = element_obj;
  u64 string_length = strlen(string_content);

  io_write(io, "\"", 1);
  if (unlikely(failure.occurred))
    return;

  io_write(io, string_content, string_length);
  if (unlikely(failure.occurred))
    return;

  io_write(io, "\"", 1);
  if (unlikely(failure.occurred))
    return;

  return;

encode_pointer:
  json_encode(element_obj, io, element_rfx);
  if (unlikely(failure.occurred))
    return;

  return;

encode_null:
  io_write(io, "null", lengthof("null"));
  if (unlikely(failure.occurred))
    return;
}

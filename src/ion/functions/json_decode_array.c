static inline void json_decode_array (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* element_rfx = NULL;
  int element_index = 0;
  slice result;

  if (rfx != NULL) {
    element_rfx = rfx->element;
    element_rfx->parent = rfx;
  }

  #define character ((char*) result.data)[0]

  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  result = io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  if (result.length == 0)
    return;

  if (character != '[') {
    fail("expected array begin '['");
    failure_add_io_info(io);
    return;
  }

parse_value:
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  result = io_peek(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  if (result.length == 0) {
    fail("expected value, or array end ']'");
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }

  if (character == ']') {
    io_read(io, sizeof(char));
    if (unlikely(failure.occurred))
      return;
    goto terminate;
  }

  if (element_rfx != NULL) {
    void* element_obj = obj + (element_index * element_rfx->size);
    json_decode(element_obj, io, element_rfx, allocator);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (unlikely(failure.occurred))
    return;

  /* Check comma -- next field --, or array end. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  result = io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  if (result.length == 0)
    return;

  switch (character) {
  case ']':
    goto terminate;

  case ',':
    element_index++;
    goto parse_value;

  default:
    fail("expected comma, or array end ']'");
    failure_add_io_info(io);
    return;
  }

terminate:
  if (rfx == NULL)
    return;

  reflection_validate(rfx, obj);
  if (unlikely(failure.occurred))
    return failure_add_reflection_info(rfx);

  #undef character
}

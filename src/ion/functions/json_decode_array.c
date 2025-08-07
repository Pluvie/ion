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
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0)
    return;

  if (character != '[') {
    fail("expected array begin '['");
    io_error_extract(io);
    return;
  }

parse_value:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_peek(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0) {
    fail("expected value, or array end ']'");
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }

  if (character == ']') {
    io_read(io, sizeof(char));
    if (error.occurred)
      return;
    goto terminate;
  }

  if (element_rfx != NULL) {
    void* element_obj = obj + (element_index * element_rfx->size);
    json_decode(element_obj, io, element_rfx, allocator);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (error.occurred)
    return;

  /* Check comma -- next field --, or array end. */
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
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
    io_error_extract(io);
    return;
  }

terminate:
  if (rfx == NULL)
    return;

  reflection_validate(rfx, obj);
  if (error.occurred)
    return reflection_error_extract(rfx);

  #undef character
}

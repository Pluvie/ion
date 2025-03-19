static inline void json_decode_sequence (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* element_rfx = NULL;
  u64 element_index = 0;
  u64 sequence_length = 0;

  if (rfx != NULL) {
    element_rfx = rfx->element;
    element_rfx->parent = rfx;
    sequence_length = rfx->size / element_rfx->size;
  }

  char* character;

sequence_begin:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (*character != '[') {
    fail("expected `[` to begin a sequence");
    error_add_io_extraction(io);
    return;
  }

check_empty_sequence:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_peek(io, sizeof(char));
  if (error.occurred)
    return;

  if (*character == ']')
    goto terminate;

  goto parse_value;

next_element:
  json_parse_spaces(io);
  if (error.occurred)
    return;

parse_value:
  /* Ignores all elements that are over the sequence length. */
  if (element_index >= sequence_length)
    element_rfx = NULL;

  if (element_rfx != NULL) {
    element_rfx->index = element_index;
    void* element_obj = obj + (element_index * element_rfx->size);
    json_decode(element_obj, io, element_rfx, allocator);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (error.occurred)
    return;

check_comma:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  switch (*character) {
  case ']':
    goto terminate;

  case ',':
    element_index++;
    goto next_element;

  default:
    fail("expected comma or sequence end after value");
    error_add_io_extraction(io);
    return;
  }

terminate:
  if (rfx == NULL)
    return;

  reflection_validate(rfx, obj);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}

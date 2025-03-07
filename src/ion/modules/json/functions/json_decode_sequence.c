static inline void json_decode_sequence (
    struct io* io,
    struct reflection* rfx
)
{
  struct reflection* element_rfx = NULL;
  u64 element_index = 0;

  if (rfx != NULL)
    element_rfx = rfx->element;

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
  if (element_index >= rfx->length)
    element_rfx = NULL;

  if (element_rfx != NULL) {
    element_rfx->index = element_index;
    element_rfx->target = rfx->target + (element_index * element_rfx->size);
    json_decode(io, element_rfx);

  } else {
    json_decode(io, NULL);
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

  reflection_validate(rfx, rfx->target);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}

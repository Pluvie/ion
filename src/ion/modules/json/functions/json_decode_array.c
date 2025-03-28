static inline void json_decode_array (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* element_rfx = NULL;
  u64 element_index = 0;

  struct array array;
  u64 array_minlength = 0;
  u64 array_maxlength = 0;
  void* empty_element = NULL;

  if (rfx != NULL) {
    element_rfx = rfx->element;
    element_rfx->parent = rfx;
    empty_element = memory_alloc_zero(allocator, element_rfx->size);
    array = array_init(element_rfx->size, 0, allocator);
    array_minlength = rfx->size_limits.min;
    array_maxlength = rfx->size_limits.max;
  }

  char* character;

array_begin:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (*character != '[') {
    fail("expected `[` to begin array");
    error_add_io_extraction(io);
    return;
  }

check_empty_array:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  character = io_peek(io, sizeof(char));
  if (error.occurred)
    return;

  if (*character == ']') {
    io_read(io, sizeof(char));
    if (error.occurred)
      return;

    goto terminate;
  }

  goto parse_value;

next_element:
  json_parse_spaces(io);
  if (error.occurred)
    return;

parse_value:
  if (element_rfx != NULL) {
    element_rfx->index = element_index;
    void* element_obj = array_push(&array, empty_element);
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
    if (array_maxlength > 0 && element_index >= array_maxlength) {
      fail("array required maximum length of %li", array_maxlength);
      error_add_io_extraction(io);
      return error_add_reflection_path(rfx);
    }
    goto next_element;

  default:
    fail("expected comma or array end after value");
    error_add_io_extraction(io);
    return;
  }

terminate:
  if (rfx == NULL)
    return;

  if (array_minlength > 0 && array.length < array_minlength) {
    fail("array required minimum length of %li", array_minlength);
    error_add_io_extraction(io);
    return error_add_reflection_path(rfx);
  }

  reflection_validate(rfx, &array);
  if (error.occurred)
    return error_add_reflection_path(rfx);

  memcpy(obj, &array, sizeof(struct array));
}

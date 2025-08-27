void json_decode_list (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* element_rfx = NULL;
  void* element_block = NULL;
  int element_index = 0;
  slice result;

  if (rfx != NULL) {
    element_rfx = rfx->element;
    element_rfx->parent = rfx;
    element_block = memory_alloc_zero(allocator, element_rfx->size);
    rfx->container_creator(8, allocator, obj);
  }

  #define character ((char*) result.data)[0]

  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  result = io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  if (result.length == 0 || character != '[') {
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
    json_decode(element_block, io, element_rfx, allocator);
    rfx->container_adder(obj, element_block);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (unlikely(failure.occurred))
    return;

  /* Check comma -- next element --, or array end. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  result = io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  if (result.length == 0) {
    fail("expected comma, or array end ']'");
    failure_add_io_info(io);
    return;
  }

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

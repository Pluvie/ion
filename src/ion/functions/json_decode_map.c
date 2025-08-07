static inline void json_decode_map (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  struct reflection* key_rfx = NULL;
  struct reflection* value_rfx = NULL;
  void* key_block = NULL;
  void* value_block = NULL;
  void* map_obj = NULL;
  int added_position = 0;
  slice result;

  if (rfx != NULL) {
    key_rfx = rfx->element;
    key_rfx->parent = rfx;
    value_rfx = key_rfx->element;
    value_rfx->parent = key_rfx;
    map_obj = rfx->container_creator(8, allocator);
    key_block = memory_alloc_zero(allocator, key_rfx->size);
    value_block = memory_alloc_zero(allocator, value_rfx->size);
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

parse_pair:
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length > 0 && character == ']')
    goto terminate;

  if (result.length == 0 || character != '[') {
    fail("expected array begin '['");
    io_error_extract(io);
    return;
  }

  /* Parse key. */
  json_parse_spaces(io);
  if (error.occurred)
    return;

  if (key_rfx != NULL) {
    json_decode(key_block, io, key_rfx, allocator);
    added_position = rfx->container_adder(map_obj, key_block);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (error.occurred)
    return;

  /* Parse comma. */
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0 || character != ',') {
    fail("expected comma");
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }

  /* Parse value. */
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_peek(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0) {
    fail("expected value");
    reflection_error_extract(rfx);
    io_error_extract(io);
    return;
  }

  if (value_rfx != NULL) {
    json_decode(value_block, io, value_rfx, allocator);
    void* map_values = *(void**) (map_obj + SET__SIZE);
    void* value_position = map_values + (added_position * value_rfx->size);
    memcpy(value_position, value_block, value_rfx->size);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (error.occurred)
    return;

  /* Check array pair end. */
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0 || character != ']') {
    fail("expected array end ']'");
    io_error_extract(io);
    return;
  }


  /* Check comma -- next pair --, or array end. */
  json_parse_spaces(io);
  if (error.occurred)
    return;

  result = io_read(io, sizeof(char));
  if (error.occurred)
    return;

  if (result.length == 0) {
    fail("expected comma, or array end ']'");
    io_error_extract(io);
    return;
  }

  switch (character) {
  case ']':
    goto terminate;

  case ',':
    goto parse_pair;

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

  memcpy(obj, map_obj, rfx->size);

  #undef character
}

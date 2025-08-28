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
  int added_position = 0;
  char character;

  if (rfx != NULL) {
    key_rfx = rfx->element;
    key_rfx->parent = rfx;
    value_rfx = key_rfx->element;
    value_rfx->parent = key_rfx;
    key_block = memory_alloc_zero(allocator, key_rfx->size);
    value_block = memory_alloc_zero(allocator, value_rfx->size);
    rfx->container_creator(8, allocator, obj);
  }

  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  if (character != '[') {
    fail("expected array begin '['");
    failure_add_io_info(io);
    return;
  }

parse_pair:
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  if (character == ']')
    goto terminate;

  if (character != '[') {
    fail("expected array begin '['");
    failure_add_io_info(io);
    return;
  }

  /* Parse key. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  if (key_rfx != NULL) {
    json_decode(key_block, io, key_rfx, allocator);
    added_position = rfx->container_adder(obj, key_block);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (unlikely(failure.occurred))
    return;

  /* Parse comma. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  if (character != ',') {
    fail("expected comma");
    failure_add_reflection_info(rfx);
    failure_add_io_info(io);
    return;
  }

  /* Parse value. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  if (value_rfx != NULL) {
    json_decode(value_block, io, value_rfx, allocator);
    void* map_values = *(void**) (obj + SET__SIZE);
    void* value_position = map_values + (added_position * value_rfx->size);
    byte_copy(value_position, value_block, value_rfx->size);

  } else {
    json_decode(NULL, io, NULL, NULL);
  }

  if (unlikely(failure.occurred))
    return;

  /* Check array pair end. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  if (character != ']') {
    fail("expected array end ']'");
    failure_add_io_info(io);
    return;
  }

  /* Check comma -- next pair --, or array end. */
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    return;

  character = string_char_at(io->result, 0);
  switch (character) {
  case ']':
    goto terminate;

  case ',':
    goto parse_pair;

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

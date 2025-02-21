static inline u64 json_parse_bool (
    struct io* input
)
{
  char buffer[5] = { 0 };

  io_peek(input, buffer, sizeof(buffer));
  if (error.occurred)
    return 0;

  if (strneq("true", buffer, 4))
    return 4;

  if (strneq("false", buffer, 5))
    return 5;

  return 0;
}

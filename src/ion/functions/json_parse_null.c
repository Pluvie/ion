static inline u64 json_parse_null (
    struct io* input
)
{
  char buffer[4] = { 0 };

  io_peek(input, buffer, sizeof(buffer));
  if (error.occurred) {
    fail("error while parsing null: %s", error.message);
    return 0;
  }

  if (strneq("null", buffer, 4))
    return 4;

  return 0;
}

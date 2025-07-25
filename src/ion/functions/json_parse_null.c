static inline int json_parse_null (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  slice result = io_read(io, 5);
  io_cursor_restore(io, cursor);

  if (error.occurred)
    return -1;

  string null_str = (string) { result.data, lengthof("null") };
  if (streq("null", null_str))
    return 1;

  return 0;
}

static inline int json_parse_bool (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  slice result = io_read(io, 5);
  io_cursor_restore(io, cursor);

  if (error.occurred)
    return -1;

  string true_str = (string) { result.data, lengthof("true") };
  if (streq("true", true_str))
    return 1;

  string false_str = (string) { result.data, lengthof("false") };
  if (streq("false", false_str))
    return 0; 

  return -1;
}

static inline u64 json_parse_bool (
    struct io* source
)
{
  io_cursor_save(source);

  char* value = io_read(source, 5);
  if (error.occurred)
    return 0;

  if (strneq("true", value, lengthof("true"))) {
    io_cursor_restore(source);
    return lengthof("true"); 
  }

  if (strneq("false", value, lengthof("false"))) {
    io_cursor_restore(source);
    return lengthof("false"); 
  }

  io_cursor_restore(source);
  return 0;
}

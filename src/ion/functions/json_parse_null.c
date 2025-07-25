static inline u64 json_parse_null (
    struct io* source
)
{
  io_cursor_save(source);

  char* value = io_read(source, lengthof("null"));
  if (error.occurred)
    return 0;

  if (strneq("null", value, lengthof("null"))) {
    io_cursor_restore(source);
    return lengthof("null"); 
  }

  io_cursor_restore(source);
  return 0;
}

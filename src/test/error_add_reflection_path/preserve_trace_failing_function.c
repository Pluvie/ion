void preserve_trace_failing_function (
    struct reflect* reflection
)
{
  byte data[8] = { 0 };
  struct io reader = io_memory(data, sizeof(data));
  io_write(&reader, (byte [2]) { 0, 1 }, 2);
  if (error.occurred)
    return error_add_reflection_path(reflection);
}

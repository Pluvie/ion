void preserve_trace_failing_function (
    struct reflection* rfx
)
{
  byte data[4] = { 0 };
  struct io memory = io_open_memory(data, sizeof(data));
  io_write(&memory, (byte [8]) { 0 }, 8);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}

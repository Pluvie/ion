enum io_flags;
/**
 * Flags used to control which operations are allowed on an io object. */
enum io_flags {
  IO_NONE               = 0,
  IO_READ               = 1 << 0,
  IO_WRITE              = 1 << 1,
  IO_NO_OVERFLOW_ERROR  = 1 << 2,
  IO_NO_BUFFERED        = 1 << 3,
};

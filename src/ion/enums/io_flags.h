enum io_flags;
/**
 * Flags used to control the behaviour of the io under specific circumstances. */
enum io_flags {
  IO_FLAGS_NONE               = 0,
  IO_FLAGS_NO_OVERFLOW_ERROR  = 1 << 0,
  IO_FLAGS_NO_BUFFERED        = 1 << 1,
};

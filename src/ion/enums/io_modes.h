enum io_modes;
/**
 * Modes of input / output: reading, writing or none. */
enum io_modes {
  IO_MODE_NONE      = 0,
  IO_MODE_READ      = 1 << 0,
  IO_MODE_WRITE     = 1 << 1,
};

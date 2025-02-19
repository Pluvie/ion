struct io;
/**
 * Explain the io abstraction. */
struct io {
  union {
    void* memory;
    void* file;
    i32 socket;
  };
  u64 length;
  u64 cursor;
  union {
    u64 written_amount;
    u64 read_amount;
  };
  enum io_channels channel;
  enum io_modes mode;
  enum io_flags flags;
  padding(16);
};
check_sizeof(struct io, 64);

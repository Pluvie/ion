struct io;
/**
 * Explain the io abstraction. */
struct io {
  byte* data;
  union {
    i32 descriptor;
    void* stream;
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
  struct buffer* allocator;
};
check_sizeof(struct io, 64);

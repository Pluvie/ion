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
  u64 saved_cursor;
  struct {
    u64 begin;
    u64 size;
    struct buffer allocator;
  } buffer;
  union {
    u64 read_amount;
    u64 written_amount;
  };
  union {
    u64 reads_count;
    u64 writes_count;
  };
  enum io_channels channel;
  enum io_flags flags;
  padding(20);
};
check_sizeof(struct io, 128);

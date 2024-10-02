struct io;
/**
 * Explain the io abstraction. */
struct io {
  byte* data;
  u64 length;
  u64 cursor;
  union {
    u64 written_amount;
    u64 read_amount;
  };
  i32 descriptor;
  void* stream;
  enum io_types type;
  enum io_flags flags;
  struct memory* allocator;
};
check_sizeof(struct io, 64);

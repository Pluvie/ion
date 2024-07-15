struct io;
/**
 * Explain the io abstraction. */
struct io {
  byte* data;
  u64 length;
  u64 cursor;
  i32 descriptor;
  void* stream;
  enum io_types type;
  enum io_flags flags;
  struct memory* allocator;
  padding(2);
};
check_sizeof(struct io, 64);

struct io;
/**
 * Explain the io abstraction. */
struct io {
  byte* data;
  u64 length;
  u64 cursor;
  u32 flags;
  i32 descriptor;
  struct memory* allocator;
  padding(24);
};
check_sizeof(struct io, 64);

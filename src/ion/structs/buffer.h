struct buffer;
/**
 * Explain the `struct buffer` and how it is different from the `struct memory`. */
struct buffer {
  u64 capacity;
  u64 position;
  byte* data;
  padding(8);
};
check_sizeof(struct buffer, 32);

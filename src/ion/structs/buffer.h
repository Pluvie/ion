/* Defines the `struct buffer` ⚡️ION⚡️ type. */
struct buffer {
  byte* data;
  uint capacity;
  uint position;
  struct {
    uint count;
    uint size;
  } allocations;
};

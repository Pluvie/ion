/* Defines the `struct allocator` ⚡️ION⚡️ type. */
struct allocator {
  byte* data;
  uint capacity;
  uint position;
  struct {
    void** addresses;
    uint capacity;
    uint count;
  } regions;
  struct {
    uint count;
    uint size;
  } allocations;
};

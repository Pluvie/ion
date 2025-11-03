/* Defines the `struct allocator` ⚡️ION⚡️ type. */
struct allocator {
  struct allocator_arena {
    byte* data;
    uint capacity;
    uint position;
    struct {
      void** addresses;
      uint capacity;
      uint count;
    } regions;
  } arena;
  struct allocator_line {
    byte* data;
    uint capacity;
    uint position;
  } line;
  struct {
    uint count;
    uint size;
  } allocations;
};

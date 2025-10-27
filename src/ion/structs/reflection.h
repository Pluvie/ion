/* Defines the `struct reflection` ⚡️ION⚡️ type. */
struct reflection {
  enum reflection_types type;
  str  name;
  cstr type_name;
  uint size;
  uint offset;
  struct reflection* descendant;
  void (*validator)(void*, struct reflection*);
  int  (*enumerator)(str);
  struct {
    void (*creator)(void*, uint, struct allocator*);
    void (*adder)(void*, void*);
  } container;
};

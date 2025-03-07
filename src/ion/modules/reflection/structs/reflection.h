struct reflection;
/**
 * Explain what reflection is and how it's useful for object inspection and
 * serialization. */
struct reflection {
  u64 offset;
  u64 index;
  u64 size;
  u64 length;
  enum types type;
  struct string* name;
  union {
    struct vector* fields;
    struct reflection* element;
  };
  void* target;
  struct reflection* parent;
  struct memory* allocator;
  bool (*validator)(void*, struct reflection*);
  struct {
    u64 min;
    u64 max;
  } size_limits;
  void* support_data;
  padding(16);
};
check_sizeof(struct reflection, 128);

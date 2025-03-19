struct reflection;
/**
 * Explain what reflection is and how it's useful for object inspection and
 * serialization. */
struct reflection {
  u64 offset;
  u64 index;
  u64 size;
  enum types type;
  struct string* name;
  struct string* struct_name;
  union {
    struct vector* fields;
    struct reflection* element;
  };
  struct reflection* parent;
  bool (*validator)(void*, struct reflection*);
  struct {
    u64 min;
    u64 max;
  } size_limits;
  void* support_data;
};
check_sizeof(struct reflection, 96);

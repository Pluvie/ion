struct reflection {
  enum reflection_types type;
  str name;
  const char* type_name;
  unsigned int size;
  union {
    unsigned int offset;
    unsigned int index;
  };
  struct {
    unsigned int min;
    unsigned int max;
  } size_limits;
  struct reflection* parent;
  struct reflection* self;
  union {
    struct reflection* fields;
    struct reflection* element;
  };
  bool (*validator)(void*, struct reflection*);
  int (*enumerator)(str);
  struct {
    void (*creator)(void*, unsigned int, struct allocator*);
    void* (*adder)(void*, void*);
  } container;
  padding(8);
};
check_sizeof(128, struct reflection);

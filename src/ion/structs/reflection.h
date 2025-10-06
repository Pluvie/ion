struct reflection {
  enum reflection_types type;
  padding(4);
  const char* type_name;
  const char* name;
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
  struct {
    void* (*creator)(unsigned int, struct allocator*);
    unsigned int (*adder)(void*, void*);
  } container;
  padding(22);
};
check_sizeof(128, struct reflection);

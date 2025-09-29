struct reflection {
  enum reflection_types type;
  padding(4);
  const char* type_name;
  const char* name;
  int size;
  union {
    int offset;
    int index;
  };
  struct {
    int min;
    int max;
  } size_limits;
  struct reflection* parent;
  struct reflection* self;
  union {
    struct reflection* fields;
    struct reflection* element;
  };
  bool  (*validator)(void*, struct reflection*);
  int   (*container_adder)(void*, void*);
  //void* (*container_creator)(int, struct allocator*, void*);
  void* (*container_creator)(int, void*, void*);
  padding(22);
};
check_sizeof(128, struct reflection);

struct object;
/**
 * Explain the object abstraction. */
struct object {
  char* name;
  void* address;
  struct reflect* schema;
  struct memory* allocator;
};
check_sizeof(struct object, 32);

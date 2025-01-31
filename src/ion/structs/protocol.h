struct protocol;
/**
 * Explain what a protocol is and how it's used for serialization. */
struct protocol {
  struct reflect* schema;
  struct memory* allocator;
  struct io* input;
  struct io* output;
  void* support_data;
  padding(24);
};
check_sizeof(struct protocol, 64);

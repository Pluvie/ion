struct protocol;
/**
 * Explain what a protocol is and how it's used for serialization. */
struct protocol {
  struct reflect* schema;
  struct memory* allocator;
  struct io* input;
  struct io* output;
  struct failure* error;
  void* support_data;
  padding(16);
};
check_sizeof(struct protocol, 64);

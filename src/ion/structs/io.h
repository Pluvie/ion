struct io {
  union {
    struct io_direct* direct;
    struct io_buffered* buffered;
  };
  enum io_types type;
  padding(4);
  struct reflection* rfx;
  memory* allocator;
};
check_sizeof(32, struct io);

struct io {
  int cursor;
  memory* buffer;
  memory* allocator;
  struct reflection* rfx;
};
check_sizeof(32, struct io);

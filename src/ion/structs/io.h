struct io {
  int cursor;
  void* target;
  memory* buffer;
  memory* allocator;
  struct reflection* rfx;
  int32 read_flags;
  int32 write_flags;
};
check_sizeof(48, struct io);

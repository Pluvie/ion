struct io {
  int cursor;
  memory* buffer;
  memory* allocator;
  struct reflection* rfx;
  struct {
    int count;
    int flags;
  } read;
  struct {
    int count;
    int flags;
  } write;
};
check_sizeof(64, struct io);

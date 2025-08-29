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




struct io_direct {
  string* data;
  char* cursor;
  char* end;
};
check_sizeof(24, struct io_direct);

struct io_buffered {
  char* cursor;
  enum io_channels channel;
  padding(4);
  union {
    struct file* file;
    struct pipe* pipe;
    struct socket* socket;
    struct stream* stream;
  };
  struct {
    memory* data;
    int length;
  } buffer;
};
check_sizeof(40, struct io_buffered);

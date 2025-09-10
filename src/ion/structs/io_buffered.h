struct io_buffered {
  struct {
    char* data;
    int position;
    int capacity;
    int window_size;
    int padding_size;
  } buffer;
  char* cursor;
  enum io_channels channel;
  padding(4);
  union {
    struct file* file;
    struct pipe* pipe;
    struct socket* socket;
    struct stream* stream;
  };
};
check_sizeof(64, struct io_buffered);

struct io {
  union {
    void* memory;
    struct file* file;
    struct pipe* pipe;
    struct socket* socket;
    struct stream* stream;
  };
  slice result;
  int cursor;
  int length;
  enum io_channels channel;
  struct {
    int count;
    int32 flags;
  } read;
  struct {
    int count;
    int32 flags;
  } write;
  struct {
    slice data;
    int cursor;
    int size;
    bool enabled;
    bool retained;
    padding(2);
  } buffer;
};
check_sizeof(128, struct io);

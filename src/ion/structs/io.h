struct io {
  union {
    int file;
    int socket;
    void* memory;
    struct pipe* pipe;
    struct stream* stream;
  };
  slice data;
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

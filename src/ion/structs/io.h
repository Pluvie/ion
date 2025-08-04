struct io {
  union {
    int   file;
    void* memory;
    int   pipe;
    int   socket;
    FILE* stream;
  };
  enum io_channels channel;
  int length;
  int cursor;
  void* storage;
  struct {
    int count;
    int flags;
  } read;
  struct {
    int count;
    int flags;
  } write;
  struct {
    bool enabled;
    bool retained;
    padding(2);
    void* data;
    int size;
    int cursor;
    int end;
    padding(8);
  } buffer;
};
check_sizeof(128, struct io);

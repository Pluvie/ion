/*
struct io {
  union {
    struct io_direct* direct;
    struct io_buffered* buffered;
  };
  enum io_types type;
  padding(4);
  struct reflection* reflection;
  struct allocator* allocator;
};
check_sizeof(32, struct io);
*/


struct io_direct {
  string* data;
  char* cursor;
};
check_sizeof(16, struct io_direct);


/*
struct io_buffered {
  struct io_channel* channel;
  char* cursor;
  struct {
    char* data;
    unsigned int position;
    unsigned int capacity;
    unsigned int window;
  } buffer;
};
check_sizeof(48, struct io_buffered);


struct io_channel {
  enum io_channel_types type;
  padding(4);
  union {
    void* pointer;
    int0 descriptor;
  } handle;
  union {
    struct {
      char* path;
      char* mode;
      unsigned int position;
    } file;
    struct {
      int0 reader;
      int0 writer;
    } pipe;
    struct {
      union {
        int0 descriptor;
        void* handle;
      };
      char* ip_address;
      char* hostname;
      char* path;
      unsigned int port;
      enum ip_protocols protocol;
      enum ip_protocol_versions version;
    } socket;
  };
};
check_sizeof(64, struct io_channel);



unsigned int io_channel_read (
    struct io_channel* channel,
    void* address,
    unsigned int length
);
unsigned int io_channel_write (
    struct io_channel* channel,
    void* address,
    unsigned int length
);
unsigned int io_channel_flush (
    struct io_channel* channel
);
unsigned int io_channel_position_set (
    struct io_channel* channel,
    unsigned int position
);
unsigned int io_channel_position_get (
    struct io_channel* channel
);
*/

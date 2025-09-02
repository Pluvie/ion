#define io_open(source, rfx, allocator)         \
  _Generic((source),                            \
    string* : io_open_string,                   \
    struct pipe* : io_open_pipe                 \
  )(source, rfx, allocator)



static inline struct io io_open_string (
    string* source,
    struct reflection* rfx,
    memory* allocator
);



static inline struct io io_open_pipe (
    struct pipe* source,
    struct reflection* rfx,
    memory* allocator
);

#define failure_add_io_info(io)                         \
  _Generic((io),                                        \
    struct io_direct* : failure_add_io_info_direct,     \
    struct io_buffered* : failure_add_io_info_buffered  \
  )(io)



void failure_add_io_info_direct (
    struct io_direct* io
);



void failure_add_io_info_buffered (
    struct io_buffered* io
);

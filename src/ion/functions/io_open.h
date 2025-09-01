#define io_open(source)                         \
  _Generic((source),                            \
    string* : io_open_string                    \
  )(source)



static inline struct io io_open_string (
    string* source
);

static inline char* io<string>_read (
    struct io* io,
    string* source,
    int amount
);

static inline char* io<struct file>_read (
    struct io* io,
    struct file* source,
    int amount
);

static inline char* io<struct pipe>_read (
    struct io* io,
    struct pipe* source,
    int amount
);

static inline char* io<struct socket>_read (
    struct io* io,
    struct socket* source,
    int amount
);

static inline char* io<struct stream>_read (
    struct io* io,
    struct stream* source,
    int amount
);

/*
void io_read (
    struct io* io,
    int amount
);
*/

static inline char* io<string>_read (
    struct io* io,
    string* source,
    int amount
);

static inline char* io<struct file>_read (
    struct io* io,
    struct file* source,
    int amount,
    void* address
);
